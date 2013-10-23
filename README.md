Neural
======

Back-propagation neural network for testing Barker 11 code.

 * Written by: Paras Chopra
 * Email: paras1987@gmail.com
 * Web: www.paraschopra.com
 * Comment: Use this code as you like, but please give me credit whenever I deserve it.
 *
 * Improved version by András Mamenyák
 * Changelog
 * - fixed build errors
 * - fixed segfault errors
 * - cleaner code
 * - improved runtime: 25% faster
 * - test the Barker 11 code
 
Build
=====

>$ cmake .

>$ make

Output
======

Start training.

Enter number of training iterations: 10000

End training.

Start testing.

Case number: 1
Input: 01100010010 (787)
Output: 0.785815

Case number: 2
Input: 10100010010 (1299)
Output: 0.662065

Case number: 3
Input: 11100010010 (1811)
Output: 0.941524

End testing.

Number of positive output: 3
