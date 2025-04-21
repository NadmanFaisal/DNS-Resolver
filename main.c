#include <stdio.h>
#include <stdlib.h>
#include <adns.h>               // Library for dns resolving
#include <arpa/inet.h>
#include <netinet/in.h>

#define MAX_CHARS 256

// Method responsible for clearing the user buffer
void clear_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) { }
}

/*
Prints the IPv4 address of a given website domain. The method 
requires the adns state, the adns query, and the domain (in 
literal). 

Params:-
    - state: A pointer to the adns_state obj which is used to hold state of the resolver. 
    - query: A pointer to adns_query obj to hold the submitted query. 
    - string: The domain taken from the user input
*/
void print_ip4_addr(adns_state *state, adns_query *query, char *string) {
    void *context = NULL;

    // Submit an async DNS query for an IPv6 address
    int result = adns_submit(*state, string, adns_r_a, adns_if_none, context, query);

    adns_answer *answer;

    // Wait for the submitted query to complete and retrieve the asnwer
    int wait_res = adns_wait(*state, query, &answer, &context);

    // If the answer has been returned, IPv4 address is printed.
    if(wait_res == 0 && answer->status == adns_s_ok) {
        for (int i = 0; i < answer->nrrs; i++) {
            struct in_addr addr = answer->rrs.inaddr[i];
            printf("IP4 Address %d: %s\n", i + 1, inet_ntoa(addr));
        }
    }
}

/*
Prints the IPv6 address of a given website domain. The method 
requires the adns state, the adns query, and the domain (in 
literal). 

Params:-
    - state: A pointer to the adns_state obj which is used to hold state of the resolver. 
    - query: A pointer to adns_query obj to hold the submitted query. 
    - string: The domain taken from the user input
*/
void print_ip6_addr(adns_state *state, adns_query *query, char *owner) {
    void *context = NULL;

    // Submit an async DNS query for an IPv6 address
    int result = adns_submit(*state, owner, adns_r_aaaa, adns_if_none, context, query);
    
    adns_answer *answer;

    // Wait for the submitted query to complete and retrieve the asnwer
    int wait_res = adns_wait(*state, query, &answer, &context);
    
    // If the answer has been returned, IPv6 address is printed.
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

    /*
    Initializes the DNS resolver, with the flag 'adns_if_none' 
    to return a value if the request hasn't been resolved (without 
    retrying or blocking).
    */
    int init = adns_init(&state, adns_if_none, log_file);
    
    char owner[MAX_CHARS];

    while(owner[0] != 'x') {
        printf("Type in the domain address: ");
        scanf("%s", owner);
        clear_buffer();
    
        print_ip4_addr(&state, &query, owner);
        print_ip6_addr(&state, &query, owner);
    }

    fclose(log_file);
    adns_finish(state);
}