#include"stdafx.h"
#include"cmdpsr.h"
#include<cstdio>
#define SET_POSITION "SetPosition"
#define SET_COLOR    "SetColor"
#define COMMENT      "#"


int main()
{
   CCmdParser* parser=new CCmdParser();
   parser->LoadScriptFile("setting.txt");
  // printf("%s\n",parser->m_script);
   char destCommand[MAX_COMMAND_SIZE]={0};
   for(int i=0;i<parser->GetTotalLines();i++)
   {
	    parser->ParseCommand(destCommand);
		if(strcmp(destCommand,"name")==0)
		{
			char* param=new char[MAX_COMMAND_SIZE];
			parser->ParseStringParam(param);
			printf("%s:%s\n",destCommand,param);
		}
		else if(strcmp(destCommand,"gender")==0)
		{
			char param[MAX_COMMAND_SIZE]={0};
			parser->ParseStringParam(param);
			printf("%s:%s\n",destCommand,param);
		}
		else if(strcmp(destCommand,"married")==0)
		{
			 
			char boolstr[6]={0};
			if(!parser->ParseBoolParam())
			{
				 
				strcpy(boolstr,"false");
				boolstr[strlen(boolstr)]='\0';
				 
			}
			else
			{
				 
				strcpy(boolstr,"true");
				boolstr[strlen(boolstr)]='\0';
				 
			}
		 printf("%s:%s\n",destCommand,boolstr);
		}
		else if(strcmp(destCommand,"age")==0)
		{
			printf("%s:%d\n",destCommand,parser->ParseIntParam());
		}
		else if(strcmp(destCommand,"temperature")==0)
		{
			  
			printf("%s:%f\n",destCommand,parser->ParseFloatParam());
		}
		else if(stricmp(destCommand,COMMENT)==0)
		{
			printf("line of comment\n");
		}
		 
		else
		{
			printf("Error...");
		}
		parser->MoveToNextLine();
   }
   
  
   
   getchar();
   return 0;
}