/*****************************************************************************/
/* Disclaimer:*/
/* Author: Carlos L Sanchez Vila   
/**/
/* INSTRUCTIONS/HOW TO USE:*/
/* To compile:*/
/* gcc -lm eAndPiGenerator.c -o epiGen.out */
/* To execute:*/
/* 	enter ./epiGen.out and view on screen results.             */
/**/
/* Notice that the -lm flag is used to enable the math.h library to be */
/* linked and referenced when compiling the program, this program makes */
/* makes use of several constants and functions from the math.h library*/
/*****************************************************************************/

#include <stdio.h>
#include <math.h>					/* Using for POW, PI and EULER*/
#include <time.h>					/* Used to allow measuring execution time*/
#define NO_PROGRAM_ERRORS 0  		/* Signal a correct program execution */
#define INITIAL_LAMBDA_VALUE 10.0 	/* The initial value for Lambda variable */
#define EULER_SIGNIF_DIGITS 10		/* Significant digits for e aproximation*/
#define PI_SIGNIF_DIGITS 6			/* Significant digits for Pi aproximation*/
#define MS_IN_A_SECOND 1000			/* Number of ms in one second unit of time*/


/* Function Prototypes declarations:*/
void computePi(int);
void computeEuler(int);
double generateLambda(int);
double absValue(double);


/**
 * main: The following program calculates the irrational numbers e and PI 
 * using the taylor series to aproximate their values up to a variable number
 * of digits of accuracy. The program takes no imput and calculates e and pi 
 * up to 10 and 6 significant digits of accuracy respectively. The code however 
 * is built in a flexible way which would allow to agregate the user imput to
 * be used instead, and determine e and PI for any desired amount of digits 
 * (Any reasonable amount of digits for this method).
 * 
 * @return: This program returns the value zero if there are no program errors.
 */
int main(){

	computeEuler(EULER_SIGNIF_DIGITS);
	computePi(PI_SIGNIF_DIGITS);

	return NO_PROGRAM_ERRORS;
}


/**
 * computePi: This function calculates the irrational number pi accurately up 
 * to a certain number of significant figures. The function makes use of the 
 * infinite taylor series for pi:
 * 	  			  ∞
 *			  4𝛑 = ∑ (-1)^n 1/(2n+1) = 1/1 - 1/3 + 1/5 -1/7...etc
 *			  	 n=0
 * to determine pi, this is done by adding consecutive terms of the series 
 * until the desired accuracy is reached. This function makes use of the number
 * lambda, which is used to determine when to stop adding consecutive series 
 * terms. This function also makes use of some built in functionality to 
 * calculate the time and the number of terms that were generated and added to
 * generate the number pi with a certain significant digit accuracy. 
 * The program finally prints the generated PI, and contrasts it with the 
 * value of PI provided by the math.h library, it indicates in which 
 * significant figure the values start to diverge and then prints the number of 
 * terms calculated followed by the time (in sec or ms) used to generate the 
 * number PI.
 * 		Notice that the number -1 is used to provide the alternating pattern 
 * in the taylor series used in this function, and the number 4 is used to 
 * perform calculations described int the formula above.
 * 		Two other constants are used in this function, M_PI which is a double 
 * that represents the accurate  value of pi and comes from the <math.h> 
 * library, and the number CLOCKS_PER_SECOND which comes from the time.h libray
 * and is used in order to obtain the number of clocks per second of the 
 * current platform where the program is running.
 */



void computePi(int signifDigits){

	/* This group of variables is used to calculate execution time */
	clock_t start, end;
	double cpu_time_used = 0.0;
	start = clock();

	/* Generate the needed lambda for the current number of digits*/
	double lambda = generateLambda(signifDigits);

	double sumOfTerms=0.0;
	double currTermVal = 0.0;
	int currentTermPos = 0.0;
	double prevSum = 0.0;
	int sign = 1;

	/* Computes the taylor series term by term and adds them until threshold*/
	/* is reached*/
	do{	
		currTermVal = sign * (pow(((2 * currentTermPos)+1),-1));

		prevSum = sumOfTerms;
		sumOfTerms +=currTermVal;
		currentTermPos++;
		sign *= -1;

	}while(absValue(4*((sumOfTerms)-(prevSum))) >= lambda);

	/* Complete the last part of the taylor series, multyplying by 4*/
	prevSum *=4;

	/* Compute the total time used to generate the number pi in milliseconds*/
	end = clock();
	cpu_time_used = (double)(end - start)/CLOCKS_PER_SEC;
	cpu_time_used = cpu_time_used * MS_IN_A_SECOND;

	/* Print the generated number, number of terms and execution time*/
	printf("\n %s\n","    Using the infinite taylor series to calculate pi:" );
	printf("+------------------------------------------------------------+\n");
	printf("|%s %d"," Calculated PI with ", PI_SIGNIF_DIGITS);
	printf(" %s %9s\n"," significant digit accuracy:","|");
	printf("+------------------------------------------------------------+\n");
	printf("|%s%.20lf %23s\n", " Math.h  PI:   ",M_PI,"|");
	printf("|%s%.20lf %23s\n", " Generated PI: ",prevSum,"|");
	printf("|%16s %*s %36s\n", " ",signifDigits+1, "^", "|");
	printf("|%s %d %23s\n"," Number of terms calculated: ",currentTermPos-1,"|");
	printf("|%s %.25lf "," Time used to compute:   ", cpu_time_used);
	printf("%s %3s\n","ms", "|" );
	printf("+------------------------------------------------------------+\n");
	printf("\n\n");
}


