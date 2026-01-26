#include "BorderlessWindow.h"
#include "../core/Log.h"

BorderlessWindow g_borderlessWindow;

bool BorderlessWindow::FindGameWindow() {
    windowHandle = ::FindWindowW(nullptr, WINDOW_TITLE);

    if (windowHandle == nullptr) {
        log(LogLevel::WARN, "Could not find Dark Souls III window");
        return false;
    }

    return true;
}

bool BorderlessWindow::Enable() {
    if (isActive) {
        log(LogLevel::WARN, "Borderless mode already enabled");
        return true;
    }

    if (!FindGameWindow()) {
        return false;
    }

    windowedStyle = ::GetWindowLongW(windowHandle, GWL_STYLE);
    if (windowedStyle == 0) {
        log(LogLevel::ERR, "Failed to get window style");
        return false;
    }

    if (!::GetWindowRect(windowHandle, &windowedRect)) {
        log(LogLevel::ERR, "Failed to get window rect");
        return false;
    }

    LONG borderlessWindowStyle = windowedStyle & ~(WS_CAPTION | WS_THICKFRAME | WS_BORDER);
    ::SetWindowLongW(windowHandle, GWL_STYLE, borderlessWindowStyle);

    int screenWidth = ::GetSystemMetrics(SM_CXSCREEN);
    int screenHeight = ::GetSystemMetrics(SM_CYSCREEN);

    ::SetWindowPos(windowHandle, HWND_TOP, 0, 0, screenWidth, screenHeight, SWP_FRAMECHANGED);

    isActive = true;
    log(LogLevel::INFO, "Borderless fullscreen enabled");

    return true;
}

bool BorderlessWindow::Disable() {
    if (!isActive) {
        log(LogLevel::WARN, "Borderless mode already disabled");
        return true;
    }

    if (!::IsWindow(windowHandle)) {
        log(LogLevel::ERR, "Window no longer exists");
        isActive = false;
        return false;
    }

    ::SetWindowLongW(windowHandle, GWL_STYLE, windowedStyle);
    ::SetWindowPos(windowHandle, HWND_NOTOPMOST, windowedRect.left, windowedRect.top, windowedRect.right - windowedRect.left, windowedRect.bottom - windowedRect.top, SWP_FRAMECHANGED);

    isActive = false;
    log(LogLevel::INFO, "Borderless fullscreen disabled");

    return true;
}

bool BorderlessWindow::IsActive() const {
    return isActive;
}
