#include <stdio.h>
#include <string.h>

struct Student
{
    int studentId;
    char fullName[100];
    char batch[20];
    char membershipType[10];
    char registrationDate[11];
    char dateOfBirth[11];
    char interest[10];
};

struct Student *students = NULL;
int studentCount = 0;
int studentCapacity = 0;

void ensureStudentCapacity()
{
    struct Student *newStudents;
    if (studentCapacity == 0)
    {
        studentCapacity = 5;
        newStudents = (struct Student *)malloc(sizeof(struct Student) * studentCapacity);
        if (newStudents == NULL)
        {
            printf("Memory allocation failed.\n");
            return;
        }
        students = newStudents;
    }
    else if (studentCount >= studentCapacity)
    {
        int newCapacity = studentCapacity * 2;
        newStudents = (struct Student *)realloc(students, sizeof(struct Student) * newCapacity);
        if (newStudents == NULL)
        {
            printf("Memory allocation failed.\n");
            return;
        }
        students = newStudents;
        studentCapacity = newCapacity;
    }
}

int findStudentIndexById(int studentId)
{
    int i;
    for (i = 0; i < studentCount; i++)
    {
        if (students[i].studentId == studentId)
        {
            return i;
        }
    }
    return -1;
}

void loadDatabase(const char *filename)
{
    FILE *file = fopen(filename, "rb");
    struct Student temp;

    if (file == NULL)
    {
        return;
    }

    studentCount = 0;

    while (fread(&temp, sizeof(struct Student), 1, file) == 1)
    {
        ensureStudentCapacity();
        if (studentCount < studentCapacity)
        {
            students[studentCount] = temp;
            studentCount++;
        }
    }

    fclose(file);
}

void saveDatabase(const char *filename)
{
    FILE *file = fopen(filename, "wb");
    int i;

    if (file == NULL)
    {
        printf("Could not open database file for writing.\n");
        return;
    }

    for (i = 0; i < studentCount; i++)
    {
        fwrite(&students[i], sizeof(struct Student), 1, file);
    }

    fclose(file);
}

void addStudent(struct Student s, const char *filename)
{
    if (findStudentIndexById(s.studentId) != -1)
    {
        printf("Student ID already exists. Cannot add duplicate.\n");
        return;
    }

    ensureStudentCapacity();
    if (studentCount >= studentCapacity)
    {
        printf("Cannot add student due to memory limit.\n");
        return;
    }

    students[studentCount] = s;
    studentCount++;

    saveDatabase(filename);
    printf("Student added.\n");
}

void updateStudent(int studentId)
{
    int index = findStudentIndexById(studentId);
    int choice;

    if (index == -1)
    {
        printf("Student not found.\n");
        return;
    }

    printf("Update options:\n");
    printf("1. Batch\n");
    printf("2. Membership Type\n");
    printf("Enter choice: ");
    scanf("%d", &choice);

    if (choice == 1)
    {
        printf("Enter new batch (CS/SE/Cyber/AI): ");
        scanf(" %19s", students[index].batch);
        printf("Batch updated.\n");
    }
    else if (choice == 2)
    {
        printf("Enter new membership type (IEEE/ACM): ");
        scanf(" %9s", students[index].membershipType);
        printf("Membership type updated.\n");
    }
    else
    {
        printf("Invalid choice.\n");
    }
}

void deleteStudent(int studentId)
{
    int index = findStudentIndexById(studentId);
    int i;

    if (index == -1)
    {
        printf("Student not found.\n");
        return;
    }

    for (i = index; i < studentCount - 1; i++)
    {
        students[i] = students[i + 1];
    }

    studentCount--;
    printf("Student deleted.\n");
}

void displayAllStudents()
{
    int i;
    if (studentCount == 0)
    {
        printf("No students to display.\n");
        return;
    }

    for (i = 0; i < studentCount; i++)
    {
        printf("\nStudent %d:\n", i + 1);
        printf("ID: %d\n", students[i].studentId);
        printf("Name: %s\n", students[i].fullName);
        printf("Batch: %s\n", students[i].batch);
        printf("Membership Type: %s\n", students[i].membershipType);
        printf("Registration Date: %s\n", students[i].registrationDate);
        printf("Date of Birth: %s\n", students[i].dateOfBirth);
        printf("Interest: %s\n", students[i].interest);
    }
}

void generateBatchReport()
{
    char batchFilter[20];
    char interestFilter[10];
    int i;
    int found = 0;

    printf("Enter batch to filter (CS/SE/Cyber/AI): ");
    scanf(" %19s", batchFilter);
    printf("Enter interest filter (IEEE/ACM/Both): ");
    scanf(" %9s", interestFilter);

    for (i = 0; i < studentCount; i++)
    {
        if (strcmp(students[i].batch, batchFilter) == 0 && strcmp(students[i].interest, interestFilter) == 0)
        {
            printf("\nID: %d\n", students[i].studentId);
            printf("Name: %s\n", students[i].fullName);
            printf("Membership Type: %s\n", students[i].membershipType);
            printf("Registration Date: %s\n", students[i].registrationDate);
            found = 1;
        }
    }

    if (!found)
    {
        printf("No records found for this filter.\n");
    }
}

void freeStudentMemory()
{
    if (students != NULL)
    {
        free(students);
    }
    students = NULL;
    studentCount = 0;
    studentCapacity = 0;
}

int main()
{
    int choice;
    int id;
    struct Student newStudent;
    char filename[] = "members.dat";

    loadDatabase(filename);

    while (1)
    {
        printf("\nMembership Manager Menu:\n");
        printf("1. Register new student\n");
        printf("2. Update student\n");
        printf("3. Delete student\n");
        printf("4. View all registrations\n");
        printf("5. Generate batch-wise report\n");
        printf("6. Save and Exit\n");
        printf("Enter choice: ");
        if (scanf("%d", &choice) != 1)
        {
            break;
        }

        if (choice == 1)
        {
            printf("Enter Student ID: ");
            scanf("%d", &newStudent.studentId);
            printf("Enter Full Name: ");
            scanf(" %99[^\n]", newStudent.fullName);
            printf("Enter Batch (CS/SE/Cyber/AI): ");
            scanf(" %19s", newStudent.batch);
            printf("Enter Membership Type (IEEE/ACM): ");
            scanf(" %9s", newStudent.membershipType);
            printf("Enter Registration Date (YYYY-MM-DD): ");
            scanf(" %10s", newStudent.registrationDate);
            printf("Enter Date of Birth (YYYY-MM-DD): ");
            scanf(" %10s", newStudent.dateOfBirth);
            printf("Enter Interest (IEEE/ACM/Both): ");
            scanf(" %9s", newStudent.interest);

            addStudent(newStudent, filename);
        }
        else if (choice == 2)
        {
            printf("Enter Student ID to update: ");
            scanf("%d", &id);
            updateStudent(id);
            saveDatabase(filename);
        }
        else if (choice == 3)
        {
            printf("Enter Student ID to delete: ");
            scanf("%d", &id);
            deleteStudent(id);
            saveDatabase(filename);
        }
        else if (choice == 4)
        {
            displayAllStudents();
        }
        else if (choice == 5)
        {
            generateBatchReport();
        }
        else if (choice == 6)
        {
            saveDatabase(filename);
            break;
        }
        else
        {
            printf("Invalid choice.\n");
        }
    }

    freeStudentMemory();
    return 0;
}
