#include<iostream>
#include "Counter.h"
#include<fstream>
#include<algorithm>

Counter::Counter()
{
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
	"and", "but", "or", "nor", "for", "so", "yet"
	};
	
	this->FileName = R"(C:\Users\Huawei\Desktop\test.txt)";
}

//对用户输入的文件路径进行多重验证，并输出提示信息
bool Counter::Verify()
{
	bool verify = false;
	//对文件路径格式进行验证

	//检查文件是否存在

	//检测文件是否为英文文本文件

	return true;
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
				}));

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
					this->WordCount.insert(std::make_pair(word, 1));
				}
			}
		}
	}

	


	file.close();
}

//根据n输出频率前n的统计记录
void Counter::ShowCount(int n)
{
	int i = 0;

	for (const auto& mit : this->WordCount) {
		if (i >= n) {
			break;
		}

		i++;

		std::cout << mit.first << "  " << mit.second << std::endl;
	}
}


void Counter::Control()
{
	std::cout << "请输入需要进行统计的英文文本文件的完整路径" << std::endl;
	
	//std::cin >> this->FileName;

	if (!Verify()) {	//文件验证失败直接返回
		return;
	}

	//文件验证通过，开始进行统计
	this->Count();

	//输入需要查看的已统计的单词个数
	this->ShowCount(this->WordCount.size());
}

Counter::~Counter()
{

}