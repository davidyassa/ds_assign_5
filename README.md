# ds_assign_5
# 🔍 Spell Checker using AVL Tree in C

This project is a **spell-checking system** implemented in C using an **AVL Tree** (a self-balancing Binary Search Tree). The dictionary is loaded from a file, and the program checks user-input sentences for correct spelling, offering **suggestions** when a word is not found.

---

## 📄 Features

- 📚 Loads dictionary words from a file (`Dictionary.txt`)
- 🌳 Constructs an AVL Tree for efficient word lookup
- 🧠 Calculates and displays:
  - Total number of words (nodes)
  - Height of the tree
- ✅ Verifies the correctness of each word in a user-entered sentence
- 🔎 If a word is not found, suggests three alternatives:
  - The last node visited before failure
  - The inorder predecessor and inorder successor of that node

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
   - If not found, prints:
     - Closest match (last visited node)
     - Inorder predecessor (lexical previous)
     - Inorder successor (lexical next)
