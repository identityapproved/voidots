# voidots

Void Linux configs for voidbox. Symlinked into place from `~/builds` and `~/.config`.

## Linked configs

| file in repo | symlinked from |
|---|---|
| `foot/foot.ini` | `~/.config/foot/foot.ini` |
| `offpunk/offpunkrc` | `~/.config/offpunk/offpunkrc` |
| `tmux/tmux.conf` | `~/.config/tmux/tmux.conf` |
| `zsh/zshrc` | `~/.zshrc` |
| `dircolors` | `~/.dircolors` |
| `dwl/config.h` | `~/builds/dwl/config.h` |
| `dwlb/config.h` | `~/builds/dwlb/config.h` |
| `luakit/theme.lua` | `~/.config/luakit/theme.lua` |
| `luakit/userconf.lua` | `~/.config/luakit/userconf.lua` |
| `luakit/search_highlight.lua` | `~/.config/luakit/search_highlight.lua` |
| `luakit/styles/chrome-dark.css` | `~/.local/share/luakit/styles/chrome-dark.css` |

## dwl patches applied

- **centeredmaster** — centered master layout
- **pertag** — per-tag layout/mfact/nmaster state
- **swapandfocusdir** — directional focus (`focusdir`) and swap (`swapdir`) with hjkl
- **vanitygaps** — inner/outer gaps (`setgaps`, `gappih`/`gappoh`/`gappiv`/`gappov`)
- **dwl-ipc-unstable-v2** — IPC protocol for status bars (dwlb integration)

## dwl keybindings (terminal)

| binding | action |
|---|---|
| `MOD+Return` | spawn foot |
| `MOD+Shift+Return` | spawn foot + tmux |
