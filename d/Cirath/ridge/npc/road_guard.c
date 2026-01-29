/* Ordinary guards in the employ of Kalak.
   Dethraine, March 1998. Code (c) Damian Horton.
*/
 
#pragma strict_types
#pragma save_binary
 
inherit "/d/Cirath/std/monster";
#include <wa_types.h>
#include "defs.h"

#define GDESC ({"confident", "competent", "strong", "cruel"})[random(4)]
#define GWEAP ({"swrd_obs","obsidian_mace"})[random(2)]
 
void
arm_me()
{
    clone_object(RIDGE_WEP+GWEAP)->move(TO);
    clone_object("/d/Cirath/tyr/arm/body_std")->move(TO);
    clone_object("/d/Cirath/tyr/arm/robe_pnc")->move(TO);
    clone_object("/d/Cirath/tyr/arm/head_hid")->move(TO);
    command("wield all");
    command("wear all");
}
 
void
create_monster ()
{
    set_name("guard");
    add_prop (LIVE_I_NEVERKNOWN, 1);
    set_race_name("human");
    set_adj(GDESC);
    set_long("A guard in the service of Kalak. He carries his "+
        "weapon with poise and confidence. It might be wise "+
        "not to upset Kalak by attacking his loyal troops.\n");

    set_stats(({68+random(10),68+random(10),68+random(10),
        48+random(16),48+random(16),64+random(16)}));

    set_skill(SS_WEP_SWORD, 48+random(18));
    set_skill(SS_WEP_CLUB, 48+random(18));
    set_skill(SS_DEFENCE, 48+random(18));
    set_skill(SS_PARRY, 44+random(18));
    set_skill(SS_UNARM_COMBAT, 18+random(26));
    set_skill(SS_BLIND_COMBAT, 8+random(22));
    set_alignment(50-random(300));
    set_exp_factor(110);
   
    set_act_time(10);
    add_act("emote curses the sun.");
    add_act("emote eyes you warily.");
    add_act("emote examines the fields and laughs at the condition "+
        "of the slaves working therein.");
    add_act("emote glances about, as if anticipating trouble.");
    add_act("emote wipes the sweat from his brow.");

    set_cact_time(7);
    add_cact("say You are going to suffer dearly for this attack!");
    add_cact("emote grips his weapon with determination.");
    add_cact("say Prepare for death, foolish one!");
}
 
