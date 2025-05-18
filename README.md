# ds_assign_5
# 🔍 Spell Checker using AVL Tree in C

This project is a **spell-checking system** implemented in C using an **AVL Tree** (a self-balancing Binary Search Tree).

---

## 📄 Features

- 📚 Loads dictionary words from a file (`Dictionary.txt`)
- 🌳 Constructs an AVL Tree for efficient word lookup
- 🧠 Calculates and displays:
  - Total number of words (nodes)
  - Height of the tree
- ✅ Verifies the correctness of each word in a user-entered sentence
- 🔎 If a word is not found, suggests three alternatives

---

## ⚙️ How It Works  

1. **Build the Dictionary Tree**  
   - Reads each word from `Dictionary.txt`  
   - Inserts them into an AVL tree to ensure balance for fast lookup  

2. **Spell Check**  
   - Accepts a user-entered sentence  
   - Splits it into individual words  
   - Searches each word in the AVL tree  

3. **Suggestions**  
   - If a word isn't found, prints:  
     - Closest match (last visited node)  
     - Inorder predecessor (lexical previous)  
     - Inorder successor (lexical next)  

## 🧪 Sample Run
```
Welcome to the Spell-checking System

Number of Nodes: 97462      
Tree Height: 20

Enter a sentence to search: I wrot ths assignmet mysel

- "i"          ✅ Found!

- "wrot"       ❌ Not Found!  Suggestions: wrote, wrongs, wroth.

- "ths"        ❌ Not Found!  Suggestions: Thucydides, thruways, Thucydides's.

- "assignmet"  ❌ Not Found!  Suggestions: assigns, assignments, assimilate.

- "mysel"      ❌ Not Found!  Suggestions: mys, myrtles, myself.
```
