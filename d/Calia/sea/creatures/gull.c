
 /*    A gull for the beach/water area

    coder(s):    Amelia

    history:    18.5.95    created          Amelia
                21.7.95    header added     Digit

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


#define H_HEAD 1
#define H_EYES 2
#define H_TAIL 3
#define H_BODY 4

create_creature()
{
	set_name("seagull");
	set_living_name("jonathan");
	set_race_name("seagull");
	set_short("seagull");
	set_pshort("seagulls");
    add_name("gull");
    add_pname("gulls");
	set_adj("white");
	
    set_long("It is a white seagull flying far above you. "+
        "It is a fairly large bird, about the size of a large "+
        "crow and looks relatively intelligent as it searches "+
        "the waters around you for food to eat.\n");

	add_prop(OBJ_I_VOLUME, 250);
	add_prop(OBJ_I_WEIGHT, 250);

	set_stats(({30,30,30,3,3,14}));

    set_skill(SS_SWIM, 50);
	set_skill(SS_UNARM_COMBAT, 50);
	set_skill(SS_BLIND_COMBAT, 50);
	set_skill(SS_DEFENCE, 50);

	set_hp(10+random(35));

	set_attack_unarmed(0, 15,25,W_SLASH, 80, "beak");
	set_attack_unarmed(1,15,25,W_BLUDGEON,20,"wings");
    set_hitloc_unarmed(H_HEAD, ({5,5,5,5}), 40, "head");
    set_hitloc_unarmed(H_BODY, ({5,5,5,5}), 35, "body");
    set_hitloc_unarmed(H_TAIL, ({5,5,5,10}), 15, "tail");
    set_hitloc_unarmed(H_EYES, ({10,5,10,5}), 10, "eye");

    set_random_move(10);
    set_restrain_path(({SECTOR_PATH(0, 0, 0),SECTOR_PATH(0, 10, 0),
        SECTOR_PATH(10, 0, 0), SECTOR_PATH(10, 10, 0)}));
	set_act_time(15);
	add_act("emote flies around overhead.");
	add_act("emote laughs loudly.");
	add_act("emote looks around for a handout.");
	add_cact("emote flaps its wings in your face.");
	add_cact("emote pecks at your head with its beak.");
	add_cact("emote squawks loudly!");

	
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

