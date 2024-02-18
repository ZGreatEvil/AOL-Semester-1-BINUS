#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct apartment{ //declare the struct for the data that will be inputted
	char location1[105];
	char location2[105];
	int price;
	int rooms;
	int bathrooms;
	int carpark;
	char type[105];
	char furnish[105];
};

struct apartment apart[5000];
int count; //declare the amount of data that will be in the file
char col[105]; // which column
char waytosort[105]; // what they want to sort by (ascending/descending)


void clear_line(int line_number) { //function to clear 1 line
    // Move the cursor to the beginning of the line
    printf("\033[%d;1H", line_number);

    // Clear the line by printing spaces
    for (int i = 0; i < 80; i++) {
        printf(" ");
    }

    // Move the cursor back to the beginning of the line
    printf("\033[%d;1H", line_number);
}

void move_cursor_to_line(int line_number) { //function to move cursor
    // Move the cursor to the beginning of the specified line
    printf("\033[%d;1H", line_number);
}

void wait_for_enter() { // to wait until enter is pressed
	fflush(stdin);
    printf("\nPlease press enter to continue...");
    getchar(); // wait until enter
}

void clear_prompt() { // to clear command prompt
    system("cls");
}

void read_file(){ //to read the file
	FILE *fp = fopen("file.csv", "r"); //read the file
	if (fp == NULL) {
    	printf("Error opening file.\n");
    	wait_for_enter();
    	return; //if file cannot be scanned
	};
 	
	fscanf(fp, "%*[^\n]\n"); // delete the first line, because we don't need it	
	
	for (int index=0;!feof(fp);index++){ //scan until end of file
		fscanf(fp, "%[^,],%[^,],%d,%d,%d,%d,%[^,],%[^\n]\n", apart[index].location1, apart[index].location2, 
		&apart[index].price, &apart[index].rooms, &apart[index].bathrooms, &apart[index].carpark, 
		apart[index].type, apart[index].furnish); // scan the data
		count+=1; //add the amount of data scanned to count
	}
	
	fclose(fp); //close the file
}

int compare(struct apartment left, struct apartment right) { //to compare the variables that aare going to be sorted (part of merge sort)
	int result = 0;
	//check which you want to sort, then find the difference
	if (strcmpi(col, "location") == 0) result = strcmp(left.location1, right.location1);
	if (strcmpi(col, "city") == 0) result = strcmp(left.location2, right.location2);
	if (strcmpi(col, "price") == 0) result = left.price - right.price;
	if (strcmpi(col, "rooms") == 0) result = left.rooms - right.rooms;
	if (strcmpi(col, "bathroom") == 0) result = left.bathrooms - right.bathrooms;
	if (strcmpi(col, "carpark") == 0) result = left.carpark - right.carpark;
	if (strcmpi(col, "type") == 0) result = strcmp(left.type, right.type);
	if (strcmpi(col, "furnish") == 0) result = strcmp(left.furnish, right.furnish);
	
	if (strcmpi(waytosort, "des") == 0 || strcmpi(waytosort, "descending") == 0) return -result;
	
	return result;
}

void merge(int left, int middle, int right) {
    int l; //index for left_data
	int r; //index for right_data
    int curr=0; //which index for sorted array
	struct apartment left_data[middle - left + 1], right_data[right - middle]; //make space for left side and right side
	
	for (l = 0; l < middle - left + 1; l++) { //put data in left to left_data
		left_data[l] = apart[left + l];
	}
	
	for (l = 0; l < right - middle; l++) { //put data in right to right_data
		right_data[l] = apart[middle + l + 1]; 
	}
	
	l = r = 0; // index for left_data and right_data (start from 0)
	curr = left; // lindex for sorted array, start from left
	
	while (l < middle - left + 1 && r < right - middle) { // if left array still < than middle (size of left) and right array still smaller than sixe of right
		if (compare(left_data[l], right_data[r]) <= 0) {
			apart[curr++] = left_data[l++]; //if left smaller than right, put in left
		} else {
			apart[curr++] = right_data[r++]; //else put in right
		}
	}
	
	while (l < middle - left + 1) { //if there is still data in left, insert it to the final data
		apart[curr++] = left_data[l++];
	}
	
	while (r < right - middle) { //if there is still data in right, insert it to the final data
		apart[curr++] = right_data[r++];
	}
}

