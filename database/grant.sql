#create database account
CREATE DATABASE IF NOT EXISTS closer default charset utf8 COLLATE utf8_general_ci; 

# create user admin
CREATE USER 'admin'@'%' IDENTIFIED BY '123456';
GRANT ALL PRIVILEGES ON closer.* TO admin@'%';
FLUSH PRIVILEGES;

# change db
USE closer;

