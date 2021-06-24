#include"stdafx.h"
#include"cmdpsr.h"
#include<fstream>
#include<cstdio>
 

using namespace std;

CCmdParser::CCmdParser():totalScriptLines(0),currentLine(0),currentLineChar(0),m_script(0){}
CCmdParser::~CCmdParser(){Shutdown();}

//加载命令脚本
bool CCmdParser::LoadScriptFile(char* filename)
{
	 
	//if(!filename) return false;
	ifstream input,input2;
	char tempLine[MAX_LINE_SIZE];

	//获取脚本文件的总行数
	input.open(filename);
	if(!input.is_open()) return false;
	Shutdown();
	while(!input.eof())
	{
		//input.getline(tempLine,MAX_LINE_SIZE,'\n');
		input.getline(tempLine,MAX_LINE_SIZE);
		totalScriptLines++;
	}
	totalScriptLines--;//去掉多余行
	//printf("total lines:%d\n",totalScriptLines);
	input.close();

	//read lines
	input2.open(filename);
	if(!input2.is_open()) return false;
	m_script = new char*[totalScriptLines];
	for(int i=0;i<totalScriptLines;i++)
	{
		//m_script[i]=new char[MAX_LINE_SIZE+1];
		char* tmp=new char[MAX_LINE_SIZE+1];
		//input2.getline(m_script[i],MAX_LINE_SIZE,'\n');
		input2.getline(tmp,MAX_LINE_SIZE);
		//printf("%s\n",tmp);
		//将每一行内容保存到vector
		m_contents.push_back(tmp);
	}
	input2.close();
	//printf("%s",m_script);
	/*for(vector<char*>::iterator it=m_contents.begin();it!=m_contents.end();it++)
	{
		printf("%s\n",*it);
	}*/
	return true;
}
//解析命令，获取属性名
void CCmdParser::ParseCommand(char *destCommand)
{
	int commandSize=0;
	if(!destCommand) return;
	//判断有效性，如果当前行比总行数大，就结束
	if(currentLine>=totalScriptLines) return;
	//如果已经读到行末尾，就结束
	if(currentLineChar>=(int)strlen(m_contents.at(currentLine))) return;
	//初始化接收字符串
	destCommand[0]='\0';
	//判断是否是注释
	if(IsLineComment())
	{
		destCommand[0]='#';
	    destCommand[1]='\0';
	}
	while(currentLineChar<(int)strlen(m_contents.at(currentLine)))
	{
		//如果判断空格或者结束符，就返回
		/*if(m_script[currentLine][currentLineChar]==' ' ||
			m_script[currentLine][currentLineChar]=='\0') return;*/
		if(m_contents.at(currentLine)[currentLineChar]==' '||
			m_contents.at(currentLine)[currentLineChar]=='\0') return;

		//将内容读到destCommand
		destCommand[commandSize]=m_contents.at(currentLine)[currentLineChar];
		//移动指针
		commandSize++;
		currentLineChar++;
	}
	//跳过下一个空格
	currentLineChar++;
	destCommand[commandSize]='\0';
	printf("%s\n",destCommand);
}

//解析参数
void  CCmdParser::ParseStringParam(char* destString)
{
	int paramSize=0;
	bool endQuoteFound = false;
	char* tmp=new char[MAX_PARAM_SIZE+1];
	//if(!destString) return;
   //判断有效性，如果当前行比总行数大，就结束
	if(currentLine>=totalScriptLines) return;
	//如果已经读到行末尾，就结束
	if(currentLineChar>=(int)strlen(m_contents.at(currentLine))) return;
	
	destString[0]='\0';
	//跳过左双引号
	/*if(m_contents.at(currentLine)[currentLineChar] =='"')
    {
               endQuoteFound = true;
			   currentLineChar+=2;
    }
	else*/
	currentLineChar++;
	//printf("%s\n",m_contents.at(currentLine));
	while(currentLineChar<(int)strlen(m_contents.at(currentLine)))
	{

		/*if(m_contents.at(currentLine)[currentLineChar] =='"')
            {
               endQuoteFound = true;
            }*/
		/*if(m_contents.at(currentLine)[currentLineChar]=='\0')
			break;*/
		
		tmp[paramSize]=m_contents.at(currentLine)[currentLineChar];
		//printf("%c",destString[paramSize]);
		paramSize++;
		currentLineChar++;
		/* if(m_contents.at(currentLine)[currentLineChar] =='"')
            {
               endQuoteFound = true;
               break;
            }
		if(m_contents.at(currentLine)[currentLineChar]=='\0')
			break;*/
		

	}
	//跳过右双引号
	// if(endQuoteFound) currentLineChar += 2;
    // else 
    currentLineChar++;
	tmp[paramSize]='\0';
	//printf("tmp=%s\n,lenght of tmp=%d",tmp,strlen(tmp));
	 
	//去掉双引号
	char* p=new char[strlen(tmp)];
	int y=0;
	 for(int i=0;i<strlen(tmp);i++)
	 {
        if(tmp[i]==' '||tmp[i]=='"') 
		{
			continue;
		}
		p[y]=tmp[i];
		y++;
	 }
	 p[y]='\0';
	//printf("p=%s\n",p);
	strncpy(destString,p,strlen(p));
	
	destString[y]='\0';
	//printf("%s\n",destString);
}

