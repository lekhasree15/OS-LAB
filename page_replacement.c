#include <stdio.h>

void FIFO(int pages[], int n, int f) {
    int frame[20], i, j, found, index = 0, faults = 0;

    for(i = 0; i < f; i++)
        frame[i] = -1;

    for(i = 0; i < n; i++) {
        found = 0;

        for(j = 0; j < f; j++) {
            if(frame[j] == pages[i]) {
                found = 1;
                break;
            }
        }

        if(!found) {
            frame[index] = pages[i];
            index = (index + 1) % f;
            faults++;
        }
    }

    printf("FIFO Page Faults = %d\n", faults);
}

void LRU(int pages[], int n, int f) {
    int frame[20], time[20];
    int i, j, found, faults = 0;
    int count = 0, min, pos;

    for(i = 0; i < f; i++) {
        frame[i] = -1;
        time[i] = 0;
    }

    for(i = 0; i < n; i++) {
        found = 0;

        for(j = 0; j < f; j++) {
            if(frame[j] == pages[i]) {
                count++;
                time[j] = count;
                found = 1;
                break;
            }
        }

        if(!found) {
            min = time[0];
            pos = 0;

            for(j = 1; j < f; j++) {
                if(time[j] < min) {
                    min = time[j];
                    pos = j;
                }
            }

            count++;
            frame[pos] = pages[i];
            time[pos] = count;
            faults++;
        }
    }

    printf("LRU Page Faults = %d\n", faults);
}

int findOptimal(int pages[], int n, int frame[], int f, int index) {
    int i, j, farthest = index, pos = -1;

    for(i = 0; i < f; i++) {
        for(j = index; j < n; j++) {
            if(frame[i] == pages[j]) {
                if(j > farthest) {
                    farthest = j;
                    pos = i;
                }
                break;
            }
        }

        if(j == n)
            return i;
    }

    if(pos == -1)
        return 0;

    return pos;
}

void Optimal(int pages[], int n, int f) {
    int frame[20];
    int i, j, found, faults = 0, pos;

    for(i = 0; i < f; i++)
        frame[i] = -1;

    for(i = 0; i < n; i++) {
        found = 0;

        for(j = 0; j < f; j++) {
            if(frame[j] == pages[i]) {
                found = 1;
                break;
            }
        }

        if(!found) {
            pos = findOptimal(pages, n, frame, f, i + 1);
            frame[pos] = pages[i];
            faults++;
        }
    }

    printf("Optimal Page Faults = %d\n", faults);
}

int main() {
    int pages[50], n, f, choice, i;

    printf("Enter number of pages: ");
    scanf("%d", &n);

    printf("Enter page reference string:\n");
    for(i = 0; i < n; i++)
        scanf("%d", &pages[i]);

    printf("Enter number of frames: ");
    scanf("%d", &f);

    printf("\n1. FIFO\n2. LRU\n3. Optimal\n4. All\n");
    printf("Enter choice: ");
    scanf("%d", &choice);

    switch(choice) {
        case 1:
            FIFO(pages, n, f);
            break;

        case 2:
            LRU(pages, n, f);
            break;

        case 3:
            Optimal(pages, n, f);
            break;

        case 4:
            FIFO(pages, n, f);
            LRU(pages, n, f);
            Optimal(pages, n, f);
            break;

        default:
            printf("Invalid Choice\n");
    }

    return 0;
}
