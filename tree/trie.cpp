struct trie {
    char c; int sz, leaf;
    trie *next[33];
}*root;

trie* NEW(char c) {
    trie *re = (trie*) malloc(sizeof(trie));
    re->c = c; re->sz = 1; re->leaf = 0;
    for(int i='a'-'a'+1;i<='z'-'a'+1;i++) re->next[i] = NULL;
    return re;
}

void make_trie(trie *node,int it, int len) {
    char c = word[it];
    
    if(it == len+1) {
        node->leaf = 1;
        return ;
    }
    if ('A' <= c && c <= 'Z') c = c - 'A' + 'a';
    if(node->next[c-'a'+1] == NULL) node->next[c-'a'+1] = NEW(c);
    
    
    make_trie(node->next[c-'a'+1],it+1,len);
}

void dfs(trie *node, int it, int tar) {
    if(it < 0) return;
    char c = sen[it];
    
    if (node->leaf && dp[it]) {
        dp[tar] = 1;
        via[tar] = it;
        return ;
    }
    
    if (node->next[c-'a'+1] == NULL) return ;
    dfs(node->next[c-'a'+1], it-1, tar);
}
