#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Playlist{
	char songName[101];
	char artistName[101];
	char duration[101];
	struct Playlist *prev;
	struct Playlist *next;
};

struct Playlist *head = NULL;
struct Playlist *tail = NULL;

void menu(){
	printf("Welcome to PlaylistMaker123!!!\n");
	printf("Here is our features\n");
	printf("1. Display Current Playlist\n");
	printf("2. Add a new song to Playlist\n");
	printf("3. Add a new song at certain Position\n");
	printf("4. Delete first song in Playlist\n");
	printf("5. Delete last song in Playlist\n");
	printf("6. Delete a song in certain Position\n");
	printf("7. Delete entire Playlist\n");
	printf("8. Reverse entire Playlist\n");
	printf("9. Choose this for a surprise!\n");
	printf("10. Exit\n");
}

struct Playlist *addSong(char songName[], char artistName[], char duration[]){
	struct Playlist *newSong = (struct Playlist*)malloc(sizeof(struct Playlist));
	strcpy(newSong->songName, songName);
	strcpy(newSong->artistName, artistName);
	strcpy(newSong->duration, duration);
	newSong->next = NULL;
	newSong->prev = NULL;
	return newSong;
}

struct Playlist *addEmpty(char songName[], char artistName[], char duration[]){
	struct Playlist *empty = (struct Playlist*)malloc(sizeof(struct Playlist));
	strcpy(empty->songName, songName);
	strcpy(empty->artistName, artistName);
	strcpy(empty->duration, duration);
	empty->next = NULL;
	empty->prev = NULL;
	head = empty;
	return head;
}

struct Playlist *addBeginning(char songName[], char artistName[], char duration[]){
	struct Playlist *beginning = addSong(songName, artistName, duration);
	beginning->next = head;
	head->prev = beginning;
	head = beginning;
	return head;
}

struct Playlist *addEnd(char songName[], char artistName[], char duration[]){
	struct Playlist *end = addSong(songName, artistName, duration);
	struct Playlist *temp;
	temp = head;
	while(temp->next != NULL){
		temp = temp->next;
	}
	temp->next = end;
	end->prev = temp;
	return head;
}

struct Playlist *createSongs(){
	char songName[101];
	char artistName[101];
	char duration[101];
	int destiny;
	do{
		printf("If you wish to stop adding type '0'\n");
		printf("Enter Song Name: ");
		scanf("%s", songName);
		printf("Enter the Artist Name: ");
		scanf("%s", artistName);
		printf("Enter the song duration: ");
		scanf("%s", duration);
		if(head == NULL){
			head = addEmpty(songName, artistName, duration);
			tail = head;
		} else {
			tail = addEnd(songName, artistName, duration);
		}
		printf("Song successfully added!\n");
		printf("Do you wish to continue? ");
		scanf("%d", &destiny);
		getchar();
		system("cls");
	} while (destiny != 0);
}

struct Playlist *certainPos() {
    char songName[101];
    char artistName[101];
    char duration[101];
    int position;

    printf("Enter Song Name: ");
    scanf("%s", songName);
    printf("Enter the Artist Name: ");
    scanf("%s", artistName);
    printf("Enter the song duration: ");
    scanf("%s", duration);
    printf("Enter The Position The Song will be inserted at: ");
    scanf("%d", &position);

    struct Playlist *SonginCertainPos = addSong(songName, artistName, duration);
    struct Playlist *temp = head;
    struct Playlist *prev = NULL;

    while (position > 1 && temp != NULL) {
        prev = temp;
        temp = temp->next;
        position--;
    }

    if (prev != NULL) {
        prev->next = SonginCertainPos;
        SonginCertainPos->prev = prev;
    } else {
        head = SonginCertainPos;
    }

    if (temp != NULL) {
        temp->prev = SonginCertainPos;
        SonginCertainPos->next = temp;
    } else {
        tail = SonginCertainPos;
    }

    return head;
}

void pop_head(){
	struct Playlist *temp = head;
	head = head->next;
	head->prev = NULL;
	free(temp);	
}

void pop_tail(){
    struct Playlist *toBeDel = head;
    struct Playlist *temp;
    while(toBeDel->next != NULL){
    	toBeDel = toBeDel->next;
	}
	temp = toBeDel->prev;
	temp->next = NULL;
	free(toBeDel);
}

struct Playlist *deleteAtCertainPos() {
    int position;
    printf("Enter the Song's position in the playlist to delete: ");
    scanf("%d", &position);

    struct Playlist *temp = head;
    struct Playlist *temp2;

