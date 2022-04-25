#ifndef __SOCKBUF_H__
#define __SOCKBUF_H__

#include <string.h>
#include "Sockcmd.h"

class Sockbuf{
public:
    Sockbuf();
    Sockbuf(SockCommand cmd, unsigned char * data);
    Sockbuf(SockCommand cmd, unsigned char * data, int length);
    ~Sockbuf();
    void SetCommand(SockCommand cmd);
    SockCommand GetCommand();
    int SetData(unsigned char * data, int length);  //返回实际设置的字符串大小
    int SetData(unsigned char * data);  //返回实际设置的字符串大小
    unsigned char* GetData();
private:
    unsigned char * serialize();
    void fill_header(SockCommand cmd, int length);
private:
    MsgHeader m_header;
    SockCommand m_cmd;
    int m_length;
    unsigned char* m_data;
};


#endif