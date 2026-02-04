/*
 * A girl that runs the gambling wheel. Mortricia 920927
 *
 * Updated 11/28/2018 by Shanoga
 *  - The girl now waits for players to start the wheel.
 *  - The girl now takes bets properly.
 *  - The girl now gives the items to the player, rather than the items
 *    just appearing in the player's inventory.
 *  - The girl now emotes to show that she is spinning the wheel.
 *
 * Updated Jan 2021 by Lucius
 *  - Misc cleanups.
 */
inherit "/std/monster";
inherit "/std/act/action";

#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>


#define ALIGN           100
#define NO_OF_BETS      11

string *tnum = ({"zero", "one", "two", "three", "four", "five", "six",
  "seven", "eight", "nine", "ten", "eleven", "twelve"});

int acting, cleared;

void
create_monster()
{
    if (!IS_CLONE)
	return;

    set_name("girl");
    set_short("girl");
    set_long("@@my_long");
    set_adj("slender");
    set_gender(1);
    set_race_name("gypsy");

    add_prop(LIVE_I_NEVERKNOWN, 0);

    set_stats(({25,25,15,30,30,25}));
    set_hp(9999);
    set_mana(9999);
    set_alignment(ALIGN);
    /* Had to boost stats so she could carry the weight of the prizes
	 but she is still terrible at fighting. */
    set_exp_factor(75);

    set_skill(SS_UNARM_COMBAT, 10);

    set_all_hitloc_unarmed(10);
    set_all_attack_unarmed(10, 10);

    set_act_time(10);
    add_act("@@action_clear");
}

string
my_long()
{
    string str = "It's a slender girl.";
    if (!acting && !cleared)
	return str + "\n";

    if (!acting)
	return str + " She is waiting to take bets on the Wheel of Chance.\n";

    return str + " She is busy with the bets on the Wheel of Chance.\n";
}

public void
game_finished()
{
    acting = 0;
    cleared = 0;
}

void
action_clear()
{
    if (!acting && !cleared)
    {
	command("g_cmd clear");
	cleared = 1;
    }
}

void
action_six()
{
    command("g_cmd stop");
    acting = 0;
}

void
action_five()
{
    command("shout Hurry up with your bets!");
    set_alarm(10.0, 0.0, &action_six());
}

void
action_four()
{
    int i = random(NO_OF_BETS) + 1;
    command("emote shivers with expectation as the wheel seems to pause on " +
      tnum[i] + " for a moment before regaining speed once again.");
    set_alarm(5.5 + itof(random(4)), 0.0, &action_five());
}

void
action_three()
{
    command("emote smiles happily as the wheel begins to slow down.");
    set_alarm(4.5 + itof(random(4)), 0.0, &action_four());
}

void
action_two()
{
    command("say The wheel is spinning!");
    set_alarm(3.5 + itof(random(3)), 0.0, &action_three());
}

public void
action_one()
{
    if (!acting)
    {
	command("emote grabs a spoke along the side of the " +
	  "wheel and starts it spinning.");
	set_alarm(1.5 + itof(random(3)), 0.0, &action_two());
	acting = 1;
    }
}
