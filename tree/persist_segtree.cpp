#include <stdio.h>

struct NODE{
    NODE(): v(0), left(0), right(0) {}
    int v;
    NODE *left, *right;
};

struct SegmentTree {
private:
    static const int MAXN = 100010;
    int ysize; NODE *tree[MAXN];
    NODE *make_tree(NODE *now, int s, int e, int y, int v)
    {
        if (y < s || e < y) return now;
        NODE *ret = new NODE();
        if (s == e){
            if (now) ret->v = now->v + v;
            else ret->v = v;
            return ret;
        }
        int m = (s+e) >> 1;
        ret->left = make_tree(now ? now->left : 0, s, m, y, v);
        ret->right = make_tree(now ? now->right : 0, m+1, e, y, v);
        ret->v = 0;
        if (ret->left) ret->v += ret->left->v;
        if (ret->right) ret->v += ret->right->v;
        return ret;
    }
    int get(NODE *node, int s, int e, int target_s, int target_e) {
        if (node == NULL) return 0;
        if (target_e < s || target_s > e) return 0;
        if (target_s <= s && e <= target_e) {
            return node->v;
        }
        int m = (s + e) >> 1;
        return get(node->left, s, m, target_s, target_e) + get(node->right, m+1, e, target_s, target_e);
    }
public:
    // x좌표가 증가하는 순으로 순차적으로 불러야함, 1 ~ N
    SegmentTree(int ysize) {
        this->ysize = ysize;
        this->tree[0] = new NODE();
    }
    void update(int x,int y,int v) {
        tree[x] = make_tree(tree[x-1], 1, ysize, y, v);
    }
    int get(int x1,int x2,int y1,int y2) {
        return get(tree[x2],1,ysize,y1,y2) - get(tree[x1-1],1,ysize,y1,y2);
    }
};
