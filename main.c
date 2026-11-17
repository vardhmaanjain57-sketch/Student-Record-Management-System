/*
 * Student Record Management System
 * Data structure: Singly Linked List
 * Language: C (C11)
 *
 * Features: Add, display, search, update, delete, sort, save and load.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define DATA_FILE "students.txt"
#define NAME_LENGTH 100
#define LINE_LENGTH 256

typedef struct Student {
    int id;
    char name[NAME_LENGTH];
    float marks;
    struct Student *next;
} Student;

static Student *head = NULL;

/* Read a complete line safely, removing the trailing newline. */
void read_line(const char *prompt, char *buffer, size_t size) {
    printf("%s", prompt);

    if (fgets(buffer, (int)size, stdin) == NULL) {
        buffer[0] = '\0';
        return;
    }

    buffer[strcspn(buffer, "\n")] = '\0';

    /* Clear remaining input if the line was longer than the buffer. */
    if (strchr(buffer, '\0') == buffer + size - 1) {
        int ch;
        while ((ch = getchar()) != '\n' && ch != EOF) {
            /* discard */
        }
    }
}

int read_int(const char *prompt) {
    char line[LINE_LENGTH];
    char *end;
    long value;

    for (;;) {
        read_line(prompt, line, sizeof(line));
        value = strtol(line, &end, 10);

        while (isspace((unsigned char)*end)) {
            end++;
        }

        if (line[0] != '\0' && *end == '\0' &&
            value >= -2147483647L - 1 && value <= 2147483647L) {
            return (int)value;
        }

        printf("Please enter a valid whole number.\n");
    }
}

float read_marks(const char *prompt) {
    char line[LINE_LENGTH];
    char *end;
    float value;

    for (;;) {
        read_line(prompt, line, sizeof(line));
        value = strtof(line, &end);

        while (isspace((unsigned char)*end)) {
            end++;
        }

        if (line[0] != '\0' && *end == '\0' &&
            value >= 0.0f && value <= 100.0f) {
            return value;
        }

        printf("Please enter marks between 0 and 100.\n");
    }
}

Student *find_student(int id) {
    Student *current = head;

    while (current != NULL) {
        if (current->id == id) {
            return current;
        }
        current = current->next;
    }

    return NULL;
}

void save_records(void) {
    FILE *file = fopen(DATA_FILE, "w");
    Student *current = head;

    if (file == NULL) {
        printf("Warning: Could not save records to %s.\n", DATA_FILE);
        return;
    }

    while (current != NULL) {
        /* Names containing tabs/newlines are rejected during input. */
        fprintf(file, "%d\t%s\t%.2f\n",
                current->id, current->name, current->marks);
        current = current->next;
    }

    fclose(file);
}

void load_records(void) {
    FILE *file = fopen(DATA_FILE, "r");
    char line[LINE_LENGTH];

    if (file == NULL) {
        return; /* First run: the data file does not exist yet. */
    }

    while (fgets(line, sizeof(line), file) != NULL) {
        int id;
        char name[NAME_LENGTH];
        float marks;
        char extra;

        if (sscanf(line, "%d\t%99[^\t]\t%f %c",
                   &id, name, &marks, &extra) == 3 &&
            id > 0 && marks >= 0.0f && marks <= 100.0f &&
            strchr(name, '\n') == NULL && find_student(id) == NULL) {

            Student *node = malloc(sizeof(Student));
            if (node == NULL) {
                printf("Not enough memory to load all records.\n");
                break;
            }

            node->id = id;
            snprintf(node->name, sizeof(node->name), "%s", name);
            node->marks = marks;
            node->next = NULL;

            if (head == NULL) {
                head = node;
            } else {
                Student *tail = head;
                while (tail->next != NULL) {
                    tail = tail->next;
                }
                tail->next = node;
            }
        }
    }

    fclose(file);
}

void add_student(void) {
    int id;
    char name[NAME_LENGTH];
    float marks;
    Student *node;
    Student *tail;

    printf("\n--- Add Student ---\n");

    id = read_int("Enter student ID: ");
    if (id <= 0) {
        printf("Student ID must be positive.\n");
        return;
    }

    if (find_student(id) != NULL) {
        printf("A student with this ID already exists.\n");
        return;
    }

    do {
        read_line("Enter student name: ", name, sizeof(name));
        if (name[0] == '\0' || strchr(name, '\t') != NULL) {
            printf("Name cannot be empty or contain a tab.\n");
        }
    } while (name[0] == '\0' || strchr(name, '\t') != NULL);

    marks = read_marks("Enter marks (0-100): ");

    node = malloc(sizeof(Student));
    if (node == NULL) {
        printf("Memory allocation failed. Student was not added.\n");
        return;
    }

    node->id = id;
    snprintf(node->name, sizeof(node->name), "%s", name);
    node->marks = marks;
    node->next = NULL;

    if (head == NULL) {
        head = node;
    } else {
        tail = head;
        while (tail->next != NULL) {
            tail = tail->next;
        }
        tail->next = node;
    }

    save_records();
    printf("Student added successfully.\n");
}

