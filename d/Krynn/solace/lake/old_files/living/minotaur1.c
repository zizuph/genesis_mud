/* Minotaur for the Encampments by Crystalmir Lake
 * Splunge, 1/12/94
 * made to inherit the minotaur_base by Aridor, 10/94
 */


#include "/d/Krynn/solace/lake/local.h"

inherit MINOTAUR;

void
create_minotaur()
{
    add_adj("evil");
    set_long("@@my_long");
    set_act_time(10);
    add_act("emote snorts violently.");
    add_act("emote laughs at you with true amusement.");
    add_act("emote folds his arms across his massive chest.");
    set_alarm(2.0,0.0,"arm_me");
}
