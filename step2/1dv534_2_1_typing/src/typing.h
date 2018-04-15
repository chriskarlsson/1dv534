#ifndef TYPING_H
#define TYPING_H

class Typing {
public:
    Typing() = default;
    ~Typing() = default;
    int run();
private:
    void _printIntroduction();
    void _printTask(const char * EXPECTED);
    bool _userYesOrNo(const char * QUESTION);
    void _getUserInput(char * userInput);
    const int _MAX_READ_INPUT_LENGTH = 100;
};

#endif // TYPING_H
