<div align="center">

# ESP32 Dev Skill 🎯

**An ESP32/ESP-IDF Development Specification & Claude Code Skill**

[![MIT License](https://img.shields.io/badge/license-MIT-green.svg)](./LICENSE)
[![ESP-IDF](https://img.shields.io/badge/ESP--IDF-v5.x-blue)](https://github.com/espressif/esp-idf)
[![PRs Welcome](https://img.shields.io/badge/PRs-welcome-brightgreen.svg)](https://github.com/yunxiao11xie/esp32-dev-skill/pulls)

*中文 | [English](./README.md)*

</div>

---

## 📖 项目简介

**ESP32 Dev Skill** 是一份面向 **ESP32 / ESP-IDF 嵌入式开发** 的规范指南，同时也是一个 **Claude Code 开发技能包**。

它定义了一整套开发规范：从分层架构设计、代码命名规范、错误处理到实时性保障，帮助开发者和 AI 辅助编程工具产出高质量、可维护的嵌入式固件。

### 适用对象

- 🧑‍💻 **嵌入式开发者** — 作为开发规范参考文档
- 🤖 **Claude Code 用户** — 作为 AI 编程技能包，提升代码质量
- 📚 **ESP32 入门学习者** — 学习规范的嵌入式开发实践

---

## ✨ 特色

| 特性 | 说明 |
|------|------|
| 🏗 **分层架构** | BSP→HAL→应用层严格分离，禁止跨层调用 |
| 📐 **统一规范** | 命名、文件结构、错误处理全统一 |
| 🚫 **红线检查** | 架构/内存/实时性/安全四条红线 |
| 📦 **静态内存** | 资源受限设备的正确姿势 |
| 🔌 **事件驱动** | FreeRTOS 队列/信号量/事件组 |
| 🛠 **模块化** | 一键生成符合规范的代码模块 |

---

## 🚀 快速使用

### 作为 Claude Code 技能使用

```bash
# 克隆仓库
git clone https://github.com/yunxiao11xie/esp32-dev-skill.git

# 复制到 Claude 技能目录
mkdir -p ~/.claude/skills
cp -r esp32-dev-skill ~/.claude/skills/esp32-dev

# 在 Claude Code 中激活：
# /esp32-dev
```

激活后可用命令：

| 命令 | 功能 |
|------|------|
| `/esp32-dev` | 激活 ESP32 开发技能 |
| `/new-module` | 生成新模块（BSP/HAL/应用层） |
| `/code-review` | 按规范审查代码 |
| `/debug-help` | 调试辅助 |
| `/fix-build` | 编译错误排查 |
| `/optimize` | 内存/性能优化 |

### 作为开发规范文档

直接阅读 [`SKILL.md`](./SKILL.md) 即可获取完整的开发规范。

---

## 📂 仓库结构

```
esp32-dev-skill/
├── SKILL.md              # 核心开发规范（同时是 Claude Code skill 定义）
├── README.md             # 本文件
├── LICENSE               # MIT 开源协议
├── docs/
│   ├── installation.md   # 详细安装指南
│   └── usage.md          # 使用说明
├── templates/            # 代码模板
│   ├── bsp_template.h/c  # BSP 层模板
│   ├── hal_template.h/c  # HAL 层模板
│   └── app_template.h/c  # 应用层模板
└── assets/
    └── images/           # 图片资源
```

---

## 🔧 配套资源

本技能与 [awesome-esp32-s31](https://github.com/yunxiao11xie/awesome-esp32-s31) 项目配合使用效果最佳：
- 实战项目代码示例
- ESP32-S3 开发板入门教程
- LVGL 图形界面开发示例

---

## 🤝 参与贡献

欢迎提交 PR 和 Issue！请确保：

1. Fork 本仓库
2. 新建特性分支 (`git checkout -b feature/amazing-feature`)
3. 提交改动 (`git commit -m 'Add amazing feature'`)
4. 推送分支 (`git push origin feature/amazing-feature`)
5. 提交 Pull Request

---

## 📄 开源协议

本项目基于 MIT License 开源 — 详见 [LICENSE](./LICENSE)

---

## ⭐ 支持项目

如果这个项目对你有帮助，请给一个 ⭐！

---

<div align="center">
Built with ❤️ for the ESP32 community
</div>
