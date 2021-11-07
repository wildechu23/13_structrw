#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

typedef struct pop_entry {
    int year;
    int population;
    char boro[15];
} pop_entry;

void read_csv();
void read_data();
void print_entry(pop_entry*);
void add_data();
void update_data();

int main(int argc, char *argv[]) {
	char flag[100];

	if (argc > 1) {
		strcpy(flag, argv[1]);
	} else {
        printf("Please enter a flag: ");
        fgets(flag, sizeof(flag), stdin);
        // printf("Flag-1: %c", flag[strlen(flag)-1]);
        if(flag[strlen(flag)-1] == '\n') {
            flag[strlen(flag)-1] = '\0';
        }
        printf("\n");
	}
    if(strcmp(flag, "-read_csv") == 0) {
        read_csv();
    } else if(strcmp(flag, "-read_data") == 0) {
        read_data();
    } else if(strcmp(flag, "-add_data") == 0) {
        add_data();
    } else if(strcmp(flag, "-update_data") == 0) {
        update_data();
    } else {
        printf("Unrecognized flag");
    }


    return 0;
} 

void print_entry(pop_entry* entry) {
    printf("Year: %d\tBoro: %s\tPop: %d\n", entry->year, entry->boro, entry->population);
}

void read_csv() {
    int file = open("nyc_pop.csv", O_RDONLY);
    int data_file = data_file = open("data", O_CREAT | O_WRONLY | O_TRUNC, 0644);
    int bytes_read;
    int l;
    char buffer[100];
    char byte[2];
    char boros[5][15];
    byte[1] = '\0';
    int year;
    for(l = 0; l < 24; l++) { 
        pop_entry entries[5];
        int i = 0;
        byte[0] = '\0';
        while(i < 100 && *byte != '\n') {
            bytes_read = read(file, byte, 1);
            if(bytes_read == 0) break;
            // printf("%s ", byte);
            buffer[i] = byte[0];
            i++;
        }
        buffer[i] = '\0';

        // printf("\nBuffer: %s\n", buffer);
        if(l == 0) {
            sscanf(buffer, "Year,%[^,],%[^,],%[^,],%[^,],%[^\n]", boros[0], boros[1], boros[2], boros[3], boros[4]);
        } else {
            sscanf(buffer, "%d,%d,%d,%d,%d,%d\n", &year, &entries[0].population, 
                &entries[1].population, &entries[2].population, 
                &entries[3].population, &entries[4].population);

            int j;
            for(j = 0; j < 5; j++)  {
                strcpy(entries[j].boro, boros[j]);
                entries[j].year = year;
            }
            
            int bytes_written = write(data_file, entries, sizeof(entries));
        }

    }
    
    close(file);
    close(data_file);
}

void read_data() {
    int file = open("data", O_RDONLY);
    pop_entry buffer;
    int bytes_read = sizeof(buffer);
    int i = 0;
    while(bytes_read == sizeof(buffer)) {
        bytes_read = read(file, &buffer, sizeof(buffer));
        if(bytes_read == sizeof(buffer)) {
            printf("%d: ", i);
            print_entry(&buffer);
            i++;
        }
    }
}

void add_data() {
    int file = open("data", O_CREAT | O_WRONLY, 0644);
    char buffer[100];
    pop_entry entry;
    printf("Please enter \"Year Boro Pop\": ");
    fgets(buffer, sizeof(buffer), stdin);
    if(buffer[strlen(buffer)-1] == '\n') {
        buffer[strlen(buffer)-1] = '\0';
    }
    printf("\n");
    sscanf(buffer, "%d %s %d", &entry.year, entry.boro, &entry.population);
    lseek(file, 0, SEEK_END);
    int bytes_written = write(file, &entry, sizeof(entry));
}

void update_data() {
    int file = open("data", O_CREAT | O_WRONLY, 0644);
    pop_entry entry;
    int i;
    char e[10];
    char buffer[100];
    read_data();
    printf("Please enter entry to update: ");
    fgets(e, sizeof(e), stdin);
    i = atoi(e);
    // printf("%d", i);

    printf("Please enter \"Year Boro Pop\": ");
    fgets(buffer, sizeof(buffer), stdin);
    if(buffer[strlen(buffer)-1] == '\n') {
        buffer[strlen(buffer)-1] = '\0';
    }
    sscanf(buffer, "%d %s %d", &entry.year, entry.boro, &entry.population);
    lseek(file, i*sizeof(pop_entry), 0);
    int bytes_written = write(file, &entry, sizeof(entry));
}