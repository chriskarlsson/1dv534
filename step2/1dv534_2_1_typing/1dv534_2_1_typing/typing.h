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
};

#endif // TYPING_H
