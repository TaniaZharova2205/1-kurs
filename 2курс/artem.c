#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>

struct file_properties {
    char filename[256];
    unsigned long filesize;
};

size_t partition(struct file_properties *arr, int l, int r) {
    if (r == l)
        return l;

    int pivot = (r + l) / 2;
    char temp[256];
    unsigned long temp2;
    strcpy(temp, arr[r - 1].filename);
    temp2 = arr[r - 1].filesize;
    strcpy(arr[r - 1].filename, arr[pivot].filename);
    arr[r - 1].filesize = arr[pivot].filesize;
    strcpy(arr[pivot].filename, temp);
    arr[pivot].filesize = temp2;

    int  i = l, j = l;
    while (j != r) {
        if (arr[j].filesize > arr[r - 1].filesize)
            ++j;
        else {
            strcpy(temp, arr[i].filename);
            temp2 = arr[i].filesize;
            strcpy(arr[i].filename, arr[j].filename);
            arr[i].filesize = arr[j].filesize;
            strcpy(arr[j].filename, temp);
            arr[j].filesize = temp2;
            ++j;
            ++i;
        }
    }
    return i - 1;
}

void quickSort(struct file_properties *arr, int l, int r) {
    if (l < r) {
        size_t m = partition(arr, l, r);
        quickSort(arr, m + 1, r);
        quickSort(arr, l, m);
    }
}

int main() {
    DIR *d;
    struct dirent *dir;
    struct file_properties *files;
    size_t files_size = 1;
    size_t files_num = 0;

    if ((files = (struct files_size *)malloc(sizeof(struct file_properties) * files_size)) == NULL)
        return 0;

    d = opendir(".");
    if (d) {
        while ((dir = readdir(d)) != NULL) {
            if (dir->d_type == DT_REG){
                if (files_num >= files_size) {
                    files_size *= 2;

                    if ((files = (struct files_size *)realloc(files, sizeof(struct file_properties) * files_size)) == NULL)
                        return 0;

                }
                strcpy(files[files_num].filename, dir->d_name);
                struct stat buff;
                stat(dir->d_name, &buff);
                files[files_num].filesize = buff.st_size;
                ++files_num;
            }
        }
        closedir(d);
    }

    unsigned long min = -1;
    quickSort(files, 0, files_num);
    for (size_t i = 0; i < files_num; i++)
        printf("%s     %lu\n", files[i].filename, files[i].filesize);

    return (0);
}