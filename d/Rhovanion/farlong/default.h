#include "/d/Emerald/room/default.h"

#define THIS_DIR        VAMP_DIR

#define GUILD_NAME      "Vampyr guild"
#define GUILD_TYPE      "occupational"
#define GUILD_STYLE     "fighter"
#define GUILD_SHADOW    THIS_DIR + "vamp_sh"
#define VAMP_SHADOW    THIS_DIR + "vamp_sh"
#define VAMP_SOUL       SOUL_DIR + "vamp_soul"
#define VAMP_CLOAK      OBJECT_DIR + "vamp/cloak"
#define VAMP_SKILL_DESC ({"savage", "blast"})

#define SS_SAVAGE   70001

#define F_SAVAGE_HIT(ob, ob2)  ob->query_stat(SS_DEX) * \
                                        ob->query_skill(SS_SAVAGE)

#define F_SAVAGE_PEN(ob, ob2)  F_PENMOD(ob->query_stat(SS_STR), \
                                        2 * ob->query_skill(SS_SAVAGE) / 3) + 35

#define SAVAGE_HIT                1500

#define SS_LUST 132001  /* Emerald is domain#32 */

#ifndef VAMP_DEF
#define VAMP_DEF

#define ADD(xxx,yyy) add_action(xxx,yyy);
#define ADA(xxx)     add_action(xxx,xxx);
#define C(xxx)       capitalize(xxx)
#define P(str, ob)   present(str, ob)
#define E(ob)        environment(ob)
#define L(str)       lower_case(str)

#define M_FILE     "/d/Emerald/npc/humanoids/monster.c";
#define C_FILE     "/d/Emerald/npc/animals/creature.c";
#define OPEN       "/d/Emerald/open/"

#define GUILD          "/d/Emerald/room/vamp/main"
#define VOID           "/d/Emerald/common/void"

#define INSIDE  add_prop(ROOM_I_INSIDE, 1);
#define OUTSIDE add_prop(ROOM_I_INSIDE, 0);
#define DARK    add_prop(ROOM_I_LIGHT,0);
#define LIGHT   add_prop(ROOM_I_LIGHT,1);

#define NEVERKNOWN add_prop(LIVE_I_NEVERKNOWN, 1)
#define ALWAYSKNOWN add_prop(LIVE_I_ALWAYSKNOWN, 1)

#endif
