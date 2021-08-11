/* 
 * CS:APP Data Lab 
 * 
 * <Abigail Barnes>
 * 
 * bits.c - Source file with your solutions to the project.
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

You will provide your solution to the project by
editing the collection of functions in this source file.

CODING RULES:
 
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
  3. Has unpredictable behavior when shifting an integer by more
     than the word size.

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


NOTES:
  1. Use the dlc (data lab checker) compiler (described in the handout) to 
     check the legality of your solutions.
  2. Each function has a maximum number of operators (! ~ & ^ | + << >>)
     that you are allowed to use for your implementation of the function. 
     The max operator count is checked by dlc. Note that '=' is not 
     counted; you may use as many of these as you want without penalty.
  3. Use the btest test harness to check your functions for correctness.
  4. The maximum number of ops for each function is given in the
     header comment for each function.

/*
 * STEP 2: Modify the following functions according to the coding rules.
 * 
 *   IMPORTANT. TO AVOID GRADING SURPRISES:
 *   1. Use the dlc compiler to check that your solutions conform
 *      to the coding rules.
 *   2. Use the btest checker to verify that your solutions produce
 *      the correct answers.
 */


#endif

/************************************************ 
 * absVal - absolute value of x
 *   Example: absVal(-1) = 1.
 *   You may assume -TMax <= x <= TMax
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 10
 *   Rating: 4
 */
int absVal(int x)
/* function will make pos nums = 0 and neg nums = -1,
XOR will be used to determine whether or not to manipulate
positive nums or ~ (inverse) negative nums. */
 {
  int shifted, negative_shift, xor_opperation, ans;
  shifted = x >> 31;
  xor_opperation = shifted ^ x; //1 if bits are different
  negative_shift = ~shifted;
  negative_shift += 1;
  ans = xor_opperation + negative_shift;
  return ans;
}

/************************************************ 
 * addOK - Determine if can compute x+y without overflow
 *   Example: addOK(0x80000000,0x80000000) = 0,
 *            addOK(0x80000000,0x70000000) = 1, 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 3
 */
int addOK(int x, int y) 
/*NOTE: there is no overflow when parameters are of opp. signs
  overflow = sign bit change
  true = 1
  false = 0*/
{
	int xshift, yshift, arg1;
	arg1 = ((x + y) >> 31);
	xshift = (x >> 31);
	yshift = (y >> 31);
  return (!(arg1 ^ xshift)) | (!(arg1 ^ yshift));
}

/************************************************ 
 * allEvenBits - return 1 if all even-numbered bits in word set to 1
 *   Examples allEvenBits(0xFFFFFFFE) = 0, allEvenBits(0x55555555) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 2
 */
int allEvenBits(int x) 
{
  int bit, byte;
  byte = 0x55;
  bit = byte | byte<<8 | byte<<16 | byte<<24;
  return !(bit ^ (x & bit));
}

/************************************************
 * bang - Compute !x without using !
 *   Examples: bang(3) = 0, bang(0) = 1
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4 
 */
int bang(int x) 
{
  /*numbers that are not 0 are 111...111 with
  an added 1 to ensure 0, 0->1 or any natural number->0*/
  int ans;
  ans = ((x | (~x + 1))>>31);
  ans++;
  return ans;
}

/************************************************
 * bitCount - returns count of number of 1's in word
 *   Examples: bitCount(5) = 2, bitCount(7) = 3
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 40
 *   Rating: 4
 */
int bitCount(int x) 
/* dividing work into groups of 2, 4, 8, 16... sum up groups for total bit count */
{
  int val0x55555555, val0x33333333, val0x0f0f0f0f, val0x00ff00ff, val0x0000ffff;

  val0x55555555 = 0x55 | 0x55 << 8 | 0x55 << 16 | 0x55 << 24;
  val0x33333333 = 0x33 | 0x33 << 8 | 0x33 << 16 | 0x33 << 24;
  val0x0f0f0f0f = 0xF | 0xF << 8 | 0xF << 16 | 0xF << 24; 
  val0x00ff00ff = 0xFF | 0xFF << 16;
  val0x0000ffff = 0xFF | 0xFF << 8;

  x += (~ (val0x55555555 & (x >> 1)) + 1);
  x = (val0x33333333 & (x >> 2)) + (x & val0x33333333);
  x = (val0x0f0f0f0f & (x >> 4)) + (x & val0x0f0f0f0f);
  x = val0x00ff00ff & (x + (x >> 8));
  x = val0x0000ffff & (x + (x >> 16)) ;
  return x;
}



