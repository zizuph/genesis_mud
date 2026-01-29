
/*
     The defaults header file for the Zintra BlackHand Order of Assassins.

        => Will be updating this file. <=        ~Rico 12.04.96
*/

#include "/d/Kalad/defs.h"

#define ZINTRA_NAME    "Zintra guild"
#define ZINTRA_TYPE    "occupational"
#define ZINTRA_STYLE   "fighter"
#define ZINTRA_TAX     20
#define ZINTRA_SHADOW  "/d/Kalad/common/zintra/specials/zintra_shadow"

#define SS_KICK     35101
#define SS_THRUST   35102

#define F_KICK_HIT(ob, ob2)    ob->query_stat(SS_DEX) * \
/* add in unarmed skill for kick */  ob->query_skill(SS_KICK)

#define F_KICK_PEN(ob, ob2)    F_PENMOD(2 * ob->query_stat(SS_STR) / 3, \
                                  2 * ob->query_skill(SS_KICK) / 3) + 35

#define F_THRUST_HIT(ob, ob2)  (((ob->query_stat(SS_DEX) + \
                   ob->query_stat(SS_STR)) / 2) * ob->query_skill(SS_THRUST))

#define F_THRUST_PEN(ob, ob2)  F_PENMOD(2 * ob->query_stat(SS_DEX) / 3, \
                                  2 * ob->query_skill(SS_THRUST) / 3) + 35

#define THRUST_HIT    12000
#define THRUST_KNOCK  6500

#define KICK_HIT      1500

#define ADD(xxx,yyy)  add_action(xxx,yyy);
#define ADA(xxx)      add_action(xxx,xxx);
#define C(xxx)        capitalize(xxx)
#define P(str, ob)    present(str, ob)
#define E(ob)         environment(ob)
#define L(str)        lower_case(str)

#define NEVERKNOWN    add_prop(LIVE_I_NEVERKNOWN, 1)
#define ALWAYSKNOWN   add_prop(LIVE_I_ALWAYSKNOWN, 1)

#define THIS_DIR      "/d/Kalad/common/zintra/"
#define ROOMS_DIR     THIS_DIR + "rooms/"
#define THIS          this_object()

