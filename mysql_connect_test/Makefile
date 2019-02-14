MYSQL_CONCPP_DIR = /usr
CPPFLAGS = -I $(MYSQL_CONCPP_DIR)/include -L $(MYSQL_CONCPP_DIR)/lib64
LDLIBS = -lmysqlcppconn8
CXXFLAGS = -std=c++11
APP = src/app.cpp
app : $(APP)
	g++ -std=c++11 $(CPPFLAGS) $(APP) $(LDLIBS) -o app
