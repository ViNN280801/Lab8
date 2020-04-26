#include<iostream>
#include<cstdlib>
#include<cstring>

#define BUFF_SIZE 256

using namespace std;

typedef enum { admin, user, blocked } PRIVILEGES;

struct Account{
	long ID;
	string name;
	string surname;
	string mail;
	string psswd;
	PRIVILEGES privileges;
};

void createFile(FILE* stream, char* fileName){
	if((stream = fopen64(fileName, "w")) == nullptr)
		printf("Can't create file!\n");
	else
		printf("File was successfully created!\n");
		
	fclose(stream);
}

void createBinary(FILE* stream, char* fileName){
	if((stream = fopen64(fileName, "wb")) == nullptr)
		printf("Can't create binary file!\n");
	else
		printf("Binary file was successfully created!\n");
		
	fclose(stream);
}
		
void renameFile(char* oldFileName){
	printf("Enter new file name: ");
	char* newFileName = (char*)calloc(BUFF_SIZE, sizeof(char*));
	scanf("%s", newFileName);
			
	if(rename(oldFileName, newFileName) == 0)
		puts("File name successfully renamed!\n");
	else perror("<ERROR>::func.h::42-46\n");
				
	free(newFileName);
}

void printFileData(FILE* stream, char* fileName){
	char* data = new char[BUFF_SIZE];
	
	if((stream = fopen64(fileName, "r")) == nullptr)
		printf("Can't read file [%s]!", fileName);
	else{
		while(!feof(stream)){
			if(feof(stream)){
				perror("Read file error!");
				break;
			}
			fscanf(stream, "%s", data);
		}
		
		printf("%s\n", data);
	}
	
	fclose(stream);
	delete[] data;
}

long fileSize(FILE* stream, char* fileName){
	int endOfFile = 0, count = 0;
	long position = 0;
	char* data = (char*)calloc(BUFF_SIZE, sizeof(char*));
	
	if((stream = fopen64(fileName, "r")) == nullptr)
		printf("Can't read file [%s]!", fileName);
	else{
		while(!feof(stream)){
			count++;
			if(feof(stream)){
				perror("Read file error!");
				break;
			}
			fscanf(stream, "%s", data);
		}
		endOfFile = fseek(stream, count, SEEK_END);
		
		position = ftell(stream);
	}
	
	printf("Size of your file is - %ld B (%.3lf kB)\n", position, 
		((double)(position)) / 1024);
		
	fclose(stream);
	delete[] data;
	
	return ((double)position);
}

void writeInBinary(FILE* stream, char* fileName){
	char* str = (char*)calloc(BUFF_SIZE, sizeof(char*));
	
	if((stream = fopen64(fileName, "ab")) == nullptr)
		printf("Can't open file!\n");
	else{
		printf("Enter something what do you want to be in binary file: ");
		scanf("%s", str);
		fwrite(str, sizeof(char*), BUFF_SIZE, stream); 
	}
	
	fclose(stream);
	free(str);
}

void writeInBinary(FILE* stream, char* fileName, char* data){
	if((stream = fopen64(fileName, "wb")) == nullptr)
		printf("Can't open file!\n");
	else{
		fwrite(data, sizeof(char*), BUFF_SIZE, stream); 
	}
	
	fclose(stream);
}

void writeInFile(FILE* stream, char* fileName){
	char* str = (char*)calloc(BUFF_SIZE, sizeof(char*));
	
	if((stream = fopen64(fileName, "w")) == nullptr)
		printf("Can't open file!\n");
	else{
		printf("Enter something what do you want to be in binary file: ");
		scanf("%s", str);
		fwrite(str, sizeof(char*), BUFF_SIZE, stream); 
	}
	
	fclose(stream);
	free(str);
}

void writeInFile(FILE* stream, char* fileName, char* data){
	if((stream = fopen64(fileName, "a")) == nullptr)
		printf("Can't open file!\n");
	else{
		fwrite(data, sizeof(char*), BUFF_SIZE, stream); 
	}
	
	fclose(stream);
}

long binaryFileSize(FILE* stream, char* fileName){
	int count = 0;
	long position = 0;
	char* data = (char*)calloc(BUFF_SIZE, sizeof(char*));
	
	if((stream = fopen64(fileName, "rb")) == nullptr)
		printf("Can't read binary file [%s]!", fileName);
	else{
		fseek(stream, 0L, SEEK_SET);
		while(!feof(stream)){
			count++;
			if(feof(stream)){
				perror("Read binary file error!");
				break;
			}
			fread(data, sizeof(char*), BUFF_SIZE, stream);
		}
		fseek(stream, count, SEEK_END);
		
		position = ftell(stream);
	}
	
	printf("Size of your binary file is - %ld B (%.3lf kB)\n", position, 
		((double)(position)) / 1024);
		
	fclose(stream);
	delete[] data;
	
	return ((double)position);
}

