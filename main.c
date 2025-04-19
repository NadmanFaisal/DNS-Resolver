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
    FILE *log_file = fopen("log.txt", "w");
    int init = adns_init(state, adns_if_none, log_file);
    
    const char owner[MAX_CHARS] = "www.google.com";
    void *context = NULL;
    int result = adns_submit(state, owner, adns_r_a, adns_if_none, context, &query);

    adns_answer *answer;
    int wait_res = adns_wait(state, &query, &answer, &context);

    // printf("Result: %d\n", init);
}