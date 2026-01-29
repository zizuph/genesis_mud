
 /*    A sea warhorse for the water area

    coder(s):    Jaacar

 */
inherit "/d/Calia/std/sea_creature";
inherit "/std/combat/unarmed";
inherit "/std/act/domove";
inherit "/std/act/action";
inherit "/std/act/attack";

#include <wa_types.h>
#include <ss_types.h>
#include <macros.h>
#include <filter_funs.h>
#include <stdproperties.h>
#include <formulas.h>
#include "defs.h"

object tp = this_player();

#define A_HOOF 0
#define A_TAIL 1
#define A_BITE 2

#define H_HEAD 0
#define H_BODY 1
#define H_HOOF 2
#define H_TAIL 3
#define H_LEG  4

create_creature()
{
    set_name("trigger");
    add_name("horse");
    set_short("large war-seahorse");
    set_adj("large");
    set_race_name("seahorse");
    set_long("This appears to be much like its land wandering "+
        "ancestor except it has no hind legs. Rather it has "+
        "a large fish-like tail to propel itself around. It "+
        "still has front hoofs like it's land cousin but they "+
        "appear to be used more for battle than for moving around.\n");

    add_prop(LIVE_I_NEVERKNOWN, 1);
    add_prop(NPC_I_NO_LOOKS, 1);
    set_alignment(100);
    set_gender(2);
    set_random_move(15);
    set_restrain_path(({(SECTOR_PATH(0, 0, 1)),(SECTOR_PATH(0, 0, 2)),
        (SECTOR_PATH(0, 0, 3)),(SECTOR_PATH(0, 0, 4)),
        (SECTOR_PATH(0, 10, 1)),(SECTOR_PATH(0, 10, 2)),
        (SECTOR_PATH(0, 10, 3)),(SECTOR_PATH(0, 10, 4)),
        (SECTOR_PATH(10, 10, 1)),(SECTOR_PATH(10, 10, 2)),
        (SECTOR_PATH(10, 10, 3)),(SECTOR_PATH(10, 10, 4)),
        (SECTOR_PATH(10, 0, 1)),(SECTOR_PATH(10, 0, 2)),
        (SECTOR_PATH(10, 0, 3)),(SECTOR_PATH(10, 0, 4))}));
    set_stats(({80,70,65,50,35,70}));

	set_skill(SS_SWIM, 100);
	set_skill(SS_UNARM_COMBAT, 100);
	set_skill(SS_BLIND_COMBAT, 80);
	set_skill(SS_DEFENCE, 100);

    set_attack_unarmed(A_HOOF,15,25,W_BLUDGEON,80,"hoof");
    set_attack_unarmed(A_TAIL,10,20,W_SLASH,10,"tail");
    set_attack_unarmed(A_BITE,10,20,W_IMPALE,10,"bite");

    set_hitloc_unarmed(H_HEAD, ({5,5,5,5}), 5, "head");
    set_hitloc_unarmed(H_LEG,({5,5,5,10}), 5, "leg");
    set_hitloc_unarmed(H_HOOF,({5,5,5,10}), 10, "hoof");
    set_hitloc_unarmed(H_TAIL,({5,5,5,10}), 10, "tail");
    set_hitloc_unarmed(H_BODY,({5,5,5,10}), 75, "body");

}

/*
 * Function name: tell_watcher
 * Description:   Send the string from the fight to people that want them
 * Arguments:     The string to send
 */
static void
tell_watcher(string str, object enemy)
{
    object me,*ob;
    int i;

    me = this_object();
    ob = FILTER_LIVE(all_inventory(environment(me))) - ({ me });
    ob -= ({ enemy });
    for (i = 0; i < sizeof(ob); i++)
        if (ob[i]->query_see_blood())
            ob[i]->catch_msg(str);
}
