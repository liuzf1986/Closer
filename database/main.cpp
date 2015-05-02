
#include <string>
#include "AccountDao.hpp"
#include "MySQLConnPool.hpp"

using namespace std;

int main(int argc, char *argv[])
{
  MySQLConnPool pool("closer", "127.0.0.1", "root", "jsf");

  //  (int, const char*&, const char*&, const mysqlpp::null_type&, const char*&, const char*&, unsigned char, uint32_t&, unsigned char)
  // (const sql_int_unsigned_null&, const sql_varchar_null&, const sql_varchar_null&, const sql_text_null&, const sql_varchar_null&, const sql_varchar_null&, const sql_tinyint_unsigned&, const sql_int_unsigned&, const sql_tinyint_unsigned_null&)      

  AccountDao dao;
  dao.createUserAccount(pool.grab(),
                        "liuzf",
                        "123456",
                        "139274145112",
                        "liuzf1986@1634.com",
                        (unsigned char) 123);
  
  return 0;
}

















