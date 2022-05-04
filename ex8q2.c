
#include <ctype.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

bool validate(const char *);
char *add(const char *, const char *);
bool eq(const char *, const char *);
bool gt(const char *, const char *);
char *diff(const char *, const char *);
char *multiply(const char *, const char *);
char *divide(const char *, const char *);
char *modulo(const char *, const char *);


int main(int argc, char *argv[]) {
	if (argc != 3)
		return 0;
	char *addStr, *diffStr, *multStr, *divStr, *modStr;
	int bool1 = validate(argv[1]);
	int bool2 = validate(argv[2]);
	if (bool1 == true && bool2 == true){
		addStr = add(argv[1], argv[2]);	
		diffStr = diff(argv[1], argv[2]);
		multStr = multiply(argv[1], argv[2]);
		divStr = divide(argv[1], argv[2]);
		modStr = modulo(argv[1], argv[2]);
	}
	printf("Add: %s\n", addStr);
	printf("Subtract: %s\n", diffStr);
	printf("Multiply: %s\n", multStr);
	printf("Divide: %s\n", divStr);
	printf("Modulo: %s\n", modStr);
	return 0;
}

//the following function validates whether the string `p` represents a non-negative integer
bool validate(const char *p) {
	//have a simple checker to see if there's a dash	
	if (p[0] == '-'){
		return false;
	}
	if (p[0] == '0'){
		p++;
		if (*p != '\0'){
			return false;
		}
	
	}	
	//go through p, if there's a zero and the next item isn't a null character return false, if it a digit continue iterating 
	for (int i = 0; i < strlen(p); i++){
		//if p is a digit continue else return false
		if (isdigit(*p) > 0){
			p++;
		
		} else {
		
			return false;
		} 
	
	}
	return true;
		
}

//the following function returns a new string representing m + n
char *add(const char *m, const char *n) {
	//create pointers and indicesm and variables 
	char *mAndN; 
	
	int m_index = strlen(m) -1, n_index = strlen(n) - 1, carry = 0, addIndex, digit;
	//our addIndex is the largest index + 1 to measure in the carry
	if (m_index > n_index) {
		addIndex = m_index + 1; 
	} else {
		addIndex = n_index + 1; 
	}
	//then we malloc our addition pointer
	mAndN =  calloc(addIndex,sizeof(char));
	//create variables for addition as well as a while loop
	int sum, newAdd = addIndex + 2;	
	//like the mergesort, create three while loops
	while (m_index >= 0 && n_index >= 0){
		//first one takes the sum, which will be used to create our number to add and our carry, decrement all indices
		sum = (m[m_index] + n[n_index] + carry - 96);
		digit = sum%10;
		carry = sum/10;
		mAndN[addIndex] = (char) (digit + 48);
		m_index--;
		n_index--;
		addIndex--;
	}
	//these ones look for stragglers and consider carry's and numbers we add in 
	while (m_index >= 0){
		sum = (m[m_index] + n[n_index] + carry - 48);
		digit = sum%10;
		carry = sum/10;
		mAndN[addIndex] = (char)(digit + 48);
		m_index--;
		addIndex--;
	}
	while (n_index >= 0){ 
		sum = (m[m_index] + n[n_index] + carry - 48);
		digit = sum%10;
		carry = sum/10;
		mAndN[addIndex] = (char)(digit + 48);
		n_index--;
		addIndex--;
	}
	//if there's still a carry at the end of it all add it into the first position
	if(carry == 1){
		// handle carry mAndN[m]
		mAndN[0] = carry + 48;
	}
	//our shifter, while the first index is 0, create a for loop that moves it to the back, then at the end add a null character, 
	int i = 0;
	while(mAndN[0] == 0){
		for(int i = 0; i < newAdd; i++){
			*(mAndN + i) = *(mAndN + i + 1);
		
		}
		*(mAndN + newAdd - 1 - i) = '\0';
		i++;
	}
	//return the new reallocated variable 	
	return mAndN;
}

//the following function validates whether m > n
bool gt(const char *m, const char *n) {
	if ( strlen(m) > strlen(n)){
		return true;
	} else if (strlen(m) == strlen(n)){
		
		int compare = strcmp(m, n);
		if (compare > 0){
			return true;
		}
	}
	return false;
}

//the following function validates whether m == n
bool eq(const char *m, const char *n) {
	return (strcmp(m, n) == 0);
}

