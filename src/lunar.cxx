
#include<cstdio>

#include<Gint.h>

int main(int argc, char **argv) {
  Gint *input = Gint::instance(argc,argv);
  input->Run(false);
  return 0;
}
