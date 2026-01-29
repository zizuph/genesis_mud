/*    Goblin for the Encampments by Crystalmir Lake
 *    Splunge, 1/12/94
 */

#include "/d/Krynn/solace/lake/local.h"
#include <ss_types.h>
#include <wa_types.h>

inherit M_FILE

void
create_krynn_monster()
{
    set_name(({"goblin","guard","goblin guard"}));
    set_race_name("goblin guard");
    set_adj("happy");
    set_long("This goblin seems very happy. Probably because of " +
	     "all the newbies he has recently gotten the honor of " +
	     "killing.\n");
    set_stats(({52,35,42,15,15,38}));
    set_skill(SS_DEFENCE, 35);
    set_skill(SS_PARRY, 10);
    set_skill(SS_WEP_SWORD, 48);
    ALIGN_ME;
    PRESTIGE_ME;
    NEVERKNOWN;
    set_act_time(5);
    add_act("chuckle");
    add_act("smile");
    add_act("bounce happily");
    if (IS_CLONE)
      set_alarm(2.0,0.0,"arm_me");
    refresh_mobile();
}

void
arm_me()
{
    seteuid(getuid(TO));
    clone_object(OBJ + "goblinsword1")->move(TO);
    clone_object(OBJ + "chainmail.c")->move(TO);
    clone_object(OBJ + "gauntlets.c")->move(TO);
    command("wield weapon");
    command("wear all");
    command("emote grunts.");
}