bool  CCmdParser::ParseBoolParam()
{
	int paramSize=0;
	char tmp[MAX_PARAM_SIZE];
	bool boolval=false;
	//判断有效性
	if(currentLine >= totalScriptLines) return false;
    if(currentLineChar >= (int)strlen(m_contents.at(currentLine))) return false;
	while(currentLineChar<(int)strlen(m_contents.at(currentLine)))
	{
		  
		/*if(m_contents.at(currentLine)[currentLineChar]==' '||
			m_contents.at(currentLine)[currentLineChar]=='\0')
			break;*/
		
		tmp[paramSize]=m_contents.at(currentLine)[currentLineChar];
		paramSize++;
		currentLineChar++;

	}
	//跳过空格
	currentLineChar++;
	tmp[paramSize]='\0';
	char res[MAX_PARAM_SIZE]={0};
	//strncpy(res,tmp+1,strlen(tmp));
	//去除空格
	int y=0;
	for(int i=0;i<strlen(tmp);i++)
	{
		if(tmp[i]==' ')
		{
			continue;
		}
		res[y]=tmp[i];
		y++;
	}
	res[y]='\0';
	//printf("%s:length:%d\n",res,strlen(res));
	char* truestr="true";
	
	if(strncmp(res,truestr,4)==0) 
	{
		//printf("equal\n");
		boolval=true;
		
	}
	else
	{
		//printf("not equal\n");
		boolval=false;
	}
	
	return boolval;
}

int  CCmdParser::ParseIntParam()
{
	int paramSize=0;
	char tmp[MAX_PARAM_SIZE];
	//判断有效性
	if(currentLine >= totalScriptLines) return 0;
    if(currentLineChar >= (int)strlen(m_contents.at(currentLine))) return 0;
	while(currentLineChar<(int)strlen(m_contents.at(currentLine)))
	{
		  
		/*if(m_contents.at(currentLine)[currentLineChar]==' '||
			m_contents.at(currentLine)[currentLineChar]=='\0')
			break;*/
		
		tmp[paramSize]=m_contents.at(currentLine)[currentLineChar];
		paramSize++;
		currentLineChar++;

	}
	//跳过空格
	currentLineChar++;
	tmp[paramSize]='\0';
	//printf("%s\n",tmp);
	return atoi(tmp);
}
float CCmdParser::ParseFloatParam()
{
	int paramSize=0;
	char tmp[MAX_PARAM_SIZE];
	//判断有效性
	if(currentLine >= totalScriptLines) return false;
    if(currentLineChar >= (int)strlen(m_contents.at(currentLine))) return false;
	while(currentLineChar<(int)strlen(m_contents.at(currentLine)))
	{
		  
		if(m_contents.at(currentLine)[currentLineChar]==' ')
			currentLineChar++;
		
		tmp[paramSize]=m_contents.at(currentLine)[currentLineChar];
		paramSize++;
		currentLineChar++;

	}
	//跳过空格
	currentLineChar++;
	tmp[paramSize]='\0';
	//printf("%s\n",tmp);
	return (float)atof(tmp);
}

//移动到开始位置
void CCmdParser::MoveToStart()
{
	currentLine = 0;
   currentLineChar=0;
}
void CCmdParser::MoveToNextLine()
{
      currentLine++;
	  currentLineChar=0;
}
	
	
//判断是否是注释
bool CCmdParser::IsLineComment()
{
	if(m_contents.at(currentLine)[0]=='#') return true;

	return false;
}

//get函数
//获取当前行号
int CCmdParser::GetCurrentLineNum()
{
	return currentLine;
}
//获取总行数
int CCmdParser::GetTotalLines()
{
	return totalScriptLines;
}
//清理工作
void CCmdParser::Shutdown()
{
	if(m_script)//二级指针先释放里面的指针，再释放外面的指针
	{
		for(int i=0;i<totalScriptLines;i++)
		{
			if(m_script[i])
			{
				delete[] m_script[i];
				m_script[i]=0;
			}
		}
		delete m_script;
		m_script=0;
	}
	currentLine=0;
	currentLineChar=0;
	totalScriptLines=0;
}