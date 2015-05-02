#pragma once

#include <mysql++/mysql++.h>

using namespace mysqlpp;

class DBOp {
 public:
  DBOp
 protected:
  ScopedConnection _sc;
};


