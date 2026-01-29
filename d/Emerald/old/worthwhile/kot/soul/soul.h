#ifndef KOT_SOUL_DEFS
#define KOT_SOUL_DEFS

#define POS(x) x->query_possessive()
#define OBJ(x) x->query_objective()
#define PRO(x) x->query_pronoun()

#define POSTP POS(this_player())
#define OBJTP OBJ(this_player())
#define PROTP PRO(this_player())

#define HIS_OR_THEIR(arr) ((sizeof(arr) > 1) ? "their" : POS(arr[0]))
#define HIM_OR_THEM(arr)  ((sizeof(arr) > 1) ? "them"  : OBJ(arr[0]))

#define POSTP POS(this_player())
#define OBJTP OBJ(this_player())
#define PROTP PRO(this_player())

#define HIS_OR_THEIR(arr) ((sizeof(arr) > 1) ? "their" : POS(arr[0]))
#define HIM_OR_THEM(arr)  ((sizeof(arr) > 1) ? "them"  : OBJ(arr[0]))

#endif
