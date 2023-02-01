#pragma once

#include <string>
#include <cctype>
#include <iostream>

namespace MultifunctionString {
    class MString : public std::string {
        using base = std::string;
    private:
        bool check_growing(const MString& str) {
            bool is_good = true;
            for (size_t i = 1; i < str.size(); ++i) {
                if (str[i - 1] > str[i]) {
                    is_good = false;
                    break;
                }
            }

            return is_good;
        }
        std::vector<MString*> additional;
    public:
        using base::base;

        MString(std::string s) : base(s) {}
        MString(const char* s) : base(s) {}

        //void m_additional(const MString)

        void m_insert(size_t ind, const MString& substr) {
            this->insert(ind, substr);
        }

        void m_replace(size_t ind, const char* new_c) {
            (*this)[ind - 1] = *new_c;
        }

        void m_replace(const MString& old_substr, const MString& new_substr) {
            MString new_str = "";

            for (size_t i = 0; i < this->size(); ++i) {
                if (i + old_substr.size() - 1 >= this->size()) {
                    new_str += (*this)[i];
                    continue;
                }

                if (this->substr(i, old_substr.size()) == old_substr) {
                    new_str += new_substr;
                    i += old_substr.size() - 1;
                } else {
                    new_str += (*this)[i];
                }
            }

            *this = new_str;
        }

        void remove_leading_zeros() {
            MString new_str = "";
            bool is_digit_now = false;
            MString digit_str = "";

            for (size_t i = 0; i < this->size(); ++i) {
                if (!std::isdigit((*this)[i])) {
                    if (is_digit_now) {
                        new_str += digit_str;
                        digit_str.clear();
                        is_digit_now = false;
                    }

                    new_str += (*this)[i];
                    continue;
                }

                if (!is_digit_now) {
                    is_digit_now = true;
                }

                if ((*this)[i] != '0' && digit_str.size() == 1 && digit_str[0] == '0') {
                    digit_str[0] = (*this)[i];
                } else if (digit_str.empty() || digit_str.size() > 1 || digit_str.size() == 1 && digit_str[0] != '0' || (*this)[i] != '0') {
                    digit_str += (*this)[i];
                }
            }

            new_str += digit_str;
            digit_str.clear();

            *this = new_str;
        }

        void delete_non_growing_subgroups() {
            MString new_str = "";
            bool is_digit_now = false;
            MString digit_str = "";

            for (size_t i = 0; i < this->size(); ++i) {
                if (!std::isdigit((*this)[i])) {
                    if (is_digit_now) {
                        if (check_growing(digit_str)) {
                            new_str += digit_str;
                        }
                        digit_str.clear();
                        is_digit_now = false;
                    }

                    new_str += (*this)[i];
                    continue;
                }

                if (!is_digit_now) {
                    is_digit_now = true;
                }

                digit_str += (*this)[i];
            }

            if (check_growing(digit_str)) {
                new_str += digit_str;
            }
            digit_str.clear();

            *this = new_str;
        }

        void replace_asterisk(const size_t N) {
            MString new_str = "";
            MString new_substr(N / 2, '+');
            bool is_aster = false;
            int aster_count = 0;

            for (size_t i = 0; i < this->size(); ++i) {
                if (i + N - 1 >= this->size()) {
                    new_str += (*this)[i];
                    continue;
                }

                if (this->at(i) == '*') {
                    if (!is_aster) is_aster = true;
                    ++aster_count;
                } else {
                    if (is_aster) {
                        if (aster_count == N) new_str += std::string(N / 2, '+');
                        else new_str += std::string(aster_count, '*');
                        aster_count = 0;
                        is_aster = false;
                    }
                    new_str += this->at(i);
                }
            }

            *this = new_str;
        }

        void delete_between(const char* c_open, const char* c_close) {
            MString new_str = "";
            int current_level = 0;

            for (size_t i = 0; i < this->size(); ++i) {
                if (current_level < 0) return;

                if ((*this)[i] == *c_open) {
                    ++current_level;
                } else if ((*this)[i] == *c_close) {
                    --current_level;
                } else if (current_level == 0) {
                    new_str += (*this)[i];
                }
            }

            *this = new_str;
        }
    };
}