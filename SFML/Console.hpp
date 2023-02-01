#pragma once

#include <xutility>
#include <vector>
#include <SFML/Graphics.hpp>
#include "Settings.h"
#include "TextEditor.hpp"
#include "Button.hpp"
#include <Windows.h>
#include "TextEditor.hpp"
#include "ConsoleBox.h"
#include <iostream>
#include <algorithm>

namespace SFML {
	class Console {
	private:
		sf::RenderWindow* window;
        sf::Font font;
        sf::Text help_text;
        ConsoleBox* consoleBox;
        TextEditor::StringsDictionary* dict;
        int pos;
        int current_state;
        int prevN, prevM;
        std::string prevStr;
	public:
        Console(TextEditor::StringsDictionary* dict) {
			window = new sf::RenderWindow(sf::VideoMode(980, 512), "Command console", sf::Style::Titlebar | sf::Style::Close);
            font.loadFromFile("Consolas.ttf");

            this->dict = dict;
		}

		void Show(int mode) {
            current_state = 0;
            help_text.setFont(font);
            if (mode == 11) {
                help_text.setString("Enter the string number after which to insert:");
                pos = 30;
            } else if (mode == 12) {
                help_text.setString("Enter the string number to insert the substring:");
                pos = 30;
            } else if (mode == 13) {
                help_text.setString("Enter the string number to delete:");
                pos = 30;
            } else if (mode == 21) {
                help_text.setString("Enter a range of strings to contextually replace the substring (by default, all strings):");
                pos = 30;
            } else if (mode == 22) {
                help_text.setString("Enter the string number to replace the character:");
                pos = 30;
            } else if (mode == 23) {
                help_text.setString("Enter a range of strings to replace N '*' with N/2 '+' (by default, all strings):");
                pos = 30;
            } else if (mode == 31) {
                help_text.setString("Enter a range of strings to remove leading zeros in substrings (by default, all strings):");
                pos = 30;
            } else if (mode == 32) {
                help_text.setString("Enter a range of strings to filter increasing sequences (by default, all strings):");
                pos = 30;
            } else if (mode == 33) {
                help_text.setString("Enter a range of strings to erase characters between { and } (by default, all strings):");
                pos = 30;
            }

            help_text.setPosition(sf::Vector2f(5, 5));
            help_text.setFillColor(sf::Color(204, 204, 204));
            help_text.setCharacterSize(14);

            consoleBox = new ConsoleBox(font);
            consoleBox->setPosition(4, pos);
            consoleBox->setSize(950, 18);
            consoleBox->setBorder(0);
            consoleBox->setText("");
            consoleBox->setFocused(true);

            while (window->isOpen()) {
                sf::Event event;

                while (window->pollEvent(event)) {
                    switch (event.type) {
                    case sf::Event::Closed: {
                        window->close();
                        break;
                    }
                    }

                    consoleBox->handleEvent(event);
                    if (!consoleBox->checkInput()) continue;

                    std::string str = consoleBox->getInput().toAnsiString();

                    if (mode == 11) {
                        try {
                            if (current_state == 0) {  
                                if (str.find(" ") != str.npos) throw std::exception();

                                prevN = std::stoi(str);
                                if (prevN > dict->size() || prevN < 0 || dict->empty() && prevN != 0) throw std::exception();

                                help_text.setString("Enter new strings in order (an empty string is a sign of the end):");
                                current_state = 1;
                            } else if (current_state == 1) {
                                if (str.empty()) {
                                    help_text.setString("Success. Enter the string number after which to insert:");
                                    current_state = 0;
                                } else {
                                    dict->insert(prevN, str);
                                    ++prevN;
                                }
                            }
                        } catch (...) {
                            current_state = 0;
                            help_text.setString("Incorrect input. Enter the string number after which to insert:");
                        }
                    } else if (mode == 12) {
                        try {
                            if (current_state == 0) {
                                if (str.find(" ") != str.npos) throw std::exception();

                                prevN = std::stoi(str);
                                if (prevN > dict->size() || prevN <= 0 || dict->empty()) throw std::exception();

                                help_text.setString("Enter the number of the character after which to insert:");
                                current_state = 1;
                            } else if (current_state == 1) {
                                if (str.find(" ") != str.npos) throw std::exception();

                                prevM = std::stoi(str);
                                if (prevM > dict->operator[](prevN)->size() || prevM < 1) throw std::exception();

                                help_text.setString("Enter a substring:");
                                current_state = 2;
                            } else if (current_state == 2) {
                                (*dict)[prevN]->insert(prevM, str);
                                help_text.setString("Success. Enter the string number to insert the substring:");
                                current_state = 0;
                            }
                        } catch (...) {
                            current_state = 0;
                            help_text.setString("Incorrect input. Enter the string number to insert the substring:");
                        }
                    } else if (mode == 13) {
                        try {
                            if (current_state == 0) {
                                if (str.find(" ") != str.npos) throw std::exception();

                                prevN = std::stoi(str);
                                if (prevN > dict->size() || prevN <= 0 || dict->empty()) throw std::exception();

                                dict->erase(prevN);
                                current_state = 0;
                                help_text.setString("Success. Enter the string number to delete:");
                            }
                        } catch (...) {
                            current_state = 0;
                            help_text.setString("Incorrect input. Enter the string number to delete:");
                        }
                    } else if (mode == 21) {
                        try {
                            if (current_state == 0) {
                                if (dict->empty()) throw std::exception();

                                if (str.empty()) {
                                    prevN = 1, prevM = dict->size();
                                    help_text.setString("Enter the original substring:");
                                    current_state = 1;
                                    consoleBox->clearInput();
                                    continue;
                                }

                                if (str.rfind(" ") != str.find(" ") || str.rfind(" ") == str.npos) throw std::exception();

                                prevN = std::stoi(str.substr(0, str.find(" ")));
                                prevM = std::stoi(str.substr(str.find(" ") + 1));

                                if (prevN > dict->size() || prevN <= 0 || dict->empty()) throw std::exception();
                                if (prevM > dict->size() || prevM <= 0) throw std::exception();

                                help_text.setString("Enter the original substring:");
                                current_state = 1;
                            } else if (current_state == 1) {
                                if (str.empty()) throw std::exception();

                                prevStr = str;
                                help_text.setString("Enter a new substring:");
                                current_state = 2;
                            } else if (current_state == 2) {
                                if (str.empty()) throw std::exception();

                                dict->replace(prevStr, str, prevN, prevM);
                                help_text.setString("Success. Enter a range of strings to contextually replace the substring (by default, all strings):");
                                current_state = 0;
                            }
                        } catch (...) {
                            current_state = 0;
                            help_text.setString("Incorrect input. Enter a range of strings to contextually replace the substring (by default, all strings):");
                        }
                    } else if (mode == 22) {
                        try {
                            if (current_state == 0) {
                                if (str.find(" ") != str.npos) throw std::exception();

                                prevN = std::stoi(str);
                                if (prevN > dict->size() || prevN <= 0 || dict->empty()) throw std::exception();
                                current_state = 1;
                                help_text.setString("Enter the character index:");
                            } else if (current_state == 1) {
                                if (str.find(" ") != str.npos) throw std::exception();

                                prevM = std::stoi(str);
                                if (prevM > dict->operator[](prevN)->size() || prevM <= 0) throw std::exception();

                                current_state = 2;
                                help_text.setString("Enter a new character");
                            } else if (current_state == 2) {
                                if (str.size() != 1) throw std::exception();

                                dict->operator[](prevN)->operator[](prevM - 1) = str[0];

                                help_text.setString("Success. Enter the string number to replace the character:");
                                current_state = 0;
                            }
                        } catch (...) {
                            current_state = 0;
                            help_text.setString("Incorrect input. Enter the string number to replace the character:");
                        }
                    } else if (mode == 23) {
                        try {
                            if (current_state == 0) {
                                if (dict->empty()) throw std::exception();

                                if (str.empty()) {
                                    prevN = 1, prevM = dict->size();
                                    help_text.setString("Enter N:");
                                    current_state = 1;
                                    consoleBox->clearInput();
                                    continue;
                                }

                                if (str.rfind(" ") != str.find(" ") || str.rfind(" ") == str.npos) throw std::exception();

                                prevN = std::stoi(str.substr(0, str.find(" ")));
                                prevM = std::stoi(str.substr(str.find(" ") + 1));

                                if (prevN > dict->size() || prevN <= 0 || dict->empty()) throw std::exception();
                                if (prevM > dict->size() || prevM <= 0) throw std::exception();

                                help_text.setString("Enter N:");
                                current_state = 1;
                            } else if (current_state == 1) {
                                if (str.find(" ") != str.npos) throw std::exception();

                                int N = std::stoi(str);
                                dict->replace_asterisk(N, prevN, prevM);

                                help_text.setString("Success. Enter a range of strings to replace N '*' with N/2 '+' (by default, all strings):");
                                current_state = 0;
                            }
                        } catch (...) {
                            current_state = 0;
                            help_text.setString("Incorrect input. Enter a range of strings to replace N '*' with N/2 '+' (by default, all strings):");
                        }
                    } else if (mode == 31) {
                        try {
                            if (current_state == 0) {
                                if (dict->empty()) throw std::exception();

                                if (str.empty()) {
                                    prevN = 1, prevM = dict->size();
                                    dict->remove_leading_zeros(prevN, prevM);
                                    help_text.setString("Success. Enter a range of strings to remove leading zeros in substrings (by default, all strings):");
                                    current_state = 0;
                                    consoleBox->clearInput();
                                    continue;
                                }

                                if (str.rfind(" ") != str.find(" ") || str.rfind(" ") == str.npos) throw std::exception();

                                prevN = std::stoi(str.substr(0, str.find(" ")));
                                prevM = std::stoi(str.substr(str.find(" ") + 1));

                                if (prevN > dict->size() || prevN <= 0 || dict->empty()) throw std::exception();
                                if (prevM > dict->size() || prevM <= 0) throw std::exception();

                                dict->remove_leading_zeros(prevN, prevM);
                                help_text.setString("Success. Enter a range of strings to remove leading zeros in substrings (by default, all strings):");
                                
                                current_state = 0;
                            }
                        } catch (...) {
                            current_state = 0;
                            help_text.setString("Incorrect input. Enter a range of strings to remove leading zeros in substrings (by default, all strings):");
                        }
                    } else if (mode == 32) {
                        try {
                            if (current_state == 0) {
                                if (dict->empty()) throw std::exception();

                                if (str.empty()) {
                                    prevN = 1, prevM = dict->size();
                                    dict->delete_non_growing_subgroups(prevN, prevM);
                                    help_text.setString("Success. Enter a range of strings to filter increasing sequences (by default, all strings):");
                                    current_state = 0;
                                    consoleBox->clearInput();
                                    continue;
                                }

                                if (str.rfind(" ") != str.find(" ") || str.rfind(" ") == str.npos) throw std::exception();

                                prevN = std::stoi(str.substr(0, str.find(" ")));
                                prevM = std::stoi(str.substr(str.find(" ") + 1));

                                if (prevN > dict->size() || prevN <= 0 || dict->empty()) throw std::exception();
                                if (prevM > dict->size() || prevM <= 0) throw std::exception();

                                dict->delete_non_growing_subgroups(prevN, prevM);
                                help_text.setString("Success. Enter a range of strings to filter increasing sequences (by default, all strings):");

                                current_state = 0;
                            }
                        } catch (...) {
                            current_state = 0;
                            help_text.setString("Incorrect input. Enter a range of strings to filter increasing sequences (by default, all strings):");
                        }
                    } else if (mode == 33) {
                        try {
                            if (current_state == 0) {
                                if (dict->empty()) throw std::exception();

                                if (str.empty()) {
                                    prevN = 1, prevM = dict->size();
                                    dict->delete_between(prevN, prevM);
                                    help_text.setString("Success. Enter a range of strings to erase characters between { and } (by default, all strings):");
                                    current_state = 0;
                                    consoleBox->clearInput();
                                    continue;
                                }

                                if (str.rfind(" ") != str.find(" ") || str.rfind(" ") == str.npos) throw std::exception();

                                prevN = std::stoi(str.substr(0, str.find(" ")));
                                prevM = std::stoi(str.substr(str.find(" ") + 1));

                                if (prevN > dict->size() || prevN <= 0 || dict->empty()) throw std::exception();
                                if (prevM > dict->size() || prevM <= 0) throw std::exception();

                                dict->delete_between(prevN, prevM);
                                help_text.setString("Success. Enter a range of strings to erase characters between { and } (by default, all strings):");

                                current_state = 0;
                            }
                        } catch (...) {
                            current_state = 0;
                            help_text.setString("Incorrect input. Enter a range of strings to erase characters between { and } (by default, all strings):");
                        }
                    }
                    if (consoleBox->checkInput() && mode == 1) {
                        try {
                            if (consoleBox->getInput().getSize() > 7 && consoleBox->getInput().substring(0, 7) == "insert " && current_state == 0) {
                                current_state = 1;
                                window->setTitle("Command console (waiting for insert input)");
                                prevN = std::stoi(consoleBox->getInput().substring(7).toAnsiString());
                            } else if (consoleBox->getInput().getSize() > 7 && consoleBox->getInput().substring(0, 7) == "delete " && current_state == 0) {
                                current_state = 0;
                                window->setTitle("Command console (prev: OK)");
                                prevN = std::stoi(consoleBox->getInput().substring(7).toAnsiString());
                                dict->erase(prevN);
                            } else if (consoleBox->getInput().getSize() > 10 && consoleBox->getInput().substring(0, 10) == "insertsub " && current_state == 0) {
                                current_state = 3;
                                window->setTitle("Command console (waiting for substr input)");
                                prevN = std::stoi(consoleBox->getInput().substring(10, consoleBox->getInput().find(" ", 10) - 10).toAnsiString());
                                prevM = std::stoi(consoleBox->getInput().substring(consoleBox->getInput().find(" ", 10) + 1).toAnsiString());
                            } else if (current_state == 1) {
                                if (consoleBox->getInput().isEmpty()) {
                                    current_state = 0;
                                    window->setTitle("Command console (prev: OK)");
                                } else {
                                    dict->insert(prevN, consoleBox->getInput().toAnsiString());
                                    prevN++;
                                }
                            } else if (current_state == 3) {
                                current_state = 0;
                                window->setTitle("Command console (prev: OK)");
                                (*dict)[prevN]->insert(prevM, consoleBox->getInput());
                            } else {
                                current_state = 0;
                                window->setTitle("Command console (prev: Incorrect input)");
                            }
                            consoleBox->clearInput();
                        } catch (...) {
                            window->setTitle("Command console (prev: Incorrect input)");
                            current_state = 0;
                            consoleBox->clearInput();
                        }
                    }

                    if (consoleBox->checkInput() && mode == 2) {
                        try {
                            if (consoleBox->getInput().getSize() > 12 && consoleBox->getInput().substring(0, 12) == "replacechar " && current_state == 0) {
                                current_state = 2;
                                window->setTitle("Command console (waiting for replacechar input)");
                                prevN = std::stoi(consoleBox->getInput().substring(12, consoleBox->getInput().find(" ", 12) - 12).toAnsiString());
                                prevM = std::stoi(consoleBox->getInput().substring(consoleBox->getInput().find(" ", 12) + 1).toAnsiString());
                            } else if (consoleBox->getInput().getSize() >= 7 && consoleBox->getInput().substring(0, 7) == "replace" && current_state == 0) {
                                current_state = 1;
                                window->setTitle("Command console (waiting for replace input)");
                                if (consoleBox->getInput().getSize() == 7) {
                                    prevN = 1, prevM = dict->size();
                                } else {
                                    prevN = std::stoi(consoleBox->getInput().substring(8, consoleBox->getInput().find(" ", 8) - 7).toAnsiString());
                                    prevM = std::stoi(consoleBox->getInput().substring(consoleBox->getInput().find(" ", 8) + 1).toAnsiString());
                                }
                            } else if (current_state == 1) {
                                current_state = 0;
                                window->setTitle("Command console (prev: OK)");
                                dict->replace(consoleBox->getInput().substring(0, consoleBox->getInput().find(" ")).toAnsiString(),
                                    consoleBox->getInput().substring(consoleBox->getInput().find(" ") + 1).toAnsiString(), prevN, prevM);
                            } else if (current_state == 2) {
                                current_state = 0;
                                window->setTitle("Command console (prev: OK)");
                                (*(*dict)[prevN])[prevM - 1] = consoleBox->getInput().toAnsiString()[0];
                            } else {
                                current_state = 0;
                                window->setTitle("Command console (prev: Incorrect input)");
                            }
                            consoleBox->clearInput();
                        } catch (...) {
                            window->setTitle("Command console (prev: Incorrect input)");
                            current_state = 0;
                            consoleBox->clearInput();
                        }
                    }

                    if (consoleBox->checkInput() && mode == 3) {
                        try {
                            if (consoleBox->getInput().getSize() > 9 && consoleBox->getInput().substring(0, 9) == "delzeros " && current_state == 0) {
                                current_state = 0;
                                window->setTitle("Command console (prev: OK)");
                                prevN = std::stoi(consoleBox->getInput().substring(9, consoleBox->getInput().find(" ", 9) - 9).toAnsiString());
                                prevM = std::stoi(consoleBox->getInput().substring(consoleBox->getInput().find(" ", 9) + 1).toAnsiString());
                                dict->remove_leading_zeros(prevN, prevM);
                            } else if (consoleBox->getInput().getSize() > 10 && consoleBox->getInput().substring(0, 10) == "lisfilter " && current_state == 0) {
                                current_state = 0;
                                window->setTitle("Command console (prev: OK)");
                                prevN = std::stoi(consoleBox->getInput().substring(10, consoleBox->getInput().find(" ", 10) - 10).toAnsiString());
                                prevM = std::stoi(consoleBox->getInput().substring(consoleBox->getInput().find(" ", 10) + 1).toAnsiString());
                                dict->delete_non_growing_subgroups(prevN, prevM);
                            } else if (consoleBox->getInput().getSize() > 14 && consoleBox->getInput().substring(0, 14) == "deletebetween " && current_state == 0) {
                                current_state = 0;
                                window->setTitle("Command console (prev: OK)");
                                prevN = std::stoi(consoleBox->getInput().substring(14, consoleBox->getInput().find(" ", 14) - 14).toAnsiString());
                                prevM = std::stoi(consoleBox->getInput().substring(consoleBox->getInput().find(" ", 14) + 1).toAnsiString());
                                dict->delete_between(prevN, prevM);
                            } else {
                                current_state = 0;
                                window->setTitle("Command console (prev: Incorrect input)");
                            }
                            consoleBox->clearInput();
                        } catch (...) {
                            window->setTitle("Command console (prev: Incorrect input)");
                            current_state = 0;
                            consoleBox->clearInput();
                        }
                    }

                    consoleBox->clearInput();
                }

                window->clear(sf::Color::Black);
                window->draw(help_text);
                consoleBox->draw(window);
                window->display();
            }
		}
	};
}