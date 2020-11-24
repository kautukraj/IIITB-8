#include "Paragraph.h"
Paragraph :: Paragraph(string text):
        text(text)
        {}

Paragraph :: Paragraph(const Paragraph &P){
    S = P.S;
    text = P.text;
}
