#ifndef __SOCKCMD_H__
#define __SOCKCMD_H__

enum SockCommand{
    COMMAND_INVALID = 0,
    COMMAND_LOGIN,
    COMMAND_LOGOUT,
};


typedef struct MsgHeader{
    SockCommand msgCmd;
    int msgLength;
    void clear(){
        msgCmd = COMMAND_INVALID;
        msgLength = 0;
    }
}MsgHeader;

#endif