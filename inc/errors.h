#ifndef ERRORS_H
    #define ERRORS_H

    #define RAGE_QUIT(msg) rageQuit(__FILE__, __LINE__, __func__,msg)
   
    void rageQuit(const char* fname, int lineno, const char* fxname, char* msg);   

#endif
