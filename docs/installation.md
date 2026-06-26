# Installation Guide

## Prerequisites

- [Claude Code](https://claude.ai/code) installed
- Git installed

## Method 1: Clone & Copy (Recommended)

```bash
# Clone the repository anywhere
git clone https://github.com/yunxiao11xie/esp32-dev-skill.git

# Create the skills directory
mkdir -p ~/.claude/skills

# Copy the entire skill directory
cp -r esp32-dev-skill ~/.claude/skills/esp32-dev

# Verify it's installed
ls ~/.claude/skills/esp32-dev/SKILL.md   # Should exist
```

## Method 2: Symbolic Link (for keeping it up-to-date)

```bash
git clone https://github.com/yunxiao11xie/esp32-dev-skill.git
mkdir -p ~/.claude/skills

# macOS / Linux
ln -s "$(pwd)/esp32-dev-skill" ~/.claude/skills/esp32-dev

# Windows PowerShell (Admin)
# New-Item -ItemType SymbolicLink -Path "$env:USERPROFILE\.claude\skills\esp32-dev" -Target "$pwd\esp32-dev-skill"
```

## Method 3: Manual Download

1. Download the [latest release ZIP](https://github.com/yunxiao11xie/esp32-dev-skill/releases)
2. Extract it to `~/.claude/skills/esp32-dev/`
3. Ensure `SKILL.md` is at the root of the extracted folder

## Verification

After installation, start Claude Code and type:

```
/esp32-dev
```

If the skill loads without errors, you're all set.

## Updating

```bash
cd esp32-dev-skill
git pull
# If you used symlink (Method 2), you're done
# If you used copy (Method 1), re-run the copy step
cp -r esp32-dev-skill ~/.claude/skills/esp32-dev
```
