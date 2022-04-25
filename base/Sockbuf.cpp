#include "Sockcmd.h"
#include "Sockbuf.h"
#include <string.h>
#include <stdlib.h>

Sockbuf::Sockbuf()
    :m_cmd(COMMAND_INVALID), m_length(0), m_data(nullptr){
    m_header.clear();
}
Sockbuf::Sockbuf(SockCommand cmd, unsigned char * data)
    :m_cmd(cmd){
    if(data != nullptr){
        m_length = (int)strlen((const char*)m_data);
        m_data = (unsigned char*)malloc(m_length+1);
        memset(m_data, 0, m_length);
        memcpy(m_data, data, m_length);
    }else{
        m_length = 0;
        m_data = nullptr;
    }
}
Sockbuf::Sockbuf(SockCommand cmd, unsigned char * data, int length)
    :m_cmd(cmd){
    int tmp_length;
    if(data != nullptr){
        tmp_length = (int)strlen((const char*)m_data);
        m_length = tmp_length < length ? tmp_length : length;
        m_data = (unsigned char*)malloc(m_length+1);
        memset(m_data, 0, m_length);
        memcpy(m_data, data, m_length);
    }else{
        tmp_length = 0;
        m_data = nullptr;
    }
}
Sockbuf::~Sockbuf(){
    if(m_data != nullptr){
        free(m_data);
    }
}
void Sockbuf::SetCommand(SockCommand cmd){
    m_cmd = cmd;
}
SockCommand Sockbuf::GetCommand(){
    return m_cmd;
}
int Sockbuf::SetData(unsigned char * data, int length){
    if(m_data != nullptr){
        free(m_data);
    }
    int tmp_length = (int)strlen((const char*)m_data);
    m_length = tmp_length < length ? tmp_length : length;
    m_data = (unsigned char*)malloc(m_length+1);
    memset(m_data, 0, m_length);
    memcpy(m_data, data, m_length);
    return tmp_length;
}
int Sockbuf::SetData(unsigned char * data){
    if(m_data != nullptr){
        free(m_data);
    }
    m_length = (int)strlen((const char*)m_data);
    m_data = (unsigned char*)malloc(m_length+1);
    memset(m_data, 0, m_length);
    memcpy(m_data, data, m_length);
    return m_length;
}
unsigned char* Sockbuf::GetData(){
    return m_data;
}

unsigned char * Sockbuf::serialize(){
    int header_length =  (int)sizeof(MsgHeader);
    unsigned char buf[header_length+m_length+1] = {0};
    memcpy(buf, &m_header, sizeof(MsgHeader));
    memcpy(buf+sizeof(MsgHeader), m_data, m_length);
    return buf;
}
void Sockbuf::fill_header(SockCommand cmd, int length){
    m_header.msgCmd = cmd;
    m_header.msgLength = length;
    return;
}
