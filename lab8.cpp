#include "func.h"

int main(){
	srand(time(NULL));
	
	FILE* fin = nullptr;
	
	int choose = 0;
	printf("Enter number of task: ");
	scanf("%d", &choose);
	
	if(choose == 1){
		int arrSize = 10;
		char* fileName = const_cast<char*>("database.dat");
		
		Account accs[arrSize] = {
			{ (rand() % 1000000 + 900000), "Edward  ", "Hussain", 
				"owafale-9254@yopmail.co", "122eg3rf8h9eoi", PRIVILEGES::user },
			{ (rand() % 1000000 + 900000), "Nicholas", "Parry  ", 
				"eamineeee.koko@arkan.co", "8273ry9hfadfea", PRIVILEGES::user },
			{ (rand() % 1000000 + 900000), "Jake    ", "Walker ", 
				"drenan_cmr2@emailonl.me", "9843ugt5ifbvhje", PRIVILEGES::user },
			{ (rand() % 1000000 + 900000), "Michael ", "Adams  ", 
				"unada-khalidx@getmap.cm", "12e9dh3krlktkn", PRIVILEGES::user },
			{ (rand() % 1000000 + 900000), "Lucas   ", "James  ", 
				"kkipkjht@dustfreetil.or", "dqefwvuasdgiuo", PRIVILEGES::user },
			{ (rand() % 1000000 + 900000), "Emmett  ", "Rasmuss", 
				"2hetlarsah@moboinfo.xyz", "12ugedqwbiksana", PRIVILEGES::user },
			{ (rand() % 1000000 + 900000), "Thomas  ", "Connor ", 
				"tazzdine_rajawim@wer.gq", "@#!EGDBKL:KLm;l", PRIVILEGES::blocked },
			{ (rand() % 1000000 + 900000), "Felix   ", "Joseph ", 
				"yomert-2010@koeken.shop", "XXXxxxXX8uodpjh", PRIVILEGES::user },
			{ (rand() % 1000000 + 900000), "Jadiel  ", "Bernard", 
				"oaymenalb@copistaed.gad", "230rpiaHCOIHj3j", PRIVILEGES::admin },
			{ (rand() % 1000000 + 900000), "Jagger  ", "Jennins", 
				"6amer@verifsvcheme.comt", "@!PIJDFMNXCSaaa", PRIVILEGES::blocked }
		};
		
		if((fin = fopen64(fileName, "w")) == nullptr)
			printf("Can't create file!\n");
		else{
			printf("File was successfully created!\n");
			
			for(int i = 0; i < arrSize; i++){
				fprintf(fin, "%s", "---------------------------------------------------------------------------------------------------------------------------------\n");
				
				fprintf(fin, "|\t%ld\t|\t%s\t|\t%s\t|\t%s\t|\t%s\t|\t%d\t|\n", 
					accs[i].ID, (accs[i].name).c_str(), (accs[i].surname).c_str(), 
					(accs[i].mail).c_str(), (accs[i].psswd).c_str(), accs[i].privileges);
			}
			fprintf(fin, "%s", "---------------------------------------------------------------------------------------------------------------------------------\n");
		
			printf("Do you want to rename file? Yes(0) No(1): ");
			scanf("%d", &choose);
			
			if(choose == 0){
				printf("Enter new file name: ");
				char* newFileName = (char*)calloc(BUFF_SIZE, sizeof(char*));
				scanf("%s", newFileName);
			
				if(rename(fileName, newFileName) == 0)
					puts("File name successfully renamed!\n");
				else perror("<ERROR>::lab8.cpp::53-56\n");
				
				delete[] newFileName;
			}
			else if(choose == 1){
				exit(EXIT_SUCCESS);
			}
			else throw "<ERROR>::lab8.cpp::48"; 
		}		
		fclose(fin);
	}
	else if(choose == 2){
		createFile(fin, const_cast<char*>("filename.dat"));
		//printFileData(fin, const_cast<char*>("filename.dat"));
	}
	else if(choose == 3){
		fileSize(fin, const_cast<char*>("database.dat"));
	}
	else if(choose == 4){
		char* str = (char*)calloc(BUFF_SIZE, sizeof(char*));
		printf("Write data in binary and common files: ");
		scanf("%s", str);
		
		createBinary(fin, const_cast<char*>("binary"));
		writeInBinary(fin, const_cast<char*>("binary"), str);
		writeInFile(fin, const_cast<char*>("filename.dat"), str);	
		
		long binary = binaryFileSize(fin, const_cast<char*>("binary"));
		long common = fileSize(fin, const_cast<char*>("filename.dat"));
		
		compareFileSizes(binary, common);
		
		free(str);
	}
	else if(choose == 5){
		readAndPrintFile(fin, const_cast<char*>("database.dat"));
		readAndPrintBinaryFile(fin, const_cast<char*>("binary"));
	}
	else if(choose == 6){
		long element = 0L;
		
		printf("Enter number of element: ");
		scanf("%ld", &element);
		
		readOneSymbolFromFile(fin, const_cast<char*>("database.dat"), element);
	}
	else if(choose == 7){
		long position = 0L;
		Account acc;
		char* name = new char[BUFF_SIZE];
		char* surname = new char[BUFF_SIZE];
		char* mail = new char[BUFF_SIZE];
		char* psswd = new char[BUFF_SIZE];
		
		printf("On which position would you like to fill data? ");
		scanf("%ld", &position);
		
		acc.ID = rand() % 1000000 + 900000;
		printf("Enter name: ");
		scanf("%s", name);
		printf("Enter surname: ");
		scanf("%s", surname);
		printf("Enter mail: ");
		scanf("%s", mail);
		printf("Enter password: ");
		scanf("%s", psswd); 
		
		acc.name = name;
		acc.surname = surname;
		acc.mail = mail;
		acc.psswd = psswd;
		acc.privileges = PRIVILEGES::user;
		
		appendStructInFile(fin, const_cast<char*>("database.dat"), position, acc);
		
		delete[] name;
		delete[] surname;
		delete[] mail;
		delete[] psswd;
	}
	return EXIT_SUCCESS;
}
