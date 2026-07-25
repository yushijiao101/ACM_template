# ACM-Template

面向三人 ACM/ICPC 队伍共同维护的 GNU++17 算法竞赛模板仓库。项目强调模板可单独阅读和复制、边界与适用条件明确、改动可审核，并为后续生成区域赛纸质板子保留清晰结构。

旧资料仍保留在原目录，并备份到 `legacy/original_sources/`。新代码只逐步迁移到 `template/`，不会假定旧实现正确。

## 编译环境

- 语言标准：GNU++17
- 推荐检查：`g++ -std=c++17 -Wall -Wextra`
- 不使用第三方 C++ 库或复杂构建系统

## 目录结构

```text
.
├─ legacy/                  # 原始模板归档，不直接作为正式板子
├─ template/
│  ├─ base/                # 基础工具与约定
│  ├─ data_structure/      # 数据结构
│  ├─ graph/               # 图论
│  ├─ string/              # 字符串
│  ├─ math/                # 数学与数论
│  ├─ tree/                # 树上算法
│  └─ geometry/            # 计算几何
├─ tests/                  # 独立测试与编译脚本
├─ docs/                   # 团队约定与常见错误
└─ .github/                # Issue 与 Pull Request 模板
```

## 使用约定

- 默认使用 `long long` 处理可能溢出的整数。
- 图和树默认使用 1-indexed；每个模板仍必须单独注明下标约定。
- 每个模板应可单独阅读和复制，非必要不依赖仓库内其他文件。
- 必须注明复杂度、适用条件、数组范围、多测清空要求和特殊边行为。
- 每个模板至少经过一道题验证后，才可标记为 `Stable`。
- 未验证模板不可加入正式打印版。
- `main` 分支只保留经过审核的版本。

## 模板状态

- `Stable`：至少有一道明确验证题，且已由队友复核。
- `Experimental`：实现基本完整，但仍可能调整接口或适用范围。
- `Unverified`：尚无可靠题目验证记录；本地编译或断言测试不等同于在线评测通过。

当前首批整理模板均为 `Unverified`。测试结果只说明本地样例或随机检查通过，不代表在线评测 AC。

## 新增模板流程

1. 从 `main` 创建独立分支。
2. 在正确分类下新增一个自包含模板，并填写统一文件头。
3. 在 `tests/` 添加最小测试；适合时补充随机对拍。
4. 运行 `python tests/compile_all.py`。
5. 提交 Pull Request，说明复杂度、适用条件、验证题和风险。
6. 至少一名队友审核后合并；有可靠验证题后才能改为 `Stable`。

## Git 分支和 Pull Request 流程

- 分支示例：`feat/dinic`、`fix/dijkstra-overflow`、`refactor/segment-tree`。
- 每项修改使用独立分支，不直接向 `main` 提交日常改动。
- 通过 Pull Request 合并，至少一名队友审核。
- 不在未经讨论时大规模统一公共代码风格。
- 合并前处理审查意见，并再次运行编译检查。

详细规则见 [CONTRIBUTING.md](CONTRIBUTING.md)。

旧代码的算法清单与已发现风险见 [docs/legacy_inventory.md](docs/legacy_inventory.md)。

## 比赛前检查建议

- 只打印 `Stable` 模板，并核对打印版本对应的 Git 提交。
- 用比赛机的 GNU++17 编译器执行一次完整编译检查。
- 检查常量范围、递归深度、整数溢出、下标和多测清空。
- 核对图是否有向、是否允许负边、重边、自环和不连通情况。
- 确认模数、输入格式、输出格式和题目要求完全一致。
- 三名队员各自抽查常用模板能否快速定位和修改。

## 当前待办事项

- [ ] 为首批模板补充在线评测验证题，再评估是否标记 `Stable`
- [ ] 整理 `common_constants`、坐标离散化和二分笔记
- [ ] 整理线段树、稀疏表、拓扑排序、二分图判定、SCC 与 Dinic
- [ ] 整理 LCA、虚树、Trie、AC 自动机
- [ ] 整理线性筛、扩展欧几里得、线性基与 BSGS
- [ ] 修复并迁移现有 PDF 生成脚本，改为读取 `template/` 和模板状态
- [ ] 设计只包含 `Stable` 模板的区域赛打印流程

## GitHub 初始化后的网页设置

创建空仓库并推送后，在 GitHub 网页端邀请两名队友为 collaborators。为 `main` 设置分支保护：要求 Pull Request、至少一名成员审核、禁止 force push、禁止删除 `main`。仓库地址、GitHub 用户名和队友账号由团队自行填写。
