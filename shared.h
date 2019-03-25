//Nathan Roehl
//homework 8

typedef struct {
char* answer;
char* hint;
} Answer;

const int BIGBUFF = 1024;
struct sockaddr serverSocket = {AF_UNIX, "server1"};
socklen_t sLength = sizeof(struct sockaddr) + 8;