/************************************************
 * bitNor - ~(x|y) using only ~ and & 
 *   Example: bitNor(0x6, 0x5) = 0xFFFFFFF8
 *   Legal ops: ~ &
 *   Max ops: 8
 *   Rating: 1
 */
int bitNor(int x, int y) 
/*negation, & to ensure both bits at a given placement
are both 1. if both given bits are not one, & will 
ensure that there will be a 0 in that place of the
final bit*/
{
  return (~x) & (~y);
}

/************************************************
 * byteSwap - swaps the nth byte and the mth byte
 *  Examples: byteSwap(0x12345678, 1, 3) = 0x56341278
 *            byteSwap(0xDEADBEEF, 0, 2) = 0xDEEFBEAD
 *  You may assume that 0 <= n <= 3, 0 <= m <= 3
 *  Legal ops: ! ~ & ^ | + << >>
 *  Max ops: 25
 *  Rating: 2
 */
int byteSwap(int x, int n, int m)
{
  /*shifting bytes, swapping using XOR which will output 1 if bits in
  same given place are different*/
  int ntemp, mtemp, shift, ans;
  n = n << 3;
  m = m << 3;

  ntemp = x >> n;
  mtemp = x >> m;

  shift = (ntemp ^ mtemp) & 0xFF;

  ans = (x ^ (shift << n) ^ (shift << m));
  return ans;
}

/************************************************ 
 * conditional - same as x ? y : z 
 *   Example: conditional(2,4,5) = 4
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 3
 */
int conditional(int x, int y, int z) 
/*will return 0 when x != 0 and -1 when x = 0*/
{
  int comp, ansy, ansz;
  comp = ~!x;
  comp++;
  ansy = ~comp & y;
  ansz = comp & z;
  return ansy | ansz;
}

/************************************************
 * ezThreeFourths - multiplies by 3/4 rounding toward 0,
 *   Should exactly duplicate effect of C expression (x*3/4),
 *   including overflow behavior.
 *   Examples: ezThreeFourths(11) = 8
 *             ezThreeFourths(-9) = -6
 *             ezThreeFourths(1073741824) = -268435456 (overflow)
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 3
 */
int ezThreeFourths(int x) 
/*bit shifting for mult and div by pwr of 2*/ 
{
  int tempx, opp, num_sign, divided_ans;
  tempx = (x << 1) + x;
  opp = (1 << 2) + (~0);
  num_sign = tempx >> 31;
  divided_ans = ((tempx + (opp & num_sign)) >> 2);
  return divided_ans;
}

/************************************************ 
 * fitsBits - return 1 if x can be represented as an 
 *  n-bit, two's complement integer.
 *   1 <= n <= 32
 *   Examples: fitsBits(5,3) = 0, fitsBits(-4,3) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 2
 */
int fitsBits(int x, int n)
/*returns 1 if x can be represented as two's compliment int
returns 0 is x cannot be represented as two's compliment int*/
{
  int tempx, argx1, argx2;
  tempx = x >> 31;
  argx1 = ~x & tempx;
  argx2 = x & ~tempx;
  return !((argx1 + argx2) >> (n + ~0));
}

/************************************************
 * getByte - Extract byte n from word x
 *   Bytes numbered from 0 (LSB) to 3 (MSB)
 *   Examples: getByte(0x12345678,1) = 0x56
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 2
 */
int getByte(int x, int n) 
/* bit * 8 can be accomplished by appending 3 0s at end of bit, bit shift
for lowest postion keeping endian-ness in mind, mask with 0xFF for last byte*/
{
	int xshift, nshift;
	nshift = n << 3;
	xshift = x >> nshift;
	return xshift & 0xFF;
}

/************************************************ 
 * greatestBitPos - return a mask that marks the position of the
 *               most significant 1 bit. If x == 0, return 0
 *   Example: greatestBitPos(96) = 0x40
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 70
 *   Rating: 4 
 */
int greatestBitPos(int x) 
/* using shifting and bitwise operator |
repeat steps for 2, 4, 8, and 16 until most sig. bit is achieved */
{
  int tempx, ans1, ans2;
  tempx = x;
  tempx = tempx | tempx >> 1;
  tempx = tempx | tempx >> 2;
  tempx = tempx | tempx >> 4;
  tempx = tempx | tempx >> 8;
  tempx = tempx | tempx >> 16;
  ans1 = tempx ^ (tempx >> 1);
  ans2 = (1 << 31) & tempx;
  return ans1 | ans2;
}

