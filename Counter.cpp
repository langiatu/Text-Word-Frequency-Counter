#include<iostream>
#include "Counter.h"
#include<fstream>
#include<algorithm>
//#include<thread>

Counter::Counter()
{

	this->WordCount.clear();
	this->Words.clear();
	this->stopWords = {
	"a", "an", "the", "is", "are", "was", "were", "be", "been", "being",
	"to", "of", "for", "on", "at", "in", "by", "with", "without", "about",
	"above", "across", "after", "against", "along", "among", "around",
	"i", "you", "he", "she", "it", "we", "they", "me", "him", "her", "us", "them",
	"my", "your", "his", "her", "our", "their", "mine", "yours", "ours", "theirs",
	"this", "that", "these", "those", "some", "any", "no", "all", "both", "each",
	"few", "more", "most", "other", "some", "such", "than", "then", "thence",
	"there", "therefore", "these", "they", "this", "those", "though", "through",
	"until", "unto", "when", "where", "wherever", "which", "while", "whilst",
	"and", "but", "or", "nor", "for", "so", "yet", "didnt", "its", "dont", "over",
	"however", "under"
	};
	
	this->FileName = R"()";
}

//对用户输入的文件路径进行验证，并输出提示信息
bool Counter::Verify()
{
	bool verify = false;

	//检查文件是否存在
	std::ifstream file(this->FileName, std::ios::in);
	if (file.is_open()) {

		//std::cout << "open" << std::endl;
		verify = true;
	}
	else {
		std::cout << "文件打开失败，请检查文件路径是否正确" << std::endl;
	}
	return verify;
}

//对文本内出现的单词进行统计
void Counter::Count()
{
	std::ifstream file;	

	file.open(this->FileName, std::ios::in);

	if (!file.is_open()) {
		std::cout << "文件打开失败" << std::endl;
	}
	else {
		while(!file.eof()) {
			std::string word;		//用于接收文本中的单词
			bool isStopWord = false;	//当前单词是否为停用词

			file >> word;

			//将英文文本的大写转为小写
			std::transform(word.begin(), word.end(), word.begin(), [](unsigned char c) {
				return std::tolower(c);
				});

			//当word不为英文字母时跳过
			word.erase(std::remove_if(word.begin(), word.end(), [](unsigned char c) {
				return !std::isalpha(c);
				}),word.end());


			//去除停用词
			for (auto it = this->stopWords.begin(); it != this->stopWords.end(); it++) {
				if (!it->compare(word)) {
					isStopWord = true;
					break;
				}
			}

			/*std::cout << word << std::endl;*/

			if (!isStopWord) {		//当word不为停用词时 1、WordCount中没有该单词 2、WordCount中已有该单词
				bool isExist = false;

				for (auto it = this->WordCount.begin(); it != this->WordCount.end(); it++) {
					if (word == it->first) {
						isExist = true;
					}
				}

				if (isExist) {		//已存在
					auto count = this->WordCount.find(word);
					count->second++;
				}
				else {				//不存在
					if (!word.empty()) {
						this->WordCount.insert(std::make_pair(word, 1));
					}
				}
			}
		}
	}

	file.close();

	std::cout << "统计完成" << std::endl;

	{
		for (auto mit = this->WordCount.begin(); mit != this->WordCount.end();mit++) {
			this->Words.push_back(std::make_pair(mit->first, mit->second));
		}
	}
}

void Counter::SortSelection(int selection) 
{
	if (selection == 1) {
		this->ShowAllCount();
	}
	else if (selection == 2) {
		this->ShowFristSort();
	}
	else if (selection == 3) {
		int n;
		std::cout << "需要统计前N个高频词" << std::endl;

		while (!(std::cin >> n)) {
			std::cout << "输入无效，请重新输入" << std::endl;
		}

		this->ShowTopN(n);
	}
}

//根据n输出频率前n的统计记录
void Counter::ShowTopN(int n)
{
	std::sort(this->Words.begin(), this->Words.end(), [](const auto& a,const auto& b) {
		return a.second > b.second;
		});

	//当N大于总单词数时
	if (n > this->Words.size()) {
		for (auto it = this->Words.begin(); it != this->Words.end(); it++) {
			std::cout << it->first << "  " << it->second << std::endl;
		}
	}
	else {
		int i = 0;
		auto it = this->Words.begin();
		while (i < n) {
			std::cout << it->first << "  " << it->second << std::endl;
			it++;
			i++;
		}
	}
}

//输出所有单词的出现频率排序
void Counter::ShowAllCount()
{
	std::sort(this->Words.begin(), this->Words.end(), [](const auto& a, const auto& b) {
			return a.second > b.second;
		});

	
	for (auto it = this->Words.begin(); it != Words.end();it++) {
		std::cout << it->first << " " << it->second << std::endl;
	}
}

//输出根据首字母进行排序
void Counter::ShowFristSort()
{

}

//根据用户选项进行排序
void Counter::Control()
{
	std::cout << "请输入需要进行统计的英文文本文件的完整路径" << std::endl;

	while (std::cin >> this->FileName && !this->Verify()) {	//文件验证失败直接返回
		std::cout << "请输入正确的路径格式\a" << std::endl;
		this->FileName.clear();
	}

	//文件验证通过，开始进行统计
	//std::thread count(Count);
	this->Count();

	{
		std::cout << "1.所有单词从高到低输出 2.按首字母排序输出 3.输出词频前N的单词" << std::endl;
		std::cout << "请输入选项  ";
	}

	int selection;
	
	while (std::cin >> selection && !(selection > 0 && selection < 4)) {
		std::cout << "选项无效，请重新输入" << std::endl;
	}

	this->SortSelection(selection);

	
}

Counter::~Counter()
{

}