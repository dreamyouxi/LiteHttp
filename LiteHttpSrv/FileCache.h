#ifndef __FILECACHE__
#define  __FILECACHE__

#include <iostream>
#include <unordered_map>
class FileData
{
public:
	unsigned char *buffer = 0;
	int size = 0;
	std::string name;
	void release()
	{
		if (buffer)delete buffer;
	}
};


class FileCache
{
public:
	static FileCache*getInstance();
	static FileCache*create();
	void release(){};
	virtual FileData * getFileData(const std::string & name) ;
	virtual void addFileData(const std::string &name) ;
	int getCurrentCacheSize(){ return 0; }
protected:
	std::unordered_map<std::string, FileData*> _map;
	FileCache(){};
};

class FileLruCache:public FileCache
{
public:

	virtual FileData * getFileData(const std::string & name) override;
	virtual void addFileData(const std::string &name) override;

};





class FileReader
{
public:

	~FileReader();
	FileReader(const std::string &fileName);

	FileData* ReadFile();

	FileData*data;
};



#endif