/**
 * computeEuler: This function calculates the irrational number e accurately up 
 * to a certain number of significant figures. The function makes use of the 
 * infinite taylor series for e:
 * 	  			  ∞
 *			  e = ∑ 1/n! = 1/0! + 1/1! + 1/2! +...+ 1/n!
 *			  	 n=0
 * to determine e. This is done by adding consecutive terms of the series 
 * until the desired accuracy is reached. This function makes use of the number
 * lambda, which is used to determine when to stop adding consecutive series 
 * terms. 
 * 		This function also makes use of some built in functionality to 
 * calculate the time and the number of terms that were generated and added to
 * generate the number e with a certain significant digit accuracy. 
 * The program finally prints the generated e, and contrasts it with the 
 * value of e provided by the math.h library, it indicates in which 
 * significant figure the values start to diverge and then prints the number of 
 * terms calculated followed by the time (in milliseconds) it took to generate 
 * the number e.
 * Notice that the number -1 is used to do a reverse exponentiation to 
 * calculate the 1/n! terms of the series.
 * Two other constants are used in this function, M_PI which is a double that 
 * represents the accurate  value of pi and comes from the math.h library, and 
 * the number CLOCKS_PER_SECOND which comes from the <time.h> libray and is used
 * in order to obtain the number of clocks per second of the current platform 
 * where the program is running.
 * 
 * @param signif_digits: This number is used to determine the needed lambda
 * value that will be determined by the helper function generateLambda().
 */
void computeEuler(int signifDigits){

	/* This group of variables is used to calculate execution time */
	clock_t start, end;
	double cpu_time_used = 0.0;
	start = clock();

	double lambda = generateLambda(signifDigits);

	double sumOfTerms = 1.0;
	double prevSum = 1.0;
	double nextTermVal = 0.0;
	int currTermPos = 1;
	long prevFactorial = 1;

	/* Computes the taylor series term by term and adds them until threshold*/
	/* is reached*/
	do{
		prevFactorial = prevFactorial*currTermPos;
		nextTermVal = pow(prevFactorial, (-1));
		prevSum = sumOfTerms;
		sumOfTerms += nextTermVal;
		currTermPos++;

	}while((sumOfTerms - prevSum) > lambda);

	/* Compute the total time used to generate the number e in milliseconds*/
	end = clock();
	cpu_time_used = (double)(end - start)/CLOCKS_PER_SEC;
	cpu_time_used = cpu_time_used * MS_IN_A_SECOND;

	/* Print the generated number, number of terms and execution time*/
	printf("\n %s\n","     Using the infinite taylor series to calculate e:" );
	printf("+------------------------------------------------------------+\n");
	printf("|%s %d"," Calculated e with ", EULER_SIGNIF_DIGITS);
	printf(" %s %9s\n"," significant digit accuracy:","|");
	printf("+------------------------------------------------------------+\n");
	printf("|%s%.20lf %24s\n", " Math.h  e:   ",M_E,"|");
	printf("|%s%.20lf %24s\n", " Generated e: ",prevSum,"|");
	printf("|%16s %*s %33s\n",     " ",signifDigits, "^", "|");
	printf("|%s %d %28s\n"," Number of terms calculated: ",currTermPos -1,"|");
	printf("|%s %.25lf "," Time used to compute:  ", cpu_time_used);
	printf("%s %5s\n","ms", "|" );
	printf("+------------------------------------------------------------+\n");
	printf("\n\n");
}


/**
 * GenerateLambda: This function generates a number (commonly known as epsilon, 
 * however in this program the name "lambda" was chosen instead) that will be 
 * used to ensure that a value of e generated using the infinite taylor series
 * and the Leibniz formula for 𝛑, is accurate up to a certain amount of 
 * significant digits. 
 * The function uses the decimal number "10" and divides it by 10 a given
 * number of times. This number is determined by "signif_digits" which is 
 * provided through the function signature. As an example, generateLambda(6) 
 * will provide the following lambda: <0.0000001> and the corresponding 
 * trailing zeroes after the number 1 like so <0.0000001000....0>.
 * Notice that the number -1 is used within the function to do a reverse
 * exponentiation to generate repeated division by 10.
 * 
 * @param  signif_digits: This parameter is used to indicate the desired number
 * of significant digits by which the initial lambda will be shifted to the 
 * right.
 * 
 * @return:This function returns the apropiate lambda created with the number of
 * precision digits given.
 */
double generateLambda(int signifDigits){
	return pow(INITIAL_LAMBDA_VALUE, (-1)*(signifDigits)); 
}



/**
 * absValue: This function takes a number as "value" and returns its absolute 
 * value also known as modulus for example:
 *  	absValue(1) = 1, absValue(-1) = 1, absValue(0) = 0 etc.
 * notice that the number -1 is used in this function to switch the vector of 
 * "value" and thus generate its modulus.
 *   
 * @param  value: This is the number that will be entered to evaluate and 
 * determine its absolute value.
 * 
 * @return: This function returns the absolute value of the number entered as 
 * "value".
 */
double absValue(double value){
	return (value >= 0) ? (value) : ((-1) * value);
}
















