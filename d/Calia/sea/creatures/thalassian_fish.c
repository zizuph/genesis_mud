
 /*    A fish for the water area

    coder(s):    Amelia

    history:    22.5.95    created          Amelia
                21.7.95    header added     Digit
                19.8.97    added movement   Jaacar
                21.7.03    modified for Thalassia    Jaacar
                
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
	set_short("neon blue fish");
	set_pshort("neon blue fish");
	set_living_name("neon");
	set_adj("neon");
	add_adj("blue");
	set_adj("tiny");
	add_adj("bright");
	set_long("This is a tiny, bright neon blue fish. It "+
		"is very colorful and darts around "+
		"quickly in the water.\n");

	set_act_time(15);
	add_act("emote nibbles on your kneecap.");
	add_act("emote darts around quickly in the water.");

    add_prop(OBJ_I_VOLUME, 10);
	add_prop(OBJ_I_WEIGHT, 10);

	set_stats(({30,30,80,3,3,140}));

	set_skill(SS_SWIM, 100);
	set_skill(SS_UNARM_COMBAT, 100);
	set_skill(SS_BLIND_COMBAT, 80);
	set_skill(SS_DEFENCE, 100);

	set_hp(random(35));

	set_attack_unarmed(A_BITE,15,25,W_SLASH,80,"teeth");
	set_attack_unarmed(1,25,65,W_SLASH, 20,"fin");
	set_hitloc_unarmed(A_HEAD, ({5,5,5,5}), 40, "head");
    set_hitloc_unarmed(H_TAIL, ({5,5,5,10}), 15, "tail");
	set_hitloc_unarmed(H_BODY, ({10,15,15,20}), 35, "body");
    set_hitloc_unarmed(H_EYES, ({10,5,10,5}), 10, "eye");

    set_random_move(10);
    set_restrain_path(({(THAL),(THALL),(THALM),(THALC)}));
	
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
