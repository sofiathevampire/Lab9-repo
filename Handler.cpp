#include "Handler.hpp"

Handler::Handler() {
    next = nullptr;
}

Handler::~Handler() {
}

void Handler::setNext(Handler* next) {
    this->next = next;
}

bool Handler::callNext(Request& request) {
    if(next != nullptr) {
        return next->handle(request);
    }

    return true;
}