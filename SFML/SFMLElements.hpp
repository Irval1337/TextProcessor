#pragma once

#include <xutility>
#include <vector>
#include <SFML/Graphics.hpp>
#include "Settings.h"
#include "TextEditor.hpp"
#include "Button.hpp"
#include "Textbox.h"
#include <Windows.h>
#include "TextEditor.hpp"
#include <iostream>
#include <algorithm>
#include "Console.hpp"
#include <cctype>

namespace SFML {
	class Elements {
	private:
		sf::Font font1, font2;
        Button minimize_button, maximize_button, close_button;
        Button insertion_button, replacement_button, algorithms_button;
        Button page_up;
        sf::Sprite icon;
        sf::Text logo_text;
        std::vector<TextBox*> text_areas;
        std::vector<Button*> insertion_children, replacement_children, algorithms_children;

#pragma region Textures
        sf::Texture minimize_button_default;
        sf::Texture minimize_button_activated;

        sf::Texture maximize_button_default;

        sf::Texture close_button_default;
        sf::Texture close_button_activated;

        sf::Texture insertion_button_default;
        sf::Texture insertion_button_activated;

        sf::Texture replacement_button_default;
        sf::Texture replacement_button_activated;

        sf::Texture algorithms_button_default;
        sf::Texture algorithms_button_activated;

        sf::Texture string_button_default;
        sf::Texture string_button_activated;

        sf::Texture substring_button_default;
        sf::Texture substring_button_activated;

        sf::Texture delete_button_default;
        sf::Texture delete_button_activated;

        sf::Texture replace_substring_button_default;
        sf::Texture replace_substring_button_activated;

        sf::Texture char_button_default;
        sf::Texture char_button_activated;

        sf::Texture asterisk_button_default;
        sf::Texture asterisk_button_activated;

        sf::Texture zeros_button_default;
        sf::Texture zeros_button_activated;

        sf::Texture lis_button_default;
        sf::Texture lis_button_activated;

        sf::Texture between_button_default;
        sf::Texture between_button_activated;

        sf::Texture icon_sf;
        sf::Texture page_up_texture;
#pragma endregion

        int focused_line = 1;
        int scrolled = 0;
        bool opened_insertion = false, opened_replacement = false, opened_algorithms = false;
	public:
        SFML::Settings sfml_settings;
        TextEditor::StringsDictionary dict;

        Elements() {

        }

        void InitializeTextures() {
            minimize_button_default.loadFromFile("img\\minimize_button\\default.png");
            minimize_button_activated.loadFromFile("img\\minimize_button\\activated.png");

            maximize_button_default.loadFromFile("img\\maximize_button\\default.png");

            close_button_default.loadFromFile("img\\close_button\\default.png");
            close_button_activated.loadFromFile("img\\close_button\\activated.png");

            insertion_button_default.loadFromFile("img\\insertion_button\\default.png");
            insertion_button_activated.loadFromFile("img\\insertion_button\\activated.png");

            replacement_button_default.loadFromFile("img\\replacement_button\\default.png");
            replacement_button_activated.loadFromFile("img\\replacement_button\\activated.png");

            algorithms_button_default.loadFromFile("img\\algorithms_button\\default.png");
            algorithms_button_activated.loadFromFile("img\\algorithms_button\\activated.png");

            string_button_default.loadFromFile("img\\insertion_button\\string_default.png");
            string_button_activated.loadFromFile("img\\insertion_button\\string_activated.png");

            substring_button_default.loadFromFile("img\\insertion_button\\substring_default.png");
            substring_button_activated.loadFromFile("img\\insertion_button\\substring_activated.png");

            delete_button_default.loadFromFile("img\\insertion_button\\delete_default.png");
            delete_button_activated.loadFromFile("img\\insertion_button\\delete_activated.png");

            replace_substring_button_default.loadFromFile("img\\replacement_button\\substring_default.png");
            replace_substring_button_activated.loadFromFile("img\\replacement_button\\substring_activated.png");

            char_button_default.loadFromFile("img\\replacement_button\\character_default.png");
            char_button_activated.loadFromFile("img\\replacement_button\\character_activated.png");

            asterisk_button_default.loadFromFile("img\\replacement_button\\asterisk_default.png");
            asterisk_button_activated.loadFromFile("img\\replacement_button\\asterisk_activated.png");

            zeros_button_default.loadFromFile("img\\algorithms_button\\zeros_default.png");
            zeros_button_activated.loadFromFile("img\\algorithms_button\\zeros_activated.png");

            lis_button_default.loadFromFile("img\\algorithms_button\\lis_default.png");
            lis_button_activated.loadFromFile("img\\algorithms_button\\lis_activated.png");

            between_button_default.loadFromFile("img\\algorithms_button\\del_betw_default.png");
            between_button_activated.loadFromFile("img\\algorithms_button\\del_betw_activated.png");

            icon_sf.loadFromFile("img\\icon.png");
            page_up_texture.loadFromFile("img\\page_up.png");
        }

