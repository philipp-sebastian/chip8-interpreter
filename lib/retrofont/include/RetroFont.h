#ifndef RETROFONT_RETROFONT_H
#define RETROFONT_RETROFONT_H

#define RF_FONTHEIGHT 7
#define RF_FONTWIDTH 5
#define RF_AMOUNTOFFONTSPRITES 64
#define RF_BYTESIZE 8
#ifdef RETROFONT_C
#define NULLPOINTER NULL
#else
#define NULLPOINTER nullptr
#endif


#ifndef RETROFONT_C
namespace RetroFont {
    extern "C" {
#endif

    typedef unsigned char RF_FontData;

    typedef enum Symbol {
        RF_A = 0, RF_M = 1, RF_G = 2, RF_E = 3, RF_O = 4, RF_V = 5, RF_R = 6, RF_P = 7, RF_S = 8,
        RF_T = 9, RF_0 = 4, RF_1 = 10, RF_2 = 11, RF_3 = 12, RF_4 = 13, RF_5 = 8, RF_6 = 14,
        RF_7 = 15, RF_8 = 16, RF_9 = 17, RF_L = 18,
        RF_C = 19, RF_X = 20, RF_N = 21, RF_I = 22, RF_DOT = 23,
        RF_J = 24, RF_K = 25, RF_Q = 26, RF_U = 27, RF_W = 28, RF_Y = 29, RF_Z = 30,
        RF_COLON = 31, RF_SEMICOLON = 32, RF_EQUAL = 33, RF_MINUS = 34, RF_PLUS = 35,
        RF_GREATER_THAN = 36, RF_LESS_THAN = 37, RF_COMMA = 38, RF_QUESTION_MARK = 39,
        RF_EXCLAMATION_MARK = 40, RF_BACKSLASH = 41, RF_SLASH = 42, RF_UNDERSCORE = 43,
        RF_PIPE = 44, RF_QUOTE = 45, RF_APOSTROPHE = 46, RF_CIRCUMFLEX = 47,
        RF_PERCENT = 48, RF_BRACKET_OPEN = 49, RF_BRACKET_CLOSE = 50,
        RF_PARENTHESIS_OPEN = 51, RF_PARENTHESIS_CLOSE = 52,
        RF_BRACE_OPEN = 53, RF_BRACE_CLOSE = 54, RF_B = 55, RF_D = 56, RF_F = 57, RF_H = 58,
        RF_TILDE = 59, RF_HASHTAG = 60, RF_ASTERISK = 61, RF_FULL_STOP = 62, RF_SPACE = 63
    } eSymbol_t ;

    RF_FontData *InitializeFont(void);
    int StringToSymbols(const char* string, int* symbolBuffer, int bufferSize);
    int CharToSymbol(const char x);


#ifndef RETROFONT_C
    }
}
#endif

#endif //RETROFONT_RETROFONT_H
