/* Wight, Sarr */
/* 2017-08-19 Malus: Added set_mm_in, moving defaults to base/std file */

#include "defs.h"
inherit STD_UNDEAD;
inherit "/std/combat/unarmed";
inherit "/d/Raumdor/common/npc/common_equipment";

void
create_monster()
{
    ::create_monster();

    string adj = one_of_list(({
      "revolting", "loathsome", "horrible", "foul",
    }));

    set_name("wight");
    set_race_name("wight");
    set_adj(adj);
    set_short(adj + " wight");
    set_long(
      "This foul creature looks like it was once a mighty soldier. Now it " +
      "roams these cursed lands in search of blood. Its eyes are sunken in, " +
      "its skin peeling and pale, its blook turned black and poisonous. This " +
      "wight is one evil creature that you don't want to mess with.\n");

    set_skill(SS_DEFENCE, 80);
    set_skill(SS_UNARM_COMBAT, 95);
    add_prop(LIVE_I_UNDEAD, 40);
    set_random_move(5);
    set_act_time(3);
    add_act("moan");
    add_act("emote scans the area for living blood.");
    set_cact_time(3);
    add_cact("say Give me your warm blood, mortal!");
    add_cact("emote lusts for your warm blood.");
    set_attack_unarmed(0, 40, 40, W_IMPALE, 10, "savage bite");
    set_attack_unarmed(1, 30, 35, W_SLASH, 45, "left claw");
    set_attack_unarmed(2, 30, 35, W_SLASH, 45, "right claw");
    set_hitloc_unarmed(0, 20, 15, "head");
    set_hitloc_unarmed(1, 20, 10, "left arm");
    set_hitloc_unarmed(2, 20, 10, "right arm");
    set_hitloc_unarmed(3, 30, 45, "body");
    set_hitloc_unarmed(4, 20, 20, "legs");
    set_mm_in("claws its way out of the ground!");

    add_undead_armours();

}

public string
race_sound()
{
    return "moans";
}

string
query_combat_file()
{
    return "/d/Raumdor/common/std/chumanoid.c";
}

void
notify_you_killed_me(object who)
{
    command("emote gurgles in delight.");
    command("say I will eat your corpse mortal!");
    who->add_prop(LIVE_I_NO_CORPSE, 1);
    command("emote devours the corpse of " + who->query_name() + ".");
}

void
do_die(object killer)
{
    command("emote slumps to the ground, lifeless and hollow.");
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

    drain = clone_object(WIGHT_DRAIN_OBJ);
    drain->move(enemy, 1);
    drain->do_drain();

    return 1;
}