		void Initialize(sf::RenderWindow& window) {
            window.setFramerateLimit(sfml_settings.frame_limit);

            font1.loadFromFile("Consolas.ttf");
            font2.loadFromFile("Calibri.ttf");

            InitializeTextures();
            minimize_button = Button({ 1, 1 }, minimize_button_default, minimize_button_activated, minimize_button_activated);
            minimize_button.setPosition(sf::Vector2f(sfml_settings.window_width - 138, 0));
            minimize_button.setTexture(minimize_button_default);

            maximize_button = Button({ 1, 1 }, maximize_button_default, maximize_button_default, maximize_button_default);
            maximize_button.setPosition(sf::Vector2f(sfml_settings.window_width - 92, 0));
            maximize_button.setTexture(maximize_button_default);

            close_button = Button({ 1, 1 }, close_button_default, close_button_activated, close_button_activated);
            close_button.setPosition(sf::Vector2f(sfml_settings.window_width - 46, 0));
            close_button.setTexture(close_button_default);

            insertion_button = Button({ 1, 1 }, insertion_button_default, insertion_button_activated, insertion_button_activated);
            insertion_button.setPosition(sf::Vector2f(40, 4));
            insertion_button.setTexture(insertion_button_default);

            Button* insertion_child = new Button({ 1, 1 }, string_button_default, string_button_activated, string_button_activated);
            insertion_child->setPosition(sf::Vector2f(40, 25));
            insertion_child->setTexture(string_button_default);
            insertion_children.push_back(insertion_child);

            insertion_child = new Button({ 1, 1 }, substring_button_default, substring_button_activated, substring_button_activated);
            insertion_child->setPosition(sf::Vector2f(40, 46));
            insertion_child->setTexture(substring_button_default);
            insertion_children.push_back(insertion_child);

            insertion_child = new Button({ 1, 1 }, delete_button_default, delete_button_activated, delete_button_activated);
            insertion_child->setPosition(sf::Vector2f(40, 67));
            insertion_child->setTexture(delete_button_default);
            insertion_children.push_back(insertion_child);

            replacement_button = Button({ 1, 1 }, replacement_button_default, replacement_button_activated, replacement_button_activated);
            replacement_button.setPosition(sf::Vector2f(140, 4));
            replacement_button.setTexture(replacement_button_default);

            Button* replacement_child = new Button({ 1, 1 }, replace_substring_button_default, replace_substring_button_activated, replace_substring_button_activated);
            replacement_child->setPosition(sf::Vector2f(140, 25));
            replacement_child->setTexture(replace_substring_button_default);
            replacement_children.push_back(replacement_child);

            replacement_child = new Button({ 1, 1 }, char_button_default, char_button_activated, char_button_activated);
            replacement_child->setPosition(sf::Vector2f(140, 46));
            replacement_child->setTexture(char_button_default);
            replacement_children.push_back(replacement_child);

            replacement_child = new Button({ 1, 1 }, asterisk_button_default, asterisk_button_activated, asterisk_button_activated);
            replacement_child->setPosition(sf::Vector2f(140, 67));
            replacement_child->setTexture(asterisk_button_default);
            replacement_children.push_back(replacement_child);
            
            algorithms_button = Button({ 1, 1 }, algorithms_button_default, algorithms_button_activated, algorithms_button_activated);
            algorithms_button.setPosition(sf::Vector2f(258, 4));
            algorithms_button.setTexture(algorithms_button_default);

            Button* algorithms_child = new Button({ 1, 1 }, zeros_button_default, zeros_button_activated, zeros_button_activated);
            algorithms_child->setPosition(sf::Vector2f(258, 25));
            algorithms_child->setTexture(zeros_button_default);
            algorithms_children.push_back(algorithms_child);

            algorithms_child = new Button({ 1, 1 }, lis_button_default, lis_button_activated, lis_button_activated);
            algorithms_child->setPosition(sf::Vector2f(258, 46));
            algorithms_child->setTexture(lis_button_default);
            algorithms_children.push_back(algorithms_child);

            algorithms_child = new Button({ 1, 1 }, between_button_default, between_button_activated, between_button_activated);
            algorithms_child->setPosition(sf::Vector2f(258, 67));
            algorithms_child->setTexture(between_button_default);
            algorithms_children.push_back(algorithms_child);

            icon.setTexture(icon_sf);
            icon.setPosition({ 10, 4 });

            page_up = Button({ 1, 1 }, page_up_texture, page_up_texture, page_up_texture);
            page_up.setPosition(sf::Vector2f(sfml_settings.window_width - 35, 40));
            page_up.setTexture(page_up_texture);

            logo_text.setFont(font1);
            logo_text.setString("Text processor - by irval1337.github.io");
            logo_text.setCharacterSize(15);
            logo_text.setFillColor(sf::Color(204, 204, 204));
            logo_text.setPosition(sfml_settings.window_width / 2 - 175, 3);

            TextBox* text_area = new TextBox(font2, font1);
            text_area->setPosition(35 + 25, 30);
            text_area->setSize(sfml_settings.window_width - 100, 20);
            text_area->setBorder(0);
            text_area->setText("");
            text_area->setNum(1);
            text_areas.push_back(text_area);

            dict.insert(0, "");
		}

