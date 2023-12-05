#ifndef USER_H
#define USER_H

typedef struct User {
	struct User *next, *prev;
	char *name;
} User;

#endif
