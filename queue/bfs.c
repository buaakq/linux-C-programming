#include <stdio.h>

#define STACK_SIZE 1000
#define MAX_ROW 5 
#define MAX_COL 5

struct path
{
	int x;
	int y;
};

struct path stack[STACK_SIZE];
typedef struct path item_t;
int head = 0;
int tail = 0;

int maze[MAX_ROW][MAX_COL] = {
	0, 1, 0, 0, 0,
	0, 1, 0, 1, 0,
	0, 0, 0, 0, 0,
	0, 1, 1, 1, 0,
	0, 0, 0, 1, 0,
};

void push(item_t i)
{
	stack[tail] = i;
	tail ++;
}

void pop()
{
	head++;
}

item_t top()
{
	return stack[head];
}

item_t last()
{
	return stack[tail-1];
}

int empty()
{
	return head == tail;
}

void print_buf(int index)
{
	if (index == 3)
		return;
	print_buf(index+1);
	printf("%d\n", index);
}

void access(item_t node)
{
	printf("Will access node (%d, %d)\n", node.x, node.y);
	int x = node.x;
	int y = node.y;
	maze[x][y] = 2;
	push(node);
}

int find_next(item_t *next)
{
	item_t curr = top();
	int x = curr.x;
	int y = curr.y;
	
	if (y < 4 && maze[x][y+1] == 0){
		next->x = x;
		next->y = y + 1;
		return 1;
	}
	else if (x > 0 && maze[x-1][y] == 0){
		next->x = x - 1;
		next->y = y;
		return 1;
	}
	else if (y > 0 && maze[x][y-1] == 0){
		next->x = x;
		next->y = y - 1;
		return 1;
	}
	else if (x < 4 && maze[x+1][y] == 0){
		next->x = x + 1;
		next->y = y;
		return 1;
	} 
	
	return 0;
}

int main()
{
	item_t root = {.x = 0, .y = 0};
	access(root);
	while(!empty())
	{
		item_t next;
		int found = find_next(&next);
		if (!found){
			pop();
		}
		else{
			access(next);
			if (last().x == 4 && last().y == 4) {
				printf("Go out!\n");
				break;
			}
		}
	}
	//print_stack_reverse();
	return 0;
}