        bool CheckHowered(sf::RenderWindow& window) {
            bool val = false;
            val |= minimize_button.autoSetTexture(window);
            val |= close_button.autoSetTexture(window);
            val |= page_up.autoSetTexture(window);
            if (insertion_button.autoSetTexture(window, insertion_children, &opened_insertion)) {
                val = true;
                opened_insertion = true;
            } else opened_insertion = false;
            if (replacement_button.autoSetTexture(window, replacement_children, &opened_replacement)) {
                val = true;
                opened_replacement = true;
            } else opened_replacement = false;
            if (algorithms_button.autoSetTexture(window, algorithms_children, &opened_algorithms)) {
                val = true;
                opened_algorithms = true;
            } else opened_algorithms = false;
            
            return val;
        }

        void CheckReleased(sf::RenderWindow& window) {
            if (minimize_button.isMouseOver(window)) {
                ::SendNotifyMessage(window.getSystemHandle(), WM_SYSCOMMAND, SC_MINIMIZE, 0);
            } else if (close_button.isMouseOver(window)) {
                window.close();
            } else if (page_up.isMouseOver(window)) {
                Scroll(scrolled);
            } else if (insertion_children[0]->isMouseOver(window) && opened_insertion) {
                text_areas[focused_line - 1]->setFocused(false);
                SFML::Console console(&dict);
                console.Show(11);
                update_from_dict();
                
            } else if (insertion_children[1]->isMouseOver(window) && opened_insertion) {
                text_areas[focused_line - 1]->setFocused(false);
                SFML::Console console(&dict);
                console.Show(12);
                update_from_dict();

            } else if (insertion_children[2]->isMouseOver(window) && opened_insertion) {
                text_areas[focused_line - 1]->setFocused(false);
                SFML::Console console(&dict);
                console.Show(13);
                update_from_dict();

            } else if (replacement_children[0]->isMouseOver(window) && opened_replacement) {
                text_areas[focused_line - 1]->setFocused(false);
                SFML::Console console(&dict);
                console.Show(21);
                update_from_dict();
            } else if (replacement_children[1]->isMouseOver(window) && opened_replacement) {
                text_areas[focused_line - 1]->setFocused(false);
                SFML::Console console(&dict);
                console.Show(22);
                update_from_dict();
            } else if (replacement_children[2]->isMouseOver(window) && opened_replacement) {
                text_areas[focused_line - 1]->setFocused(false);
                SFML::Console console(&dict);
                console.Show(23);
                update_from_dict();
            } else if (algorithms_children[0]->isMouseOver(window) && opened_algorithms) {
                text_areas[focused_line - 1]->setFocused(false);
                SFML::Console console(&dict);
                console.Show(31);
                update_from_dict();
            } else if (algorithms_children[1]->isMouseOver(window) && opened_algorithms) {
                text_areas[focused_line - 1]->setFocused(false);
                SFML::Console console(&dict);
                console.Show(32);
                update_from_dict();
            } else if (algorithms_children[2]->isMouseOver(window) && opened_algorithms) {
                text_areas[focused_line - 1]->setFocused(false);
                SFML::Console console(&dict);
                console.Show(33);
                update_from_dict();
            }
        }

