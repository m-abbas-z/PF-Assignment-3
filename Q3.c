#include <stdio.h>
#include <string.h>

struct Employee
{
    int id;
    char name[100];
    char designation[100];
    double salary;
};

void inputEmployees(struct Employee employees[], int count)
{
    int i;
    for (i = 0; i < count; i++)
    {
        printf("Employee %d ID: ", i + 1);
        scanf("%d", &employees[i].id);
        printf("Employee %d Name: ", i + 1);
        scanf(" %99[^\n]", employees[i].name);
        printf("Employee %d Designation: ", i + 1);
        scanf(" %99[^\n]", employees[i].designation);
        printf("Employee %d Salary: ", i + 1);
        scanf("%lf", &employees[i].salary);
    }
}

void displayEmployees(struct Employee employees[], int count)
{
    int i;
    printf("\n%-10s %-25s %-25s %-10s\n", "ID", "Name", "Designation", "Salary");
    for (i = 0; i < count; i++)
    {
        printf("%-10d %-25s %-25s %-10.2f\n", employees[i].id, employees[i].name, employees[i].designation, employees[i].salary);
    }
}

void findHighestSalary(struct Employee employees[], int count)
{
    if (count <= 0)
    {
        return;
    }

    int i;
    int highestIndex = 0;
    for (i = 1; i < count; i++)
    {
        if (employees[i].salary > employees[highestIndex].salary)
        {
            highestIndex = i;
        }
    }

    printf("\nEmployee with highest salary:\n");
    printf("ID: %d\n", employees[highestIndex].id);
    printf("Name: %s\n", employees[highestIndex].name);
    printf("Designation: %s\n", employees[highestIndex].designation);
    printf("Salary: %.2f\n", employees[highestIndex].salary);
}

void searchEmployee(struct Employee employees[], int count)
{
    int choice;
    printf("\nSearch by:\n");
    printf("1. ID\n");
    printf("2. Name\n");
    printf("Enter choice: ");
    scanf("%d", &choice);

    if (choice == 1)
    {
        int searchId;
        int i;
        int found = 0;
        printf("Enter ID to search: ");
        scanf("%d", &searchId);
        for (i = 0; i < count; i++)
        {
            if (employees[i].id == searchId)
            {
                printf("Record found:\n");
                printf("ID: %d\n", employees[i].id);
                printf("Name: %s\n", employees[i].name);
                printf("Designation: %s\n", employees[i].designation);
                printf("Salary: %.2f\n", employees[i].salary);
                found = 1;
            }
        }
        if (!found)
        {
            printf("No employee found with this ID.\n");
        }
    }
    else if (choice == 2)
    {
        char searchName[100];
        int i;
        int found = 0;
        printf("Enter Name to search (case-sensitive): ");
        scanf(" %99[^\n]", searchName);
        for (i = 0; i < count; i++)
        {
            if (strcmp(employees[i].name, searchName) == 0)
            {
                printf("Record found:\n");
                printf("ID: %d\n", employees[i].id);
                printf("Name: %s\n", employees[i].name);
                printf("Designation: %s\n", employees[i].designation);
                printf("Salary: %.2f\n", employees[i].salary);
                found = 1;
            }
        }
        if (!found)
        {
            printf("No employee found with this Name.\n");
        }
    }
    else
    {
        printf("Invalid choice.\n");
    }
}

void applyBonus(struct Employee employees[], int count, double threshold)
{
    int i;
    for (i = 0; i < count; i++)
    {
        if (employees[i].salary < threshold)
        {
            employees[i].salary = employees[i].salary * 1.10;
        }
    }
}

int main()
{
    int employeeCount;
    int menuChoice;
    double threshold;

    printf("Enter number of employees: ");
    scanf("%d", &employeeCount);

    if (employeeCount <= 0)
    {
        return 0;
    }

    struct Employee employees[200];

    if (employeeCount > 200)
    {
        employeeCount = 200;
    }

    inputEmployees(employees, employeeCount);

    while (1)
    {
        printf("\nMenu:\n");
        printf("1. Display all employees\n");
        printf("2. Find employee with highest salary\n");
        printf("3. Search employee\n");
        printf("4. Apply 10%% bonus below threshold\n");
        printf("5. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &menuChoice);

        if (menuChoice == 1)
        {
            displayEmployees(employees, employeeCount);
        }
        else if (menuChoice == 2)
        {
            findHighestSalary(employees, employeeCount);
        }
        else if (menuChoice == 3)
        {
            searchEmployee(employees, employeeCount);
        }
        else if (menuChoice == 4)
        {
            printf("Enter salary threshold: ");
            scanf("%lf", &threshold);
            applyBonus(employees, employeeCount, threshold);
            printf("Bonus applied.\n");
        }
        else if (menuChoice == 5)
        {
            break;
        }
        else
        {
            printf("Invalid choice.\n");
        }
    }

    return 0;
}
