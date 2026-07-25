# 协作规范

本仓库供三名队员共同维护。目标是让每次算法修改都小而清晰，方便在比赛前复核。

## 分支命名

```text
feat/dinic
fix/dijkstra-overflow
refactor/segment-tree
docs/virtual-tree
test/linear-basis
```

每个分支只处理一个明确主题。

## Commit 格式

```text
feat: add Dinic template
fix: prevent overflow in Dijkstra
refactor: simplify segment tree
docs: add virtual tree notes
test: add DSU test
```

推荐类型：`feat`、`fix`、`refactor`、`docs`、`test`、`chore`。

## 模板要求

- 使用统一文件头，说明算法、用途、复杂度、下标、适用条件、验证题、易错点和状态。
- 默认 GNU++17，不引入第三方库。
- 模板尽量自包含、容易复制，不为缩短代码牺牲可读性。
- 明确数组或容器范围，以及多测时需要清空的状态。
- 可能溢出的距离、容量、计数或乘法使用 `long long`，必要时进一步说明范围。
- 图算法说明有向/无向、重边、自环、不连通和负权边行为。

## 合并要求

- 使用独立分支。
- 通过 Pull Request 合并。
- 至少一名队友审核。
- 必须说明复杂度和适用范围。
- 必须能够在 GNU++17 下编译。
- 标记为 `Stable` 前必须有验证题目。
- 不允许在未经讨论的情况下大规模修改公共代码风格。

本地断言、样例或随机对拍应如实记录，但不能写成在线评测 AC。若只完成本地检查，状态保持 `Unverified` 或 `Experimental`。
