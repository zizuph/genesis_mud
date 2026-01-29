#define IS_JR(x) (interactive(x) && \
                  wildmatch("*jr", x->query_real_name()))

#define PRO(x)       (x->query_pronoun())

#define CO(x)        (clone_object(x))
#define COTO(x, y)   clone_object(x)->move(y, 1)

#define STR(x) (x->query_stat(SS_STR))
#define DEX(x) (x->query_stat(SS_DEX))
#define CON(x) (x->query_stat(SS_CON))
#define INT(x) (x->query_stat(SS_INT))
#define WIS(x) (x->query_stat(SS_WIS))
#define DIS(x) (x->query_stat(SS_DIS))
