/* 
 * CS:APP Data Lab 
 * 
 * <AshanJiang>
 * 
 * bits.c - Source file with your solutions to the Lab.
 *          This is the file you will hand in to your instructor.
 *
 * WARNING: Do not include the <stdio.h> header; it confuses the dlc
 * compiler. You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.  
 */

#if 0
/*
 * Instructions to Students:
 *
 * STEP 1: Read the following instructions carefully.
 */

You will provide your solution to the Data Lab by
editing the collection of functions in this source file.

INTEGER CODING RULES:
 
  Replace the "return" statement in each function with one
  or more lines of C code that implements the function. Your code 
  must conform to the following style:
 
  int Funct(arg1, arg2, ...) {
      /* brief description of how your implementation works */
      int var1 = Expr1;
      ...
      int varM = ExprM;

      varJ = ExprJ;
      ...
      varN = ExprN;
      return ExprR;
  }

  Each "Expr" is an expression using ONLY the following:
  1. Integer constants 0 through 255 (0xFF), inclusive. You are
      not allowed to use big constants such as 0xffffffff.
  2. Function arguments and local variables (no global variables).
  3. Unary integer operations ! ~
  4. Binary integer operations & ^ | + << >>
    
  Some of the problems restrict the set of allowed operators even further.
  Each "Expr" may consist of multiple operators. You are not restricted to
  one operator per line.

  You are expressly forbidden to:
  1. Use any control constructs such as if, do, while, for, switch, etc.
  2. Define or use any macros.
  3. Define any additional functions in this file.
  4. Call any functions.
  5. Use any other operations, such as &&, ||, -, or ?:
  6. Use any form of casting.
  7. Use any data type other than int.  This implies that you
     cannot use arrays, structs, or unions.

 
  You may assume that your machine:
  1. Uses 2s complement, 32-bit representations of integers.
  2. Performs right shifts arithmetically.
  3. Has unpredictable behavior when shifting if the shift amount
     is less than 0 or greater than 31.


EXAMPLES OF ACCEPTABLE CODING STYLE:
  /*
   * pow2plus1 - returns 2^x + 1, where 0 <= x <= 31
   */
  int pow2plus1(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     return (1 << x) + 1;
  }

  /*
   * pow2plus4 - returns 2^x + 4, where 0 <= x <= 31
   */
  int pow2plus4(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     int result = (1 << x);
     result += 4;
     return result;
  }

FLOATING POINT CODING RULES

For the problems that require you to implement floating-point operations,
the coding rules are less strict.  You are allowed to use looping and
conditional control.  You are allowed to use both ints and unsigneds.
You can use arbitrary integer and unsigned constants. You can use any arithmetic,
logical, or comparison operations on int or unsigned data.

You are expressly forbidden to:
  1. Define or use any macros.
  2. Define any additional functions in this file.
  3. Call any functions.
  4. Use any form of casting.
  5. Use any data type other than int or unsigned.  This means that you
     cannot use arrays, structs, or unions.
  6. Use any floating point data types, operations, or constants.


NOTES:
  1. Use the dlc (data lab checker) compiler (described in the handout) to 
     check the legality of your solutions.
  2. Each function has a maximum number of operations (integer, logical,
     or comparison) that you are allowed to use for your implementation
     of the function.  The max operator count is checked by dlc.
     Note that assignment ('=') is not counted; you may use as many of
     these as you want without penalty.
  3. Use the btest test harness to check your functions for correctness.
  4. Use the BDD checker to formally verify your functions
  5. The maximum number of ops for each function is given in the
     header comment for each function. If there are any inconsistencies 
     between the maximum ops in the writeup and in this file, consider
     this file the authoritative source.

/*
 * STEP 2: Modify the following functions according the coding rules.
 * 
 *   IMPORTANT. TO AVOID GRADING SURPRISES:
 *   1. Use the dlc compiler to check that your solutions conform
 *      to the coding rules.
 *   2. Use the BDD checker to formally verify that your solutions produce 
 *      the correct answers.
 */

#endif
//1 只使用取反~和与&达到异或^操作
/* 
 * bitXor - x^y using only ~ and & 
 *   Example: bitXor(4, 5) = 1
 *   Legal ops: ~ &
 *   Max ops: 14
 *   Rating: 1
 */
int bitXor(int x, int y)
{
  /* 利用如下等式
      a^b = (x & ~y) | (~x & y)
      a|b = ~(~x & ~y)
  */
  return ~(~(x & ~y) & (~(~x & y)));
}
//只能使用0-255的整数0xff和这些预算得出int最小值
/* 
 * tmin - return minimum two's complement integer 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 4
 *   Rating: 1
 */
