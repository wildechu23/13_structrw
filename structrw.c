#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

typedef struct pop_entry {
    int year;
    int population;
    char boro[15];
} pop_entry;



int main(int argc, char *argv[]) {
    int file = open("nyc_pop.csv", O_RDONLY);

    pop_entry entries[5];
    char buffer[100];
    int year;
    int bytes_read = read(file, buffer, 100);
    sscanf(buffer, "%d,%d,%d,%d,%d,%d", year, entries[1].population, entries[2].populatin, entries[3].population, entries[4].population, entries[5].population;

    printf("%d", entries[1].year);

    return 0;
}
