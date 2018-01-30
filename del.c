#include <stdio.h>

int main(int argc, char const *argv[]) {
      char str[10] = "literal";
      char *s = str;
      s[0] = 'k';
      printf("%s\n", str);
      return 0;
}
