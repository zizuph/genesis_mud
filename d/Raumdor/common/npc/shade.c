/* Shade, Sarr */
/* 2017-08-19 Malus: Added set_mm_in, moving defaults to base/std file */
#include "defs.h"
inherit STD_UNDEAD;
inherit "/d/Raumdor/common/lib/fear.c";

int    fear_alarm, fear_cooldown_alarm;
object weapon;

void
equip_weapon()
{
    if (weapon)
        weapon->do_destroy();
    weapon = clone_object(COMMON_WEP_DIR + "shaded");
    equip(weapon);
}

void
create_monster()
{
    ::create_monster();
    set_name("shade");
    set_race_name("shade");
    set_adj("black");
    set_short("black shade");
    set_long(
      "This dark creature looks rather humanoid, only it is pure black. All " +
      "light seems to be absorbed in its dark black shape. The only color " +
      "you see are its blazing red eyes that glare at you with utter hate. " +
      "It carries with it a black dagger of death. Fear creeps into your " +
      "heart as you behold this deadly creature of the night.\n");
    set_skill(SS_DEFENCE, 50);
    set_skill(SS_PARRY, 80);
    set_skill(SS_WEP_KNIFE, 100);
    set_skill(SS_AWARENESS, 100);
    add_prop(LIVE_I_NO_CORPSE, 1);
    add_prop(LIVE_I_UNDEAD, 53);
    set_act_time(3);
    add_act("emote radiates a coldness that sinks into your bones.");
    set_cact_time(3);
    add_cact("emote hisses: A quick death for thee, yes, my pretty.");
    add_cact("emote flashes its blazing red eyes in fury.");
    add_cact(
      "emote hisses: Why do you resist? Just let me take you to the darkness " +
      "of the grave.");
    set_hitloc_unarmed(0, 40, 15, "head");
    set_hitloc_unarmed(1, 40, 10, "left arm");
    set_hitloc_unarmed(2, 40, 10, "right arm");
    set_hitloc_unarmed(3, 45, 45, "body");
    set_hitloc_unarmed(4, 40, 20, "legs");
    set_mm_in("pounces out of the shadows!");

    equip_weapon();
}

void
react_missing()
{
    command("emote hisses: Fool!");
    command("emote waves its hand and a new dagger appears in it.");
    equip_weapon();
}

void
notify_you_killed_me(object who)
{
    command("emote hisses in delight.");
    command("emote hisses: Welcome, my pretty.");
    TELL_CAN_SEE(E(TO),
      QCTNAME(TO) +
        " reaches down and touches the corpse and another black shade rise " +
        "from it!\n");
    clone_object(COMMON_NPC_DIR + "shade")->move_living("M", E(TO));
}

void
do_die(object killer)
{
    if (weapon)
        weapon->remove_object();
    command("emote hisses: I shall be baaaack!");
    command("emote fades away into oblivion!");
    ::do_die(killer);
}

void
init_living()
{
    ::init_living();
    if (!interactive(TP) || get_alarm(fear_cooldown_alarm))
        return;

    fear_alarm          = set_alarm(1.0, 0.0, "do_fear");
    fear_cooldown_alarm = set_alarm(1.0, 0.0, &command(""));
}
void
do_fear(object player)
{
    tell_room(E(TO),
      ({TO->query_name() + " radiates a terrifying aura!\n",
        "The " + TO->query_nonmet_name() + " radiates a terrifying aura!\n",
        "You are suddenly struck by a feeling of terror!\n"}),
      0, TO);
    fear(E(TO), 68);
}

int
special_attack(object enemy)
{
    int     dis, wis, sum;
    object *plays;
    if (!present(weapon, TO))
    {
        react_missing();
        return 1;
    }
    if (random(15))
        return 0;
    tell_room(E(TO),
      QCTNAME(TO) +
        " lifts its arms and opens its chest, showing you fiery pits of " +
        "hell!\n");
    plays = FILTER_PLAYERS(all_inventory(E(TO)));
    for (int i = 0; i < sizeof(plays); i++)
    {
        dis = plays[i]->query_stat(5);
        wis = plays[i]->query_stat(4);
        sum = (dis + wis) / 2;
        if (sum < 70)
        {
            tell_room(E(TO),
              QCTNAME(plays[i]) +
                " stares at the horrible vision with a look of utter horror " +
                "on " +
                plays[i]->query_possessive() + " face.\n",
              plays[i]);
            plays[i]->catch_msg(
              "You stare at the horrible vision and gasp in utter horror!\n");
            plays[i]->command("scream");
            plays[i]->heal_hp(-300);

            // New check for death. Nerull 8/5-09.
            if (plays[i]->query_hp() <= 0)
            {
                tell_room(E(TO),
                  QCTNAME(plays[i]) + " falls to the ground in agony!\n",
                  plays[i]);
                plays[i]->catch_msg(
                  "The vision is too much for your weak mind and courage! " +
                  "You fall the ground in agony, and succumb...\n");
                plays[i]->do_die(TO);
            }
        }
        // Instakill abilities, even for the small, is not
        // wanted. Nerull 8/5-09.
        /*if( sum < 70 )
        {
            plays[i]->command("scream");
            tell_room(E(TO),QCTNAME(plays[i])+" falls to the ground "+
            "in agony!\n",plays[i]);
          plays[i]->catch_msg("The vision is too much for your weak mind and
        "+
            "courage! You fall the ground in agony...and slowly "+
            "die....\n");
            plays[i]->heal_hp(-100000);
            plays[i]->do_die(TO);
        }*/
    }
    return 1;
}
