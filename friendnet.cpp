#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
using namespace std;
 
const int N = 10;
const string U[N] = {"Aarav", "Bhavna", "Chetan", "Divya", "Esha",
                     "Farhan", "Gauri", "Harsh", "Ishaan", "Jiya"};
typedef vector<vector<int> > Matrix;
 
Matrix emptyRel() { return Matrix(N, vector<int>(N, 0)); }
 
Matrix build(const vector<pair<int, int> >& p, bool mutual) {
    Matrix M = emptyRel();
    for (size_t i = 0; i < p.size(); i++) {
        M[p[i].first - 1][p[i].second - 1] = 1;
        if (mutual) M[p[i].second - 1][p[i].first - 1] = 1;
    }
    return M;
}
 
int countPairs(const Matrix& M) {
    int c = 0;
    for (int i = 0; i < N; i++) for (int j = 0; j < N; j++) c += M[i][j];
    return c;
}
 
// ---------- property tests ----------
bool isReflexive(const Matrix& M, int& w) {
    for (int i = 0; i < N; i++) if (!M[i][i]) { w = i; return false; }
    return true;
}
bool isIrreflexive(const Matrix& M, int& w) {
    for (int i = 0; i < N; i++) if (M[i][i]) { w = i; return false; }
    return true;
}
bool isSymmetric(const Matrix& M, int& a, int& b) {
    for (int i = 0; i < N; i++) for (int j = 0; j < N; j++)
        if (M[i][j] && !M[j][i]) { a = i; b = j; return false; }
    return true;
}
bool isAntisymmetric(const Matrix& M, int& a, int& b) {
    for (int i = 0; i < N; i++) for (int j = i + 1; j < N; j++)
        if (M[i][j] && M[j][i]) { a = i; b = j; return false; }
    return true;
}
// counts violations of transitivity; stores the first one with distinct ends
bool isTransitive(const Matrix& M, int& a, int& b, int& c, int& total) {
    total = 0; a = b = c = -1;
    for (int i = 0; i < N; i++) for (int j = 0; j < N; j++) {
        if (!M[i][j]) continue;
        for (int k = 0; k < N; k++)
            if (M[j][k] && !M[i][k]) {
                total++;
                if (a < 0 && i != k) { a = i; b = j; c = k; }
            }
    }
    return total == 0;
}
 
// ---------- closures ----------
Matrix reflexiveClosure(Matrix M) { for (int i = 0; i < N; i++) M[i][i] = 1; return M; }
Matrix symmetricClosure(Matrix M) {
    for (int i = 0; i < N; i++) for (int j = 0; j < N; j++) if (M[i][j]) M[j][i] = 1;
    return M;
}
Matrix transitiveClosure(Matrix M) {          // Warshall's algorithm
    for (int k = 0; k < N; k++)
        for (int i = 0; i < N; i++)
            for (int j = 0; j < N; j++)
                if (M[i][k] && M[k][j]) M[i][j] = 1;
    return M;
}
Matrix compose(const Matrix& A, const Matrix& B) {
    Matrix C = emptyRel();
    for (int i = 0; i < N; i++) for (int k = 0; k < N; k++) if (A[i][k])
        for (int j = 0; j < N; j++) if (B[k][j]) C[i][j] = 1;
    return C;
}
 
// ---------- graph analysis ----------
void dfs(const Matrix& S, int u, vector<int>& comp, int id) {
    comp[u] = id;
    for (int v = 0; v < N; v++) if (S[u][v] && comp[v] < 0) dfs(S, v, comp, id);
}
vector<int> components(const Matrix& M, int& count) {
    Matrix S = symmetricClosure(M);
    vector<int> comp(N, -1);
    count = 0;
    for (int i = 0; i < N; i++) if (comp[i] < 0) dfs(S, i, comp, count++);
    return comp;
}
 
void printMatrix(const Matrix& M) {
    cout << "     ";
    for (int j = 0; j < N; j++) cout << setw(3) << j + 1;
    cout << endl;
    for (int i = 0; i < N; i++) {
        cout << setw(2) << i + 1 << " | ";
        for (int j = 0; j < N; j++) cout << setw(3) << M[i][j];
        cout << endl;
    }
}
void printGroups(const vector<int>& comp, int count) {
    for (int g = 0; g < count; g++) {
        cout << "  {";
        bool first = true;
        for (int i = 0; i < N; i++) if (comp[i] == g) {
            cout << (first ? "" : ", ") << U[i]; first = false;
        }
        cout << "}" << endl;
    }
}
string yn(bool b) { return b ? "Yes" : "No"; }
void sizeLine(const string& name, const Matrix& M, int base) {
    cout << left << setw(30) << name << right << "= " << countPairs(M)
         << "  (+" << countPairs(M) - base << ")" << endl;
}
 
