#include <stdlib.h>
#include <stdio.h>

int checkParens(char* str) {
    int stacksize = 1000000;
    char* stack = (char*)malloc(stacksize * sizeof(char));
    char* stackbase = stack;

    int stackCount = 0;

    int* indexstack  = (int*)malloc(stacksize * sizeof(int));
    int* indexstackbase = indexstack;

    char* ptr;
    int count = 0;
    for (ptr = str; *ptr != '\0'; ptr++) {
        //printf("%s, %d\n", ptr, *ptr);
        count++;
        switch (*ptr) {
            case '(':
            case '[':
            case '{':
                //printf("HOI\n");
                *stack = *ptr;
                stack++;
                stackCount++;

                *indexstack = count;
                indexstack++;
                break;

            case ')':
                //printf("KAK\n");
                stack--;
                stackCount--;
                if (*stack != '(') {
                    //printf("BOOM\n");
                    return count;
                } else {
                    //printf("CHIK\n");
                    indexstack--;
                }
                break;
            case ']':
                stack--;
                stackCount--;
                if (*stack != '[') {
                    //printf("FAF\n");
                    return count;
                } else {
                    //printf("ADAD\n");
                    indexstack--;
                }
                break;
            case '}':
                stack--;
                stackCount--;
                if (*stack != '{') {
                    //printf("IOAS\n");
                    return count;
                } else {
                    //printf("PAOIS\n");
                    indexstack--;
                }
                break;

            default:
                //printf("HAH\n");
                break;

        }

        //printf("COUNT\n");
    }

    //printf("TROY\n");
    //printf("%d", stackCount);

    if (stackCount != 0) {
        return *indexstackbase;
    } else {
        return -999;
    }
}

int main(void) {
    int bufsize = 1000000;
    char* str = (char*)malloc(bufsize * sizeof(char));

    scanf("%s", str);

    int res = checkParens(str);

    if (res == -999) {
        printf("Success");
    } else {
        printf("%d", res);
    }

    free(str);
    return 0;
}