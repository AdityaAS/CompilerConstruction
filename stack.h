struct stack{
	struct Node* head;
};

struct stack* getStack();
void push(struct stack* st,char* name);
struct Node* pop(struct stack* st);
struct Node* top(struct stack* st);
bool checkEmpty(struct stack * st);