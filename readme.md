See `master` branch for the actual QMK README.

# Quick links
- https://config.qmk.fm/#/boardsource/unicorne/LAYOUT_split_3x6_3

# Development Workflow

https://erovia.github.io/posts/workflow/

## Setup for git workflow
```shell
git remote add myfork git@github.com:mattngu01/qmk_firmware.git
# it may not work using the link's commands, here's what I did to set up the remote fork
git checkout -b personal
git push -u myfork personal

# can probably just create the branch and track personal in the future
git checkout -b personal -t myfork/personal
```

Use the `personal` branch for all changes. 

## Changing keymap

- use [QMK Configurator](https://config.qmk.fm/#/boardsource/unicorne/LAYOUT_split_3x6_3) load & save keymap 
  - https://raw.githubusercontent.com/mattngu01/qmk_firmware/personal/keyboards/boardsource/unicorne/keymaps/mattngu01/keymap.json for import from link
- download & copy paste keymap
- compile (`qmk compile -kb boardsource/unicorne -km mattngu01`)
- `cp boardsource_unicorne_mattngu01.uf2 /mnt/c/Users/Akihiro/Downloads/`