/************************************************
 * implication - return x -> y in propositional logic - 0 for false, 1
 * for true
 *   Example: implication(1,1) = 1
 *            implication(1,0) = 0
 *   Legal ops: ! ~ ^ |
 *   Max ops: 5
 *   Rating: 2
 */
int implication(int x, int y) 
/* false only when x = 1, y = 0 */
{
  return !(x ^ y) | y;
}

/************************************************ 
 * isAsciiDigit - return 1 if 0x30 <= x <= 0x39 (ASCII codes for characters '0' to '9')
 *   Example: isAsciiDigit(0x35) = 1.
 *            isAsciiDigit(0x3a) = 0.
 *            isAsciiDigit(0x05) = 0.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 3
 */
int isAsciiDigit(int x) 
/* given bounds of x presented in description above, low | high = positive else neg */
{
  return !(((x + ~0x2F) | (~x + 0x3A)) >> 31);
}

/************************************************ 
 * isEqual - return 1 if x == y, and 0 otherwise 
 *   Examples: isEqual(5,5) = 1, isEqual(4,5) = 0
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
int isEqual(int x, int y) 
/* return 0 if bits are equal, so must reverse output of x ^ y */
{
  return !(x ^ y);
}

/************************************************
 * isLess - if x < y  then return 1, else return 0 
 *   Example: isLess(4,5) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
int isLess(int x, int y) 
/* return 1 if x < y else return 0.
return 1 when x - y is neg, x and y same sign, x neg and y pos/0 */
{
  int sign, ans1, ans2, final_ans;
  sign = x ^ y;
  ans1 = sign & x;
  ans2 = ~sign & (x + ~y + 1);
  final_ans = ((ans1 | ans2) >> 31) & 1;
  return final_ans;
}

/************************************************
 * isNonNegative - return 1 if x >= 0, return 0 otherwise 
 *   Example: isNonNegative(-1) = 0.  isNonNegative(0) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 3
 */
int isNonNegative(int x) 
/* most sig bit and correlation to negativity */
{
	int ans = x >> 31;
	return !ans;
}

/************************************************
 * isPower2 - returns 1 if x is a power of 2, and 0 otherwise
 *   Examples: isPower2(5) = 0, isPower2(8) = 1, isPower2(0) = 0
 *   Note that no negative number is a power of 2.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 4
 */
int isPower2(int x) 
/* true if power of two, false if not, should only have a single one and pos */
{
  int pos, single;
  pos = x >> 31;
  pos = !pos;
  single = !((x + ~0) & x) & !!x;
  return pos & single;
}

/************************************************
 * isTmin - returns 1 if x is the minimum, two's complement number,
 *     and 0 otherwise 
 *   Legal ops: ! ~ & ^ | +
 *   Max ops: 10
 *   Rating: 1
 */
int isTmin(int x) 
/* utilizing properties of overflow for bits */
{
  int arg1, arg2;
  arg1 = !x;
  arg2 = x + x;
  return !(arg1 | arg2);
}

/************************************************
 * minusOne - return a value of -1 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 2
 *   Rating: 1
 */
int minusOne(void) 
/* considering -1 and 0 in binary */
{
  return ~0;
}

/************************************************
 * rotateLeft - Rotate x to the left by n
 *   Can assume that 0 <= n <= 31
 *   Examples: rotateLeft(0x87654321,4) = 0x76543218
 *   Legal ops: ~ & ^ | + << >> !
 *   Max ops: 25
 *   Rating: 3 
 */
int rotateLeft(int x, int n) 
/* shifting bits for rotation */
{
	int arg1, arg2, ans;
	arg1 = x << n;
	arg2 = 32 + ~n + 1;
	arg2 = 31 & arg2;
	arg2 = x >> arg2;
	ans = arg1 | (arg2 & ~(~0 << n));
	return ans;
}

/************************************************
 * satMul2 - multiplies by 2, saturating to Tmin or Tmax if overflow
 *   Examples: satMul2(0x30000000) = 0x60000000
 *             satMul2(0x40000000) = 0x7FFFFFFF (saturate to TMax)
 *             satMul2(0x60000000) = 0x80000000 (saturate to TMin)
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 3
 */
int satMul2(int x) 
{
  int sat_val, min, max, ans, arg1, arg2;
  min = 1 << 31;
  max = ~min;
  sat_val = ((x ^ (x << 1)) >> 31);
  arg1 = ((x << 1) & ~sat_val);
  arg2 = (((1 & (x >> 31)) + max) & sat_val);
  ans = (~sat_val & (x << 1)) | (sat_val & ((1 & (x >> 31)) + max));
  return ans;
}

