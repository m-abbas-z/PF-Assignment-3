#include <stdio.h>
#include <string.h>

char **lines = NULL;
int lineCount = 0;
int lineCapacity = 0;

void ensureCapacity()
{
    int newCapacity;
    char **newLines;
    int i;

    if (lineCapacity == 0)
    {
        lineCapacity = 2;
        newLines = (char **)malloc(sizeof(char *) * lineCapacity);
        if (newLines == NULL)
        {
            printf("Memory allocation failed.\n");
            return;
        }
        lines = newLines;
    }
    else if (lineCount >= lineCapacity)
    {
        newCapacity = lineCapacity * 2;
        newLines = (char **)realloc(lines, sizeof(char *) * newCapacity);
        if (newLines == NULL)
        {
            printf("Memory allocation failed.\n");
            return;
        }
        lines = newLines;
        lineCapacity = newCapacity;
    }
}

void insertLine(int index, const char *text)
{
    int length;
    char *newLine;
    int i;

    if (index < 0)
    {
        index = 0;
    }
    if (index > lineCount)
    {
        index = lineCount;
    }

    ensureCapacity();
    if (lineCount >= lineCapacity)
    {
        return;
    }

    if (lineCount > index)
    {
        memmove(&lines[index + 1], &lines[index], (lineCount - index) * sizeof(char *));
    }

    length = (int)strlen(text);
    newLine = (char *)malloc(length + 1);
    if (newLine == NULL)
    {
        printf("Memory allocation failed.\n");
        return;
    }

    strcpy(newLine, text);
    lines[index] = newLine;
    lineCount++;
}

void deleteLine(int index)
{
    int i;
    if (index < 0 || index >= lineCount)
    {
        return;
    }

    if (lines[index] != NULL)
    {
        free(lines[index]);
    }

    if (index < lineCount - 1)
    {
        memmove(&lines[index], &lines[index + 1], (lineCount - index - 1) * sizeof(char *));
    }

    lineCount--;
}

void printAllLines()
{
    int i;
    for (i = 0; i < lineCount; i++)
    {
        if (lines[i] != NULL)
        {
            printf("%d: %s\n", i, lines[i]);
        }
    }
}

void freeAll()
{
    int i;
    for (i = 0; i < lineCount; i++)
    {
        if (lines[i] != NULL)
        {
            free(lines[i]);
        }
    }
    if (lines != NULL)
    {
        free(lines);
    }
    lines = NULL;
    lineCount = 0;
    lineCapacity = 0;
}

void shrinkToFit()
{
    char **newLines;
    if (lineCount == 0)
    {
        if (lines != NULL)
        {
            free(lines);
            lines = NULL;
        }
        lineCapacity = 0;
        return;
    }

    newLines = (char **)realloc(lines, sizeof(char *) * lineCount);
    if (newLines == NULL)
    {
        printf("Memory allocation failed.\n");
        return;
    }
    lines = newLines;
    lineCapacity = lineCount;
}

void saveToFile(const char *fileName)
{
    FILE *file = fopen(fileName, "w");
    int i;
    if (file == NULL)
    {
        printf("Could not open file for writing.\n");
        return;
    }
    for (i = 0; i < lineCount; i++)
    {
        if (lines[i] != NULL)
        {
            fprintf(file, "%s\n", lines[i]);
        }
    }
    fclose(file);
}

void loadFromFile(const char *fileName)
{
    FILE *file = fopen(fileName, "r");
    char buffer[1024];
    int i;

    if (file == NULL)
    {
        printf("Could not open file for reading.\n");
        return;
    }

    freeAll();

    while (fgets(buffer, sizeof(buffer), file) != NULL)
    {
        int length = (int)strlen(buffer);
        if (length > 0 && buffer[length - 1] == '\n')
        {
            buffer[length - 1] = '\0';
        }
        insertLine(lineCount, buffer);
    }

    fclose(file);
}

void readLineFromUser(char *buffer, int size)
{
    int length;
    if (fgets(buffer, size, stdin) == NULL)
    {
        buffer[0] = '\0';
        return;
    }
    length = (int)strlen(buffer);
    if (length > 0 && buffer[length - 1] == '\n')
    {
        buffer[length - 1] = '\0';
    }
}

int main()
{
    int choice;
    int index;
    char text[1024];
    char fileName[100];

    while (1)
    {
        printf("\nText Editor Menu:\n");
        printf("1. Insert line at end\n");
        printf("2. Insert line at position\n");
        printf("3. Delete line at position\n");
        printf("4. Print all lines\n");
        printf("5. Save to file\n");
        printf("6. Load from file\n");
        printf("7. Shrink to fit\n");
        printf("8. Exit\n");
        printf("Enter choice: ");
        if (scanf("%d", &choice) != 1)
        {
            break;
        }
        getchar();

        if (choice == 1)
        {
            printf("Enter line text: ");
            readLineFromUser(text, sizeof(text));
            insertLine(lineCount, text);
        }
        else if (choice == 2)
        {
            printf("Enter index to insert at: ");
            scanf("%d", &index);
            getchar();
            printf("Enter line text: ");
            readLineFromUser(text, sizeof(text));
            insertLine(index, text);
        }
        else if (choice == 3)
        {
            printf("Enter index to delete: ");
            scanf("%d", &index);
            getchar();
            deleteLine(index);
        }
        else if (choice == 4)
        {
            printAllLines();
        }
        else if (choice == 5)
        {
            printf("Enter file name: ");
            scanf(" %99s", fileName);
            saveToFile(fileName);
        }
        else if (choice == 6)
        {
            printf("Enter file name: ");
            scanf(" %99s", fileName);
            loadFromFile(fileName);
        }
        else if (choice == 7)
        {
            shrinkToFit();
        }
        else if (choice == 8)
        {
            break;
        }
        else
        {
            printf("Invalid choice.\n");
        }
    }

    freeAll();
    return 0;
}