void merge_sort(int left, int right) {
	if (left >= right) return; // if left >= right, return because the array can no longer be split
	int middle = left + (right - left) /2; //find middle
	
	merge_sort(left, middle); //seperate left
	merge_sort(middle + 1, right); //seperate right
    
	merge(left, middle, right); //combine left, right, and sort them
}

void display_rows(){ //to display rows wanted
	long long rows;
	
	do {
	    printf("Number of rows: ");
		scanf("%lld", &rows); //input the amount of rows they want to apart
	    if (rows <= 0) {
	        printf("Invalid input. Please enter a positive number.\n"); // if number entered is negative or 0
	        wait_for_enter();
	        clear_line(8);
	        clear_line(9);
	        clear_line(10);
	        clear_line(11);
	        move_cursor_to_line(8);
	    }
	} while (rows <= 0); //repeat if number still negative
	
	if(rows>count) rows=count; //if the amount of rows you want to print exceeds number of rows, rows wanted=number of rows
	
	for(int line=0;line<108;line++){
		printf("="); //print title divider
	}
	puts("");
	
	printf("%-26s%-15s%-10s%-7s%-10s%-10s%-12s%-10s\n", "Location", "City", "Price", "Rooms", "Bathroom", "Carpark", "Type", "Furnish");
	//print title
	for(int line=0;line<108;line++){
		printf("="); //print title divider
	}
	puts("");
	
	for(int index=0;index<rows;index++){ //print until wanted rows
		printf("%-26s%-15s%-10d%-7d%-10d%-10d%-12s%-10s\n", apart[index].location1, apart[index].location2,  
		apart[index].price, apart[index].rooms, apart[index].bathrooms,  apart[index].carpark, 
		apart[index].type, apart[index].furnish); 
		// print the data
		for(int line=0;line<108;line++){
			printf("-"); // print line divider
		}
		puts("");
	}
	
	wait_for_enter(); //after done wait for enter
}

void search_data(){ //to search for data
	char column[105];
	
	do {
		
		printf("Choose column: ");
		scanf("%[^\n]", column); //ask which column they want to search
		getchar();
		
		if (strcmpi(column, "location") != 0 && strcmpi(column, "city") != 0 && strcmpi(column, "price") != 0 
		&& strcmpi(column, "rooms") != 0 && strcmpi(column, "bathroom") != 0 && strcmpi(column, "carpark") != 0 
		&& strcmpi(column, "type") != 0 && strcmpi(column, "furnish") != 0){ 
		//if they don't enter a correct column
			printf("Column not found!\n"); //print when they don't enter a correct column
			wait_for_enter(); //wait for enter
			clear_line(8); //clear lines
			clear_line(9);
			clear_line(10);
			clear_line(11);
			move_cursor_to_line(8); //go back to the line it was upposed to start at
		}
		
	} while (strcmpi(column, "location") != 0 && strcmpi(column, "city") != 0 && strcmpi(column, "price") != 0 
	&& strcmpi(column, "rooms") != 0 && strcmpi(column, "bathroom") != 0 && strcmpi(column, "carpark") != 0 
	&& strcmpi(column, "type") != 0 && strcmpi(column, "furnish") != 0);  
	// repeat until they enter a correct column
	
	char find[105];
	printf("What data do you want to find? ");
	scanf("%[^\n]", find); //ask which data they want to find
	getchar();
	
	int printed=0;
	for(int index=0;index<count;index++){
		int found=0;
		
		//make temporary variables
		char temp_price[105];
        char temp_rooms[105];
        char temp_bathrooms[105];
        char temp_carpark[105];
        // copy from struct to a temporary variable, because we are going to compare using strcmpi, which can only compare char
        // so we should change the int to char first
        sprintf(temp_price, "%d", apart[index].price);
        sprintf(temp_rooms, "%d", apart[index].rooms);
        sprintf(temp_bathrooms, "%d", apart[index].bathrooms);
        sprintf(temp_carpark, "%d", apart[index].carpark);
        
		// check every possibilty, when found, found+=1
		if (strcmpi(column, "location") == 0 && strcmpi(find, apart[index].location1) == 0) {
			found=1;
		} else if (strcmpi(column, "city") == 0 && strcmpi(find, apart[index].location2) == 0) {
            found=1;
        } else if (strcmpi(column, "price") == 0 && strcmpi(find, temp_price) == 0) {
            found=1;
        } else if (strcmpi(column, "rooms") == 0 && strcmpi(find, temp_rooms) == 0) {
            found=1;
        } else if (strcmpi(column, "bathroom") == 0 && strcmpi(find, temp_bathrooms) == 0) {
            found=1;
        } else if (strcmpi(column, "carpark") == 0 && strcmpi(find, temp_carpark) == 0) {
            found=1;
        } else if (strcmpi(column, "type") == 0 && strcmpi(find, apart[index].type) == 0) {
            found=1;
        } else if (strcmpi(column, "furnish") == 0 && strcmpi(find, apart[index].furnish) == 0){
            found=1;
		}
		if (found){
			if (!printed){ //if title, not printed , print.
				puts("Data found. Detail of data:");
				
				for(int line=0;line<108;line++){
					printf("="); //print title divider
				}
				puts("");
				
				printf("%-26s%-15s%-10s%-7s%-10s%-10s%-12s%-10s\n", "Location", "City", "Price", "Rooms", "Bathroom", "Carpark", "Type", "Furnish"); //print the title
				for(int line=0;line<108;line++){
					printf("="); //print title divider
				}
				puts("");
			}
			printf("%-26s%-15s%-10d%-7d%-10d%-10d%-12s%-10s\n", apart[index].location1, apart[index].location2,  
			apart[index].price, apart[index].rooms, apart[index].bathrooms,  apart[index].carpark, 
			apart[index].type, apart[index].furnish); 
			// print the data
			for(int line=0;line<108;line++){
				printf("-"); //print line divider
			}
			puts("");
			printed=1; // add printed, so the system knows that title is already printed
		}
	}
	
	if(!printed){
		puts("Data not found!"); // if no data was found, print "data not found"
	}
	wait_for_enter(); //wait for enter, then go back to user interface
}

