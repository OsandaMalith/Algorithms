#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

/*
 * A variant Vignere cipher impleneted in C for encrypting text.
 * Coded by Osanda Malith Jayathissa
 * https://github.com/OsandaMalith/
 * @osandaMalith
*/

void fatal(char *msg) {
  char err_msg[100];
  strcpy(err_msg, "[!!] Fatal Error");
  strncat(err_msg, msg, 75);
  perror(err_msg);
  getch();
  exit(EXIT_FAILURE);
}

void banner() {
  const char *banner = 

"\t _ _  _                          \n"
"\t| | |<_> ___ ._ _  ___  _ _  ___ \n"
"\t| ' || |/ . || ' |/ ._>| '_>/ ._>\n"
"\t|__/ |_|\\_. ||_|_|\\___.|_|  \\___.\n"
"\t        <___'                   \n"
"\t ___                            _            \n"
"\t| __>._ _  ___  _ _  _ _  ___ _| |_ ___  _ _ \n"
"\t| _> | ' |/ | '| '_>| | || . \\ | | / ._>| '_>\n"
"\t|___>|_|_|\\_|_.|_|  `_. ||  _/ |_| \\___.|_|  \n"
"\t                    <___'|_|                 \n\n";


  for(banner; *banner; ++banner) fprintf(stdout, "%c", *banner);            
}

void Decrypt() {
  size_t i;
  int enc = 0;
  FILE *fpIn, *fpOut;
  char filename[100];
  unsigned char key[1024];
  
  printf("[+] Enter the file location: ");
  scanf("%[^\n]", &filename);
  
  if(!(fpIn = fopen(filename, "r"))) fatal(" in opening file");
  
  printf("[*] Enter your key: ");
  fflush(stdin);
  
  for(i = 0; (key[i] = getchar())!='\n'; ++i);
  key[i]='\0';
 
  if(!(fpOut = fopen("dtext.txt", "w"))) 
  fatal(" in decryption while writing buffer to file\n");

  printf("[*] Decrypting using a key length of: %d\n", strlen(key));
    
  for (i = 0; fscanf(fpIn, "%02X", &enc) != EOF; ++i) 
  fprintf(fpOut, "%c", enc ^ key[i % strlen(key)]);   
  
  fclose(fpIn);
  fclose(fpOut);
}

void Encrypt(){
  size_t i;
  FILE *fpIn, *fpOut;
  char filename[100];
  unsigned char key[1024],ch;
  
  printf("[+] Enter the file location: ");
  scanf("%[^\n]", &filename);
  
  if(!(fpIn = fopen(filename, "r"))) fatal(" in opening file");
  
  printf("[*] Enter your key: ");
  fflush(stdin);
  
  for(i = 0; (key[i] = getchar())!='\n'; ++i);
  key[i]='\0';
  
  if(!(fpOut = fopen("ctext.txt", "w"))) 
  fatal(" in encryption while writing buffer to file\n");

  printf("[*] Encrypting using a key length of: %d\n", strlen(key));
   
  for (i = 0; fscanf(fpIn, "%c", &ch) != EOF; ++i) 
  fprintf(fpOut, "%02X", ch ^ key[i % strlen(key)]);   
 
  fclose(fpIn);
  fclose(fpOut);
}
  
void (*funcs[])() = { Encrypt, Decrypt, NULL };

int main(int argc, char *argv[]) {
  banner();
  
  puts("\t---Welcome to Osanda's Crypto Program---\n");
   
  while(prompt());
  
  return 0;
} 

int prompt() {
  puts("\n[?] Choose an Option");
  puts("");
  puts("1. Encrypt the File");
  puts("2. Decrypt the File");
  puts("Q. Quit.");
  printf(">> ");
  
  char *response;
  size_t numchars = 1;

  response = fgets(&numchars, sizeof(numchars), stdin);
  return jump(response);
}

int jump(char * s) {
	char code = s[0];
	if(code == 'q' || code == 'Q') return 0;

	int func_length;
	for(func_length = 0; funcs[func_length] != NULL; func_length++);

	unsigned int i = (int) code - '0';
	i--;
	if((i < 0) || (i > 8)) {
		puts("[!] Invalid choice");
		return 1;
	}

	if(i < func_length) {
		funcs[i]();
		return 1;
	} else {
		puts("[!] Invalid choice");
		return 1;
	}
}