        bool CheckPressed(sf::RenderWindow& window) {
            bool children = false;
            for (auto& i : insertion_children) {
                children |= i->isMouseOver(window);
            }
            return minimize_button.isMouseOver(window) || maximize_button.isMouseOver(window) ||
                close_button.isMouseOver(window) || insertion_button.isMouseOver(window) ||
                replacement_button.isMouseOver(window) || algorithms_button.isMouseOver(window) ||
                page_up.isMouseOver(window) || children;
        }

        void Scroll(int count) {
            if (text_areas.size() == 1) return;
            if (scrolled == text_areas.size() - 1 && count < 0) return;
            if (scrolled == 0 && count > 0) return;

            scrolled -= count;
            for (size_t i = 0; i < text_areas.size(); ++i) {
                text_areas[i]->setPosition(text_areas[i]->getPosition().x, text_areas[i]->getPosition().y + 19 * count);
            }
        }

        void HandleText(sf::Event& event, sf::RenderWindow& window) {
            if (CheckHowered(window)) return;

            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Up && focused_line > 1) {
                text_areas[focused_line - 1]->setFocused(false);
                --focused_line;
                text_areas[focused_line - 1]->setFocused(true);

                if (text_areas[focused_line - 1]->getPosition().y < 30) Scroll(1);
            } 
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Down && focused_line < text_areas.size()) {
                text_areas[focused_line - 1]->setFocused(false);
                ++focused_line;
                text_areas[focused_line - 1]->setFocused(true);

                if (text_areas[focused_line - 1]->getPosition().y >= sfml_settings.window_height - 1) Scroll(-1);
            }

