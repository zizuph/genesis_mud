/* partly copied from the Skeletal hero of percy*/
/* otherwise created by Aridor 09/15/93 */

#include <ss_types.h>
#include <macros.h>
#include <stdproperties.h>
#include "../local.h"
#include <money.h>

inherit M_FILE

void
create_krynn_monster()
{
        int i;

        set_name("bog body");
        set_pname("bog bodies");
        set_short("bog body");
        set_pshort("bog bodies");
        add_name("body");
        add_pname("bodies");
        set_race_name("body");
        set_long("This bog body has risen from the depths of the moor.\n"
         + "It now bears a hatred for all living things......\n");
        set_adj("bog");

        for (i = 0; i < 6; i++)
                set_base_stat(i, 20 + random(6));
        set_skill(SS_DEFENCE, random(10) + 40);
        set_skill(SS_WEP_SWORD, 75);
        set_skill(SS_PARRY, 30);
        set_skill(SS_2H_COMBAT, 30);

        set_all_attack_unarmed(75, 10);
        set_all_hitloc_unarmed(10);
        set_alignment(-300);
        set_knight_prestige(250);
        add_act("emote stares at you, death in his eyes.");
        add_act("emote looks at you in disdain.");
        add_act("emote watches your every move.");
        add_act("get all");
        add_act("wield all");
        add_act("wear all");
        set_act_time(15);
        set_aggressive(1);
        add_prop(NPC_I_NO_RUN_AWAY, 1);
        add_prop(LIVE_I_UNDEAD, 20);



        if (IS_CLONE)
	  set_alarm(1.0,0.0,"arm_me");
}
void
arm_me()
{
        seteuid(geteuid(TO));
        MONEY_MAKE_SC(random(30))->move(TO);
        MONEY_MAKE_GC(random(3))->move(TO);
}

