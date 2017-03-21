#include <sys/time.h>
#include <stdlib.h>

struct timeval t_start, t_stop, t_spent;

void set_timer() {
  gettimeofday(&t_start, NULL);
}

double get_timer() {
  gettimeofday(&t_stop, NULL);
  timersub(&t_stop, &t_start, &t_spent);
  return 1000.0 * t_spent.tv_sec + t_spent.tv_usec / 1000.0;
}
