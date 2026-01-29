#include "default.h"
inherit "/d/Kalad/std/monster";

void
create_kalad_monster()
{
    set_name("guardian");
    set_race_name("human");
    set_adj("otherworldly");
    add_adj("invisible");
    set_long("Nothing can be seen, save for a few twirling mists of vapor.\n");
    set_gender(G_NEUTER);
    set_stats(({125, 100, 125, 50, 50, 100}));
    set_all_hitloc_unarmed(20);
    set_skill(SS_UNARM_COMBAT, 100);
    set_skill(SS_BLIND_COMBAT, 100);
    set_skill(SS_DEFENCE, 100);
    set_act_time(6);
    add_act("open redwood door");
    add_act("open iron door");
    add_act("close redwood door");
    add_act("close iron door");
    add_prop(OBJ_I_INVIS, 1);
    add_prop(LIVE_I_NO_CORPSE, 1);
    add_prop(LIVE_I_SEE_DARK, 50);
    add_prop(LIVE_I_SEE_INVIS, 50);
    add_prop(NPC_I_NO_RUN_AWAY, 1);
    set_knight_prestige(500);
}

void
help_friend(object ob)
{
    if (ob && !query_attack() && present(ob, environment()))
    {
	command("emote laughs insidiously.");
	command("emote snarls: Death to those that oppose Thanar!");
	command("kill " + OB_NAME(ob));
    }
}
