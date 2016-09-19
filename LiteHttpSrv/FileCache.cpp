#include "FileCache.h"
#include <string>
#include <mutex>

using namespace std;

static  FileCache * ins = nullptr;

static std::mutex _mutex;


FileCache* FileCache::getInstance()
{
	if (!ins)ins = new FileCache;
	return ins;

}


FileCache* FileCache::create()
{
	return new FileCache;
 

}

FileData * FileCache::getFileData(const std::string & name)
{

//	std::lock_guard<std::mutex>lock(_mutex);
	auto &  iter = _map.find(name);
	if (iter != _map.end())
	{
		return (*iter).second;

	}

	FileReader* reader = new FileReader(name);
	FileData* data = reader->ReadFile();
	if (data)
	{
		_map[name] = data;
		return data;
	}

	return nullptr;
}


void FileCache::addFileData(const std::string &name)
{

}




FileReader::~FileReader()
{

}

FileReader::FileReader(const string &fileName)
{

	this->data = new FileData;
	this->data->name = fileName;

}



static std::mutex _mutex_io;
static void ReadFile(const char * fileName,unsigned char ** ret_buffer, int * ret_size)
{
	//this function is for only one acess to read file to HDD
	_mutex_io.lock();
	FILE *file = fopen(fileName, "rb");
	if (!file)
	{
		*ret_buffer = 0;
		*ret_size = 0;
		//cout << " error open file : " << na << endl;
		_mutex_io.unlock();

		return  ;
	}


	fseek(file, 0, SEEK_END);
	int size = ftell(file);
	fseek(file, 0, SEEK_SET);

	unsigned char *buf = new  unsigned char[size];
	fread(buf, size, 1, file);
	fclose(file);
	_mutex_io.unlock();
 
	*ret_buffer = buf;
	*ret_size = size;

}

FileData* FileReader::ReadFile()
{
	::ReadFile(this->data->name.c_str(), &data->buffer, &data->size);
	if (!data->size)
	{
		return 0;
	}
	return this->data;
}






