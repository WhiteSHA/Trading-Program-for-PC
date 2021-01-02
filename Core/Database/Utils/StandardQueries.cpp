#include "StandardQueries.h"

namespace StandardQueries
{
    const QStringList dropTables =
    {
        "DROP TABLE IF EXISTS users;",
        "DROP TABLE IF EXISTS departments;",
        "DROP TABLE IF EXISTS user_dep;",
        "DROP TABLE IF EXISTS measurement_units;",
        "DROP TABLE IF EXISTS product_typecodes;",
        "DROP TABLE IF EXISTS goods;",
        "DROP TABLE IF EXISTS coupons;"
    };

    const QStringList createTables =
    {
        "CREATE TABLE users (id INT PRIMARY KEY NOT NULL,username TEXT,password TEXT,is_admin INT,is_active INT,name TEXT, surname TEXT, address TEXT);",
        "CREATE TABLE departments (id INT PRIMARY KEY NOT NULL,name TEXT,is_operating INT,tax_type_id INT,is_active INT);",
        "CREATE TABLE user_dep (user_id INT,dep_id INT);",
        "CREATE TABLE measurement_units (id INT PRIMARY KEY NOT NULL,name TEXT);",
        "CREATE TABLE product_typecodes (id INT PRIMARY KEY NOT NULL,code TEXT, name TEXT);",
        "CREATE TABLE goods (id INT PRIMARY KEY NOT NULL, name TEXT, code TEXT, measurement_id INT, price REAL, discount REAL, dep_id INT, adg_code TEXT);",
        "CREATE TABLE coupons (id INT PRIMARY KEY NOT NULL, fiscal INT UNIQUE, time INT, type INT, ref INT, refcrn INT, rrt INT, cid INT, did INT, ta REAL, cash REAL, card REAL, partialAmount REAL, ppu REAL, with_qr REAL, saleType INT, sync INT, returned INT, items_count INT, i_id TEXT, i_gc TEXT, i_gn TEXT, i_qty TEXT, i_p TEXT, i_adg TEXT, i_mu TEXT, i_rpid TEXT, i_dsc TEXT, i_adsc TEXT, i_dsct TEXT, i_adsct TEXT, i_did TEXT, i_dt TEXT, i_dtm TEXT, i_t TEXT, i_tt TEXT, refcid INT ,tin TEXT DEFAULT \"\");"
    };

    const QStringList insertQueries =
    {
        "INSERT INTO users (id,username,password,is_admin,is_active,name,surname) VALUES(1,'sadmin','1111',1,1,'sadmin','sadmin');",
        "INSERT INTO measurement_units (id,name) VALUES(1,'տուփ;пакет;pack');",
        "INSERT INTO measurement_units (id,name) VALUES(2,'լիտր;литр;liter');",
        "INSERT INTO measurement_units (id,name) VALUES(3,'կգ;кг;kg');",
        "INSERT INTO measurement_units (id,name) VALUES(4,'հատ;шт.;unit');",
        "INSERT INTO measurement_units (id,name) VALUES(5,'գրամ;грамм;gram');",
        "INSERT INTO measurement_units (id,name) VALUES(6,'այլ;друг.;other');",
    };
}
