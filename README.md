# Student Record Management System

A menu-driven mini-project written in C. It uses a **singly linked list** to manage student records.

## Features

- Add a student (ID, name and marks)
- Display all student records
- Search for a student using their ID
- Update a student's name and marks
- Delete a student record
- Sort students by marks (highest to lowest)
- Save records to a text file and load them the next time the program starts

## Data structures and concepts used

| Concept | How it is used |
|---|---|
| Structure (`struct`) | Groups each student's ID, name, marks and next pointer |
| Singly linked list | Stores the student records as dynamically allocated nodes |
| Dynamic memory allocation | `malloc()` creates nodes and `free()` releases deleted nodes |
| Traversal | Visits nodes to display, search, append and sort records |
| Searching | Linear search finds a student by ID |
| Sorting | Bubble sort arranges students by marks |
| File handling | `students.txt` stores records between program runs |

## Requirements

- A C compiler such as GCC
- Windows, Linux or macOS terminal

## Compile and run

### Windows (MinGW GCC)

```bash
gcc -std=c11 -Wall -Wextra -pedantic main.c -o student_manager.exe
student_manager.exe
```

### Linux / macOS

```bash
gcc -std=c11 -Wall -Wextra -pedantic main.c -o student_manager
./student_manager
```

The program creates `students.txt` in the current working directory when records are saved. Keep this file in the same folder when you want to retain your sample records.

## Example use

1. Run the program.
2. Select `1` to add a student.
3. Enter an ID, name and marks.
4. Select `2` to view all records.
5. Select `3` to search by ID.
6. Select `6` to sort by marks.
7. Select `0` to exit.

## How the linked list works

Each node contains:

- `id`: student ID
- `name`: student's name
- `marks`: marks out of 100
- `next`: address of the next node

The `head` pointer stores the address of the first node. The last node points to `NULL`.

```text
head
  |
  v
+------------------+     +------------------+     +------------------+
| ID | Name | Marks| --> | ID | Name | Marks| --> | ID | Name | Marks|
| next pointer     |     | next pointer     |     | NULL             |
+------------------+     +------------------+     +------------------+
```

## Time complexity

Let `n` be the number of student records.

| Operation | Time complexity |
|---|---:|
| Add student (append) | O(n) |
| Display all students | O(n) |
| Search by ID | O(n) |
| Update by ID | O(n) |
| Delete by ID | O(n) |
| Bubble sort | O(n²) |

## Project objective

The objective is to demonstrate how a linked list can store a collection of records whose size can grow or shrink during program execution. The project also demonstrates searching, sorting, dynamic memory allocation and file handling.

## Limitations

- Student IDs must be unique.
- Marks are accepted from 0 to 100.
- Names cannot contain tab characters because records are stored in a tab-separated text file.
- This is a console-based academic project; it does not use a database or graphical interface.

## Author

Vardhmaan Jain
