/* Lesser zombie, Sarr */
/* 2017-08-19 Malus: Added set_mm_in, moving defaults to base/std file */
/* 2017-11-02 Malus: Changed to use equip(), removed gold, and did cleanup. */
#include "defs.h"
inherit STD_UNDEAD;
inherit "/std/combat/unarmed";
inherit "/d/Raumdor/common/npc/common_equipment";

void
create_monster()
{
    ::create_monster();
    string adj =
      one_of_list(({"filthy", "rotting", "disgusting", "grotesque"}));
    set_name("zombie");
    set_race_name("zombie");
    set_adj(adj);
    set_short(adj + " zombie");
    set_long(
      "This foul creatures looks fresh out of the grave. Its glowing eyes, " +
      "savage claws, and decaying flesh are dreadful.\n");
    set_skill(SS_DEFENCE, 50);
    set_skill(SS_UNARM_COMBAT, 70);
    add_prop(LIVE_I_UNDEAD, 10);
    set_random_move(5);
    set_act_time(3);
    add_act("moan");
    add_act("emote shambles around.");
    set_cact_time(3);
    add_cact("emote snatches at your face, like it is trying to rip out your eyeballs.");
    add_cact("emote stares at you, transfixed with bloodlust.");
    add_cact("emote licks its chops while giving you a hungry look.");
    set_attack_unarmed(0, 35, 35, W_IMPALE, 10, "savage bite");
    set_attack_unarmed(1, 25, 30, W_SLASH, 45, "left claw");
    set_attack_unarmed(2, 25, 30, W_SLASH, 45, "right claw");
    set_hitloc_unarmed(0, 10, 15, "head");
    set_hitloc_unarmed(1, 10, 10, "left arm");
    set_hitloc_unarmed(2, 10, 10, "right arm");
    set_hitloc_unarmed(3, 20, 45, "body");
    set_hitloc_unarmed(4, 10, 20, "legs");
    set_mm_in("claws its way out of the trees!");

    add_undead_armours();
}

string
query_combat_file()
{
    return "/d/Raumdor/common/std/chumanoid.c";
}

void
notify_you_killed_me(object who)
{
    command("emote hisses in satisfaction as a fresh body falls before it.");
    command("emote moans: Your corpse isss miinnnneeee.");
    who->add_prop(LIVE_I_NO_CORPSE, 1);
    command(
      "emote quickly devours the remains of its victim, splatting flood and " +
      "flesh all around.");
}

void
do_die(object killer)
{
    command(
      "emote falls to the ground, spewing black ooze out of its mouth.");
    command("emote moans: Yourrr tiiime will commme soooon, mortaaal.");
    ::do_die(killer);
}
