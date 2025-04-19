#include <stdio.h>
#include <stdlib.h>
#include <adns.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define MAX_CHARS 256

void clear_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) { }
}

void print_ip4_addr(adns_state *state, adns_query *query, char *owner) {
    void *context = NULL;
    int result = adns_submit(*state, owner, adns_r_a, adns_if_none, context, query);

    adns_answer *answer;
    int wait_res = adns_wait(*state, query, &answer, &context);

    if(wait_res == 0 && answer->status == adns_s_ok) {
        for (int i = 0; i < answer->nrrs; i++) {
            struct in_addr addr = answer->rrs.inaddr[i];
            printf("IP4 Address %d: %s\n", i + 1, inet_ntoa(addr));
        }
    }
}

void print_ip6_addr(adns_state *state, adns_query *query, char *owner) {
    void *context = NULL;
    int result = adns_submit(*state, owner, adns_r_aaaa, adns_if_none, context, query);
    
    adns_answer *answer;
    int wait_res = adns_wait(*state, query, &answer, &context);
    
    if(wait_res == 0 && answer->status == adns_s_ok) {
        for (int i = 0; i < answer->nrrs; i++) {
            char ipv6[INET6_ADDRSTRLEN];
            inet_ntop(AF_INET6, &answer->rrs.in6addr[i], ipv6, sizeof(ipv6));
            printf("IPv6 Address %d: %s\n", i + 1, ipv6);
        }
    }
}

int main(int argc, char **argv) {
    adns_state state;
    adns_query query;
    FILE *log_file = fopen("log.txt", "w");
    int init = adns_init(&state, adns_if_none, log_file);
    
    char owner[MAX_CHARS];
    printf("Type in the domain address: ");
    scanf("%s", owner);
    clear_buffer();

    print_ip4_addr(&state, &query, owner);
    print_ip6_addr(&state, &query, owner);
}