            if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left &&
                sf::Mouse::getPosition(window).y > text_areas[text_areas.size() - 1]->getPosition().y + text_areas[text_areas.size() - 1]->getSize().y) {
                text_areas[text_areas.size() - 1]->setFocused(true);
                return;
            }

            for (size_t i = 0; i < text_areas.size(); ++i) {
                int focused = text_areas[i]->handleEvent(event);

                if (focused) {
                    focused_line = i + 1;
                }
            }

            bool is_recovered = text_areas[focused_line - 1]->checkInput();

            *dict[focused_line] = text_areas[focused_line - 1]->getCurrentText().toAnsiString();

            if (is_recovered || !text_areas[focused_line - 1]->isChanged() && event.key.code != sf::Keyboard::Up && event.key.code != sf::Keyboard::Down &&
                event.key.code != sf::Keyboard::Left && event.key.code != sf::Keyboard::Right && 31 < int(event.text.unicode) && 256 > int(event.text.unicode)) {
                bool new_line = is_recovered || !text_areas[focused_line - 1]->isChanged();
                bool is_in_mid = text_areas[focused_line - 1]->getfocusChar() != text_areas[focused_line - 1]->getCurrentText().getSize();
                if (is_in_mid)
                    text_areas[focused_line - 1]->insert(event);

                std::string need_to_add = is_recovered ? text_areas[focused_line - 1]->getCurrentText().toAnsiString() :
                    !is_in_mid ? sf::String(event.text.unicode).toAnsiString() : dict[focused_line]->substr(dict[focused_line]->size() - 1);

                if (!text_areas[focused_line - 1]->isChanged())
                    *dict[focused_line] = text_areas[focused_line - 1]->getCurrentText().toAnsiString();
                
                if (new_line && !is_in_mid)
                    text_areas[focused_line - 1]->setFocused(false);

                if (is_recovered) text_areas[focused_line - 1]->recover();

                dict.insert(focused_line, need_to_add);

                TextBox* text_area = new TextBox(font2, font1);
                text_area->setPosition(35 + 25, 30 + 19 * (focused_line - scrolled));
                text_area->setSize(sfml_settings.window_width - 100, 20);
                text_area->setBorder(0);
                text_area->setText(sf::String(need_to_add));
                text_area->setNum(focused_line + 1);
                text_areas.insert(text_areas.begin() + focused_line, text_area);
                for (size_t i = focused_line + 1; i < text_areas.size(); ++i) {
                    text_areas[i]->setPosition(text_areas[i]->getPosition().x, text_areas[i]->getPosition().y + 19);
                    text_areas[i]->setNum(i + 1);
                }

                if ((is_recovered || new_line) && !is_in_mid) {
                    text_areas[focused_line]->setFocused(true);
                    ++focused_line;
                }

                if (text_areas.size() - scrolled > 45) {
                    Scroll(-1);
                }
            }

            if (text_areas[focused_line - 1]->checkDelete() && focused_line != 1) {
                int appended = text_areas[focused_line - 2]->append(text_areas[focused_line - 1]->getCurrentText(), true);
                text_areas[focused_line - 2]->setFocused(true);
                text_areas[focused_line - 1]->setFocused(false);
                if (appended == text_areas[focused_line - 1]->getCurrentText().getSize()) {
                    *dict[focused_line - 1] += *dict[focused_line];
                    dict.erase(focused_line);
                    delete text_areas[focused_line - 1];
                    text_areas.erase(text_areas.begin() + focused_line - 1);
                    for (size_t i = focused_line - 1; i < text_areas.size(); ++i) {
                        text_areas[i]->setPosition(text_areas[i]->getPosition().x, text_areas[i]->getPosition().y - 19);
                        text_areas[i]->setNum(i + 1);
                    }
                } else {
                    *dict[focused_line - 1] += dict[focused_line]->substr(0, appended);
                    *dict[focused_line] = dict[focused_line]->substr(appended);
                    text_areas[focused_line - 1]->popText(appended);
                }
                --focused_line;
            }

            for (size_t i = 1; i <= dict.size(); ++i) {
                *dict[i] = text_areas[i - 1]->getCurrentText().toAnsiString();
            }
        }

        int getLastY() {
            return std::min(text_areas.size() - scrolled - 1, 45ULL) * 19 + 30;
        }

        void Draw(sf::RenderWindow& window) {
            minimize_button.drawTo(window);
            maximize_button.drawTo(window);
            close_button.drawTo(window);
            insertion_button.drawTo(window);
            replacement_button.drawTo(window);
            algorithms_button.drawTo(window);
            window.draw(icon);
            window.draw(logo_text);
            page_up.drawTo(window);
            for (size_t i = 0; i < 45 && i + scrolled < text_areas.size(); ++i) {
                text_areas[i + scrolled]->draw(window);
            }
            for (auto& but : insertion_children) {
                if (opened_insertion) {
                    but->drawTo(window);
                }
            }

            for (auto& but : replacement_children) {
                if (opened_replacement) {
                    but->drawTo(window);
                }
            }

            for (auto& but : algorithms_children) {
                if (opened_algorithms) {
                    but->drawTo(window);
                }
            }
        }

        private:
            void update_from_dict() {
                for (size_t i = 0; i < text_areas.size(); ++i) {
                    delete text_areas[i];
                }
                text_areas.clear();
                scrolled = 0;
                focused_line = 1;

                for (size_t i = 0; i < dict.size(); ++i) {
                    TextBox* text_area = new TextBox(font2, font1);
                    text_area->setPosition(35 + 25, 30 + i * 19);
                    text_area->setSize(sfml_settings.window_width - 100, 20);
                    text_area->setBorder(0);
                    text_area->setText("");
                    text_area->setNum(i + 1);
                    int appended = text_area->append(*dict[i + 1], false);
                    text_areas.push_back(text_area);
                    if (appended != dict[i + 1]->size()) {
                        dict.insert(i + 1, dict[i + 1]->substr(appended));
                        *dict[i + 1] = dict[i + 1]->substr(0, appended);
                    }
                }

                text_areas[0]->setFocused(true);
            }
	};
}