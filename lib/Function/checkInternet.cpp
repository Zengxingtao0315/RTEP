#include <iostream> // C++标准头文件，其中包含cout和endl的定义。
#include "checkInternet.h"
/*******************************************************************************
function:
            Check internet connection
*******************************************************************************/
class InternetConnectionChecker {
public:
    bool InternetConnectionChecker::CheckInternetConnection() {
        struct addrinfo hints;
        struct addrinfo *res;
        memset(&hints, 0, sizeof hints);
        hints.ai_family = AF_UNSPEC;
        hints.ai_socktype = SOCK_STREAM;
        hints.ai_flags = AI_PASSIVE;

        int status = getaddrinfo("www.google.com", NULL, &hints, &res);
        if(status != 0) {
            return false;
        }
        freeaddrinfo(res);
        return true;
    }
};