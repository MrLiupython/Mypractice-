LDLIBS = -lmysqlcppconn
APP = src/jdbc_test.cpp
app : $(APP)
	g++ -std=c++11 -I include -L lib64 $(LDLIBS) $(APP) -o app
