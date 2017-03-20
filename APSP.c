#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

#define inf INFINITY

void floyd_apsp(float* distances, int n) {
  int changed;

  for (int k = 0; k < n; k++) {
    changed = 0;
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        float detour = distances[i*n + k] + distances[k*n + j];
        if (detour < distances[i*n + j]) {
          distances[i*n + j] = detour;
          changed += 1;
        }
      }
    }
    if (changed == 0) break;
  }
}

int main() {
  float distances[16] = {
    0.0, inf, 3.0, inf,
    2.0, 0.0, inf, inf,
    inf, 7.0, 0.0, 1.0,
    6.0, inf, inf, 0.0
  };

  floyd_apsp(distances, 4);

  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      printf("%i ", (int)distances[i*4 + j]);
    }
    printf("\n");
  }

  return 0;
}
