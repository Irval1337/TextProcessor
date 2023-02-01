#pragma once

#include <xutility>
#include <Windows.h>

namespace SFML {
    class Settings {
    private:
        std::pair<int, int> _GetScreenSize() {
            int cx = GetSystemMetrics(SM_CXFULLSCREEN);
            int cy = GetSystemMetrics(SM_CYFULLSCREEN);
            return std::make_pair(cx, cy);
        }
    public:
        int window_width;
        int window_height;
        int frame_limit;

        Settings() {
            SetCustomSize();
            frame_limit = 144;
        }

        void SetToScreenSize() {
            std::pair<int, int> metrics = _GetScreenSize();
            window_width = metrics.first;
            window_height = metrics.second;
        }
        void SetCustomSize() {
            window_width = 1790;
            window_height = 886;
        }
    };
}