int tmin(void)
{
  //只需要把1左移31为即可得到32位最小补码数
  int t = 1;
  return t << 31;
}
//2如果x是最大int值返回1否则返回0
/*
 * isTmax - returns 1 if x is the maximum, two's complement number,
 *     and 0 otherwise 
 *   Legal ops: ! ~ & ^ | +
 *   Max ops: 10
 *   Rating: 1
 */
int isTmax(int x)
{
  /*
  只需要让0111 1111 ... 1111这个最大数返回1其他数返回0就可以了
  只有0和1000 0000 ... 0000这两个数自己加自己还是0
  利用这个性质，最大数（前四位）0111 + 1溢出得到1000再自加就能溢出为0
  但需要处理-1，但是不能用&&和if，想到利用0和1000 0000 ... 0000的不同
  现在要0返回0，而1000 0000 ... 0000返回1，利用!!num将非0数都转化为1
  再让!!num与之前自加得出的结果相与(Tmax和-1返回都是1)，就会让0得到0，Tmax得到1
  */
  //这样写编译器优化会导致出错
  // int y, z;
  // y = x + 1;
  // z = y + y;
  // return (!z) & (!!y);
  return (!(x + 1 + x + 1)) & (!!(x + 1));
}
/* 
 *   所有奇数位为1的数返回1，最低有效位序号是0，最高有效位序号是31
 * allOddBits - return 1 if all odd-numbered bits in word set to 1
 *   where bits are numbered from 0 (least significant) to 31 (most significant)
 *   Examples allOddBits(0xFFFFFFFD) = 0, allOddBits(0xAAAAAAAA) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 2
 */
int allOddBits(int x)
{
  /*
  以0xAAAAAAAA位掩码，所有和这个数相与还是这个数的x就满足条件
  再异或掩码本身，取反即可
  */
  int mask = 0xaa + (0xaa << 8) + (0xaa << 16) + (0xaa << 24);
  return !((x & mask) ^ mask);
}
/* 
 * 取反
 * negate - return -x 
 *   Example: negate(1) = -1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
int negate(int x)
{
  //按位取反再加1
  return ~x + 1;
}
//3
/* 
 * x是不是ascii的'0'-'9'
 * isAsciiDigit - return 1 if 0x30 <= x <= 0x39 (ASCII codes for characters '0' to '9')
 *   Example: isAsciiDigit(0x35) = 1.
 *            isAsciiDigit(0x3a) = 0.
 *            isAsciiDigit(0x05) = 0.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 3
 */
int isAsciiDigit(int x)
{
  int mask = 1 << 31;
  int upperBound = ~(mask | 0x39); //x>0x39时，x+upperBound会溢出，变为负数
  int lowerBound = ~0x30 + 1;      //x<0x30时,x+lowerBound不会溢出，为负数
  //综上，x>0x39以及x<0x30为负数
  int greater = (mask & (x + upperBound)) >> 31; //提取符号位,超出范围的符号位会变为1
  int lower = (mask & (x + lowerBound)) >> 31;
  return !(greater | lower);
}
/* 
 * 构成三元运算符?:
 * conditional - same as x ? y : z 
 *   Example: conditional(2,4,5) = 4
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 3
 */
int conditional(int x, int y, int z)
{
  // 对于x≠0，做出一个全1的掩码，对于x=0做出一个全0的掩码
  int mask = !x + ~0x00;
  // 全1的掩码与一个数相与得到这个数本身，全0掩码直接将一个数屏蔽为0
  // 0与任意一个数相或是其本身
  return (mask & y) | (~mask & z);
}

/* 
 * x<=y则返回1否则返回0
 * isLessOrEqual - if x <= y  then return 1, else return 0 
 *   Example: isLessOrEqual(4,5) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
int isLessOrEqual(int x, int y)
{
  int mask = 1 << 31;
  int signX = 1 & (x >> 31);    //x的符号位
  int signY = 1 & (y >> 31);    //y的符号位
  int polarity = signX ^ signY; // 同号还是异号
  // printf("signX=%d,signY=%d,polarity=%d\n", signX, signY, polarity);
  int sign = (mask & (~x + 1 + y)) >> 31; // 当x和y同号时，通过该计算，x>y时sign为1，x<=y时sign为0
  // 通过&符号前的运算，可得如下结果，保证同号时可以用sign反应结果
  //      x 1 0 1 0
  //      y 0 1 1 0
  // result 1 0 1 1
  // 通过&符号后的运算，当x与y同号时，无需屏蔽sign的值，而x与y异号时，将后半部分屏蔽为1，结果只受符号影响，x正y负为0，反之为1
  return (!!(signX + !signY)) & ((!sign) | polarity);
}

//4
/* 
 * 不用!达成非运算
 * logicalNeg - implement the ! operator, using all of 
 *              the legal operators except !
 *   Examples: logicalNeg(3) = 0, logicalNeg(0) = 1
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4 
 */
