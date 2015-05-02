#pragma once

#include <string>
#include <mysql++/mysql++.h>


class MySQLConnPool : public mysqlpp::ConnectionPool {
 public:
  MySQLConnPool(const char* db,
                const char* server,
                const char* user,
                const char* passwd) :
      _db(db ? db : ""),
      _server(server ? server : ""),
      _user(user ? user : ""),
      _password(passwd ? passwd : "")
  {}

  ~MySQLConnPool() {
    clear();
  }

  mysqlpp::Connection* grab () {
    ++ _connInUse;
    return mysqlpp::ConnectionPool::grab();
  }

  void release(const mysqlpp::Connection* connPtr) {
    mysqlpp::ConnectionPool::release(connPtr);
    -- _connInUse;
  }
  
 protected:
  mysqlpp::Connection* create() {
    return new mysqlpp::Connection(
        _db.empty() ? nullptr : _db.c_str(),
        _server.empty() ? nullptr : _server.c_str(),
        _user.empty() ? nullptr : _user.c_str(),
        _password.empty() ? "" : _password.c_str());
  }

  void destroy(mysqlpp::Connection* connPtr) {
    delete connPtr;
  }

  unsigned int max_idle_time() {
    return 20 * 60;
  }
  
 private:
  // Number of connections currently in use
  unsigned int _connInUse;
  // Our connection parameters  
  std::string _db, _server, _user, _password;
};



