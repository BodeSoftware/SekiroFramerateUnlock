# Sekiro FPS Unlock Mod

Unlock the framerate in Sekiro: Shadows Die Twice and play at higher refresh rates!

## 📋 What This Does

This mod removes the 60 FPS cap from Sekiro, allowing you to play at higher framerates like 120, 144, or even 240 FPS. Perfect for high refresh rate monitors!
This mod sets the game to borderless windowed mode.

## ⚙️ Installation

1. **Download** the mod files:
   - `d3dcompiler_43.dll` (the mod file)
   - `SekiroFPS.ini` (configuration file)

2. **Locate your Sekiro game folder**:
   - Right-click Sekiro in Steam → Manage → Browse local files
   - Default location: `C:\Program Files (x86)\Steam\steamapps\common\Sekiro`

3. **Copy both files** into the Sekiro folder (where `sekiro.exe` is located)

4. **Done!** Launch the game normally through Steam

## 🎮 Configuration

Edit `SekiroFPS.ini` with Notepad to change your target framerate:

```ini
[Settings]
; Target framerate (valid range: 30-300)
TargetFPS=144
```

### How to Save the INI Correctly:
1. Open `SekiroFPS.ini` 
2. Change the `TargetFPS` value
3. Save

### Mod Not Working?
- Verify both files are in the correct folder (same folder as `sekiro.exe`)
- Make sure the INI file is actually `.ini` and not `.txt`
- Try deleting the INI file and let the mod create a new one automatically
- Restart the game after making changes

### Game Crashes or Glitches?
- Lower your target FPS (try 120 instead of 240)
- Some effects/physics may glitch at very high framerates
- This is normal for FromSoftware games at high FPS

### Still Using 60 FPS?
- The mod only works if `d3dcompiler_43.dll` is in the game folder
- Check that the INI file is being read (it should be in the same folder)
- Try setting a very obvious value like `TargetFPS=30` to test if it's working

## 🗑️ Uninstalling

Simply delete these two files from your Sekiro folder:
- `d3dcompiler_43.dll`
- `SekiroFPS.ini`

The game will return to normal 60 FPS.
