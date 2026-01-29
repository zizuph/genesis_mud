/* Minotaur for the Encampments by Crystalmir Lake
 * Splunge, 1/12/94 
 * made to inherit the minotaur_base by Aridor, 10/94
 * 
 * This one is tougher than minotaur1 & 2.  He has an
 * axe similar to the one Kaz used.
 */


#include "/d/Krynn/solace/lake/local.h"
#include <ss_types.h>

inherit MINOTAUR;

void
create_minotaur()
{
    remove_adj("huge");
    set_adj("hairy");
    set_adj("gigantic");
    set_long("This is an excessively hairy minotaur. Even among his fellow " +
	     "minotaurs, he stands out as being very large. The double " +
	     "bladed axe he is wielding seems all the more deadly in this " +
	     "guy's hands!\n");
    set_stats(({160,90,100,80,50,120}));
    set_skill(SS_PARRY, 90);
    set_act_time(5);
    add_act("emote snorts violently.");
    add_act("emote laughs at you with true amusement.");
    add_act("emote folds his arms across his massive chest.");
    set_alarm(2.0,0.0,"arm_me");
}

void
arm_me()
{
    object wep;
    seteuid(getuid(this_object()));
    wep = clone_object("/d/Krynn/solace/lake/obj/minoaxe.c");
    wep->move(this_object());
    command("wield weapon");
}

