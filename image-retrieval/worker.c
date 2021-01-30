#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <math.h>
#include <float.h>
#include "worker.h"


/*
 * Read an image from a file and create a corresponding
 * image struct
 */

Image* read_image(char *filename) {
    Image *img;
    FILE *fp;
    fp = fopen(filename, "rb");

    char temp[3];
    fscanf(fp, "%s", temp);

    if (temp[0] != 'P' || temp[1] != '3') {
       fprintf(stderr, "Invalid image format (must be 'P3')\n");
       exit(1);
    }

    img = (Image *) malloc(sizeof(Image));

    fscanf(fp, "%d %d %d", &img->width, &img->height, &img->max_value);

    int num_pixs = img->width * img->height;
    img->p = (Pixel *)malloc(num_pixs * sizeof(Pixel));

    for(int i = 0; i < num_pixs; i++) {
        Pixel pix;
        fscanf(fp, "%d %d %d", &pix.red, &pix.green, &pix.blue);
        img->p[i] = pix;
    }

    fclose(fp);
    return img;
}

/*
 * Print an image based on the provided Image struct
 */

void print_image(Image *img) {
    printf("P3\n");
    printf("%d %d\n", img->width, img->height);
    printf("%d\n", img->max_value);

    for(int i=0; i<img->width*img->height; i++)
        printf("%d %d %d  ", img->p[i].red, img->p[i].green, img->p[i].blue);
    printf("\n");
}

/*
 * Compute the Euclidian distance between two pixels
 */
float eucl_distance (Pixel p1, Pixel p2) {
    return sqrt( pow(p1.red - p2.red,2 ) + pow( p1.blue - p2.blue, 2) + pow(p1.green - p2.green, 2));
}

/*
 * Compute the average Euclidian distance between the pixels
 * in the image provided by img1 and the image contained in
 * the file filename
 */

float compare_images(Image *img1, char *filename) {
    Image *img2 = read_image(filename);

    if(img2->width != img1->width || img2->height != img1->height) {
        return FLT_MAX;
    }

    int num_pixs = img1->width * img1->height;

    float sum = 0;
    for(int i = 0; i < num_pixs; i++) {
        sum = sum + eucl_distance(img1->p[i], img2->p[i]);
    }
    float distance = sum/(num_pixs);

    free(img2);
    return distance;
}

/* process all files in one directory and find most similar image among them
* - open the directory and find all files in it
* - for each file read the image in it
* - compare the image read to the image passed as parameter
* - keep track of the image that is most similar
* - write a struct CompRecord with the info for the most similar image to out_fd
*/
CompRecord process_dir(char *dirname, Image *img, int out_fd) {
    char path[PATHLENGTH];
    char *startdir = dirname;

    DIR *dirp;
    if((dirp = opendir(startdir)) == NULL) {
        perror("opendir");
        exit(1);
    }

    /* For each entry in the directory, eliminate . and .., and check
    * to make sure that the entry is a directory, then call run_worker
    * to process the image files contained in the directory.
    */

    struct dirent *dp;
    CompRecord CRec;
    strcpy(CRec.filename, "");
    CRec.distance = FLT_MAX;

    while((dp = readdir(dirp)) != NULL) {

        if(strcmp(dp->d_name, ".") == 0 ||
           strcmp(dp->d_name, "..") == 0 ||
           strcmp(dp->d_name, ".svn") == 0){
            continue;
        }
        strncpy(path, startdir, PATHLENGTH);
        strncat(path, "/", PATHLENGTH - strlen(path) - 1);
        strncat(path, dp->d_name, PATHLENGTH - strlen(path) - 1);

        struct stat sbuf;
        if(stat(path, &sbuf) == -1) {
            //This should only fail if we got the path wrong
            // or we don't have permissions on this entry.
            perror("stat");
            exit(1);
        }

        if(S_ISREG(sbuf.st_mode)) {
            if(compare_images(img, path) < CRec.distance) {
                strcpy(CRec.filename, path);
                CRec.distance = compare_images(img, path);
            }
        }
    }

    if(out_fd != 0) {
        char str[100];
        sprintf(str, "%f", CRec.distance);
        char text[sizeof(CRec.filename) + 101] = "";
        strncpy(text, CRec.filename, sizeof(CRec.filename));
        strncat(text, ":", sizeof(char) * 1);
        strncat(text, str, sizeof(char) * 100);
        write(out_fd, text, sizeof(text));
    }

    return CRec;
}