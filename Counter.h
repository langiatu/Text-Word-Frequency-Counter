#pragma once
#include<iostream>
#include<vector>
#include<unordered_map>
#include<unordered_set>
//#include<mutex>





class Counter {
public:
	Counter();

	bool Verify();		//对用户输入的文本文件路径进行验证

	void Control();		//显示功能菜单

	void Count();		//对当前FileName内的文本文件进行统计

	void ShowTopN(int n);	//根据n输出频率前n的统计记录

	void ShowAllCount();	//输出所有单词的出现频率排序

	void ShowFristSort();	//根据首字母排序

	void SortSelection(int selection);		//选择排序方式 1.所有单词从高到低输出 2.按首字母排序输出 3.输出词频前N的单词
	
	~Counter();


	std::string FileName;	//接收用户输入的文件名
	std::unordered_map<std::string, int> WordCount;		//用于统计英文文本单词出现的次数
    std::unordered_set<std::string> stopWords;			//常见的英文停用词
	std::vector<std::pair<std::string, int>> Words;		//用于排序后的
};

