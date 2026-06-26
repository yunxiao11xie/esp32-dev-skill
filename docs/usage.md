# Usage Guide

## Activating the Skill

In Claude Code, simply type:

```
/esp32-dev
```

The skill will activate and apply the ESP32 development guidelines to all subsequent interactions.

## Available Commands

### `/new-module` — Generate a New Module

Scaffolds a new code module following the layered architecture:

```
/new-module
```

You will be prompted for:
- **Module name** — e.g., `led`, `button`, `display`
- **Layer** — `bsp`, `hal`, or `app`
- **Hardware details** — GPIO pins, peripherals used

The command generates:
- `{module}.h` — header with interface declarations
- `{module}.c` — implementation following the skill's coding standards
- Include guards, proper naming, and documentation comments

### `/code-review` — Review Code

Analyze existing code for compliance with the skill's standards:

```
/code-review <file_or_directory>
```

Checks for:
- Layered architecture violations
- Naming convention compliance
- Memory safety issues
- Error handling completeness
- Real-time constraint violations

### `/debug-help` — Debugging Assistance

Get help diagnosing embedded issues:

```
/debug-help
```

Describe your problem (crash, unexpected behavior, performance issue) and the skill will:
1. Ask for relevant information (logs, configuration, hardware setup)
2. Analyze the root cause
3. Suggest specific fixes

### `/fix-build` — Build Error Resolution

Paste build errors for analysis:

```
/fix-build
```

Paste the full compiler/linker error output, and the skill will:
1. Identify the root cause
2. Explain what went wrong
3. Provide the exact fix

### `/optimize` — Memory & Performance Optimization

Optimize code for embedded constraints:

```
/optimize <file_or_module>
```

Focus areas:
- Reduce RAM usage (static allocation, smaller buffers)
- Minimize flash footprint
- Improve real-time performance
- Reduce power consumption

## Best Practices

1. **Always provide hardware context** — pin numbers, peripheral configuration, board model
2. **Share full error messages** — when debugging, context is everything
3. **Use the BSP → HAL → App flow** — define hardware in BSP, abstract in HAL, use in App
4. **Review generated code** — AI assists, but ultimately hardware testing is your responsibility
