# Backend

### database

Currently the dbo implemented is SQLite3, to change to PostgreSQL change the following:
    ./dboConnString.txt - should have a PQ connection string like this "host= port= dbname= user= password="
    ./makefile - change linkier from "-lwtdbosqlite3" to "-lwtdbopostgres"
    ./main.cpp - change "#include <Wt/Dbo/backend/Sqlite3.h>" to "#include <Wt/Dbo/backend/Postgres.h>"
    Currently the configuration for dependencies is in a docker file installs wt with sqlite as default, you need to change the install to postgress with cmake
