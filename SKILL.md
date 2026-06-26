---
name: esp32-dev
description: "ESP32/ESP-IDF Development Skill - Layered architecture, coding standards, module generation, debug assistance. BSP→HAL→Application layers, event-driven design, static memory allocation, no-compile rule. Commands: /new-module, /code-review, /debug-help, /fix-build, /optimize"
triggers:
  - esp32
  - esp-idf
  - embedded
  - microcontroller
  - firmware
  - freertos
  - hal
  - bsp
---

# ESP32 / ESP-IDF Development Guide

> A comprehensive development specification for ESP32/ESP-IDF firmware engineering.

---

## Architecture: Layered Design

All code MUST follow the layered architecture. Cross-layer calls are strictly prohibited:

```
Application Layer (app_*)
    ↑
Business Logic
    ↑
HAL — Hardware Abstraction Layer (hal_*)
    ↑
BSP — Board Support Package (bsp_*)
    ↑
ESP-IDF Driver Framework
    ↑
Hardware
```

### Layer Responsibilities

| Layer | What goes here | Rules |
|-------|---------------|-------|
| **BSP** | Pin definitions, peripheral config macros, board-specific constants | Pure hardware description — macros and defines only, NO logic |
| **HAL** | Hardware operation wrappers, unified interfaces | Abstract hardware details, hide implementation, provide clean API |
| **Application** | Business logic, tasks, state machines | Never call ESP-IDF directly — go through HAL only |

---

## Event-Driven Design

- Use FreeRTOS queues, semaphores, and event groups for inter-task communication
- Global variables for data passing between tasks is **forbidden**
- Prefer non-blocking design; avoid `vTaskDelay` busy-waiting

---

## Resource Constraints

ESP32 MCUs have limited resources (SRAM: a few hundred KB, Flash: a few MB). Every byte counts:

- **Static allocation first** — avoid arbitrary `malloc`/`free`
- **Stack sizing** — estimate precisely; leave headroom to prevent overflow
- **Peripheral conflicts** — always verify pin multiplexing
- Arrays over 256 bytes on the stack → consider static or heap allocation instead

---

## Coding Standards

### Naming Conventions

| Type | Rule | Example |
|------|------|---------|
| Functions | snake_case, module prefix | `hal_led_set_brightness()` |
| Variables | snake_case | `current_brightness` |
| Macros | UPPER_SNAKE_CASE, module prefix | `BSP_LED_GPIO_NUM` |
| Type definitions | snake_case, `_t` suffix | `led_mode_t` |
| Enum values | UPPER_SNAKE_CASE, module prefix | `LED_MODE_BREATH` |
| Globals | `g_` prefix, minimize usage | `g_led_state` |
| Statics | `s_` prefix | `s_is_initialized` |

### File Structure

- Header files MUST have `#ifndef` include guards
- One `.c` + `.h` pair per module
- `.h` files expose only the public interface — keep internals private
- Every function MUST have a comment describing its purpose, parameters, and return value

### Error Handling

- All fallible functions MUST return `esp_err_t`
- Return values MUST be checked — never ignore
- Fatal errors → `ESP_ERROR_CHECK()`
- Use `ESP_LOGx` for logging; each module has its own TAG

---

## Development Workflow

### Adding a New Module

1. **Requirements** — clarify hardware resources, functionality, interface contracts, and constraints
2. **Interface design** — write the `.h` file first: define public functions and data structures
3. **Implementation** — write the `.c` file following the layered architecture
4. **Build verification** — zero errors, zero warnings (compile locally)
5. **Hardware test** — validate on real hardware
6. **Code review** — check standards, memory safety, and performance

### Debugging Workflow

1. **Reproduce** — establish reliable reproduction steps
2. **Gather** — serial logs, observable behavior, test results
3. **Locate** — trace from symptom to root cause using binary search
4. **Fix & verify** — apply the fix and confirm on hardware
5. **Regression** — ensure the fix introduces no new issues

---

## Red Lines (DO NOT VIOLATE)

### ❌ Architecture

- Application layer MUST NOT call ESP-IDF driver functions directly (must go through HAL)
- Modules MUST NOT call each other's internal functions
- Cross-layer modification of another module's internal state is forbidden

### ❌ Memory

- No dynamic allocation inside loops
- No large arrays on the stack (>256 bytes → static or heap)
- No memory leaks (every `malloc` must have a matching `free`)
- No stack overflow (leave headroom on task stack sizes)

### ❌ Real-Time

- No complex operations inside interrupts
- No long interrupt disabling
- No high-priority task spinning at 100% CPU
- No blocking waits exceeding the expected time

### ❌ Safety

- No array out-of-bounds access
- No NULL pointer dereferencing
- Never proceed without checking return values
- Never write hardware registers blindly — consult the datasheet

---

## Best Practices

### Peripheral Drivers

- Check if already initialized before initializing (guard against double init)
- Use static allocation for driver resources
- Keep ISRs short — flags only, logic goes in tasks

### FreeRTOS

- Prioritize tasks sensibly — don't set everything to the highest priority
- Estimate queue lengths based on real-world data rates
- Use semaphores for synchronization, queues for data transfer
- Configure the watchdog timer to prevent lockups

### Low Power

- Disable clocks on unused peripherals
- Enter Light Sleep when idle
- Enter Deep Sleep for extended inactivity
- Configure wake-up sources reliably

### Debugging

- Use `ESP_LOG` levels appropriately (ERROR, WARN, INFO, DEBUG, VERBOSE)
- Add timestamps on critical paths for performance measurement
- Periodically log memory usage to catch leaks
- When a crash occurs, analyze the backtrace to locate the fault

---

## Installation (Claude Code)

To use this skill with Claude Code, add it to your Claude configuration:

```bash
# Clone the skill repository
git clone https://github.com/yunxiao11xie/esp32-dev-skill.git

# Create the skills directory if it doesn't exist
mkdir -p ~/.claude/skills

# Symlink or copy the skill
ln -s "$(pwd)/esp32-dev-skill" ~/.claude/skills/esp32-dev

# On Windows (PowerShell):
# New-Item -ItemType SymbolicLink -Path "$env:USERPROFILE\.claude\skills\esp32-dev" -Target "$pwd\esp32-dev-skill"
```

Then in Claude Code, use:
- `/esp32-dev` — activate the skill
- `/new-module` — scaffold a new module following the layered architecture
- `/code-review` — review code against these standards
- `/debug-help` — get debugging assistance
- `/fix-build` — help fix build errors
- `/optimize` — optimize for memory or performance

---

## Key Reminders

1. **Never assume hardware** — all pinouts and parameters must come from the BSP header or user-provided docs
2. **Don't over-engineer** — MCU resources are limited; keep it simple and functional
3. **Never ignore errors** — embedded code must be robust; handle every failure path
4. **Always verify** — AI-generated code must be compiled, flashed, and tested on real hardware
5. **If unsure, ask** — never guess hardware details; confirm with the user

Remember: **In embedded development, reliability is everything.** Code that crashes on hardware is useless, no matter how clean it looks.
