#include <stdio.h>
#include <stdlib.h>

int findOptimal(int pages[], int n, int frame[], int fn, int index) {
    int farthest = index, pos = -1;
    for (int i = 0; i < fn; i++) {
        int j;
        for (j = index; j < n; j++) {
            if (frame[i] == pages[j]) {
                if (j > farthest) {
                    farthest = j;
                    pos = i;
                }
                break;
            }
        }
        if (j == n) return i; // Not used again
    }
    return (pos == -1) ? 0 : pos;
}

void FIFO(int pages[], int n, int fn) {
    int frame[fn], count = 0, index = 0;
    for (int i = 0; i < fn; i++) frame[i] = -1;

    for (int i = 0; i < n; i++) {
        int flag = 0;
        for (int j = 0; j < fn; j++) {
            if (frame[j] == pages[i]) {
                flag = 1;
                break;
            }
        }
        if (!flag) {
            frame[index] = pages[i];
            index = (index + 1) % fn;
            count++;
        }
    }
    printf("FIFO Page Faults: %d\n", count);
}

void LRU(int pages[], int n, int fn) {
    int frame[fn], count = 0, recent[fn];
    for (int i = 0; i < fn; i++) frame[i] = -1;

    for (int i = 0; i < n; i++) {
        int flag = 0;
        for (int j = 0; j < fn; j++) {
            if (frame[j] == pages[i]) {
                flag = 1;
                recent[j] = i;
                break;
            }
        }
        if (!flag) {
            int min = 9999, pos = -1;
            for (int j = 0; j < fn; j++) {
                if (frame[j] == -1) {
                    pos = j;
                    break;
                }
                if (recent[j] < min) {
                    min = recent[j];
                    pos = j;
                }
            }
            frame[pos] = pages[i];
            recent[pos] = i;
            count++;
        }
    }
    printf("LRU Page Faults: %d\n", count);
}

void Optimal(int pages[], int n, int fn) {
    int frame[fn], count = 0;
    for (int i = 0; i < fn; i++) frame[i] = -1;

    for (int i = 0; i < n; i++) {
        int flag = 0;
        for (int j = 0; j < fn; j++) {
            if (frame[j] == pages[i]) {
                flag = 1;
                break;
            }
        }
        if (!flag) {
            int pos = -1;
            for (int j = 0; j < fn; j++) {
                if (frame[j] == -1) {
                    pos = j;
                    break;
                }
            }
            if (pos == -1) pos = findOptimal(pages, n, frame, fn, i + 1);
            frame[pos] = pages[i];
            count++;
        }
    }
    printf("Optimal Page Faults: %d\n", count);
}

int main() {
    int n, fn;
    printf("Enter number of pages: ");
    scanf("%d", &n);
    int pages[n];
    printf("Enter the reference string: ");
    for (int i = 0; i < n; i++) scanf("%d", &pages[i]);
    printf("Enter number of frames: ");
    scanf("%d", &fn);

    FIFO(pages, n, fn);
    LRU(pages, n, fn);
    Optimal(pages, n, fn);

    return 0;
}
