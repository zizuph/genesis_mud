/*
 * A Solace peacekeeper
 *
 * by Rastlin
 */

#include "/d/Krynn/common/defs.h"
#include "../local.h"
#include <ss_types.h>
#include <macros.h>

inherit M_FILE

public void
create_krynn_monster()
{
    int i, level = random(4) + 3;

    set_color("grey");

    set_race_name("human");

    set_adj("solace");

    set_name("peacekeeper");
    add_name("solace peacekeeper");

    set_short("solace peacekeeper");

    set_long("The peacekeeper looks proud. He appears to take his " +
	     "job seriously. " + query_level_desc(level) + "\n");

    for(i = 0; i < 6; i++)
        set_base_stat(i, level * 7 + random(10));

    set_skill(SS_DEFENCE, level * 6 + random(20));
    set_skill(SS_WEP_SWORD, level * 5 + random(20));
    set_skill(SS_WEP_KNIFE, level * 5 + random(20));
    set_skill(SS_WEP_CLUB, level * 5 + random(20));
    set_skill(SS_WEP_POLEARM, level * 5 + random(20));
    set_skill(SS_WEP_JAVELIN, level * 4 + random(20));
    set_skill(SS_WEP_AXE, level * 5 +random(20));

    i = query_average_stat();
    i = i*i/10;
    set_alignment(i);
    set_knight_prestige(-i);

    set_all_attack_unarmed(level * 5, level * 6);
    set_all_hitloc_unarmed(level * 5);

    set_random_move(1);

    if (IS_CLONE)
        set_alarm(0.5, 0.0, "npc_arm_me", level);

}






