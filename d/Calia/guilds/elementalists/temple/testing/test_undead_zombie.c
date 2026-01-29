/*
 * Test golem for the WoHS.
*/

#include <std.h>
#include <ss_types.h>
#include <wa_types.h>
#include <macros.h>
#include <money.h>
#include "/d/Krynn/common/defs.h";
inherit M_FILE

inherit "/std/act/domove";     
inherit "/std/act/action";  
inherit "/std/act/attack";   

void
create_krynn_monster()
{
    set_name("zombie");
    set_short("offensive undead zombie");
    set_adj("offensive");
    add_adj("undead");
    set_race_name("zombie");
    set_long("This is an offensive undead zombie for EC beta testers. It has myth-base stats, " +
             "superior guru defence and parry, and base armour equivalent to " +
             "plate. This creation gives reduced experience. It hits like a Sparkle " +
             "giant's stone.\n"); 
    set_gender(G_NEUTER);
    add_prop(NPC_I_NO_LOOKS,1);
    add_prop(LIVE_I_NO_CORPSE, 1);
    add_prop(NPC_I_NO_RUN_AWAY, 1);
    add_prop(LIVE_I_UNDEAD, 1);
    add_prop(CONT_I_HEIGHT, 190);
    add_prop(CONT_I_WEIGHT, 70100);

    set_stats(({190,190,190,190,190,190}));
    set_skill(SS_DEFENCE, 100);
    set_skill(SS_PARRY, 100);
    set_skill(SS_WEP_CLUB, 100);
    set_hp(query_max_hp());

    set_all_hitloc_unarmed(40);


    // As a test npc it provides reduced experience.
    set_exp_factor(50);
  
    set_default_answer("The test zombie cannot communicate with you.\n");
}  

void
arm_me()
{
    seteuid(getuid(TO));

    clone_object("/d/Genesis/start/human/obj/boulder")->move(TO);
    command("wear all");
    command("wield all");
}
