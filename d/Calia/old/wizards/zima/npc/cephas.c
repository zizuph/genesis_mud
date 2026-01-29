/* 
            Cornelius the Winged Horse
                   by Zima
                  taken from
		Zax the white lion v2.0
			By Guido
*/
inherit "/std/creature";
inherit "/std/combat/unarmed";
inherit "/std/act/domove";
inherit "/std/act/action";

#include <wa_types.h>
#include <ss_types.h>
#include <macros.h>
#include <filter_funs.h>
#include "/d/Dville/abbrev.h"

#define A_BITE  0
#define A_LHOOF 1
#define A_RHOOF 2

#define H_HEAD 0
#define H_BODY 1

void
create_creature()
{
    set_name("cephas the winged horse");
    set_race_name("winged horse");
    set_adj(({"white", "majestic"}));
    set_long(BS(
        "This mystical winged horse is the personal steed of Zima, " +
        "the Hierophant of Argos.  He looks at you with distrust " +
        "in his eyes.\n"));

    set_stats(({ 300, 300, 250, 250, 250, 200}));

    set_hp(100000);

    set_skill(SS_DEFENCE, 100);

    set_skill(SS_CLIMB, 100);

    set_skill(SS_SWIM, 80);

    set_attack_unarmed(A_BITE, 90, 90, W_IMPALE, 20, "jaws");
    set_attack_unarmed(A_LHOOF, 90, 90, W_SLASH, 40, "left hoof");
     set_attack_unarmed(A_RHOOF, 90, 90, W_SLASH, 40, "right hoof");

    set_hitloc_unarmed(H_HEAD, ({15, 25, 20, 20 }), 20, "head");
    set_hitloc_unarmed(H_BODY, ({10, 15, 30, 20 }), 80, "body");

    set_act_time(4);
    add_act("neighs deeply");

}
static void
tell_watcher(string str, object enemy)
{
    object me, *ob;
    int i;

    me = this_object();
    ob = FILTER_LIVE(all_inventory(environment(me))) - ({me});
    ob -= ({ enemy });
    for (i = 0; i < sizeof(ob); i++)
        if (ob[i]->query_see_blood())
            ob[i]->catch_msg(str);
}

