/* Odic (part 2), Sarr */
/* 2017-08-19 Malus: Changed to inherit base/std undead and use those defaults
 */
#include "defs.h"
#include <poison_types.h>
inherit STD_UNDEAD;
inherit "/std/combat/unarmed";

create_monster()
{
    ::create_monster();
    set_name("odic");
    add_name("tree");
    set_race_name("tree");
    set_adj("glowing");
    set_short("glowing tree");
    set_long("A living tree that glows with a purple and black aura!\n");
    set_skill(SS_DEFENCE, 100);
    set_skill(SS_UNARM_COMBAT, 100);
    add_prop(LIVE_I_NO_CORPSE, 1);
    add_prop(LIVE_I_UNDEAD, 55);
    set_act_time(3);
    set_cact_time(3);
    add_cact("emote blazes even brighter for a moment.");
    set_attack_unarmed(0, 40, 40, W_SLASH, 25, "lower left branch");
    set_attack_unarmed(1, 40, 40, W_SLASH, 25, "lower right branch");
    set_attack_unarmed(2, 40, 40, W_SLASH, 25, "upper left branch");
    set_attack_unarmed(3, 40, 40, W_SLASH, 25, "upper right branch");
    set_hitloc_unarmed(0, 40, 40, "lower trunk");
    set_hitloc_unarmed(1, 40, 10, "left branch");
    set_hitloc_unarmed(2, 40, 10, "right branch");
    set_hitloc_unarmed(3, 40, 40, "upper trunk");
}

string
query_combat_file()
{
    return "/d/Raumdor/common/std/chumanoid.c";
}

void
do_die(object killer)
{
    command(
      "emote crashes to the ground with a thud, as a purple mist flows out " +
      "and vanishes!");
    ::do_die(killer);
}

int
special_attack(object enemy)
{
    object poison;
    if (random(10))
        return 0;
    tell_watcher(QCTNAME(TO) + " slashes " + QCTNAME(enemy) +
                   " with a slime coated vine!\n",
      enemy);
    enemy->catch_msg(
      QCTNAME(TO) + " slashes you with a slime coated vine!\n");
    poison = clone_object("/std/poison_effect.c");
    poison->move(enemy);
    poison->set_time(20);
    poison->set_interval(5);
    poison->set_strength(40);
    poison->set_damage(({POISON_HP, 100}));
    poison->start_poison();
    return 1;
}
