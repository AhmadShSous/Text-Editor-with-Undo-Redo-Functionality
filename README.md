# Text-Editor-with-Undo-Redo-Functionality


# Text Editor with Undo/Redo System

## Project Overview
This project is a **C-language console application** designed to perform text editing operations with full **Undo** and **Redo** functionalities.

The system loads an initial text from a file, allows the user to insert or remove text dynamically, and supports undoing and redoing previous operations. The final text can be saved back into an output file.

---

## Features
- **Load Text**: Load initial text from an input file (`input.txt`).
- **Print Loaded Text**: Display the original text before any changes.
- **Insert Strings**: Insert words or phrases into specific locations in the text.
- **Remove Strings**: Delete words or phrases from the text.
- **Undo Operation**: Revert the last insert/remove operation.
- **Redo Operation**: Reapply the last undone operation.
- **Print Undo/Redo Stack**: Show history of operations.
- **Save Updated Text**: Save the modified text into an output file (`output.txt`).
- **Print Current Text**: Display the text after modifications.

---

## Data Structures
- **Stack (Undo Stack, Redo Stack)**:  
  - Each stack node stores the word, operation type (insert/remove), and position.
- **Queue**:
  - Used temporarily when inserting multiple words.

---

## Technologies Used
- **Language**: C
- **Dynamic Memory Management**: Using `malloc`, `free`.
- **File Handling**: Reading from and writing to `.txt` files.

---

## How to Run
1. Make sure you have a C compiler installed (like GCC).
2. Prepare an input file named `input.txt` containing the initial text.
3. Compile the project:
   ```bash
   gcc main.c -o text_editor
   ```
4. Run the executable:
   ```bash
   ./text_editor
   ```
5. Follow the menu to interact with the text editor.

---

## Menu Options
- 1: Load the input file.
- 2: Print the loaded text.
- 3: Insert strings into the text.
- 4: Remove strings from the text.
- 5: Perform Undo operation.
- 6: Perform Redo operation.
- 7: Print Undo Stack and Redo Stack.
- 8: Save the updated text to the output file.
- 9: Print the current text.
- 10: Exit.

---

## Example of `input.txt`
```
Welcome to the simple text editor.
```

---

## Author
- **Ahmad Shaher Ahmad Sous**  
  Student ID: 1221371  
  Section: 4

---
