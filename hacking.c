#include <stdio.h>
#include <string.h>

int func_one(){
  printf("This is a function\n");
  return 1;
}

int func_two(){
  printf("This is a function two");
  return 2;
  }
int main(){
  int value;
  int (*function_ptr) ();

  function_ptr = func_one;
  printf("function_ptr is 0x%08x\n", function_ptr);
  value = functioin_ptr();
  printf("value returned was %d\n", value);

  function_ptr = func_two;
  printf("function_ptr is 0x%08x\n", function_ptr);
  value = function_ptr();
  printf("value returned was %d\n", value);



}
