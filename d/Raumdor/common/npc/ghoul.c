/* Ghoul, Sarr
 *
 * Cotillion modified Alarm starting, 2004-12-07
 * Mirandus modified the message given when paralyzed, 2015-04-08
 */
/* 2017-08-19 Malus: Added set_mm_in, moving defaults to base/std file */
/* 2017-09-04 Malus: Use fixed paralysis effect in lib */
#include "defs.h"
inherit STD_UNDEAD;
inherit "/std/combat/unarmed";
inherit "/d/Raumdor/common/lib/paralyze";
inherit "/d/Raumdor/common/npc/common_equipment";


void
create_monster()
{
    ::create_monster();
    string adj = one_of_list(({
      "revolting", "loathsome", "horrible", "foul",
    }));

    set_name("ghoul");
    set_race_name("ghoul");
    set_adj(adj);
    set_short(adj + " ghoul");
    set_long(
      "This foul, reeking ghoul is so disgusting it could make you vomit. " +
      "The mere smell of it is enough to churn stomachs. Its eyes drip with " +
      "blood and crawl with maggots. Thick yellow slime slowly spills from " +
      "its mouth, worms wriggling in the corners. Its entire body is covered " +
      "with peeling skin and open sores.\n");
    set_skill(SS_DEFENCE, 80);
    set_skill(SS_UNARM_COMBAT, 90);
    add_prop(LIVE_I_UNDEAD, 40);
    set_random_move(5);
    set_act_time(3);
    add_act("moan");
    add_act(
      "emote spits out maggot-covered rotting bone fragments, probably from " +
      "its last meal.");
    set_cact_time(3);
    add_cact("say Shaa willl eschoy y'ouur corpshe, shaka!!");
    add_cact("emote lusts for your warm blood.");
    set_attack_unarmed(0, 40, 40, W_IMPALE, 10, "savage bite");
    set_attack_unarmed(1, 30, 35, W_SLASH, 45, "left claw");
    set_attack_unarmed(2, 30, 35, W_SLASH, 45, "right claw");
    set_hitloc_unarmed(0, 20, 15, "head");
    set_hitloc_unarmed(1, 20, 10, "left arm");
    set_hitloc_unarmed(2, 20, 10, "right arm");
    set_hitloc_unarmed(3, 30, 45, "body");
    set_hitloc_unarmed(4, 20, 20, "legs");
    set_mm_in("rips itself out of the ground!");

    KLOG("ghoul", file_name(TO) + " SPAWN");
    init_despawn();

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
    command("emote gurgles in delight.");
    command("emote moans: Yhoour corpsshee ish mahyneee!");
    who->add_prop(LIVE_I_NO_CORPSE, 1);
    command("emote devours the corpse of " + who->query_name() + ".");
}

void
do_die(object killer)
{
    command(
      "emote falls to the ground, spewing blood and guts out of its mouth.");
    killer->catch_msg(
      "The ghoul turns at you one final time and pukes its insides all over " +
      "you.\n");
    killer->command("$puke");
    ::do_die(killer);
}


void
stink(object player)
{
    if (player && environment(player) == environment())
    {
        player->catch_msg(
          "A foul, rotting smell wafts off the ghoul. You feel like " +
          "puking.\n");
        set_alarm(30.0, 0.0, "stink");
    }
}

int
special_attack(object enemy)
{
    if (random(20))
        return 0;
    if (is_paralyzed(enemy))
        return 0;
    tell_watcher(QCTNAME(TO) + " reaches out and strikes " + QCTNAME(enemy) +
                   " with a paralyzing touch! " + QCTNAME(enemy) +
                   " seems unable to move.\n",
      enemy);
    enemy->catch_msg(QCTNAME(TO) +
                     " reaches out and strikes you with a paralyzing touch! " +
                     "You feel unable to move!\n");

    paralyze(enemy, 30);

    return 1;
}

void
init_living()
{
    ::init_living();
    if (interactive(this_player()))
    {
        reset_despawn();
        set_alarm(20.0, 0.0, &stink(this_player()));
    }
}

