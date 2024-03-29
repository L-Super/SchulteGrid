//
// Created by LMR on 2022/12/22.
//

#ifndef LEVELDBPIMPL_H
#define LEVELDBPIMPL_H

#include <list>
#include <string>

#include "leveldb/db.h"

class LeveldbPimpl
{
public:
  LeveldbPimpl();
  ~LeveldbPimpl();

public:
  bool PutData(const std::string& key, const std::string& value);
  std::list<std::string> GetAllData();
  bool ClearDB();

private:
  bool OpenDB(const std::string& dbName);

private:
  std::string dbName;
  leveldb::DB* db{};
};

#endif  // LEVELDBPIMPL_H
