#include <stdio.h>

/*
 * Read an image from the standard input and set the red value of each pixel to
 * zero.
 */
void remove_red()
{
    char head[3];
    int col;
    int row;
    int pixel;
    scanf("%s %d %d %d", head, &col, &row, &pixel);
    printf("%s\n%d %d\n%d\n", head, col, row, pixel);

    int array[col*3];
    for(int i=0; i<row; i++) {
      for(int j=0; j<col*3; j+=3) {
        scanf("%d %d %d", &array[j], &array[j+1], &array[j+2]);
        array[j] = 0;
        printf("%d %d %d  ", array[j], array[j+1], array[j+2]);
      }
      printf("\n");
    }
}

/*
 * Read an image from the standard input and convert it from colour to black and white.
 */
void convert_to_black_and_white()
{
  char head[3];
  int col;
  int row;
  int pixel;
  scanf("%s %d %d %d", head, &col, &row, &pixel);
  printf("%s\n%d %d\n%d\n", head, col, row, pixel);

  int array[col*3];
  for(int i=0; i<row; i++) {
    for(int j=0; j<col*3; j+=3) {
      scanf("%d %d %d", &array[j], &array[j+1], &array[j+2]);
      int avg = (array[j] + array[j+1] + array[j+2]) / 3;
      array[j] = avg;
      array[j+1] = avg;
      array[j+2] = avg;
      printf("%d %d %d  ", array[j], array[j+1], array[j+2]);
    }
    printf("\n");
  }
}

/*
 * Read an image from the standard input and convert it to a square image.
 */
void instagram_square()
{
  char head[3];
  int col;
  int row;
  int pixel;
  scanf("%s %d %d %d", head, &col, &row, &pixel);
  int c_mar = 0;
  int r_mar = 0;
  int broken = 0;

  if(col<row) {
    r_mar = row-col;
    broken--;
  } else if(row<col) {
    c_mar = col-row;
    broken++;
  }

  printf("%s\n%d %d\n%d\n", head, col - c_mar, row - r_mar, pixel);
  int array[col*3];
  for(int i=0; i<row; i++) {
    for(int j=0; j<col*3; j+=3) {
      scanf("%d %d %d", &array[j], &array[j+1], &array[j+2]);

      if(broken == 1 && j/3 < (col - c_mar)) {
        printf("%d %d %d  ", array[j], array[j+1], array[j+2]);

      }
      else if(broken == -1 && i < row - r_mar) {
        printf("%d %d %d  ", array[j], array[j+1], array[j+2]);

      }
      else if(broken == 0) {
        printf("%d %d %d  ", array[j], array[j+1], array[j+2]);
      }
    }
    printf("\n");
  }
}
