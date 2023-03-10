#include "Textbox.h"

TextBox::Text::Text(sf::String string, float x, float y, sf::Font& font) {
    text.setFont(font);
    text.setString(string);
    text.setFillColor(sf::Color::White);
    text.setCharacterSize(12);
    text.setPosition(sf::Vector2f(x, y));
    text.setLineSpacing(0);
    text.setOutlineThickness(0);
}

sf::Text TextBox::Text::get() { return text; }

void TextBox::Text::setText(sf::String string) { text.setString(string); }

void TextBox::Text::setPosition(float x, float y) { text.setPosition(sf::Vector2f(x, y)); }

void TextBox::Text::setSize(unsigned int x) { text.setCharacterSize(x); }

//Main TextBox methods start here
TextBox::TextBox(sf::Font& font1, sf::Font& font2) : inpText("", 6, 5, font2) {
    outerRect.setSize(sf::Vector2f(460, 32));
    innerRect.setSize(sf::Vector2f(456, 28));
    outerRect.setPosition(sf::Vector2f(0, 0));
    innerRect.setPosition(sf::Vector2f(2, 2));
    outerRect.setFillColor(sf::Color::Black);
    innerRect.setFillColor(sf::Color(40, 44, 52));

    blinker.setSize(sf::Vector2f(1, 26));
    blinker.setPosition(sf::Vector2f(4, 3));
    blinker.setFillColor(sf::Color::White);

    numText.setFont(font1);
    numText.setString("1");
    numText.setFillColor(sf::Color(153, 153, 153));
    numText.setCharacterSize(13);
    numText.setLineSpacing(0);
    numText.setOutlineThickness(0);

    sf::FloatRect bounds = numText.getLocalBounds();
    numText.setPosition(-bounds.width - 15, 0);

    time = sf::Time::Zero;
    textSize = 18;
    getPinp = "";
    txtInp = "";
    thickness = 2;
    posX = 0;
    posY = 0;
    height = 20;
    width = 460;
    focusChar = 0;
    focus = false;
    charWidth = 0;
    needDelete = false;
    gotInput = false;
}
TextBox::TextBox(float x1, float x2, float y1, float y2, float z, sf::Font& font) : inpText("", y1 + z + 2, y2 + z - 1, font) {
    outerRect.setSize(sf::Vector2f(x1, x2));
    innerRect.setSize(sf::Vector2f(x1 - 2 * z, x2 - 2 * z));
    outerRect.setPosition(sf::Vector2f(y1, y2));
    innerRect.setPosition(sf::Vector2f(y1 + z, y2 + z));
    outerRect.setFillColor(sf::Color::Black);
    innerRect.setFillColor(sf::Color::White);

    blinker.setSize(sf::Vector2f(1, x2 - 2 * z - 2));
    blinker.setPosition(sf::Vector2f(y1 + z + 2, y2 + z + 1));
    blinker.setFillColor(sf::Color(40, 44, 52));

    time = sf::Time::Zero;
    textSize = (unsigned int)(x2 - 4 - 2 * z);
    getPinp = "";
    txtInp = "";
    thickness = z;
    posX = y1;
    posY = y2;
    height = x2;
    width = x1;
    focusChar = 0;
    focus = false;
    charWidth = 0;
    needDelete = false;
    gotInput = false;

    inpText.setSize(textSize);
}

void TextBox::setFocused(bool focused) {
    focus = focused;
}

void TextBox::setSize(float x, float y) {
    height = y;
    width = x;
    textSize = (unsigned int)(y - 4 - 2 * thickness);
    outerRect.setSize(sf::Vector2f(x, y));
    innerRect.setSize(sf::Vector2f(x - 2 * thickness, y - 2 * thickness));
    blinker.setSize(sf::Vector2f(1, y - 2 * thickness - 2));
    inpText.setSize(textSize);
    inpText.setPosition(posX + thickness + 2, posY + thickness - 1);
}

sf::Vector2f TextBox::getSize() {
    return sf::Vector2f(width, height);
}

void TextBox::setPosition(float x, float y) {
    posX = x;
    posY = y;
    outerRect.setPosition(sf::Vector2f(x, y));
    innerRect.setPosition(sf::Vector2f(x + thickness, y + thickness));
    blinker.setPosition(sf::Vector2f(x + thickness + 2, y + thickness + 1));
    inpText.setPosition(x + thickness + 2, y + thickness - 1);

    sf::FloatRect bounds = numText.getLocalBounds();
    numText.setPosition(sf::Vector2f(x - bounds.width - thickness - 15, y + thickness + 1));
}

void TextBox::setNum(int num) {
    numText.setString(std::to_string(num));
    setPosition(getPosition().x, getPosition().y);
}

sf::Vector2f TextBox::getPosition() {
    return sf::Vector2f(posX, posY);
}

void TextBox::setBorder(float x) {
    thickness = x;
    textSize = (unsigned int)(height - 4 - 2 * x);
    innerRect.setSize(sf::Vector2f(width - 2 * x, height - 2 * x));
    inpText.setSize(textSize);
    setPosition(posX, posY);
}

sf::String TextBox::getCurrentText() { return getPinp; }

sf::String TextBox::getInput() { return txtInp; }

