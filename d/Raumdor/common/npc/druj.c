/* Druj, Sarr */
/* 2017-06-26 Malus: Fix delayed foul */
/* 2017-08-19 Malus: Added set_mm_in, moving defaults to base/std file */
/* 2017-09-03 Malus: Replace foul effect */
#include "defs.h"
#include <poison_types.h>
inherit STD_UNDEAD;
inherit "/std/combat/unarmed";
inherit "/d/Raumdor/common/lib/corrupt.c";

int corrupt_alarm;
int corrupt_cooldown_alarm;

void
do_despawn()
{
    TELL_CAN_SEE(environment(), QCTNAME(TO) +  " floats out of view.\n");
    remove_object();
}

void
create_monster()
{
    ::create_monster();
    set_name("hand");
    set_race_name("hand");
    set_adj("floating");
    add_adj("dismembered");
    set_short("floating dismembered hand");
    set_long(
      "This thing is surely and awful sight. It is a severed hand, blood " +
      "dripping off the protruding bone fragments at the stump of what was " +
      "once part of the wrist. Its fingers move and wiggle, while its nails, " +
      "long and sharp, seem to drip some black ooze. It glows with a sickly " +
      "green and black aura.\n");
    set_skill(SS_DEFENCE, 100);
    set_skill(SS_UNARM_COMBAT, 100);
    add_prop(LIVE_I_NO_CORPSE, 1);
    add_prop(LIVE_I_SEE_DARK, 1);
    add_prop(OBJ_I_WEIGHT, 6500);
    add_prop(OBJ_I_VOLUME, 3500);
    add_prop(LIVE_I_UNDEAD, 53);
    add_act("emote writhes around in the air.");
    set_cact_time(3);
    add_cact("emote writhes around in the air.");
    add_cact("emote pulses with a green and black aura.");
    set_attack_unarmed(0, 40, 50, W_SLASH, 50, "hand");
    set_attack_unarmed(1, 40, 50, W_IMPALE, 50, "hand");
    set_hitloc_unarmed(0, 43, 70, "palm");
    set_hitloc_unarmed(1, 43, 30, "fingers");
    set_mm_in("floats out of the gloom!");
}

string
query_combat_file()
{
    return "/d/Raumdor/common/std/drujplain.c";
}

void
do_die(object killer)
{
    command("finger " + OB_NAME(killer));
    command("emote vaporizes into the air.");
    ::do_die(killer);
}

int
special_attack(object enemy)
{
    object poison;
    object me = TO;
    if (random(12))
        return 0;
    tell_watcher(QCTNAME(me) + " clamps down on " + QCTNAME(enemy) +
                   "'s neck! " + enemy->query_pronoun() +
                   " grabs at it rips it off, but not before it was able to " +
                   "inject its black poison into " +
                   enemy->query_possessive() + " veins!\n",
      enemy);
    enemy->catch_msg(QCTNAME(me) +
                     " clamps down on your neck! You grab at it and rip it " +
                     "off, but not before it was able to inject its black " +
                     "poison into your veins!\n");
    poison = clone_object("/std/poison_effect.c");
    poison->move(enemy);
    poison->set_time(20);
    poison->set_interval(5);
    poison->set_strength(30);
    poison->set_damage(({POISON_HP, 50}));
    poison->start_poison();
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