void compareFileSizes(long size1, long size2){
	if(size1 > size2)
		printf("File [binary] is bigger than [filename.dat]\n");
	else if(size2 > size1)
		printf("File [filename.dat] is bigger than [binary]\n");
	else if(size1 == size2)
		printf("Sizes of files are equals\n");
	else throw "<ERROR>::func.h::157-Unknown error";
}

void readAndPrintBinaryFile(FILE* stream, char* fileName){
	binaryFileSize(stream, fileName);
	
	char* data = new char[BUFF_SIZE];
	
	if((stream = fopen64(fileName, "rb")) == nullptr)
		printf("Can't read file [%s]!", fileName);
	else{
		fseek(stream, 0L, SEEK_SET);
		printf("There is what I was able to read from the binary file - [%s]:\n", fileName);
		
		while(!feof(stream)){
			if(feof(stream)){
				perror("Read file error!");
				break;
			}
			
			fread(data, sizeof(char*), BUFF_SIZE, stream);
		}
		printf("%s", data);
		printf("\n");
	}
	
	fclose(stream);
	delete[] data;
}

void readAndPrintFile(FILE* stream, char* fileName){
	fileSize(stream, fileName); 

	char* data = new char[BUFF_SIZE];
	
	if((stream = fopen64(fileName, "r")) == nullptr)
		printf("Can't read file [%s]!", fileName);
	else{
		printf("There is what I was able to read from the file - [%s]:\n", fileName);
		
		while(!feof(stream)){
			if(feof(stream)){
				perror("Read file error!");
				break;
			}
			
			fread(data, sizeof(char*), BUFF_SIZE, stream);
		}
		printf("%s\n", data);
	}
	
	fclose(stream);
	delete[] data;
}

void readOneSymbolFromFile(FILE* stream, char* fileName, long numberOfElement){
	char* data = new char[BUFF_SIZE];
	char symbol = '*';
	
	if((stream = fopen64(fileName, "rb")) == nullptr)
		printf("Can't read file [%s]!", fileName);
	else{
		if(fseek(stream, numberOfElement, SEEK_CUR))
			perror("fseek() failed");
		else{
			fread(data, sizeof(char), 1, stream);
		}		
		symbol = data[0];
		
		printf("Symbol from file: \n");
		if(symbol == ' '){
			printf("Your symbol is \"%c\" (space)\n", symbol);
		}
		else if(symbol == '\0'){
			printf("Your symbol is \'\\0\'\n");
		}
		else 
			printf("Symbol in file [%s] under the number %ld is - \"%c\"\n", 
				fileName, numberOfElement, symbol);
	}
	
	fclose(stream);
	delete[] data;
}

void appendStructInFile(FILE* stream, char* fileName, long offset, Account acc){
	char* structData = new char[(acc.name).length() + (acc.surname).length() + (acc.mail).length() + (acc.psswd).length() + BUFF_SIZE];
	
	if((stream = fopen(fileName, "a")) == nullptr)
		printf("Can't open file [%s] to add data\n", fileName);
	else{		
		if(fseek(stream, offset, SEEK_CUR)) 
			perror("fseek() error");
		else{
			const char* separator = "---------------------------------------------------------------------------------------------------------------------------------\n";
			
			strncat(structData, "|\t", sizeof(char*));
			strncat(structData, (to_string(acc.ID)).c_str(), sizeof(to_string(acc.ID))); 
			strncat(structData, "\t|\t", sizeof(char*));
			strncat(structData, (acc.name).c_str(), (acc.name).length());
			strncat(structData, "\t|\t", sizeof(char*));
			strncat(structData, (acc.surname).c_str(), (acc.surname).length());
			strncat(structData, "\t|\t", sizeof(char*));
			strncat(structData, (acc.mail).c_str(), (acc.mail).length());
			strncat(structData, "\t|\t", sizeof(char*));
			strncat(structData, (acc.psswd).c_str(), (acc.psswd).length());
			strncat(structData, "\t|\t", sizeof(char*));
			strncat(structData, (to_string(acc.privileges)).c_str(), sizeof(to_string(acc.privileges))); 
			strncat(structData, "\t|\n", sizeof(char*));
			strncat(structData, separator, strlen(separator));
			
			fwrite(structData, sizeof(Account), 1, stream);
		}
	}
	
	fclose(stream);
	delete[] structData;
}
