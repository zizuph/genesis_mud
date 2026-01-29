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
    set_adj("watchful");
    set_long("This goblin seems to be more cautious than is typical " +
	     "for his race.  However, if a chance for combat comes up, " +
        "he will dive in with very typical goblin fervour.\n");
    set_stats(({50,45,40,15,15,35}));
    set_skill(SS_DEFENCE, 25);
    set_skill(SS_PARRY, 30);
    set_skill(SS_WEP_SWORD, 28);
    ALIGN_ME;
    PRESTIGE_ME;
    NEVERKNOWN;
    set_act_time(5);
    add_act("scream");
    add_act("cackle");
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
