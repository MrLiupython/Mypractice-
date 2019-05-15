#include <stdlib.h>
#include <iostream>
#include <string.h>

#include <boost/scoped_ptr.hpp>

#include<jdbc/mysql_connection.h>
#include<jdbc/cppconn/driver.h>
#include<jdbc/cppconn/exception.h>
#include<jdbc/cppconn/resultset.h>
#include<jdbc/cppconn/statement.h>

using namespace std;

int main(void) {
    cout << "mysql connector" << endl;
    try {
        sql::Driver *driver;
        sql::Connection *conn;
        sql::Statement *stmt;
        sql::ResultSet *res;
        
        /* Create a connection */
        driver = get_driver_instance();
        conn = driver->connect("tcp://127.0.0.1:3306", "name", "pwd");
        /* Connect to the Mysql test database */
        conn->setSchema("test");
        
        stmt = conn->createStatement();
        /* stmt->execute("insert into test (id) values (3)"); */
        res = stmt->executeQuery("select * from test2");
        while (res->next()) {
            cout << "name: age\n" << res->getString("name") << " " << res->getString("age") << endl;
        }
        delete res;
        delete stmt;
        delete conn;
    } catch (sql::SQLException &e) {
        cout << "Error in:" << __FILE__;
        cout << "ERR: " << e.what();
        cout << "(error code: " << e.getErrorCode();
        cout << "SQLState: " << e.getSQLState();
    }
    return EXIT_SUCCESS;
}
