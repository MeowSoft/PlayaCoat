#ifndef DIGIT_H
#define DIGIT_H

#include "DisplayInterface.h"

class Digit {
    public:
    void inc();
    void dec();

    private: 
    bool needsRedraw;
    unsigned char value;
    int screenX;
    int screenY;
};

class EditableDigit : Digit {

    private:
    bool isSelected;
};



// void incDigit(EditableDigit digit);
// void decDigit(EditableDigit digit);
// void drawDigit(DisplayInterface_t display, EditableDigit digit);

#endif
