/* To compile this program:
 *   gcc cs3210_f2025_pa1_stoopid_sort.c -o cs3210_f2025_pa1_stoopid_sort
 * Change N and recompile to run on arrays of different sizes.
 *
 * For this assignment, you'll be implementing Stoopid Sort (a new sort of
 * your instructor's devising) in the LEG subset of the ARMv8 ISA.  Stoopid
 * Sort is an O(n^2 lg n) comparison sort, akin to Selection Sort but worse.
 *
 * Regardless of how comfortable you may be with recursion or Selection Sort,
 * or with how well you may comprehend this C implementation, we want to
 * stress here that you do not have to understand this algorithm!  You don't
 * even have to try to understand it.  All that you have to do is,
 * essentially, be the compiler and translate this C code into LEGv8.  This
 * is not to discourage understanding.  Understanding is a good and useful
 * thing.  We are simply pointing out that you don't need to understand the
 * algorithm in order to implement your solution.  It's not rare that a route
 * of expedience is optimal.
 *
 * See the comments and code below for details on exactly what you must 
 * implement.
 *
 * Note that this C implementation uses 32-bit ints, but your ARM solution
 * will use 64-bit ints.  In your code, all variables will be 64-bit ints or
 * pointers to 64-bit ints.  This will not be stated elsewhere.
 */

#include <stdio.h>
#include <stdlib.h>

#define N 512

/* Swaps the value in a at index i with the value at index j. */
void swap(int *a, int i, int j)
{
  int tmp;

  tmp = a[i];
  a[i] = a[j];
  a[j] = tmp;
}

/* Given array and and indices n and m, returns the index whose *
 * corresponding element is larger.                             */
int max_index(int *a, int n, int m)
{
  return a[n] > a[m] ? n : m;
}

/* Uses recursive divide-and-conquer to find the largest element in the   *
 * subarray of a that begins at element start and contains size elements. */
int find_largest(int *a, int start, int size)
{
  if (size == 1) {
    return start;
  }

  return max_index(a,
                   find_largest(a, start, size / 2),
                   find_largest(a, start + size / 2, (size + 1) / 2));
}

/* Sorts the first size elements in array a.                     *
 * This is essentially selection sort except that it uses        *
 * divide-and-conquer to find the largest unsorted element of a. */
void stoopid_sort(int *a, int size)
{
  int i;
  int n;
  
  for (i = 0; i < size - 1; i++) {
    n = find_largest(a, 0, size - i);
    swap(a, n, size - i - 1);
  }
}

/* fill fills the array a (of n elements) with decreasing values from  *
 * n - 1 to zero (reverse sorted order).                               *
 *                                                                     *
 * Optionally, instead of filling a in reverse-sorted order, you may   *
 * implement a random number generator and call it here.  The emulator *
 * exports a TIME instruction that places the current time in its      *
 * single register parameter; this was implemented at the request of   *
 * past students who wanted to implement random number generators and  *
 * have variability in their output from run to run.                  .*/
void fill(int *a, int n) {
  int i;
  
  for (i = n - 1; i >= 0; i--) {
    a[n - i - 1] = i;
  }
}

/* Iterates through the first size elements of a, checking that adjacent *
 * pairs are in sorted order.  Terminates early (short circuits) when it *
 * finds an unsorted pair.  Returns zero if a is sorted; otherwise       *
 * returns non-zero.                                                     */
int is_sorted(int *a, int size)
{
  int i;

  for (i = 1; i < size && a[i] >= a[i - 1]; i++)
    ;

  return i == size;
}

/* Your main function should allocate space for an array, call fill to   *
 * fill it with decreasing numbers, and then call stoopid_sort to sort   *
 * it.  Use the HALT emulator instruction to see the memory contents and *
 * confirm that your functions work.  You may choose any array size you  *
 * like (up to the default limit of memory, 4096 bytes or 512 8-byte     *
 * integers).                                                            *
 *                                                                       *
 * Because Stoopid Sort is recursive and the emulator has a very small   *
 * default stack size, you will run out of stack space in with even      *
 * moderately sized arrays.  You can work around this by either keeping  *
 * your array small, or by using the -s emulator switch to specify a     *
 * larger stack on the command line.
 *                                                                       * 
 * Please terminate your main program with a HALT pseudo-instruction to  *
 * force a core dump so that you (and the TAs) can examine the contents  *
 * of memory.                                                            *
 *                                                                       *
 * You must implement all functions described above.  You are acting as  *
 * the compiler; you are not granted creative freedom to refactor these  *
 * functions to your liking.  You must adhere to ARMv8 calling           *
 * conventions; in particular, you must correctly use the stack when     *
 * calling and implementing procedures, and a procedure may not "know"   *
 * anything that it was not explicitly informed of by way of its         *
 * parameters!  For example: Even though you--the programmer--know that  *
 * no other procedure uses X22, you still must save it before you use it *
 * and restore it when you are finished with it.  Imagine that, instead  *
 * of you writing all of these procedures, each of them is written by a  *
 * different person, but none of you are permitted to communicate with   *
 * each other in any way.  The only thing each of you has is this        *
 * specification.  When we put all of your procedures together, your     *
 * program should work, but the only way that will be possible is if you *
 * fully adhere to convention.                                           *
 *                                                                       *
 * You may work alone or with a single partner on this assignment.       */
int main(int argc, char *argv[])
{
  /* In your LEGv8 program, main will not be a procedure.  Control will *
   * begin at the top of the file, so you should think of that as main. *
   * If control reaches the end of the file, the program will exit,     *
   * which you may think of as leaving main.                            */

  int a[N];

  fill(a, N);
  /* a now contains data in reverse-sorted (descending) order. */

  is_sorted(a, N); /* Returns 0 (false). */
  
  /*
  int i;
  for (i = 0; i < N; i++) {
    printf("%d\t", a[i]);
  }
  printf("\n");
  */
  
  stoopid_sort(a, N);
  /* a now contains data in sorted (ascending) order. */

  /*
  for (i = 0; i < N; i++) {
    printf("%d\t", a[i]);
  }
  printf("\n");
  */

  is_sorted(a, N); /* Returns non-zero (true). */
  //  printf("%d\n", is_sorted(a, N));

  return 0;
}