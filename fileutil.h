#ifndef FILEUTIL_H
#define FILEUTIL_H

#include <fstream>
#include <string>
#include <vector>

#include <logger.h>

class fileUtil
{
public:
    fileUtil();
    fileUtil(const fileUtil& orig);
    virtual ~fileUtil();

    virtual bool writeline(std::string datei,std::string text);
    virtual bool readLine(std::string datei, std::vector<std::string> & lines);
    void setFlags(std::ifstream::openmode fileflags);
    bool readShaderSource(std::string & s, std::string path);
    void clear();
    std::string Parse(std::string line, std::string delString,std::string spacestring= " ");
    int ParseToint(std::string line, std::string delString,std::string spacestring= " ");
private:
    Logger log;
    std::string filename;   // globaler  Dateiname
    std::ifstream::openmode flags;
    bool fileopen;
};

#endif // FILEUTIL_H