void sort_data(){ //to sort data
	
	do {
		
		printf("Choose column: ");
		scanf("%[^\n]", col); //scan what column they want to sort
		getchar();
		
		if (strcmpi(col, "location") != 0 && strcmpi(col, "city") != 0 && strcmpi(col, "price") != 0 
		&& strcmpi(col, "rooms") != 0 && strcmpi(col, "bathroom") != 0 && strcmpi(col, "carpark") != 0 
		&& strcmpi(col, "type") != 0 && strcmpi(col, "furnsih") != 0){  
		// if they don't enter a correct column
			printf("Column not found!\n"); //print if there is no column by that name
			wait_for_enter(); //wait for enter
			clear_line(8); //clear lines
			clear_line(9);
			clear_line(10);
			clear_line(11);
			move_cursor_to_line(8); //go back to the line it was upposed to start at
		}
		
	} while (strcmpi(col, "location") != 0 && strcmpi(col, "city") != 0 && strcmpi(col, "price") != 0 
	&& strcmpi(col, "rooms") != 0 && strcmpi(col, "bathroom") != 0 && strcmpi(col, "carpark") != 0 
	&& strcmpi(col, "type") != 0 && strcmpi(col, "furnsih") != 0); 
	// repeat until they enter a correct column
	
	do {
		printf("Sort ascending or descending? ");
		scanf("%[^\n]", waytosort); //ask if they want to sort ascending or descending
		getchar();
		
		if(strcmpi(waytosort, "asc") != 0 && strcmpi(waytosort, "ascending") != 0 
		&& strcmpi(waytosort, "des") != 0 && strcmpi(waytosort, "descending") != 0){ 
		//if they type anything else
			printf("Please choose either ascending or descending!");
			wait_for_enter();
			clear_line(9); //clear lines
			clear_line(10);
			clear_line(11);
			clear_line(12);
			move_cursor_to_line(9); //go back to the line it was upposed to start at
		}
		
	} while (strcmpi(waytosort, "asc") != 0 && strcmpi(waytosort, "ascending") != 0 
	&& strcmpi(waytosort, "des") != 0 && strcmpi(waytosort, "descending") != 0); 
	//repeat until they do type ascending or descending
	
	merge_sort(0,count-1);
	
	for(int line=0;line<108;line++){
		printf("="); //print title divider
	}
	puts("");
	
	printf("%-26s%-15s%-10s%-7s%-10s%-10s%-12s%-10s\n", "Location", "City", "Price", "Rooms", "Bathroom", "Carpark", "Type", "Furnish");
	//print title
	for(int line=0;line<108;line++){
		printf("="); //print title divider
	}
	puts("");
	
	for(int index=0;index<10;index++){ //print until wanted rows
		printf("%-26s%-15s%-10d%-7d%-10d%-10d%-12s%-10s\n", apart[index].location1, apart[index].location2,  
		apart[index].price, apart[index].rooms, apart[index].bathrooms,  apart[index].carpark, 
		apart[index].type, apart[index].furnish); 
		// print the data
		for(int line=0;line<108;line++){
			printf("-"); // print line divider
		}
		puts("");
	}
	
	wait_for_enter(); //after done wait for enter
}

