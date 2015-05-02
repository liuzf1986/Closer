/*
Navicat MySQL Data Transfer

Source Server         : local-test
Source Server Version : 50619
Source Host           : 192.168.1.102:3306
Source Database       : closer

Target Server Type    : MYSQL
Target Server Version : 50619
File Encoding         : 65001

Date: 2015-05-01 18:55:23
*/

SET FOREIGN_KEY_CHECKS=0;

-- ----------------------------
-- Table structure for account
-- ----------------------------
DROP TABLE IF EXISTS `account`;
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

-- ----------------------------
-- Table structure for ownership
-- ----------------------------
DROP TABLE IF EXISTS `ownership`;
CREATE TABLE `ownership` (
  `ownerid` int(11) unsigned NOT NULL COMMENT '设备持有者账户id',
  `deviceid` int(11) unsigned NOT NULL COMMENT '设备账户id',
  `createtime` int(11) unsigned DEFAULT NULL,
  `remarks` varchar(255) DEFAULT NULL COMMENT '备注名称',
  PRIMARY KEY (`ownerid`,`deviceid`),
  UNIQUE KEY `owner` (`ownerid`),
  KEY `device` (`deviceid`),
  CONSTRAINT `device` FOREIGN KEY (`deviceid`) REFERENCES `account` (`accid`) ON DELETE CASCADE ON UPDATE NO ACTION,
  CONSTRAINT `owner` FOREIGN KEY (`ownerid`) REFERENCES `account` (`accid`) ON DELETE CASCADE ON UPDATE NO ACTION
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COMMENT='设备持有关系表\r\n一个设备可以给多个用户绑定\r\n一个用户也可以绑定多个设备\r\n因此为多对多关系\r\n\r\n以用户id与设备id一起为主键';
