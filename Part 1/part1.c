

// PART 1: myprintf Function
		   
//            Objective: I/O Function and Stack Usage

// Given: putchar(char c) of Linux, which prints a char.

// 1-1. Write YOUR own prints(char *s) fucntion to print a string.
   //  If you don't know how to do it, you BETTER attend my class lecture !!!!

// Given: The following printu() function print unsigned integer.

typedef unsigned int u32;

char *ctable = "0123456789ABCDEF";
int  BASE = 10; 

int rpu(u32 x)
{  
    char c;
    if (x){
       c = ctable[x % BASE];   
       rpu(x / BASE);
       putchar(c);           
    }
}

int printu(u32 x)
{
   (x==0)? putchar('0') : rpu(x);
   putchar(' ');
}


	//	          EXAMPLE:                             stack
    //  Assume u32 x = 123;                                      ------ High
    //  1st call to rpu(x): x=123; x%10 = 3 ===>  c = ctable[3] = '3';   
    //  2nd call to rpu(x): x=12;  x%10 = 2 ===>  c = ctable[2] = '2';  
    //  3rd call          : x=1;   x%10 = 1 ===>  c = ctable[1] = '1';  
    //  --------------------------------------------------------------- Low
    //  4th call          : x=0 => return  ====>      print       '1';
    //                             retrun  ====>      print       '2'
    //                             retrun  ====>      print       '3'

// 2-2. Write YOUR OWN fucntions
		  
// int  printx(u32 x) which print x in HEX   (prefixed with 0x )
// int  printd(int x) which print an integer (x may be negative!!!)

int rpx(u32 x)
{
    char c;
    if (x){
         c = ctable[x % 16];   
         rpx(x / 16);
         putchar(c);           
    }
}

int printx(u32 x)
{
    putchar('0'); putchar('x');
    if (x==0)
       putchar('0');
    else
       rpx(x);
}

int rpd(int x)
{
    char c;
    if (x){
         c = ctable[x % BASE];   
         rpd(x / BASE);
         putchar(c);           
    }
}

int printd(int x)
{
    if (x<0){
       putchar('-');
       x = -x;
    }
    if (x==0)
       putchar('0');
    else
       rpd(x);
}


// 3. REQUIREMENTS:
// ====================================================================
//   Write YOUR own myprintf(char *fmt, ...) function to print 
//         char                      by %c
//         string                    by %s
//	 unsigned integer          by %u
		  
//         unsigned integer in HEX   by %x
//         integer                   by %d

//   Ignore field width and precision, just print the items as specified.

void myprintf(char *fmt, ...)
{
    char *cp = fmt;
    int *ip = &fmt + 1;
    while (*cp){
        if (*cp != '%'){
            putchar(*cp);
            if (*cp=='\n')
                putchar('\r');
            cp++;
            continue;
        }
        cp++;
        switch(*cp){
            case 'c': putchar(*ip); break;
            case 's': prints(*ip); break;
            case 'u': printu(*ip); break;
            case 'x': printx(*ip); break;
            case 'd': printd(*ip); break;
        }
        cp++; ip++;
    }
}

// 1-3. In the int main(int argc, char *argv[ ], char *env[ ]) function, 
//     use YOUR myprintf() to print
//              argc value
//              argv strings
//              env  strings
//    Then,
//    myprintf("char=%c string=%s       dec=%u  hex=%x neg=%d\n", 
//	        'A', "this is a test",  100,   100,   -100);

/********************** HELP INFO **************************/
// NOTE: This assignment is for 32-bit GCC, which passes parameters on stack.
//      Use  
//               gcc -m32 t.c

//      to compile your C source files.

// int myprintf(char *fmt, ...)      // C compiler requires the 3 DOTs
// {
//   Assume the call is myprintf(fmt, a,b,c,d);
//   Upon entry, the following diagram shows the stack contents.
 
//                char *cp -> "...%c ..%s ..%u .. %d\n"
//   HIGH               |                                              LOW 
// --------------------------- --|------------------------------------------
//   | d | c | b | a | fmt |retPC| ebp | locals
// ----------------|----------------|---------------------------------------
//                 |                | 
//            int *ip            CPU.ebp
  
//     1. Let char *cp point at the format string: HOW?

//     2. Let int *ip  point at the first item to be printed on stack: HOW?

// NOTE: In 32-bit mode, Every entry in the stack is 4-byte;
//      for chars, they are in the lowest byte (of the 4-byte entry)
//      for strings, they are POINTERs to the actual strings.
     
//  *************** ALGORITHM ****************
//   Use cp to scan the format string:
//       spit out each char that's NOT %
//       for each \n, spit out an extra \r

//   Upon seeing a %: get next char, which must be one of 'c','s','u','x','d'
//   Then call YOUR

//        putchar(*ip) for 'c';
//        prints(*ip)  for 's';
//        printu(*ip)  for 'u';

//        printx(*ip)  for 'x';
//        printd(*ip)  for 'd';

//   Advance ip to point to the next item on stack.

int main(int argc, char *argv[ ], char *env[ ])
{
    myprintf("argc=%d\n", argc);
    int i;
    for (i=0; i<argc; i++)
        myprintf("argv[%d]=%s\n", i, argv[i]);
    for (i=0; env[i]; i++)
        myprintf("env[%d]=%s\n", i, env[i]);
    myprintf("char=%c string=%s dec=%u  hex=%x neg=%d\n", 
            'A', "this is a test",  100,   100,   -100);
    return 0;
}




// After implementing your myprintf() function, write C program to test your 
// myprintf() function first. Then use it in the assignment.