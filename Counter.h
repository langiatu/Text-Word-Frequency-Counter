#pragma once
#include<iostream>
#include<vector>
#include<unordered_map>
#include<unordered_set>





class Counter {
public:
	Counter();

	bool Verify();		//对用户输入的文本文件路径进行验证

	void Control();		//显示功能菜单

	void Count();		//对当前FileName内的文本文件进行统计

	void ShowCount(int n);	//根据n输出频率前n的统计记录
	
	~Counter();


	std::string FileName;	//接收用户输入的文件名
	std::unordered_map<std::string, int> WordCount;		//用于统计英文文本单词出现的次数
    std::unordered_set<std::string> stopWords;			//常见的英文停用词
	std::unordered_set<std::string> punc;				//常出现的标点符号
};

