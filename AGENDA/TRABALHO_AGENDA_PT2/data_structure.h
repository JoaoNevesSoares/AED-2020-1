struct Node{

    char nome[50];
    struct Node* next;
    struct Node* prev;

};

//Doubly Linked list // Queue
struct List{
    struct Node* head_ref;
    struct Node* last_ref;

};

//Buffer principal do código
struct Agenda{

    char nome_holder[50];
    int int_holder;
    int int_holder_2;
    struct List* lista_sentinel;
    struct List* queue_sentinel;
};

struct List* create_list();
struct Node* new_node(char* nome);
void append(struct List* ref,struct Node* new_node);
struct Node* search(struct List* reference, char nome[]);
void remove_nome(struct List* reference,char nome[]);
void show_queue(struct List* ref);
struct Node* dequeue(struct List* queue_ref);
void enqueue(struct List* queue_ref, struct Node* new_node);
void print_Queue(struct List* queue_ref);
void free_list(struct List* reference);