//the following function returns a new string representing |m - n|
char *diff(const char *m, const char *n) {
	char *mAndN; 
	//create vars	
	int sub = 0;  
	//indicies and sizes
	int m_index = strlen(m) -1, n_index = strlen(n) - 1, carry = 0, subIndex, newSize;
	//check if m > n 
	//check of they're equal and return 0
	char *null = calloc(2, sizeof(char));
	if (strcmp(m,n) == 0){
		null[0] = '0';
		null[1] = '\0';
		return null;
	
	}
	// check if m > n
	if (m_index > n_index || (m_index == n_index && strcmp(m, n) > 0)) {
		//make our index = m and our realloc size the index + 2 (give us space for an extra num + null)
		subIndex = m_index; 
		newSize = subIndex + 1; 
		mAndN = calloc(subIndex + 1, sizeof(char));
		
		//while both are greater than 0
		
		while (m_index >= 0 && n_index >= 0){
			//check if we carried, if we have create a borrow so that we can subtract, i.e. 15-06, our borrow would basically be 1 - 0 - borrow (1 or 0) 
			//
			//if the m - borrow is greater than the n , subtract and reconvert carry 
			
			if ((m[m_index] - carry - 48) >= (n[n_index] - 48 )){
				sub = m[m_index] - n[n_index] - carry;
				carry = 0;
			} else {
				sub = m[m_index] - n[n_index] + 10 - carry;
				carry = 1;
			}

		//add it into the combination array
		mAndN[subIndex] = (char) (sub + 48);
		m_index--;										
		n_index--;
		subIndex--;
		}			        
	} else {
		//same as the if but use n instead of m
		subIndex = n_index; 
		newSize = subIndex + 1; 
		mAndN = calloc(subIndex + 1, sizeof(char));
		
		while (m_index >= 0 && n_index >= 0){
			if ((n[n_index] - 48 - carry) >= (m[m_index] - 48)){
				
				sub = n[n_index] - m[m_index]- carry;
				carry = 0;
	            	} else {
				sub = n[n_index] - m[m_index] + 10 - carry;
				carry = 1;
			}
			mAndN[subIndex] = (char) (sub + 48);
	        	m_index--;
			n_index-- ;
			subIndex--;
		}
	}
	//look for stragglers, check for the carry, subtract and add it in
	while (m_index >= 0){
		if (m[m_index] - 48 - carry >= 0){
			sub = m[m_index] - 48 - carry;
			carry = 0;
		} else {
			sub = m[m_index] - 48 - carry + 10;
			carry = 1;
		}
		mAndN[subIndex] = (char)(sub + 48);
		m_index--;
		subIndex--;
	}
	while (n_index >= 0){ 
		if (n[n_index] - 48 - carry  >= 0){
			sub = n[n_index] - 48 - carry;
			carry = 0;
		} else {
			sub = n[n_index] - 48 - carry + 10;
			carry = 1;
		}
		mAndN[subIndex] = (char)(sub + 48);
		n_index--;
		subIndex--;
	}
	//our shifter, same concept for add.
	while (mAndN[0] == '0') {
		for(int i = 0; i < newSize; i++){
			mAndN[i] = mAndN[i + 1]; 		
		}
		newSize--;
		mAndN = realloc(mAndN, sizeof(char) * newSize + 1 ); 	        
	}
	
	return mAndN;
}


