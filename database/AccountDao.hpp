#pragma once

#include <mysql++/mysql++.h>
#include <mysql++/ssqls.h>

#include <string>
#include <iostream>

using namespace mysqlpp;

typedef enum {
  ACCOUNT_UESR = 0,     // user account
  ACCOUNT_DEVICE = 1    // device account
} EAccountType;

typedef enum {
  AUTH_NONE = 0,            // have't authored
  AUTH_PHONE = 1,           // phone authored
  AUTH_EMAIL = 2           // email authored
} EAuthType;

/*
CREATE TABLE `account` (
  `accid` int(11) unsigned NOT NULL AUTO_INCREMENT COMMENT '账户id',
  `username` varchar(255) DEFAULT NULL,
  `passwd` varchar(32) DEFAULT NULL COMMENT 'md5 32位小写',
  `icon` text,
  `number` varchar(32) DEFAULT NULL COMMENT '注册手机号码或imei',
  `email` varchar(255) DEFAULT NULL COMMENT '注册邮箱',
  `authtype` tinyint(2) unsigned NOT NULL DEFAULT '0' COMMENT '认证类型，0表示未认证，1表示手机，2表示邮箱，或关系',
  `createtime` int(11) unsigned NOT NULL COMMENT '账户创建时间戳',
  `acctype` tinyint(3) unsigned DEFAULT NULL COMMENT '0表示用户账户，1表示监控设备账户...',
  PRIMARY KEY (`accid`),
  UNIQUE KEY `email` (`email`) USING BTREE,
  UNIQUE KEY `username` (`username`) USING BTREE,
  UNIQUE KEY `phoneorimei` (`number`) USING BTREE
) ENGINE=InnoDB AUTO_INCREMENT=10000002 DEFAULT CHARSET=utf8 COMMENT='注册用户表，注册用户包括个人账户用户，设备账户等\r\n不同类型账户已acctype区分';
*/

sql_create_9(account, 1, 9,
             sql_int_unsigned_null, accid, // define accid null because auto increment
             sql_varchar_null, name,
             sql_varchar_null, passwd,
             sql_text_null, icon,
             sql_varchar_null, number,
             sql_varchar_null, email,
             sql_tinyint_unsigned, authtype,
             sql_int_unsigned, createtime,
             sql_tinyint_unsigned_null, acctype);

class AccountDao {
 public:

  uint32_t createDeviceAccount(
      Connection* connPtr,
      const char* imei,
      uint32_t current) {
  }

  uint32_t createUserAccount(
      Connection* connPtr,
      const char* username,
      const char* passwd,
      const char* phone,
      const char* email,
      uint32_t current) {
    
    if(!connPtr) {
      return 0;
    }

    if(!phone && !email) {
      return 0;
    }
    
    account acc;
    SimpleResult result;
    
    acc.accid = mysqlpp::null;
    acc.name = username;
    acc.passwd = passwd;
    acc.icon = mysqlpp::null;
    if(phone) acc.number = phone;
    else acc.number = mysqlpp::null;
    if(email) acc.email = email;
    else acc.email = mysqlpp::null;
    acc.authtype = 0;
    acc.createtime = current;
    acc.acctype = static_cast<sql_tinyint_unsigned>(ACCOUNT_UESR);
    
    try {
      mysqlpp::Query query = connPtr->query();
      query.insert(acc);

      // Show the query about to be executed.
      std::cout << "Query: " << query << std::endl;
      result = query.execute();
    }
    catch (const mysqlpp::Exception& er) {
      // Catch-all for any other MySQL++ exceptions
      return 0;
	}

    return result.insert_id();
  }

  

};


