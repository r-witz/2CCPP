#ifndef INPUT_HANDLER_HPP
#define INPUT_HANDLER_HPP

enum inputs { UP, DOWN, RIGHT, LEFT, ENTER, NONE };

class InputHandler {
public:
    InputHandler();

    inputs getKeyPress();
};

#endif
