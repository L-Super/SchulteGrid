//
// Created by LMR on 2022/12/22.
//

#include "LeveldbPimpl.h"

LeveldbPimpl::LeveldbPimpl():dbName("./data")
{
	OpenDB(dbName);
}
LeveldbPimpl::~LeveldbPimpl()
{
	delete db;
}
bool LeveldbPimpl::OpenDB(const std::string& dbName)
{
	leveldb::Options options;
	options.create_if_missing = true;
	leveldb::Status status = leveldb::DB::Open(options, dbName, &db);
	if (!status.ok())
	{
//		cout << "打开数据失败：dbName:" << dbName << endl;
		return false;
	}
	return true;
}
bool LeveldbPimpl::PutData(const std::string &key, const std::string &value)
{
	leveldb::Status status = db->Put(leveldb::WriteOptions(), key, value);

	if (status.ok())
	{
		return true;
	}
	return false;
}
std::list<std::string> LeveldbPimpl::GetAllData()
{
	std::list<std::string> list;
	leveldb::Iterator* it = db->NewIterator(leveldb::ReadOptions());
	for (it->SeekToFirst(); it->Valid(); it->Next()) {
//		spdlog::info("key: {} value: {}", it->key().ToString(), it->value().ToString());
		list.emplace_back(it->value().ToString());
	}
	delete it;
	return list;
}
bool LeveldbPimpl::ClearDB()
{
	leveldb::Iterator* it = db->NewIterator(leveldb::ReadOptions());
	for (it->SeekToFirst(); it->Valid(); it->Next()) {
		auto status = db->Delete(leveldb::WriteOptions(), it->key());
		if (!status.ok())
		{
			return false;
		}
	}
	return true;
}
