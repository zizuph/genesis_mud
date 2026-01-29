/* Apparition, Sarr */
/*
 * Changed alignment from -445 to -245. - Nerull 8/5-09.
 * Paralyze now works for 3 seconds, and not 50.
 *
 */
/* 2017-08-19 Malus: Added set_mm_in, moving defaults to base/std file */
/* 2017-08-29 Malus: Modified do_fear to add panic and do run_away if
 * over F_PANIC_WIMP_LEVEL */
/* 2017-08-31 Malus: Fix and unify the two paralysis effects */
/* 2017-09-04 Malus: Move core effect to lib for use elsewhere */
#include "defs.h"

#define A_BITE 0
#define A_LPAW 1
#define A_RPAW 2

inherit STD_UNDEAD;
inherit "/std/combat/unarmed";
inherit "/d/Raumdor/common/lib/paralyze.c";
inherit "/d/Raumdor/common/lib/fear.c";

int fear_alarm;
int fear_cooldown_alarm;

void
do_despawn()
{
    TELL_CAN_SEE(E(TO), QCTNAME(TO) + " fades away into nothingness.\n");
    remove_object();
}

void
create_monster()
{
    ::create_monster();
    string adj = one_of_list(({
      "horrible", "faint", "shadowy", "pale",
    }));
    set_name("apparition");
    set_race_name("apparition");
    set_adj(adj);
    set_short(adj + " apparition");
    set_long(
      "This awful looking apparition stares at you with a ghostly eye. It " +
      "appears to be a transparent shadow of a warrior, its stomach torn " +
      "out, one of its legs hacked away, and its ghostly armour in shambles. " +
      "A sword fades and glows in and out of its hands, while its face seems " +
      "to be covered in ghostly blood, with one eye missing.\n");
    set_skill(SS_DEFENCE, 90);
    set_skill(SS_UNARM_COMBAT, 100);
    add_prop(LIVE_I_NO_CORPSE, 1);
    add_prop(LIVE_I_UNDEAD, 50);
    set_act_time(3);
    add_act("emote wails.");
    add_act("moan softly");
    add_act("emote radiates a coldness that sinks into your bones.");
    set_cact_time(3);
    add_cact(
      "emote wails: You, mortal, will feel the wrath of the... " +
      "ggraaavveeee!");
    add_cact("emote moans loudly.");
    add_cact("emote wails: Thou shalt... die!");
    set_attack_unarmed(A_BITE, 40, 43, W_IMPALE, 10, "ethereal sword");
    set_attack_unarmed(A_LPAW, 30, 35, W_SLASH, 45, "left ethereal claw");
    set_attack_unarmed(A_RPAW, 30, 35, W_SLASH, 45, "right ethereal claw");
    set_hitloc_unarmed(0, 40, 15, "head");
    set_hitloc_unarmed(1, 40, 10, "left arm");
    set_hitloc_unarmed(2, 40, 10, "right arm");
    set_hitloc_unarmed(3, 45, 45, "body");
    set_hitloc_unarmed(4, 40, 20, "legs");
    set_mm_in("slowly forms out of a swirl of mist!");
}

void
do_paralyze()
{
    object target, *players;

    tell_room(E(TO),
      ({TO->query_name() + " raises its arms and releases a grey mist that " +
                           "envelopes the area!\n",
        "The " + TO->query_nonmet_name() + " raises its arms and releases a " +
                                           "grey mist that envelopes the " +
                                           "area!\n",
        "A strange mist suddenly hits you!\n"}),
      0, TO);

    players = FILTER_PLAYERS(all_inventory(E(TO)));

    for (int i = 0; i < sizeof(players); i++)
    {
        if (is_paralyzed(players[i]))
            continue;

        if (!players[i]->can_see_in_room() || random(4) == 0)
        {
            players[i]->reveal_me(1);
            players[i]->command("scream");
            players[i]->catch_msg("You fall to the ground paralyzed!\n");
            tell_room(E(players[i]),
              QCTNAME(players[i]) +
                " falls to the ground in a shuddering heap!\n",
              players[i]);
            paralyze(players[i]);
            target = players[i];
        }
        else
        {
            players[i]->catch_msg(
              "You manage to hold your breath while the mist dissipates.\n");
        }
    }
    aggressive_attack(target);
}

string
query_combat_file()
{
    return "/d/Raumdor/common/std/chumanoid.c";
}

void
notify_you_killed_me(object who)
{
    command("emote wails: Hahahaha, welcome to your grave!");
}

void
do_die(object killer)
{
    command("emote screams in fury!");
    command("emote fades away into oblivion!");
    ::do_die(killer);
}

void
init_living()
{
    ::init_living();
    if (!interactive(TP) || get_alarm(fear_cooldown_alarm))
        return;
    fear_alarm          = set_alarm(1.0, 0.0, "do_fear", TP);
    fear_cooldown_alarm = set_alarm(30.0, 0.0, &command(""));
}

void
do_fear(object player)
{
    tell_room(E(TO),
      ({TO->query_name() + " radiates a terrifying aura!\n",
        "The " + TO->query_nonmet_name() + " radiates a terrifying aura!\n",
        "You are suddenly struck by a feeling of terror!\n"}),
      0, TO);
    fear(E(TO));
}

int
special_attack(object enemy)
{
    if (random(15))
        return 0;
    do_paralyze();
    return 1;
}
