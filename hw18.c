#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#define READ 0
#define WRITE 1

int main() {
		int pipe1[2];
		int pipe2[2];
		pipe(pipe1);
		pipe(pipe2);

		int f = fork();

		if(f) {
			close(pipe1[READ]);
			close(pipe2[WRITE]);

			while(1) {
				printf("Enter a string. Type \"exit\" to exit the program: ");
				char input[100];
				fgets(input, sizeof(input), stdin);

				input[strcspn(input, "\n")] = '\0';

				if(strcmp(input, "exit") == 0) {
					return 0;
				}

				write(pipe1[WRITE], input, sizeof(input));

				read(pipe2[READ], input, sizeof(input));
				printf("New string: %s\n", input);
			}
		}

		else {
			close(pipe1[WRITE]);
			close(pipe2[READ]);

			char temp[100];

			while(1) {
				while(read(pipe1[READ], temp, sizeof(temp))) {
					//Capitalizes input string.
					int i = 0;
					while(temp[i]) {
						if(temp[i] >= 'a' && temp[i] <= 'z') {
							temp[i] = temp[i] - 32;
						}
						i++;
					}
					write(pipe2[WRITE], temp, sizeof(temp));
				}
			}
		}

	return 0;
}