void display_students(void) {
    Student *current = head;

    printf("\n---------------- STUDENT RECORDS ----------------\n");
    printf("%-10s %-30s %10s\n", "ID", "NAME", "MARKS");
    printf("-------------------------------------------------\n");

    if (current == NULL) {
        printf("No student records found.\n");
        return;
    }

    while (current != NULL) {
        printf("%-10d %-30s %10.2f\n",
               current->id, current->name, current->marks);
        current = current->next;
    }
}

void search_student(void) {
    int id = read_int("\nEnter student ID to search: ");
    Student *student = find_student(id);

    if (student == NULL) {
        printf("Student not found.\n");
    } else {
        printf("\nStudent found:\n");
        printf("ID    : %d\n", student->id);
        printf("Name  : %s\n", student->name);
        printf("Marks : %.2f\n", student->marks);
    }
}

void update_student(void) {
    int id = read_int("\nEnter student ID to update: ");
    Student *student = find_student(id);
    char name[NAME_LENGTH];

    if (student == NULL) {
        printf("Student not found.\n");
        return;
    }

    printf("Current name: %s\n", student->name);
    do {
        read_line("Enter new name: ", name, sizeof(name));
        if (name[0] == '\0' || strchr(name, '\t') != NULL) {
            printf("Name cannot be empty or contain a tab.\n");
        }
    } while (name[0] == '\0' || strchr(name, '\t') != NULL);

    student->marks = read_marks("Enter new marks (0-100): ");
    snprintf(student->name, sizeof(student->name), "%s", name);

    save_records();
    printf("Student record updated successfully.\n");
}

void delete_student(void) {
    int id = read_int("\nEnter student ID to delete: ");
    Student *current = head;
    Student *previous = NULL;

    while (current != NULL && current->id != id) {
        previous = current;
        current = current->next;
    }

    if (current == NULL) {
        printf("Student not found.\n");
        return;
    }

    if (previous == NULL) {
        head = current->next;
    } else {
        previous->next = current->next;
    }

    free(current);
    save_records();
    printf("Student record deleted successfully.\n");
}

/* Bubble sort by marks in descending order. */
void sort_students(void) {
    Student *i;
    Student *j;
    int swapped;

    if (head == NULL || head->next == NULL) {
        printf("Not enough records to sort.\n");
        return;
    }

    do {
        swapped = 0;
        i = head;

        while (i->next != NULL) {
            j = i->next;

            if (i->marks < j->marks) {
                int temp_id = i->id;
                float temp_marks = i->marks;
                char temp_name[NAME_LENGTH];

                snprintf(temp_name, sizeof(temp_name), "%s", i->name);

                i->id = j->id;
                i->marks = j->marks;
                snprintf(i->name, sizeof(i->name), "%s", j->name);

                j->id = temp_id;
                j->marks = temp_marks;
                snprintf(j->name, sizeof(j->name), "%s", temp_name);

                swapped = 1;
            }
            i = i->next;
        }
    } while (swapped);

    save_records();
    printf("Students sorted by marks (highest to lowest).\n");
}

void free_list(void) {
    Student *current = head;

    while (current != NULL) {
        Student *next = current->next;
        free(current);
        current = next;
    }

    head = NULL;
}

void show_menu(void) {
    printf("\n========================================\n");
    printf("     STUDENT RECORD MANAGEMENT SYSTEM\n");
    printf("========================================\n");
    printf("1. Add student\n");
    printf("2. Display all students\n");
    printf("3. Search student by ID\n");
    printf("4. Update student record\n");
    printf("5. Delete student record\n");
    printf("6. Sort students by marks\n");
    printf("0. Exit\n");
    printf("----------------------------------------\n");
}

int main(void) {
    int choice;

    load_records();
    printf("Welcome! Student records have been loaded.\n");

    do {
        show_menu();
        choice = read_int("Enter your choice: ");

        switch (choice) {
            case 1:
                add_student();
                break;
            case 2:
                display_students();
                break;
            case 3:
                search_student();
                break;
            case 4:
                update_student();
                break;
            case 5:
                delete_student();
                break;
            case 6:
                sort_students();
                break;
            case 0:
                save_records();
                printf("Records saved. Goodbye!\n");
                break;
            default:
                printf("Invalid choice. Please select an option from the menu.\n");
        }
    } while (choice != 0);

    free_list();
    return 0;
}
