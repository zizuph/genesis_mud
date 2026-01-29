inherit "/std/monster";
inherit "/std/combat/unarmed";   /* This gets us standard unarmed routines */

inherit "/std/act/domove";
inherit "/std/act/action";

#include <wa_types.h>
#include <ss_types.h>
#include <macros.h>
#include <filter_funs.h>
#include "/sys/money.h"
#include "/sys/stdproperties.h"

#include "defs.h"

#define A_STINGER 0

#define H_HEAD 0
#define H_BODY 1

void
create_monster()
{
    set_name("bee");
    set_adj(({"golden", "honey"}));
    set_living_name("_bee_");
    set_short("golden honey bee");
    set_long("A small golden honey bee, which feeds on clover "+
      "flowers.\n");

    /* str, con, dex, int, wis, dis
    */
    set_stats(({5, 5, 5, 5, 5, 5}));

    set_attack_unarmed(A_STINGER, 10, 20, W_IMPALE, 30, "stinger");
    set_hp(query_max_hp());

    add_prop(LIVE_I_NEVERKNOWN, 1);

    set_skill(SS_UNARM_COMBAT, 5);
    set_skill(SS_DEFENCE, 5);

    set_hitloc_unarmed(H_HEAD, ({ 15, 25, 20, 20 }), 20, "head");
    set_hitloc_unarmed(H_BODY, ({ 10, 15, 30, 20 }), 80, "body");

    set_act_time(80);
}