//the following function returns a new string representing m * n
char *multiply(const char *m, const char *n) {
	//create indices, pointers, etc.
	int n_i = strlen(n) - 1, m_i = strlen(m) - 1;
	int mAndN_i = strlen(n) + strlen(m) ;
	char *newN = malloc((n_i + 1)* sizeof(char));
	char *newM = malloc((m_i + 1)* sizeof(char));
	
	strcpy(newN, n);
	strcpy(newM, m);
	//if either are 0, return the 0 pointer
	if (newN[0] == '0'){
		return newN;
	} else if (newM[0] == '0'){
		return newM;
	}
	//create a pointer that takes in the worst case scenario for our size of multiply, (both indices added)
	int mult;
	//create an int array to add all our multiply values
	
	int *array = calloc(strlen(m) + strlen(n), sizeof(int));
	//do a double for loop that will multiple each digit by eachother, 
	for (int i = m_i; i >= 0; i--){
		for (int j = n_i; j >= 0; j-- ){
			//add it into our int array
			mult = (n[j] - 48) * (m[i] - 48);
			array[i + j + 1] += mult;
		}
	}
		int carry = 0, digit;
		//go through the array, if at any point its > 9 create an array and digit variable, your carry should be placed in the number after. 
		for (int i = mAndN_i - 1; i > 0; i--){
				carry = array[i]/10;	
				array[i-1] += carry;
				digit = array[i]%10;
				array[i] = digit;
		}
	//this is our swap part, 
	//basically that while the first number is zero, go through a loop,
	//move it till that there is a value at [0] that isn't 0
	while (array[0] == 0) {
		for(int i = 0; i < mAndN_i; i++){
			array[i] = array[i + 1]; 		
		}
		mAndN_i--;
	}
	
	//array = realloc(array, sizeof(char) * (mAndN_i + 1)); 	        
	//afterwards create an array that will add those variables inside
	char *returnArr = calloc(mAndN_i, sizeof(char)); 
	for(int i = 0; i < mAndN_i ; i++){
		returnArr[i] =  (array[i] + 48); 		
	}
	return returnArr;
	
}

//the following function returns a new string representing m / n
char *divide(const char *m, const char *n) {	
	
	//create our lengths and copies
	int len_n = strlen(n) -1, len_m = strlen(m) - 1, len_d;
	char *new_m = calloc(len_m + 1, sizeof(char)), *new_n = calloc(len_n + 1, sizeof(char));
	
	strcpy(new_n, n);
	strcpy(new_m, m);
	//create base cases so we don't have to worry about it
	char *simpleCase = calloc(2, sizeof(char));
	if (n[0] == '0'){
		return NULL;
	}
	if (strlen(n) == 1 && n[0] == '1'){
		return new_m;
	
	}
	if (m[0] == '0'){
		return new_m;
	}
	if (gt(n,m)){
		simpleCase[0] = '0';
		return simpleCase;
	}
	if (eq(m,n)){
		simpleCase[0] = '1';
		return simpleCase;
	}

	//create your total array
	char *mAndN;
	if (len_m > len_n){
		mAndN = calloc(len_m + 1,sizeof(char));
		len_d = len_m;
	
	} else {
		mAndN = calloc(len_n  + 1, sizeof(char));
		len_d = len_n;
	}
	

	int counter = 0, newSize = len_d + 1;
	
	if (gt(m,n)){
		//while our first value is greater than our second, create a diff that is reassigned to new_m, and increase our counter, our counter is the answer
		while(gt(new_m, new_n) || eq(new_m, new_n)){
			new_m = diff(new_m, new_n);
			counter++;
		}
		//while it doesn't equal zero, add it into the back of the length, divide it by 10, and decrement the length of divide
		while (counter != 0 && len_d >= 0){
			mAndN[len_d] = (char) ((counter%10) + 48);
			counter /= 10;
			len_d--;
		}
	
	}
	//
	//our mover
	int i = 0;
	while (mAndN[0] == 0 ) {
		for(int i = 0; i < newSize; i++){
			mAndN[i] = mAndN [i + 1]; 		
		}
		i++;
	}
	mAndN = realloc(mAndN, sizeof(char) * newSize - i + 1); 	        
	
	return mAndN;
}

//the following function returns a new string representing m % n
char *modulo(const char *m, const char *n) {
	//create base cases
	if (n[0] == '0'){
		return NULL;
	}
	//create variables
	int len_m = strlen(m) - 1;
	char *newM = calloc(len_m, sizeof(char)), *newM2 = calloc(len_m, sizeof(char));
	strcpy(newM, m);
	strcpy(newM2, m);
	char  *newMAndN, *simpleCase = calloc(2, sizeof(char));	
	if (m[0] == '0'){
		
		return newM;
	}
	if (eq(m,n)){
		simpleCase[0] = '0';
		return simpleCase;
	}
	//divide, multiply and subtract for modulo
	newM = divide(m,n);
	newM2 = multiply(newM, n);
	newMAndN = diff(m, newM2);
	//modulo is m - (m/n) = mAndN, reason why we do two m's is because we want to keep the m value. after we divide m/n. so basically val = divide(newM2/newN), then mAndN = (diff (newM, val);  
	
	return newMAndN;
}
	
