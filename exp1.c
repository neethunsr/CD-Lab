#include <stdio.h>
#include <stdlib.h>

typedef struct Transition Transition_t;
typedef struct State State_t;

struct State {
    char name;
    Transition_t *transitionListHead;
    State_t *next; 
};

struct Transition {
    State_t *nextState;
    char symbol;
    Transition_t *next; 
};

State_t*
createState(char symbol) {
    State_t *s = malloc(sizeof(State_t));
    
    s->name = symbol;
    s->next = NULL;
    s->transitionListHead = NULL;

    return s;
}

State_t*
lookupOrCreateState(State_t *HEAD, char symbol) {
    State_t *prevState = HEAD;

    while(prevState->name != symbol && prevState->next != NULL) {
        prevState = prevState->next;
    }
    
    if(prevState->name == symbol) {
        return prevState;
    }

    State_t *s = createState(symbol);
    prevState->next = s;

    return s;
}

Transition_t*
createTransition(State_t *dest, char symbol) {
    Transition_t *t = malloc(sizeof(Transition_t));

    t->nextState = dest;
    t->symbol = symbol;
    t->next = NULL;

    return t;
}

State_t*  
addTransition(State_t *HEAD, char sourceState, char destState, char inputSymbol) {
    State_t *source = NULL, *dest = NULL;
    Transition_t *prevTransition, *t;
    
    if(HEAD == NULL) {
        source = createState(sourceState);
        dest = createState(destState);

        HEAD = source;
        HEAD->next = dest;
    } else {
        source = lookupOrCreateState(HEAD, sourceState);
        dest = lookupOrCreateState(HEAD, destState);
    }

    if(source == NULL || dest == NULL) {
        fprintf(stderr, "Failed to add transition\n");
        exit(0);
    }

    t = createTransition(dest, inputSymbol);

    if(source->transitionListHead == NULL) {
        source->transitionListHead = t;
    }
    else {
        prevTransition = source->transitionListHead;
        while(prevTransition->next != NULL) {
            prevTransition = prevTransition->next;
        }

        prevTransition->next = t;
    }

    return HEAD;
}

void
printEpsilonTransitionHelper(State_t *node) {
    // TODO: Remove infinite loop on cycles
    Transition_t *t = node->transitionListHead;

    while(t != NULL) {
        if(t->symbol == 'e') {
            fprintf(stdout, "%c, ", t->nextState->name);
            printEpsilonTransitionHelper(t->nextState);
        }

        t = t->next;
    }
}

void 
printEpsilonTransitions(State_t *node) {
    if(node == NULL) return;

    fprintf(stdout, "%c: { %c, ", node->name, node->name);
    printEpsilonTransitionHelper(node);
    fprintf(stdout, "}\n");

    printEpsilonTransitions(node->next);
}

void
freeTransitions(Transition_t *node) {
    if(node == NULL) return;
    freeTransitions(node->next);
    free(node);
}

void
freeMemory(State_t *node) {
    if(node == NULL) return;

    if(node->next != NULL) return freeMemory(node->next);

    freeTransitions(node->transitionListHead);
    free(node);
}

int main() {
    int noOfTransitions;
    char sourceState, destState, inputSymbol; 
    State_t *HEAD = NULL;

    fprintf(stdout, "Enter number of transitions: ");
    scanf("%d", &noOfTransitions);
    
    fprintf(
        stdout, 
        "Enter transition in the format\n"
        "Start State ---- End State ---- Symbol\n"
        
    );

    while(noOfTransitions--) {
        scanf(" %c", &sourceState);
        scanf(" %c", &destState);
        scanf(" %c", &inputSymbol);
        HEAD = addTransition(HEAD, sourceState, destState, inputSymbol);
    }

    printEpsilonTransitions(HEAD);
    freeMemory(HEAD);
}