bool TextBox::handleEvent(sf::Event& event) {
    changed = true;
    if (event.type == sf::Event::TextEntered && focus) {
        if ((inpText.get().findCharacterPos(getPinp.getSize()).x + 1.2 * textSize) < (width + posX) && 31 < int(event.text.unicode) && 256 > int(event.text.unicode)) {
            if (focusChar == getPinp.getSize()) getPinp += event.text.unicode;
            else {
                getPinp = getPinp.substring(0, focusChar) + event.text.unicode + getPinp.substring(focusChar, getPinp.getSize() - focusChar);
            }
            focusChar++;
        } else changed = false;
    }
    if (event.type == sf::Event::KeyPressed && focus) {
        if (event.key.code == sf::Keyboard::BackSpace) {
            if (focusChar != 0) {
                getPinp.erase(focusChar - 1, 1);
                if (focusChar > 0) focusChar--;
            } else {
                needDelete = true;
            }
        }
        if (event.key.code == sf::Keyboard::Delete) {
            if (focusChar != getPinp.getSize()) {
                getPinp.erase(focusChar);
            }
        }
        if (event.key.code == sf::Keyboard::Enter) {
            txtInp = getPinp.substring(0, focusChar);
            getPinp = getPinp.substring(focusChar);
            focusChar = 0;
            gotInput = true;
        } else if (event.key.code == sf::Keyboard::Left) {
            if (focusChar > 0) { focusChar--; }
        } else if (event.key.code == sf::Keyboard::Right) {
            if (focusChar < getPinp.getSize()) focusChar++;
        }
    }

    if (event.type == sf::Event::MouseButtonPressed) {
        if (event.mouseButton.button == sf::Mouse::Left) {
            if (getPinp.getSize() > 0) {
                if (charWidth == 0) charWidth = inpText.get().findCharacterPos(1).x - inpText.get().findCharacterPos(0).x;
                unsigned int temp = (unsigned int)((event.mouseButton.x - posX) / charWidth);
                if (temp > getPinp.getSize()) focusChar = getPinp.getSize();
                else focusChar = temp;
            }
            if (event.mouseButton.x > posX && event.mouseButton.x <posX + width && event.mouseButton.y>posY && event.mouseButton.y < posY + height) focus = true;
            else focus = false;
        }
    }

    return focus;
}

int TextBox::getfocusChar() {
    return  focusChar;
}

bool TextBox::insert(sf::Event& event) {
    getPinp.erase(getPinp.getSize() - 1, 1);
    if (event.type == sf::Event::TextEntered && focus) {
        if ((inpText.get().findCharacterPos(getPinp.getSize()).x + 1.2 * textSize) < (width + posX) && 31 < int(event.text.unicode) && 256 > int(event.text.unicode)) {
            if (focusChar == getPinp.getSize()) getPinp += event.text.unicode;
            else {
                getPinp = getPinp.substring(0, focusChar) + event.text.unicode + getPinp.substring(focusChar, getPinp.getSize() - focusChar);
            }
            focusChar++;
        } else changed = false;
    }

    return true;
}

bool TextBox::isChanged() {
    return changed;
}

void TextBox::draw(sf::RenderWindow& window) {
    time += clock.restart();
    if (focus) {
        if (time.asSeconds() > 1) {
            time = sf::Time::Zero;
            blinker.setFillColor(sf::Color::White);
        } else if (time.asSeconds() > 0.5) blinker.setFillColor(sf::Color(53, 68, 78));
    } else {
        blinker.setFillColor(sf::Color(40, 44, 52));
        if (time.asSeconds() > 300) time = sf::Time::Zero;
    }
    if (focusChar == 0) blinker.setPosition(posX + thickness + 2, posY + thickness + 1);
    else blinker.setPosition(sf::Vector2f(inpText.get().findCharacterPos(focusChar).x, posY + thickness + 1));
    inpText.setText(getPinp);
    if (focus) {
        innerRect.setFillColor(sf::Color(53, 68, 78));
        numText.setFillColor(sf::Color(198, 198, 198));
        if (blinker.getFillColor() == sf::Color(40, 44, 52))
            blinker.setFillColor(sf::Color(53, 68, 78));
    } else {
        innerRect.setFillColor(sf::Color(40, 44, 52));
        numText.setFillColor(sf::Color(153, 153, 153));
    }
    window.draw(outerRect);
    window.draw(innerRect);
    window.draw(blinker);
    window.draw(inpText.get());
    window.draw(numText);
}

void TextBox::recover() {
    sf::String text = txtInp;
    txtInp.clear();
    getPinp.clear();
    focusChar = 0;
    gotInput = false;
    setText(text);
}

bool TextBox::checkInput() {
    return gotInput;
}

bool TextBox::checkDelete() {
    bool ans = needDelete;
    needDelete = false;
    return ans;
}

void TextBox::setText(sf::String str) {
    while (getPinp.getSize() != 0) {
        getPinp.erase(focusChar - 1, 1);
        if (focusChar > 0) focusChar--;
    }

    for (auto c : str) {
        if ((inpText.get().findCharacterPos(focusChar).x + 1.2 * textSize) < (width + posX) && 31 < int(c) && 256 > int(c)) {
            if (focusChar == getPinp.getSize()) getPinp += c;
            else {
                getPinp = getPinp.substring(0, focusChar) + c + getPinp.substring(focusChar, getPinp.getSize() - focusChar);
            }
            focusChar++;
        }
    }
}

void TextBox::popText(int count) {
    getPinp = getPinp.substring(count);
}

int TextBox::append(sf::String str, bool focus) {
    int cnt = 0;
    if (focus)
        focusChar = getPinp.getSize();
    for (auto& c : str) {
        if ((inpText.get().findCharacterPos(focusChar).x + 1.2 * textSize) < (width + posX)) {
            getPinp += c;
            inpText.setText(getPinp);
            cnt++;
            focusChar++;
        }
    }

    return cnt;
}