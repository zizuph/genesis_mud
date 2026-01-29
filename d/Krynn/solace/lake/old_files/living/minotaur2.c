/* Minotaur for the Encampments by Crystalmir Lake
 * Splunge, 1/12/94 
 * made to inherit the minotaur_base by Aridor, 10/94
 */


#include "/d/Krynn/solace/lake/local.h"
#include <ss_types.h>

inherit MINOTAUR;

void
create_minotaur()
{
    set_adj("nasty");
    set_long("This is an enormous, and very evil minotaur.\n" +
             "This minotaur is a true servant of Takhisis.\n" +
	     "It seems that minotaurs were chosen as the best\n" +
	     "able to guard the camps.\n");
    set_stats(({140,85,90,80,50,100}));
    set_skill(SS_PARRY, 70);
    set_skill(SS_WEP_SWORD, 80);
    set_act_time(8);
    add_act("emote snorts violently.");
    add_act("emote laughs at you with true amusement.");
    add_act("emote folds his arms across his massive chest.");
    set_alarm(2.0,0.0,"arm_me");
}
