# K-D Tree 学习笔记

k-D Tree(KDT , k-Dimension Tree) 是一种高效处理$k$维空间信息的数据结构。

KDT的建树过程可以看作一棵二叉搜索树，二叉搜索树上的每个结点都对应$k$维空间内的一个点。其每个子树中的点都在一个 $k$ 维的超长方体内，这个超长方体内的所有点也都在这个子树中。

假设我们已经确定了空间中所有点的坐标，那么我们的建树过程可以看作：

1. 若当前超长方体中只有一个点，返回这个点。
2. 选择一个维度，将当前超长方体按照这个维度分成两个超长方体。
3. 选择切割点：在选择的维度上选择一个点，这一维度上的值小于这个点的归入一个超长方体（左子树），其余的归入另一个超长方体（右子树）。
4. 将选择的点作为这棵子树的根节点，递归对分出的两个超长方体构建左右子树，维护子树的信息。

引用https://oi-wiki.org/ds/kdt/ 中的例子：

当$k=2$时

![img](https://oi-wiki.org/ds/images/kdt1.jpg)

其构建出 k-D Tree 的形态可能是这样的：

![img](https://oi-wiki.org/ds/images/kdt2.jpg)

其中树上每个结点上的坐标是选择的分割点的坐标，非叶子结点旁的$x$或$y$是选择的切割维度。