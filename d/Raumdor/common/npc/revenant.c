/* The feared revenant, Sarr
 *
 * 2015-09-14 - Cotillion
 * - Runtime fixes and some cleanups
 */
/* 2017-09-03 Malus: Replace foul effect */

#include "defs.h"
#include <files.h>

inherit STD_UNDEAD;
inherit "/std/combat/unarmed";
inherit "/d/Raumdor/common/lib/corrupt.c";
inherit "/d/Raumdor/common/npc/common_equipment";

int bias = -1;
int corrupt_alarm;
int corrupt_cooldown_alarm;

void
create_monster()
{
    string adj = one_of_list(({
      "treacherous", "feared", "deadly", "lethal",
    }));
    ::create_monster();
    set_name("revenant");
    add_name("revenant");
    set_race_name("revenant");
    set_adj(adj);
    set_short(adj + " revenant");
    set_long(
      "Of all the mighty undead, this one is one of the deadliest. It looks " +
      "like a zombie in every way, only it move faster, much faster. Its " +
      "eyes blaze red with a hellish fury. Its long, nasty, sharp claws drip " +
      "black ooze and its face is contorted into an expression of great hate " +
      "and anger.\n");
    set_stats(STAT_ARRAY(200));
    set_skill(SS_DEFENCE, 100);
    set_skill(SS_UNARM_COMBAT, 100);
    set_random_move(6);
    add_prop(LIVE_I_NO_CORPSE, 1);
    add_prop(LIVE_I_UNDEAD, 60);
    set_cact_time(3);
    add_cact("emote lets off an awful howl that leaves your ears ringing.");
    add_cact(
      "emote screams: You cannot escape the powers of the grave, mortal!");
    add_cact("emote snarls with inhuman rage.");
    add_cact(
      "emote screams: I shall slice open your stomach and feast on your " +
      "guts!");
    add_cact(
      "emote screams: I will tear your heart out and squeeze its blood out " +
      "into my mouth!");
    set_attack_unarmed(0, 40, 40, W_IMPALE, 10, "savage bite");
    set_attack_unarmed(1, 40, 40, W_SLASH, 45, "left claw");
    set_attack_unarmed(2, 40, 40, W_SLASH, 45, "right claw");
    set_hitloc_unarmed(0, 10, 15, "head");
    set_hitloc_unarmed(1, 10, 10, "left arm");
    set_hitloc_unarmed(2, 10, 10, "right arm");
    set_hitloc_unarmed(3, 20, 45, "body");
    set_hitloc_unarmed(4, 10, 20, "legs");
    set_mm_in("leaps out from the shadows screaming!");

    add_undead_armours();
}

string
query_combat_file()
{
    return "/d/Raumdor/common/std/chumanoid.c";
}

void
notify_you_killed_me(object enemy)
{
    /* If we're going to do this, we should produce the head
     *
    command("emote reaches down quickly to the fallen foe and slices off "
    +
        HIS(enemy) + " head!\n");
    command("emote lifts the head up victoriously, then flings it to the
    "+
        "ground.");
    */
    command("emote laughs mockingly.");
}

void
do_die(object killer)
{
    // Revenant stone dropchance. Currently closed for review - Nerull
    /* if (random(REV_DROPCHANCE) == 1)
     {
           seteuid(getuid(TO));
         clone_object("/d/Raumdor/common/obj/rev_stone.c")->move(TO, 1);

         command("emote drops a shimmering red stone!");

         log_file("spectre_med","A revenant dropped a shimmering stone at
     " +
         extract(ctime(time())) + ".\n");
     }*/

    command("emote screams with the fury of hell!\n");
    command("emote seems to be consumed in some strange black flame.");
    command("emote falls the the ground, dead.");
    ::do_die(killer);
}

int
special_attack(object enemy)
{
    object *players;

    if (random(10))
        return 0;

    mixed exits = E(TO)->query_exit();
    if (!sizeof(exits))
    {
        return 0;
    }

    if (bias < 0 || bias >= sizeof(exits))
    {
        bias = random(sizeof(exits) / 3) * 3;
    }

    // Exclude rooms that may have special conditions
    if (exits[bias + 2] != 0)
        return 0;

    string exit = exits[bias + 1];
    string room = exits[bias];

    tell_room(E(TO),
      "The " + TO->query_short() + " lifts " + QCTNAME(enemy) +
        " up in the air and hurls " + enemy->query_objective() + " " + exit +
        "!\n",
      enemy);
    enemy->catch_msg("The " + TO->query_short() +
                     " lifts you up in the air and hurls you " + exit +
                     "!\n");
    enemy->move_living("M", room);
    enemy->catch_msg("You land with a thud.\n");
    tell_room(E(enemy),
      QCTNAME(enemy) +
        " comes flying out of the air and lands with a thud.\n",
      enemy);
    enemy->heal_hp(-150);

    players = FILTER_PLAYERS(all_inventory(E(TO)));
    players = FILTER_CAN_SEE(players, this_object());

    if (sizeof(players) == 0)
        set_alarm(2.0, 0.0, &command("$" + exit));
    return 1;
}

void
check_corrupt(object player)
{
    if (!CAN_SEE(TO, player) || get_alarm(corrupt_cooldown_alarm))
        return;
    corrupt_alarm          = set_alarm(2.0, 0.0, "do_corrupt");
    corrupt_cooldown_alarm = set_alarm(30.0, 0.0, &command(""));
}

void
init_living()
{
    ::init_living();
    check_corrupt(TP);
}
