# Ember

A lightweight companion app for Dark Souls 3 that tracks your stats in real-time and displays them on Discord.

## Features

- **Real-time stats tracking** - Deaths, playtime, current zone, character info
- **Discord Rich Presence** - Show your progress to friends
- **Session history** - Track your gaming sessions with detailed statistics
- **HTTP API** - Access your stats programmatically via REST endpoints
- **SSE streaming** - Real-time stats updates via Server-Sent Events
- **Borderless fullscreen** - Force DS3 into borderless windowed mode
- **Auto-start** - Launch automatically with Windows

## API Endpoints

| Endpoint | Method | Description |
|----------|--------|-------------|
| `/health` | GET | Health check with uptime |
| `/api/stats` | GET | Current deaths and playtime |
| `/api/stats/stream` | GET | SSE stream of real-time stats |
| `/api/sessions` | GET | All recorded gaming sessions |
| `/api/settings` | GET | Current settings |
| `/api/settings` | PATCH | Update settings |

## Settings

| Setting | Description |
|---------|-------------|
| `isDeathCountVisible` | Show death count in Discord presence |
| `isPlaytimeVisible` | Show playtime in Discord presence |
| `isDiscordRpcEnabled` | Enable Discord Rich Presence |
| `isBorderlessFullscreenEnabled` | Force borderless fullscreen mode |
| `isAutoStartEnabled` | Start with Windows |

## Building

```bash
# Open Ember.vcxproj in Visual Studio 2022+ and build (Release x64)
```

## Usage

1. Launch `Ember.exe`
2. Start Dark Souls 3
3. Your stats will automatically appear in Discord

The API server runs on `http://localhost:3000` by default.
