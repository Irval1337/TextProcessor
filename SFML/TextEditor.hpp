#pragma once

#include <vector>
#include <xutility>
#include <string>
#include <iostream>
#include "MultifunctionString.hpp"

namespace TextEditor {
	class StringsDictionary {
		using MString = MultifunctionString::MString;
	private:
		size_t _size;
		std::vector<MString*> _strings_pointers;
	public:
		StringsDictionary() {
			_size = 0;
		}

		~StringsDictionary() {
			clear();
		}

		size_t size() {
			return _size;
		}

		bool empty() {
			if (_size == 1 && _strings_pointers[0]->size() == 0) return true;
			return size() == 0;
		}

		void insert(size_t ind, std::string str) {
			if (_size == 1 && _strings_pointers[0]->empty() && ind == 0) {
				delete _strings_pointers[0];
				--_size;
			}

			MString* new_pointer = new MString(str);
			_strings_pointers.insert(_strings_pointers.begin() + ind, new_pointer);
			++_size;
		}

		void insert(size_t ind, std::vector<std::string> strings) {
			if (_size == 1 && _strings_pointers[0]->empty() && ind == 0) {
				delete _strings_pointers[0];
				--_size;
			}

			std::vector<MString*> strings_pointers(strings.size());
			for (int i = 0; i < strings.size(); ++i) {
				strings_pointers[i] = new MString(strings[i]);
			}
			_strings_pointers.insert(_strings_pointers.begin() + ind, strings_pointers.begin(), strings_pointers.end());
			_size += strings.size();
		}

		void replace(const MString& old_substr, const MString& new_substr, size_t L = -1, size_t R = -1) {
			if (L == -1)
				L = 1;
			if (R == -1)
				R = _size;

			for (size_t i = L; i <= R; ++i) {
				_strings_pointers[i - 1]->m_replace(old_substr, new_substr);
			}
		}

		void replace_asterisk(const size_t N, size_t L = -1, size_t R = -1) {
			if (L == -1)
				L = 1;
			if (R == -1)
				R = _size;

			for (size_t i = L; i <= R; ++i) {
				_strings_pointers[i - 1]->replace_asterisk(N);
			}
		}

		void remove_leading_zeros(size_t L = -1, size_t R = -1) {
			if (L == -1)
				L = 1;
			if (R == -1)
				R = _size;

			for (size_t i = L; i <= R; ++i) {
				_strings_pointers[i - 1]->remove_leading_zeros();
			}
		}

		void delete_non_growing_subgroups(size_t L = -1, size_t R = -1) {
			if (L == -1)
				L = 1;
			if (R == -1)
				R = _size;

			for (size_t i = L; i <= R; ++i) {
				_strings_pointers[i - 1]->delete_non_growing_subgroups();
			}
		}

		void delete_between(size_t L = -1, size_t R = -1) {
			if (L == -1)
				L = 1;
			if (R == -1)
				R = _size;

			for (size_t i = L; i <= R; ++i) {
				_strings_pointers[i - 1]->delete_between("{", "}");
			}
		}

		void erase(size_t ind) {
			if (this->size() == 1) {
				*_strings_pointers[0] = "";
				return;
			}
			delete _strings_pointers[ind - 1];
			_strings_pointers.erase(_strings_pointers.begin() + ind - 1);
			--_size;
		}

		void clear() {
			for (size_t i = 0; i < _size; ++i) {
				delete _strings_pointers[i];
			}
			_strings_pointers.clear();
			_size = 0;
		}

		MString* operator[](size_t i) {
			return _strings_pointers[i - 1];
		}

		friend std::ostream& operator<< (std::ostream& out, const StringsDictionary& dict) {
			MString elements = "";
			for (auto& pointer : dict._strings_pointers) {
				elements += "\n" + *pointer;
			}
			return out << "size: " << dict._size << elements << "\n";
		}
	};
}