/*
 *  Coded by Amelia, October 1997.
*/
inherit "/std/monster";
inherit "/std/combat/unarmed";

inherit "/std/act/domove";
inherit "/std/act/action";

#include <wa_types.h>
#include <ss_types.h>
#include <macros.h>
#include <filter_funs.h>

#include "defs.h"

#define A_FOOT 0
#define A_TEETH 1
#define A_TAIL 2

#define H_HEAD 0
#define H_BODY 1

void
create_monster()
{
    set_name("rat");
    set_race_name("rat");
    set_short("dirty grey rat");
    set_adj(({"dirty", "grey"}));
    set_gender(G_MALE);
    set_long("A sneaky ship rat, perhaps the captain's pet.\n");

    /* str, con, dex, int, wis, dis
    */
    set_stats(({50, 35, 100, 5, 5, 75}));

    set_hp(query_max_hp());

    set_skill(SS_DEFENCE, 80);
    set_skill(SS_UNARM_COMBAT, 50);
    set_skill(SS_HIDE, 75);
    set_skill(SS_AWARENESS, 90);

    set_attack_unarmed(A_TEETH, 10, 20, W_IMPALE, 33, "sharp teeth");
    set_attack_unarmed(A_TAIL, 10, 20, W_BLUDGEON, 33,
      "whiplike tail");
    set_attack_unarmed(A_FOOT, 10, 20, W_BLUDGEON, 33, 
      "sharp-clawed paw");
    set_hitloc_unarmed(H_HEAD, ({ 15, 25, 20, 20 }), 20, "head");
    set_hitloc_unarmed(H_BODY, ({ 10, 15, 30, 20 }), 80, "body");

    set_act_time(80);
    add_act("emote nibbles on a bit of cheese.");
    add_act("hide");
}
