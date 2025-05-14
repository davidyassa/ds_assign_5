# ds_assign_5
### Implementing a spell-checking system using a self-correcting Binary Search Tree (AVL tree)  
The program prompts the user to enter a sentence to check its spelling.  
Each word in the entered sentence is checked to see whether it exists in the BST.  
1. If the word exists, it will print that the word is correct.  
2. If the word does not exist, it will print three suggestions for the correct word:  
A. The word in the last node reached before declaring that the word does not exist.  
B. The word in the inorder predecessor of that node in Part A.  
C. The word in the inorder successor of that node in Part A.

When the program starts, it loads a text file containing all language words by default, and prints the size and height of the tree.  
Then it asks the user to enter a sentence and checks whether each word in the sentence exists in the dictionary. If not, it prints the three suggestions as mentioned above.  
