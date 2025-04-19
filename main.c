#include <stdio.h>
#include <stdlib.h>
#include <adns.h>

#define MAX_CHARS 256

void clear_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) { }
}

int main(int argc, char **argv) {
    adns_state state;
    adns_query query;
    adns_initflags flag = adns_if_none;
    FILE *log_file = fopen("log.txt", "w");

    int result = adns_init(&state, flag, log_file);

    printf("Result: %d\n", result);

    char user_input[MAX_CHARS];
    printf("Provide a domain address: ");
    scanf("%s", user_input);
    clear_buffer();

    printf("User input: %s\n", user_input);
    adns_finish(state);
}