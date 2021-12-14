#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* read_file(char *file_name) {
  FILE *input = fopen(file_name, "r");
  char *input_data;
  size_t size;

  if (input) {
    fseek(input, 0, SEEK_END);
    size_t size = ftell(input);
    fseek(input, 0, SEEK_SET);

    input_data = (char *)malloc(size);
    fread(input_data, size, 1, input);

    fclose(input);
  }

  return input_data;
}

int part_one() {
  char *input_data = read_file("input/day1-input");  
  char *depths = strtok(input_data, "\n");
  int prev_depth = 0;
  int increase_count = 0;

  while (depths != NULL) {
    int depth = atoi(depths);

    if ((prev_depth) && depth > prev_depth) {
      increase_count++;
    }

    prev_depth = depth;
    depths = strtok(NULL, "\n");
  }

  return increase_count;
}

/* In this problem, we want to compare a sliding window of 3 elements.
 * Since for each set of 3 elements, the middle two elements are the same,
 * we should be able to only compare elements 3 spaces apart, e.g. elements 0 and 3
 */
int part_two() {
  char *input_data = read_file("input/day1-test");
  char *depths = strtok(input_data, "\n");
  int measurements[3] = {0, 0, 0};
  int prev_sum = 0;
  int increase_count = 0;
  int curr_index = 0;
  int reset_index = curr_index + 3;

  // Populate initial 3 measurement window
  for (int i = 0; i < reset_index; i++) {
    measurements[i] = atoi(depths);
    depths = strtok(NULL, "\n");
  }
  curr_index += 3;
  reset_index = curr_index + 3;
  prev_sum = depths[0] + depths[1] + depths[2];

  while (depths != NULL) {
    // reset the measurements array by shifting all values left,
    // set third vlaue to 0
    measurements[0] = measurements[1];
    measurements[1] = measurements[2];
    measurements[2] = 0;

    measurements[2] = atoi(depths);

    int sum = measurements[0] + measurements[1] + measurements[2];

    if (sum > prev_sum) {
      increase_count++;
    }

    prev_sum = sum;

    depths = strtok(NULL, "\n");
  }

  return increase_count;
}

int main() {
  int part_one_result = part_one();
  fprintf(stdout, "Part 1: Depth increases %d times\n", part_one_result);
  int part_two_result = part_two();
  fprintf(stdout, "Part 2: Depth increases %d times\n", part_two_result);
}
