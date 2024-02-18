#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main () {
	
	char word[105]; //declare a variable with the length of what user might enter
	char reversed_word[105]={}; // declare a variable for the converted sentence/word
	
	printf("Please enter what you would like to covert: ");
	scanf("%[^\n]", word); //scan desired sentence/word to convert
	getchar();
	
	for(int i=0;i<strlen(word);i++){ //covert every character of the sentence/desired word
		reversed_word[i]=word[strlen(word)-1-i]; //reverse scanned word
		
		if(isalpha(reversed_word[i])){ // if the character isalpha then if upper to lower, if lower to upper
			if(isupper(reversed_word[i])){
				reversed_word[i]=tolower(reversed_word[i]); // is upper=tolower
			} else if (islower(reversed_word[i])){
				reversed_word[i]=toupper(reversed_word[i]); //islower=toupper
			}
		}
	}
	
	printf("Here is your converted word: %s\n", reversed_word); //print converted word
	
	return 0;
}
