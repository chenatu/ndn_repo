#ifndef SQLITE_HANDLE_H
#define SQLITE_HANDLE_H

#include "../storage_handle.h"

#include <string>
#include <iostream>
#include <sqlite3.h> 
#include <stdlib.h>

using namespace std;

class sqlite_handle:public storage_handle{
public:
	sqlite_handle();
	sqlite_handle(string dbpath);
	virtual int insert_encrypted_data(string& name, string &data);
	virtual int delete_data(string& name);
	virtual int check_data(string& name, string& blobdata);
private:
	sqlite3 *db;
	char* dbpath;
};

#endif