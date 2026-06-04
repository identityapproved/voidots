# voidots

Void Linux configs for voidbox. Symlinked into place from `~/builds` and `~/.config`.

## Linked configs

| file in repo | symlinked from |
|---|---|
| `alacritty/alacritty.toml` | `~/.config/alacritty/alacritty.toml` |
| `tmux/tmux.conf` | `~/.config/tmux/tmux.conf` |
| `dircolors` | `~/.dircolors` |
| `dwl/config.h` | `~/builds/dwl/config.h` |
| `dwlb/config.h` | `~/builds/dwlb/config.h` |

## dwl patches applied

- **centeredmaster** — centered master layout
- **pertag** — per-tag layout/mfact/nmaster state
- **swapandfocusdir** — directional focus (`focusdir`) and swap (`swapdir`) with hjkl
- **vanitygaps** — inner/outer gaps (`setgaps`, `gappih`/`gappoh`/`gappiv`/`gappov`)
- **dwl-ipc-unstable-v2** — IPC protocol for status bars (dwlb integration)

## dwl keybindings (terminal)

| binding | action |
|---|---|
| `MOD+Return` | spawn alacritty |
| `MOD+Shift+Return` | spawn alacritty + tmux |
