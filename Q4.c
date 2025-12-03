#include <stdio.h>
#include <string.h>

struct Book
{
    int id;
    int popularity;
    int lastTime;
    int used;
};

int findBook(struct Book shelf[], int size, int id)
{
    int i;
    for (i = 0; i < size; i++)
    {
        if (shelf[i].used && shelf[i].id == id)
        {
            return i;
        }
    }
    return -1;
}

int findEmpty(struct Book shelf[], int size)
{
    int i;
    for (i = 0; i < size; i++)
    {
        if (shelf[i].used == 0)
        {
            return i;
        }
    }
    return -1;
}

int findLRU(struct Book shelf[], int size)
{
    int i;
    int index = -1;
    int lowest = 0;
    for (i = 0; i < size; i++)
    {
        if (shelf[i].used)
        {
            if (index == -1 || shelf[i].lastTime < lowest)
            {
                lowest = shelf[i].lastTime;
                index = i;
            }
        }
    }
    return index;
}

void addBook(struct Book shelf[], int size, int id, int popularity, int *time)
{
    int pos = findBook(shelf, size, id);
    if (pos != -1)
    {
        shelf[pos].popularity = popularity;
        shelf[pos].lastTime = *time;
        (*time)++;
        return;
    }

    int empty = findEmpty(shelf, size);
    if (empty != -1)
    {
        shelf[empty].id = id;
        shelf[empty].popularity = popularity;
        shelf[empty].lastTime = *time;
        shelf[empty].used = 1;
        (*time)++;
        return;
    }

    int remove = findLRU(shelf, size);
    if (remove != -1)
    {
        shelf[remove].id = id;
        shelf[remove].popularity = popularity;
        shelf[remove].lastTime = *time;
        shelf[remove].used = 1;
        (*time)++;
    }
}

int accessBook(struct Book shelf[], int size, int id, int *time)
{
    int pos = findBook(shelf, size, id);
    if (pos == -1)
    {
        return -1;
    }
    shelf[pos].lastTime = *time;
    (*time)++;
    return shelf[pos].popularity;
}

void showShelf(struct Book shelf[], int size)
{
    int i;
    printf("\n-----------------------------------------\n");
    printf("             Library Shelf               \n");
    printf("-----------------------------------------\n");
    printf("%-10s %-12s %-10s\n", "Book ID", "Popularity", "Last Used");
    printf("-----------------------------------------\n");

    for (i = 0; i < size; i++)
    {
        if (shelf[i].used)
        {
            printf("%-10d %-12d %-10d\n",
                   shelf[i].id, shelf[i].popularity, shelf[i].lastTime);
        }
        else
        {
            printf("%-10s %-12s %-10s\n", "-", "-", "-");
        }
    }

    printf("-----------------------------------------\n\n");
}

int main()
{
    int size;
    int queries;
    int time = 1;
    int i;
    char option[10];

    printf("\n=============================\n");
    printf("     LIBRARY SHELF MENU      \n");
    printf("=============================\n\n");

    printf("Enter shelf capacity: ");
    scanf("%d", &size);

    printf("Enter number of operations: ");
    scanf("%d", &queries);

    struct Book shelf[200];

    for (i = 0; i < size; i++)
    {
        shelf[i].used = 0;
        shelf[i].id = 0;
        shelf[i].popularity = 0;
        shelf[i].lastTime = 0;
    }

    for (i = 0; i < queries; i++)
    {
        printf("\nChoose Operation:\n");
        printf("1. ADD Book\n");
        printf("2. ACCESS Book\n");
        printf("3. SHOW Shelf\n");
        printf("Enter option: ");
        scanf("%s", option);

        if (strcmp(option, "ADD") == 0 || strcmp(option, "1") == 0)
        {
            int id, pop;
            printf("Enter Book ID: ");
            scanf("%d", &id);
            printf("Enter Popularity: ");
            scanf("%d", &pop);
            addBook(shelf, size, id, pop, &time);
            printf("Book added.\n");
        }
        else if (strcmp(option, "ACCESS") == 0 || strcmp(option, "2") == 0)
        {
            int id;
            printf("Enter Book ID to access: ");
            scanf("%d", &id);
            int result = accessBook(shelf, size, id, &time);
            if (result == -1)
            {
                printf("Book not found on shelf.\n");
            }
            else
            {
                printf("Book found. Popularity = %d\n", result);
            }
        }
        else if (strcmp(option, "SHOW") == 0 || strcmp(option, "3") == 0)
        {
            showShelf(shelf, size);
        }
        else
        {
            printf("Invalid option.\n");
        }
    }

    printf("\nAll operations completed.\n");
    showShelf(shelf, size);

    return 0;
}
