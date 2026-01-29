
 /*    A mini octopus for the water area

    coder(s):    Jaacar

 */
inherit "/std/creature";
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

object tp = this_player();

#define A_TENTACLE 0

#define H_HEAD 0
#define H_TENTACLE 1

create_creature()
{
    set_name("squeeze");
    add_name("octopus");
    set_short("small dangerous octopus");
    set_adj("small");
    add_adj("dangerous");
    set_race_name("octopus");
    set_long("This creatures is not very large, but appears to be quite "+
        "dangerous none the less. It is dark green in colour, and "+
        "has eight very long tentacles with which to grasp its "+
        "prey and squeeze the life out of them. Its body is "+
        "quite small and looks to be vulnerable if you can get by "+
        "all of those tentacles.\n");

    add_prop(LIVE_I_NEVERKNOWN, 1);
    add_prop(NPC_I_NO_LOOKS, 1);
    set_alignment(-100);
    set_gender(2);
	set_act_time(15);
	add_act("swim n");
	add_act("swim s");
	add_act("swim e");
	add_act("swim w");
	add_act("swim ne");
	add_act("swim nw");

	add_act("swim se");
	add_act("swim sw");
	add_act("swim u");
	add_act("swim d");

    set_stats(({40,60,60,45,45,50}));

	set_skill(SS_SWIM, 100);
	set_skill(SS_UNARM_COMBAT, 100);
	set_skill(SS_BLIND_COMBAT, 80);
	set_skill(SS_DEFENCE, 100);

    set_attack_unarmed(A_TENTACLE,15,25,W_SLASH,100,"tentacle");
	set_hitloc_unarmed(A_HEAD, ({5,5,5,5}), 5, "head");
    set_hitloc_unarmed(H_TENTACLE, ({5,5,5,10}), 95, "tentacle");

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
