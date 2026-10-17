# Discrete Mathematics Friendship Network Analyzer

[![C++](https://img.shields.io/badge/Language-C%2B%2B11%20%7C%20C%2B%2B14%20%7C%20C%2B%2B17-blue.svg)](https://isocpp.org/)
[![Topic](https://img.shields.io/badge/Topic-Discrete%20Mathematics%20%26%20Graph%20Theory-orange.svg)]()
[![License](https://img.shields.io/badge/License-MIT-green.svg)](LICENSE)

A C++ application that models social network interactions using **Discrete Mathematics** and **Relation Theory**. The project represents friendship and follow networks as binary relations over a finite set of users, evaluates algebraic relation properties, computes closures (including Warshall's Algorithm for transitive closure), and performs network graph analytics like connected components, reachability, and friend/follow recommendations via relation composition.

---

## 📌 Table of Contents

- [Overview](#-overview)
- [Key Features](#-key-features)
- [Mathematical Foundations](#-mathematical-foundations)
  - [1. Binary Relations and Matrix Representation](#1-binary-relations-and-matrix-representation)
  - [2. Relation Properties & Counterexamples](#2-relation-properties--counterexamples)
  - [3. Closures of Relations](#3-closures-of-relations)
  - [4. Graph Analysis & Recommendation Engine](#4-graph-analysis--recommendation-engine)
- [Supported Datasets](#-supported-datasets)
- [Project Structure](#-project-structure)
- [Getting Started](#-getting-started)
  - [Prerequisites](#prerequisites)
  - [Compilation](#compilation)
  - [Running the Program](#running-the-program)
- [Sample Execution & Output](#-sample-execution--output)
  - [Dataset 1: Mutual Friendship Network](#dataset-1-mutual-friendship-network)
  - [Dataset 2: Directed Follow Network](#dataset-2-directed-follow-network)
- [Algorithms and Time Complexity](#-algorithms-and-time-complexity)
- [License](#-license)

---

## 📖 Overview

In discrete mathematics, a social network can be formally defined as a **binary relation** $R$ on a finite set of entities $U$:

$$U = \{u_1, u_2, \dots, u_n\}$$
$$R \subseteq U \times U$$

where $(a, b) \in R$ signifies an edge (e.g., "$a$ is friends with $b$" or "$a$ follows $b$").

This application analyzes two distinct interaction topologies:
1. **Undirected Social Network (Friendship)**: Interactions are mutual, producing symmetric relations.
2. **Directed Social Network (Following)**: Asymmetric interactions (e.g., Twitter/X or Instagram), where following does not guarantee a follow-back.

---

## ✨ Key Features

- **Adjacency Matrix Representation**: $10 \times 10$ binary matrix representation of relations over user set $U$.
- **Automated Property Testing**:
  - Reflexivity and Irreflexivity.
  - Symmetry and Antisymmetry.
  - Transitivity (with violation counter and concrete counterexample triples).
  - Equivalence relation determination.
- **Closure Computations**:
  - Reflexive Closure $r(R)$.
  - Symmetric Closure $s(R)$.
  - Transitive Closure $t(R)$ using **Warshall's Algorithm**.
  - Equivalence Closure $e(R) = t(s(r(R)))$ with verification.
- **Graph & Network Analysis**:
  - **Connected Components (Clusters)** using Depth-First Search (DFS) on $s(R)$.
  - **Degree Profiling**: Out-degree, in-degree, and mutual connection counts for every user.
  - **Isolated Users**: Automatic detection of users with zero inward and outward degrees.
  - **Strongly Connected Components (Mutually Reachable Groups)**: Identifying sub-communities where every pair has bidirectional reachability.
  - **Friend/Follow Recommendation System**: Computes relation composition $R \circ R$ ($R^2$) to identify "friends of friends" not yet directly connected.

---

## 📐 Mathematical Foundations

### 1. Binary Relations and Matrix Representation
Let $U = \{\text{Aarav}, \text{Bhavna}, \text{Chetan}, \text{Divya}, \text{Esha}, \text{Farhan}, \text{Gauri}, \text{Harsh}, \text{Ishaan}, \text{Jiya}\}$ with $|U| = 10$.

The relation $R$ is represented as a boolean matrix $M \in \{0, 1\}^{N \times N}$ where:
$$M_{i, j} = \begin{cases} 1 & \text{if } (u_i, u_j) \in R \\ 0 & \text{otherwise} \end{cases}$$

### 2. Relation Properties & Counterexamples

| Property | Formal Definition | Verification in Matrix $M$ | Counterexample Detection |
| :--- | :--- | :--- | :--- |
| **Reflexive** | $\forall x \in U, (x, x) \in R$ | $M_{i, i} = 1, \forall i$ | Reports first $i$ where $M_{i,i} = 0$ |
| **Irreflexive** | $\forall x \in U, (x, x) \notin R$ | $M_{i, i} = 0, \forall i$ | Reports first $i$ where $M_{i,i} = 1$ |
| **Symmetric** | $\forall x, y \in U, (x, y) \in R \implies (y, x) \in R$ | $M_{i, j} = M_{j, i}, \forall i, j$ | Reports $(u_i, u_j) \in R$ with $(u_j, u_i) \notin R$ |
| **Antisymmetric** | $\forall x, y \in U, ((x, y) \in R \land (y, x) \in R) \implies x = y$ | If $M_{i, j} = 1$ and $i \neq j$, then $M_{j, i} = 0$ | Reports mutual pair $u_i \leftrightarrow u_j$ |
| **Transitive** | $\forall x, y, z \in U, ((x, y) \in R \land (y, z) \in R) \implies (x, z) \in R$ | If $M_{i, j} = 1 \land M_{j, k} = 1$, then $M_{i, k} = 1$ | Counts total violations; reports first $(u_i, u_j, u_k)$ |
| **Equivalence** | Reflexive $\land$ Symmetric $\land$ Transitive | Satisfies all 3 simultaneously | Evaluates boolean conjunction |

### 3. Closures of Relations

- **Reflexive Closure**:
  $$r(R) = R \cup \{(x, x) \mid x \in U\} = R \cup \Delta$$
- **Symmetric Closure**:
  $$s(R) = R \cup \{(y, x) \mid (x, y) \in R\} = R \cup R^{-1}$$
- **Transitive Closure (Warshall's Algorithm)**:
  $$W_k[i][j] = W_{k-1}[i][j] \lor (W_{k-1}[i][k] \land W_{k-1}[k][j])$$
- **Equivalence Closure**:
  The smallest equivalence relation containing $R$:
  $$e(R) = t(s(r(R)))$$

### 4. Graph Analysis & Recommendation Engine

- **Degree Calculation**:
  $$\text{deg}^+(u_i) = \sum_{j=1}^N M_{i, j}, \quad \text{deg}^-(u_i) = \sum_{j=1}^N M_{j, i}$$
- **Strongly Connected Components**:
  Two users $u_i$ and $u_j$ belong to the same mutually reachable group if and only if:
  $$(u_i, u_j) \in t(R) \quad \text{and} \quad (u_j, u_i) \in t(R)$$
- **Relation Composition Recommendation ($R \circ R$)**:
  Identifies non-adjacent 2-hop connections:
  $$(u_i, u_k) \in (R \circ R) \setminus R \quad \text{where } i \neq k$$
  Suggests $u_k$ to $u_i$ through a mutual intermediary $u_j$ where $(u_i, u_j) \in R$ and $(u_j, u_k) \in R$.

---

## 📊 Supported Datasets

1. **Friendship Network (`ds = 1`)**:
   - Model: Undirected, mutual friendships.
   - Pairs: `(1,2), (1,3), (2,3), (3,4), (5,6), (6,7), (5,7), (8,9)` (and their symmetric inverses).
   - Generates 16 ordered pairs across 4 distinct community clusters.

2. **Follow Network (`ds = 2`)**:
   - Model: Directed follows (social media style).
   - Pairs: `(1,2), (2,1), (3,1), (3,2), (4,3), (5,6), (6,7), (7,5), (8,9), (9,8), (10,1)`.
   - Contains directed cycles, asymmetric links, and non-trivial reachability paths.

---

## 📁 Project Structure

```
Discrete-Mathematics-Friendship-Network/
│
├── .gitignore          # Git ignore rules for build artifacts
├── README.md           # Project documentation and theoretical background
└── friendnet.cpp       # Core C++ implementation
```

---

## 🚀 Getting Started

### Prerequisites

A modern C++ compiler supporting C++11 or later:
- **GCC / MinGW**: `g++ >= 4.8`
- **Clang**: `clang++ >= 3.3`
- **MSVC**: Visual Studio 2015 or newer

### Compilation

Clone the repository and compile using `g++`:

```bash
git clone https://github.com/JayParadox32/Discrete-Mathematics-Friendship-Network.git
cd Discrete-Mathematics-Friendship-Network
g++ -O2 -std=c++11 friendnet.cpp -o friendnet
```

### Running the Program

Execute the binary:

```bash
# On Linux / macOS:
./friendnet

# On Windows:
.\friendnet.exe
```

When prompted, input `1` for the Friendship Network or `2` for the Follow Network.

---

## 🖥️ Sample Execution & Output

### Dataset 1: Mutual Friendship Network

```text
Enter dataset (1 = Friendship, 2 = Follow): 1

== 1. Relation R on U ==
  1 = Aarav
  2 = Bhavna
  3 = Chetan
  4 = Divya
  5 = Esha
  6 = Farhan
  7 = Gauri
  8 = Harsh
  9 = Ishaan
 10 = Jiya
|U| = 10, |R| = 16 ordered pairs
       1  2  3  4  5  6  7  8  9 10
 1 |   0  1  1  0  0  0  0  0  0  0
 2 |   1  0  1  0  0  0  0  0  0  0
 3 |   1  1  0  1  0  0  0  0  0  0
 4 |   0  0  1  0  0  0  0  0  0  0
 5 |   0  0  0  0  0  1  1  0  0  0
 6 |   0  0  0  0  1  0  1  0  0  0
 7 |   0  0  0  0  1  1  0  0  0  0
 8 |   0  0  0  0  0  0  0  0  1  0
 9 |   0  0  0  0  0  0  0  1  0  0
10 |   0  0  0  0  0  0  0  0  0  0

== 2. Properties of R ==
Reflexive     : No   (Aarav, Aarav) not in R
Irreflexive   : Yes
Symmetric     : Yes
Antisymmetric : No   Aarav <-> Bhavna both in R
Transitive    : No   (Aarav,Chetan),(Chetan,Divya) in R but (Aarav,Divya) not
                20 violating triples in all
Equivalence   : No

== 3. Closures ==
|R|                           = 16
|reflexive closure|           = 26  (+10)
|symmetric closure|           = 16  (+0)
|transitive closure|          = 29  (+13)
|equivalence closure|         = 30  (+14)
Equivalence closure is reflexive, symmetric, transitive: Yes

== 4. Network analysis ==
Clusters (connected groups): 4
  {Aarav, Bhavna, Chetan, Divya}
  {Esha, Farhan, Gauri}
  {Harsh, Ishaan}
  {Jiya}
Degrees:
  User      Out  In  Mutual
  Aarav      2   2      2
  Bhavna     2   2      2
  Chetan     3   3      3
  Divya      1   1      1
  Esha       2   2      2
  Farhan     2   2      2
  Gauri      2   2      2
  Harsh      1   1      1
  Ishaan     1   1      1
  Jiya       0   0      0
Mutual connections (unordered pairs): 8
Isolated users: Jiya
Mutually reachable groups: 4
  {Aarav, Bhavna, Chetan, Divya}
  {Esha, Farhan, Gauri}
  {Harsh, Ishaan}
  {Jiya}
Suggestions (R o R, not in R, distinct users):
  Aarav - Divya
  Bhavna - Divya
```

---

### Dataset 2: Directed Follow Network

```text
Enter dataset (1 = Friendship, 2 = Follow): 2

== 1. Relation R on U ==
  1 = Aarav
  2 = Bhavna
  3 = Chetan
  4 = Divya
  5 = Esha
  6 = Farhan
  7 = Gauri
  8 = Harsh
  9 = Ishaan
 10 = Jiya
|U| = 10, |R| = 11 ordered pairs
       1  2  3  4  5  6  7  8  9 10
 1 |   0  1  0  0  0  0  0  0  0  0
 2 |   1  0  0  0  0  0  0  0  0  0
 3 |   1  1  0  0  0  0  0  0  0  0
 4 |   0  0  1  0  0  0  0  0  0  0
 5 |   0  0  0  0  0  1  0  0  0  0
 6 |   0  0  0  0  0  0  1  0  0  0
 7 |   0  0  0  0  1  0  0  0  0  0
 8 |   0  0  0  0  0  0  0  0  1  0
 9 |   0  0  0  0  0  0  0  1  0  0
10 |   1  0  0  0  0  0  0  0  0  0

== 2. Properties of R ==
Reflexive     : No   (Aarav, Aarav) not in R
Irreflexive   : Yes
Symmetric     : No   (Chetan, Aarav) in R but (Aarav, Chetan) not
Antisymmetric : No   Aarav <-> Bhavna both in R
Transitive    : No   (Divya,Chetan),(Chetan,Aarav) in R but (Divya,Aarav) not
                10 violating triples in all
Equivalence   : No

== 3. Closures ==
|R|                           = 11
|reflexive closure|           = 21  (+10)
|symmetric closure|           = 18  (+7)
|transitive closure|          = 24  (+13)
|equivalence closure|         = 38  (+27)
Equivalence closure is reflexive, symmetric, transitive: Yes

== 4. Network analysis ==
Clusters (connected groups): 3
  {Aarav, Bhavna, Chetan, Divya, Jiya}
  {Esha, Farhan, Gauri}
  {Harsh, Ishaan}
Degrees:
  User      Out  In  Mutual
  Aarav      1   3      1
  Bhavna     1   2      1
  Chetan     2   1      0
  Divya      1   0      0
  Esha       1   1      0
  Farhan     1   1      0
  Gauri      1   1      0
  Harsh      1   1      1
  Ishaan     1   1      1
  Jiya       1   0      0
Mutual connections (unordered pairs): 2
Isolated users: none
Mutually reachable groups: 6
  {Aarav, Bhavna}
  {Chetan}
  {Divya}
  {Esha, Farhan, Gauri}
  {Harsh, Ishaan}
  {Jiya}
Suggestions (R o R, not in R, distinct users):
  Divya -> Aarav
  Divya -> Bhavna
  Esha -> Gauri
  Farhan -> Esha
  Gauri -> Farhan
  Jiya -> Bhavna
```

---

## ⚡ Algorithms and Time Complexity

| Component | Method / Algorithm | Time Complexity | Space Complexity |
| :--- | :--- | :--- | :--- |
| **Property Tests** | Direct Matrix Traversal | $O(N)$ (Refl/Irrefl) / $O(N^2)$ (Sym/Antisym) / $O(N^3)$ (Trans) | $O(1)$ |
| **Reflexive Closure** | Diagonal element update | $O(N)$ | $O(N^2)$ |
| **Symmetric Closure** | Matrix transpose OR | $O(N^2)$ | $O(N^2)$ |
| **Transitive Closure** | Warshall's Algorithm | $O(N^3)$ | $O(N^2)$ |
| **Connected Components** | DFS on symmetric closure | $O(V + E) = O(N^2)$ | $O(N)$ recursion depth |
| **Relation Composition** | Boolean Matrix Multiplication ($R \circ R$) | $O(N^3)$ | $O(N^2)$ |
| **Reachability Groups** | Bidirectional reachability check via $t(R)$ | $O(N^2)$ | $O(N)$ |

*Note: For this system $N = 10$, executing all computations instantaneously.*

---

## 📄 License

This project is licensed under the MIT License. Feel free to use, modify, and distribute for educational and academic purposes.
