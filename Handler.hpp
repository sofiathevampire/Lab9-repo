#pragma once
#include "Request.hpp"

class Handler {
    protected:
    Handler* next;

    public:
    Handler();
    virtual ~Handler();
    void setNext(Handler* next);
    bool callNext(Request& request);
    virtual bool handle(Request& request) = 0;
};