    if (position == 1) {
        pop_head();
    } else {
        while (position > 1 && temp != NULL) {
            temp = temp->next;
            position--;
        }

        if (temp->next == NULL) {
            pop_tail();
        } else {
            temp2 = temp->prev;
            temp2->next = temp->next;
            temp->next->prev = temp2;
            free(temp);
            temp = NULL;
        }
    }

    printf("Playlist has been successfully updated!\n");
    return head;
}


void deletePlaylist(){
	struct Playlist *temp = head;
	struct Playlist *nextInLine;
	while(temp != NULL){
		nextInLine = temp->next;
		free(temp);
		temp = nextInLine;
	}
	head = NULL;
	tail = NULL;
}

struct Playlist *reversePlaylist(){
	struct Playlist *temp1 = head;
	struct Playlist *temp2= temp1->next;
	temp1->next = NULL;
	temp1->prev = temp2;
	
	while(temp2 != NULL){
		temp2->prev = temp2->next;
		temp2->next = temp1;
		temp1 = temp2;
		temp2 = temp2->prev;
	}
	head = temp1;
	return head;
}

void print(){
	struct Playlist *currSong = head;
	if(currSong == NULL){
		printf("The Playlist is Empty\n");
	} else {
		printf("Here is your current Playlist:\n");
		while(currSong != NULL){
			printf("%s - %s - %s\n", currSong->songName, currSong->artistName, currSong->duration);
			currSong = currSong->next;
		}
	}
}

void surprise(){
	char asciiArt[] =
        "                                                                                           \n"
        "                                                                                           \n"
        "                                                                                           \n"
        "                                                             -#                            \n"
        "                                                         .-*@@%                            \n"
        "                                                ..:-=+*#@@@@@@+                            \n"
        "                                     :==+*##%%@@@@@@@@@@@@@@@%.                            \n"
        "                                .-*%@@@@@@@@@@@@@@@@@@@@@@@@%.                             \n"
        "                              =#@@@@@@@@@@@@@@@@@@@@@@@@@@%=.                              \n"
        "                           .*@@@@%#*#**@@@@@@@@@@@@@%%#*=:                                 \n"
        "                         .*@@*:.      :@@@@@@@%.                                            \n"
        "                        -@@*.         %@@@@@@@:            .:                              \n"
        "                       +@@+          -@@@@@@@:           +%@@@* :%@#                       \n"
        "                      -@@@           %@@@@@@=           .%@@@@@@*%@@.                      \n"
        "                      %@@@.         =@@@@@@+     .::.    .*@@@@@@@#:                       \n"
        "                     .@@@@%.        %@@@@@#   :*@@@@@%:    %@@@@%                          \n"
        "                      @@@@@@#=-    :@@@@@@.  -@@@@@@@@@    =@@@@#                          \n"
        "                      +@@@@@@+.    +@@@@@+   %@@%:.@@@@    =@@@@=                          \n"
        "                       -#@#-       #@@@@@:  .@@@* -@@@*    #@@@@.                          \n"
        "                                   %@@@@@    %@@%:@@@%    =@@@@-                           \n"
        "                                   *@@@@@.   -@@@@@@*    =@@@@-                            \n"
        "                                   :@@@@@%.   +@@@@-   -%@@@@-                             \n"
        "                                    :%@@@@@%##@@%@@@%%@@@@@*.                              \n"
        "                                      :+*%%@%*=. :*%@@@%*=.                                \n"
        "                                                                                           \n";

    printf("%s", asciiArt);
}

int main (){
	int input;
	char choice;
	do{
		menu();
		printf("Your Choice: ");
		scanf("%d", &input);
		getchar();	
		switch(input){
			case 1:
				system("cls");
				print();
				break;
			case 2:
				system("cls");
				createSongs();
				break;
			case 3:
				system("cls");
				certainPos();
				break;
			case 4:
				system("cls");
				pop_head();
				printf("Playlist has been successfully updated!\n");
				break;
			case 5:
				system("cls");
				pop_tail();
				printf("Playlist has been successfully updated!\n");
				break;
			case 6:
				system("cls");
				deleteAtCertainPos();
				break;
			case 7:
				system("cls");
				deletePlaylist();
				printf("Playlist Completely Erased from Humanity's Historical Record\n");
				break;
			case 8:
				system("cls");
				reversePlaylist();
				printf("Playlist has been Reversed\n");
				break;
			case 9:
				system("cls");
				surprise();
				break;
			case 10:
				system("cls");
				printf("Exiting PlaylistMaker123. Thank you for using my program!\n");
                break;
            default:
                printf("Invalid choice! Please choose a valid option.\n");
                break;		
		}
		if(input != 10) {
        	printf("Do you wish to continue using the program? (y/n): ");
        	scanf(" %c", &choice);
        	if(choice == 'y'){
            	system("cls");
        	}
        }
	} while(input != 10);
	
	return 0;
}
