/* Greater zombie, Sarr */
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
    set_name("zombie");
    set_race_name("zombie");
    set_adj("large");
    add_adj(adj);
    set_short("large " + adj + " zombie");
    set_long(
      "This foul creatures looks fresh out of the grave. His glowing eyes, " +
      "savage claws, and decaying flesh are dreadful. It looks quite large " +
      "and mean, even for a zombie.\n");
    set_skill(SS_DEFENCE, 70);
    set_skill(SS_UNARM_COMBAT, 90);
    add_prop(LIVE_I_UNDEAD, 20);
    set_random_move(5);
    set_act_time(10);
    add_act("moan");
    add_cact("@@seen_emote|looks at you, and looks hungry.@@");

    set_attack_unarmed(0, 40, 40, W_IMPALE, 10, "savage bite");
    set_attack_unarmed(W_LEFT, 30, 35, W_SLASH, 45, "left claw");
    set_attack_unarmed(W_RIGHT, 30, 35, W_SLASH, 45, "right claw");

    remove_attack(W_FOOTR);
    remove_attack(W_FOOTL);

    set_hitloc_unarmed(A_HEAD, 20, 15, "head");
    set_hitloc_unarmed(A_L_ARM, 20, 10, "left arm");
    set_hitloc_unarmed(A_R_ARM, 20, 10, "right arm");
    set_hitloc_unarmed(A_BODY, 30, 45, "body");
    set_hitloc_unarmed(A_LEGS, 20, 20, "legs");

    set_mm_in("tears itself out of the ground!");

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
    command("emote hisses in satisfaction as its victim falls.");
    command("emote moans: Your corpsssee isss mineee!");
    who->add_prop(LIVE_I_NO_CORPSE, 1);
    command("emote immediately devours the corpse.");
}

void
do_die(object killer)
{
    command(
      "emote falls to the ground, spewing black ooze out of its mouth.");
    command("emote moans: Yourrr tiiime will commme soooon, mortaaal.");
    ::do_die(killer);
}
int
special_attack(object enemy)
{
    object me;
    mixed *hitresult;
    string how;
    string ohow;
    string tar;
    me = TO;
    if (random(10))
        return 0;
    hitresult = enemy->hit_me(100 + random(450), W_SLASH, TO, -1);
    how       = " but miss";
    ohow      = " but misses";
    if (hitresult[0] >= 0)
    {
        how  = " and slashes across ";
        ohow = " and slashes across ";
        tar  = " chest";
    }
    if (hitresult[0] > 10)
    {
        how  = " and rip across ";
        ohow = " and rips across ";
        tar  = " chest";
    }
    if (hitresult[0] > 20)
    {
        how  = " and brutaly slashes across ";
        ohow = " and brutaly slashes across ";
        tar  = " chest, spraying blood everywhere";
    }
    if (hitresult[0] == -1)
    {
        TO->catch_msg("You strike out at " + QCTNAME(enemy) +
                      " with your claws," + how + ".\n");
        enemy->catch_msg(QCTNAME(TO) +
                         " strikes out at you with its clawed foot," + ohow +
                         ".\n");
        tell_watcher(QCTNAME(TO) + " strikes out at " + QCTNAME(enemy) +
                       " with its clawed foot," + ohow + ".\n",
          enemy);
    }
    if (hitresult[0] >= 0)
    {
        TO->catch_msg("You strike out at " + QCTNAME(enemy) +
                      " with your claws," + how + enemy->query_possessive() +
                      tar + ".\n");
        enemy->catch_msg(QCTNAME(TO) +
                         " strikes out at you with its clawed foot," + ohow +
                         "your" + tar + ".\n");
        tell_watcher(QCTNAME(TO) + " strikes out at " + QCTNAME(enemy) +
                       " with its clawed foot," + ohow +
                       enemy->query_possessive() + tar + ".\n",
          enemy);

        CHECK_DEAD(enemy, TO);
    }
    return 1;
}