int main() {
    int ds;
    cout << "Enter dataset (1 = Friendship, 2 = Follow): ";
    cin >> ds;
 
    vector<pair<int, int> > p;
    bool mutual = (ds == 1);
    if (ds == 1) {
        int e[8][2] = {{1,2},{1,3},{2,3},{3,4},{5,6},{6,7},{5,7},{8,9}};
        for (int i = 0; i < 8; i++) p.push_back(make_pair(e[i][0], e[i][1]));
    } else {
        int e[11][2] = {{1,2},{2,1},{3,1},{3,2},{4,3},{5,6},{6,7},{7,5},{8,9},{9,8},{10,1}};
        for (int i = 0; i < 11; i++) p.push_back(make_pair(e[i][0], e[i][1]));
    }
    Matrix R = build(p, mutual);
 
    cout << "\n== 1. Relation R on U ==" << endl;
    for (int i = 0; i < N; i++) cout << setw(3) << i + 1 << " = " << U[i] << endl;
    cout << "|U| = " << N << ", |R| = " << countPairs(R) << " ordered pairs" << endl;
    printMatrix(R);
 
    cout << "\n== 2. Properties of R ==" << endl;
    int a = -1, b = -1, c = -1, tot = 0;
    bool refl = isReflexive(R, a);
    cout << "Reflexive     : " << yn(refl);
    if (!refl) cout << "   (" << U[a] << ", " << U[a] << ") not in R";
    cout << endl;
    bool irr = isIrreflexive(R, a);
    cout << "Irreflexive   : " << yn(irr) << endl;
    bool sym = isSymmetric(R, a, b);
    cout << "Symmetric     : " << yn(sym);
    if (!sym) cout << "   (" << U[a] << ", " << U[b] << ") in R but ("
                   << U[b] << ", " << U[a] << ") not";
    cout << endl;
    bool asym = isAntisymmetric(R, a, b);
    cout << "Antisymmetric : " << yn(asym);
    if (!asym) cout << "   " << U[a] << " <-> " << U[b] << " both in R";
    cout << endl;
    bool tr = isTransitive(R, a, b, c, tot);
    cout << "Transitive    : " << yn(tr);
    if (!tr) {
        cout << "   (" << U[a] << "," << U[b] << "),(" << U[b] << "," << U[c]
             << ") in R but (" << U[a] << "," << U[c] << ") not";
        cout << "\n                " << tot << " violating triples in all";
    }
    cout << endl;
    bool eq = refl && sym && tr;
    cout << "Equivalence   : " << yn(eq) << endl;
 
    cout << "\n== 3. Closures ==" << endl;
    Matrix Rr = reflexiveClosure(R), Rs = symmetricClosure(R), Rt = transitiveClosure(R);
    Matrix Re = transitiveClosure(symmetricClosure(reflexiveClosure(R)));
    cout << "|R|                           = " << countPairs(R) << endl;
    int base = countPairs(R);
    sizeLine("|reflexive closure|", Rr, base);
    sizeLine("|symmetric closure|", Rs, base);
    sizeLine("|transitive closure|", Rt, base);
    sizeLine("|equivalence closure|", Re, base);
    int w1, w2, w3, t2;
    bool okEq = isReflexive(Re, w1) && isSymmetric(Re, w1, w2)
                && isTransitive(Re, w1, w2, w3, t2);
    cout << "Equivalence closure is reflexive, symmetric, transitive: "
         << yn(okEq) << endl;
 
    cout << "\n== 4. Network analysis ==" << endl;
    int k;
    vector<int> comp = components(R, k);
    cout << "Clusters (connected groups): " << k << endl;
    printGroups(comp, k);
    cout << "Degrees:" << endl;
    cout << "  User      Out  In  Mutual" << endl;
    int mutualPairs = 0;
    vector<int> iso;
    for (int i = 0; i < N; i++) {
        int out = 0, in = 0, mu = 0;
        for (int j = 0; j < N; j++) if (j != i) {
            out += R[i][j]; in += R[j][i];
            if (R[i][j] && R[j][i]) mu++;
        }
        mutualPairs += mu;
        if (out == 0 && in == 0) iso.push_back(i);
        cout << "  " << left << setw(9) << U[i] << right << setw(3) << out
             << setw(4) << in << setw(7) << mu << endl;
    }
    cout << "Mutual connections (unordered pairs): " << mutualPairs / 2 << endl;
    cout << "Isolated users: ";
    if (iso.empty()) cout << "none";
    for (size_t i = 0; i < iso.size(); i++) cout << (i ? ", " : "") << U[iso[i]];
    cout << endl;
 
    // strongly connected groups: a ~ b when each can reach the other
    vector<int> sc(N, -1);
    int scn = 0;
    for (int i = 0; i < N; i++) if (sc[i] < 0) {
        sc[i] = scn;
        for (int j = i + 1; j < N; j++) if (sc[j] < 0 && Rt[i][j] && Rt[j][i]) sc[j] = scn;
        scn++;
    }
    cout << "Mutually reachable groups: " << scn << endl;
    printGroups(sc, scn);
 
    Matrix R2 = compose(R, R);
    cout << "Suggestions (R o R, not in R, distinct users):" << endl;
    int sug = 0;
    for (int i = 0; i < N; i++) for (int j = 0; j < N; j++)
        if (i != j && R2[i][j] && !R[i][j] && (!mutual || i < j)) {
            cout << "  " << U[i] << (mutual ? " - " : " -> ") << U[j] << endl; sug++;
        }
    if (!sug) cout << "  none" << endl;
    return 0;
}
