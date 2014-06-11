#ifndef LOGGER
#define LOGGER

#include "Engine.h"
#include <vector>
#include <fstream>
#include <sstream>
#include <string>

using std::vector;
using std::string;

enum Severity { Info, Warning, Error, Severe };

#ifdef LOG_ON
#define ASSERT(expr, ...) do { const char* msg = #expr##" "##__VA_ARGS__; if (!(expr)) {LOG(Severe, msg ); END_LOG DebugBreak(); exit(1);}}while(0);
#else
#define ASSERT(expr, ...) assert(expr)
#endif

#define LOG( severity, message) Logger::Log( severity, message, __LINE__, __FILE__ )
#define END_LOG Logger::shutDown();

#pragma warning ( disable : 4100)
#pragma warning ( disable : 4127)

class Logger
{
public:
#ifdef LOG_ON
	Logger(void);
	~Logger(void);
	static void StringReplace(string& str, const string& from, const string& to);
	static string Sanitize(string str);
	ENGINE_SHARED static void Log( Severity severity, const char* message, int logLine, const char* logFile);
	ENGINE_SHARED static void shutDown();
#else
#define ASSERT(expr, ...) assert(expr)
	Logger(void){}
	~Logger(void){}
	static void StringReplace(string& str, const string& from, const string& to){}
	static string Sanitize(string str){}
	ENGINE_SHARED static void Log( Severity severity, const char* message, int logLine, const char * logFile){}
	ENGINE_SHARED static void shutDown(){}
#endif

private:
#ifdef LOG_ON
	static vector <string> logList;
	static vector <Severity> severityList;
	static void WriteFile();
#endif
};

#pragma warning ( default : 4100)

#endif