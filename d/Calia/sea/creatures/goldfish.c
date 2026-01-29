
 /*    A fish for the water area

    coder(s):    Amelia

    history:    7.5.95    created          Amelia
               21.7.95    header added     Digit
                8.2.96    stats changed    Jaacar

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
#include "defs.h"

#define A_BITE  0

#define H_HEAD 0
#define H_BODY 1
#define H_TAIL 2
#define H_EYES 3

create_creature()
{
	set_name("fish");
	set_living_name("goldie");
    add_name("goldfish");
	set_race_name("fish");
	set_short("goldfish");
	set_pshort("goldfish");
	set_adj("small");
	add_adj("bright");
    set_alignment(100);
    set_gender(2);
	set_long("This is a small, bright goldfish. It "+
		"is very colorful and darts around "+
		"quickly in the water.\n");

	add_prop(OBJ_I_VOLUME, 10);
	add_prop(OBJ_I_WEIGHT, 10);
    add_prop(LIVE_I_NEVERKNOWN,1);
    add_prop(NPC_I_NO_LOOKS,1);

	set_stats(({30,30,30,3,3,14}));

	set_skill(SS_SWIM, 100);
	set_skill(SS_UNARM_COMBAT, 100);
	set_skill(SS_BLIND_COMBAT, 80);
	set_skill(SS_DEFENCE, 100);

	set_attack_unarmed(A_BITE,15,25,W_SLASH,80,"teeth");
	set_attack_unarmed(1,25,65,W_SLASH, 20,"fin");
	set_hitloc_unarmed(A_HEAD, ({5,5,5,5}), 40, "head");
	set_hitloc_unarmed(H_TAIL, ({5,5,5,10}), 15, "tail");
	set_hitloc_unarmed(H_BODY, ({10,15,15,20}), 35, "body");
	set_hitloc_unarmed(H_EYES, ({10,5,10,5}), 10, "eye");

	set_act_time(35);
	add_act("emote darts around quickly in the water.");
	add_act("emote nibbles on your kneecap.");
	add_act("emote bites you on the toe.");
    set_random_move(10);
    set_restrain_path(({(SECTOR_PATH(0, 0, 1)),(SECTOR_PATH(0, 0, 2)),
        (SECTOR_PATH(0, 0, 3)),(SECTOR_PATH(0, 0, 4)),
        (SECTOR_PATH(0, 10, 1)),(SECTOR_PATH(0, 10, 2)),
        (SECTOR_PATH(0, 10, 3)),(SECTOR_PATH(0, 10, 4)),
        (SECTOR_PATH(10, 0, 1)),(SECTOR_PATH(10, 0, 2)),
        (SECTOR_PATH(10, 0, 3)),(SECTOR_PATH(10, 0, 4)),
        (SECTOR_PATH(10, 10, 1)),(SECTOR_PATH(10, 10, 2)),
        (SECTOR_PATH(10, 10, 3)),(SECTOR_PATH(10, 10, 4)),
        (THAL),(THALL),(THALM),(THALC)}));

	
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
