
#ifndef _CMDPSR_H_
#define _CMDPSR_H_
#include<vector>
using namespace std;//这个不能少
#define MAX_COMMAND_SIZE   32
#define MAX_LINE_SIZE      3072
#define MAX_PARAM_SIZE     2048
 

class CCmdParser
{
public:
	CCmdParser();
	~CCmdParser();

	//加载命令脚本
	bool LoadScriptFile(char* filename); 
	//解析命令，获取属性名
	void ParseCommand(char *destCommand);
	//解析参数
	void  ParseStringParam(char* destString);
	bool  ParseBoolParam();
	int   ParseIntParam();
	float ParseFloatParam();

	//移动到行首或者下一行
	void MoveToStart();
	void MoveToNextLine();
	
	
	//判断是否是注释
	bool IsLineComment();

	//get函数
	//获取当前行号
	int GetCurrentLineNum();
	//获取总行数
	int GetTotalLines();
	//清理工作
	void Shutdown();
private:
	  int totalScriptLines;
      int currentLine;//当前行
      int currentLineChar;//当前行的当前第n个字符
      char **m_script;
	  vector<char*> m_contents;
};


#endif