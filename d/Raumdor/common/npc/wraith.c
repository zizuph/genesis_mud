/* Wraith, Sarr */
/* 2017-08-19 Malus: Added set_mm_in, moving defaults to base/std file */

#include "defs.h"
inherit STD_UNDEAD;
inherit "/std/combat/unarmed";

void
create_monster()
{
    ::create_monster();
    string adj = one_of_list(({
      "transparent", "luminous", "shadowy", "black",
    }));

    set_name("wraith");
    set_race_name("wraith");
    set_adj(adj);
    set_short(adj + " wraith");
    set_long(
      "This ghostly phantom is black in color, with two red, glowing eyes. " +
      "You think you can see the fires of hell reflecting from them. They " +
      "burn with an inner fury. Its body is vaguely humanoid, and fades in " +
      "and out slowly, but evenly, like a steady heart beat. Occasionally it " +
      "spasms a bit, and flickers in and out briefly, but steadies itself " +
      "quickly.\n");

    set_stats(STAT_ARRAY(200));
    set_skill(SS_DEFENCE, 90);
    set_skill(SS_UNARM_COMBAT, 100);
    add_prop(LIVE_I_NO_CORPSE, 1);
    add_prop(LIVE_I_UNDEAD, 48);
    add_prop(LIVE_I_SEE_INVIS, 1);
    set_random_move(5);
    set_act_time(3);
    add_act("@@seen_emote|flickers in and out briefly.@@");
    add_act("emote flashes its burning red eyes.");
    add_act("emote radiates a coldness that sinks into your bones.");
    set_cact_time(3);
    add_cact("say You will see the darkness of hell soon, mortal!");
    set_attack_unarmed(0, 40, 40, W_IMPALE, 10, "ethereal jaws");
    set_attack_unarmed(1, 30, 35, W_SLASH, 45, "left ethereal claw");
    set_attack_unarmed(2, 30, 35, W_SLASH, 45, "right ethereal claw");
    set_hitloc_unarmed(0, 40, 15, "head");
    set_hitloc_unarmed(1, 40, 10, "left arm");
    set_hitloc_unarmed(2, 40, 10, "right arm");
    set_hitloc_unarmed(3, 45, 45, "body");
    set_hitloc_unarmed(4, 40, 20, "legs");
    set_mm_in("slowly materializes in front of you!");
}

public string
race_sound()
{
    return "hisses";
}

string
query_combat_file()
{
    return "/d/Raumdor/common/std/chumanoid.c";
}

void
notify_you_killed_me(object who)
{
    command("say Hahahaha, puny mortal!!");
}

void
do_die(object killer)
{
    command("emote fades away into oblivion!");
    ::do_die(killer);
}

int
special_attack(object enemy)
{
    object drain;
    if (random(10))
        return 0;
    tell_watcher(QCTNAME(TO) + " reaches out and strikes " + QCTNAME(enemy) +
      " with a draining touch!\n", enemy);
    enemy->catch_msg(
      QCTNAME(TO) + " reaches out and strikes you with a draining touch!\n");
    drain = clone_object(WRAITH_DRAIN_OBJ);
    drain->move(enemy, 1);
    drain->do_drain();
    return 1;
}