int logicalNeg(int x)
{
  //除0之外，任何一个数x与其相反数-x(~x+1)相或得到的值都是负数，显然这个数符号位位1
  //这样就可以区分0和其他数了，之后就很好办了，提取出符号位即可
  //由于不能用取反，所以要弄出个-1(1111 1111 .... 1111)来，再加1
  return ((x | (~x + 1)) >> 31) + 1;
}
/*
 * 最小需要多少位补码数来表示x（要包含符号位）
 * howManyBits - return the minimum number of bits required to represent x in
 *             two's complement
 *  Examples: howManyBits(12) = 5
 *            howManyBits(298) = 10
 *            howManyBits(-5) = 4
 *            howManyBits(0)  = 1
 *            howManyBits(-1) = 1
 *            howManyBits(0x80000000) = 32
 *  Legal ops: ! ~ & ^ | + << >>
 *  Max ops: 90
 *  Rating: 4
 */
int howManyBits(int x)
{
  // 思路很简单，只需要找到第一个为1的位，然后数出这一位到最后一位共有多少位再加1即可，对于负数要先取反，但是只用位操作实现真的很麻烦
  // 1.正数不变，负数进行位翻转
  // 1.1提取符号位
  int isNegative = (x >> 31) & 1;
  // 1.2生成全0或全1的屏蔽位
  int mask = (~isNegative) + 1;
  int a = ~x & mask;   //mask在x>0时应为全0，屏蔽~x；x<0时应为全1，保留~x
  int b = x & (~mask); //~mask为全1，保留x原值；~mask为全0，屏蔽x原值
  int normX = a | b;
  // printf("normX=%d\n", normX);
  // 2.用二分法（不循环，手动二分）查找第一位1的位置
  int bit16, bit8, bit4, bit2, bit1, bit0;
  bit16 = !!(normX >> 16) << 4; // 前16位，是否为0，不为0，则最少16位，此时bit16=16否则为0
  normX = normX >> bit16;       // 当前16位有数时，过滤掉后16位，否则保留原数
  bit8 = !!(normX >> 8) << 3;   //以此类推，每次手动折半
  normX = normX >> bit8;
  bit4 = !!(normX >> 4) << 2;
  normX = normX >> bit4;
  bit2 = !!(normX >> 2) << 1;
  normX = normX >> bit2;
  bit1 = !!(normX >> 1); //倒数第二位
  normX = normX >> bit1;
  bit0 = normX; // 最后一位
  // printf("bit16=%d, bit8=%d, bit4=%d, bit2=%d, bit1=%d, bit0=%d\n", bit16, bit8, bit4, bit2, bit1, bit0);
  return 1 + bit0 + bit1 + bit2 + bit4 + bit8 + bit16; // 最后要加上符号为1位
}
//float
/* 返回二进制表示的浮点数的2倍值
 * floatScale2 - Return bit-level equivalent of expression 2*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned floatScale2(unsigned uf)
{
  unsigned s = (uf >> 31) & 1;      // 提取符号位
  unsigned exp = (uf >> 23) & 0xff; // 提取阶码
  unsigned frac = uf & 0x7fffff;    // 提取尾数
  unsigned inf = 0x7f800000;
  unsigned ninf = 0xff800000;
  // 1.无穷大和溢出
  if (exp == 255)
  {
    if (frac == 0)
    {
      if (s == 1)
        return ninf;
      else
        return inf;
    }
    else
    {
      return uf; // 不是一个数
    }
  }
  // 2.非规格化
  if (exp == 0)
  {
    return (frac << 1) + (s << 31); // 小数部分直接放大2倍，不需要考虑溢出，溢出到阶码位计算结果不变
  }
  // 3.规格化
  if (exp == 254)
  {
    if (s == 1)
        return ninf;
      else
        return inf;
  }
  else
  {
    return (s << 31) + ((exp + 1) << 23) + frac;
  }
}
/* 
 * floatFloat2Int - Return bit-level equivalent of expression (int) f
 *   for floating point argument f.
 *   Argument is passed as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point value.
 *   Anything out of range (including NaN and infinity) should return
 *   0x80000000u.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
int floatFloat2Int(unsigned uf)
{
  return 2;
}
/* 
 * floatPower2 - Return bit-level equivalent of the expression 2.0^x
 *   (2.0 raised to the power x) for any 32-bit integer x.
 *
 *   The unsigned value that is returned should have the identical bit
 *   representation as the single-precision floating-point number 2.0^x.
 *   If the result is too small to be represented as a denorm, return
 *   0. If too large, return +INF.
 * 
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. Also if, while 
 *   Max ops: 30 
 *   Rating: 4
 */
unsigned floatPower2(int x)
{
  return 2;
}
