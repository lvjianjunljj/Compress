#include <vector>
#include <map>
using namespace std;

namespace File
{
	long ReadFileToStringOrDie(const char* inputFilePath, string* data);
	long WriteStringToFileOrDie(const string& data, const char* outputFilePath);
	vector<string> folderTraversalSingleLayerName(string dirPath);
	map<string, int> folderTraversalSingleLayerNameSize(string dirPath);
	void Txt2Binary(const char* inputFilePath, const char* outputFilePath);
}