void export_data(){
	char file_name[105];
	
	do {
		printf("File name: ");
		scanf("%[^\n]", file_name);
		
		if(file_name[strlen(file_name)-1] == '.' || strstr(file_name, "/") != NULL 
		|| strstr(file_name, "<") != NULL || strstr(file_name, "*") != NULL || strstr(file_name, "?") != NULL 
		|| strstr(file_name, ">") != NULL || strstr(file_name, "\"") != NULL || strstr(file_name, "\\") != NULL 
		|| strstr(file_name, ":") != NULL || strstr(file_name, "|") != NULL){ //check if there are illegal characterd
			printf("Sorry, you cant't name a file that!\n");
			wait_for_enter(); //wait for enter
			clear_line(8); //clear lines
			clear_line(9);
			clear_line(10);
			clear_line(11);
			move_cursor_to_line(8); //go back to the line it was upposed to start at
		}
		
	} while (file_name[strlen(file_name)-1] == '.' || strstr(file_name, "/") != NULL 
		|| strstr(file_name, "<") != NULL || strstr(file_name, "*") != NULL || strstr(file_name, "?") != NULL 
		|| strstr(file_name, ">") != NULL || strstr(file_name, "\"") != NULL || strstr(file_name, "\\") != NULL 
		|| strstr(file_name, ":") != NULL || strstr(file_name, "|") != NULL); //repeat until there are illegal characterd
	
	strcat(file_name,".csv");
	FILE *new_file = fopen(file_name, "w");
    if (new_file == NULL) {
        printf("Sorry, file could not be created!\n"); // declare that the file cannot be created
        wait_for_enter();
        return;
    } else {
    	fprintf(new_file, "Location 1,Location 2,Price,Rooms,Bathrooms,CarParks,Type,Furnish\n"); //print the top row
	    for(int index=0;index<count;index++){ //print until wanted rows
			fprintf(new_file, "%s,%s,%d,%d,%d,%d,%s,%s\n", 
			apart[index].location1, apart[index].location2,  
			apart[index].price, apart[index].rooms, apart[index].bathrooms,  
			apart[index].carpark, apart[index].type, apart[index].furnish); 
			// print the data to the new file
		}
		printf("Data successfully written to file %s!", file_name); //print that the file has been created
	}
	fclose(new_file); //close the file
	wait_for_enter(); //wait until they press enter
}

int main () {
	int choice;
	read_file();
	
	do {	
		puts("What do you want to do?"); //ask what they want to do
		puts("1. Display data");
		puts("2. Search Data");
		puts("3. Sort Data");
		puts("4. Export Data");
		puts("5. Exit");
		
		printf("Your Choice: ");
		scanf("%d", &choice); //input their chocie
		getchar();
		
		switch(choice){
			case 1:
				display_rows(); //call the display_rows function to display rows
				break;
			case 2:
				search_data(); //call the search_data function to search data
				break;
			case 3:
				sort_data(); //call the sort data function to sort data
				break;
			case 4:
				export_data(); //call the export data function to export data
				break;	
		}
		
		clear_prompt(); //clear the command prompt
		
	} while (choice != 5); //while the user doesn't enter 5, which is exit, repeat the user interface

	printf("Program exited!\n");//declare that the program has sucessfully exited
	
	return 0;
}
