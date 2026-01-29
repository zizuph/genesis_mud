inherit "/std/poison_effect";

#include "/d/Krynn/common/defs.h"
#include <macros.h>
#include <poison_types.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <formulas.h>
#include <filter_funs.h>
#include "/d/Krynn/open/sys/combat.h"

#define SPECIAL_INTERVAL 15
int gLevel, gAlarm_id;

void set_power_level(int lev)
{
    gLevel = lev;
}

int query_power_level()
{
    return gLevel;
}

void create_poison_effect()
{
    set_interval(20);
    set_time(1500);
    set_damage( ({ POISON_MANA, 100, POISON_STAT, SS_INT, POISON_STAT,
	SS_WIS, POISON_USER_DEF, 100 }) );
    set_strength(40);
    set_silent(1);
    set_poison_type("disease");
    recovery = 1;
}

void init()
{
    add_action("do_search", "search");
    add_action("do_look", "exa");
    add_action("do_look", "examine");
    add_action("do_look", "l");
    add_action("do_look", "look");
    gAlarm_id = set_alarm(10.0, 0.0, "special_function");
    ::init();
}

int do_search()
{
    if (query_power_level() < 1)
	return 0;

    if (random(E(TO)->query_stat(SS_DIS)) > (query_power_level() * 7 + 30))
	return 0;

    E(TO)->catch_msg("You try to search, but your mind throbs so intensely that "+
      "you cannot focus yourself enough to make the effort worthwile.\n");
    return 1;
}

int do_look()
{
    if (query_power_level() < 3)
	return 0;

    if (random(E(TO)->query_stat(SS_DIS)) > (query_power_level() * 5 + 30))
	return 0;

    E(TO)->catch_msg("Your mind is so clouded and in turmoil that you cannot "+
      "even study your surroundings effectively.\n");
    return 1;
}

mapping query_introduced()
{
    if (query_power_level() < 5)
	return E(TO)->query_introduced();

    if (random(E(TO)->query_stat(SS_DIS)) > query_power_level() * 5)
	return E(TO)->query_introduced();

    return ([ ]);
}

int attack_function(object target)
{
    object liv = E(TO);

    liv->catch_msg(QCTNAME(target)+" attacks you!\n");
    target->catch_msg(QCTNAME(liv)+" suddenly screams madly and attacks you!\n");
    liv->tell_watcher(QCTNAME(liv)+" suddenly screams madly and attacks "+
      QTNAME(target)+"!\n", target);
    return 1;
}

int combat_function()
{
    object *enemies;
    object target;
    int i;
    string a;

    if (sizeof(FILTER_LIVE( ({ E(TO) }) )) == 0)
	return 0;

    enemies = FILTER_LIVE( ({ E(TO) }) );
    enemies -= ({ E(TO) });

    for (i = 0; i < sizeof(enemies); i++)
    {
	target = enemies[i];
	a = c_can_attack(target, query_verb());

	if (!stringp(a))
	{
	    return attack_function(target);
	}
    }

    return 0;
}

int hysterics_function()
{
    E(TO)->catch_msg("The world seems to sway back and forth slowly; "+
      "out of the sky descends a gaping maw, with lightning racing along "+
      "the exposed fangs and with a tremendous crash of thunder. The maw "+
      "seems intent on you! With a cry of horror, you flee!\n");
    E(TO)->tell_watcher(QCTNAME(E(TO))+" pales as "+PRONOUN(E(TO))+" he stares "+
      "into the sky. Suddenly, "+PRONOUN(E(TO))+" he lets out a terrible "+
      "cry of horror!\n");
    E(TO)->run_away();
    E(TO)->run_away();
    E(TO)->run_away();
    return 1;
}

public void timeout()
{
    if (silent < 2)
    {
	tell_object(poisonee, "The coldness retreats, leaving you in "+
	  "control of your mind.\n");
    }

    remove_alarm(a_dam);

    if (gAlarm_id)
	remove_alarm(gAlarm_id);

    set_alarm(1.0, 0.0, remove_object);
}

public void tell_damage_player(int phit, string str)
{
    if (silent > 1)
    {
	return;
    }

    if (phit > 90)
    {
	tell_object(poisonee, "Your head throbs with such violence "+
	  "that you feel you must be dying.\n");
	return;
    }

    if (phit > 75)
    {
	tell_object(poisonee, "Your head aches terribly, and you "+
	  "cannot seem to focus on anything.\n");
	return;
    }

    tell_object(poisonee, "Your head starts hurting badly.\n");
    return;
}

public int special_function()
{
    gAlarm_id = set_alarm(itof(SPECIAL_INTERVAL), 0.0, "special_function");

    if (query_power_level() >= 8 && !random(3))
	if (random(E(TO)->query_stat(SS_DIS)) < query_power_level() * 7)
	{
	    set_alarm(2.0, 0.0, "combat_function");
	    return 1;
	}

    if (query_power_level() > 6 && !(random(3)))
    {
	if (random(E(TO)->query_stat(SS_DIS)) < query_power_level() * 7)
	    set_alarm(2.0, 0.0, "hysterics_function");
    }
}

public void start_poison()
{
    poisonee = environment(this_object());

    /* Find out who owns us */
    if (!living(poisonee))
    {
	/* If they aren't living, we punt. */
	remove_object();
	return;
    }

    if (silent < 2)
    {
	tell_object(poisonee, "You feel a coldness grip your mind!\n");
    }

    add_prop(OBJ_I_NO_DROP, no_drop);
    add_prop(OBJ_I_NO_GIVE, "Give what to whom?\n");

    if (interval)
    {
	a_dam = set_alarm((interval / 2.0) + (rnd() * interval), 0.0,
	  damage_player);
    }

    a_time = set_alarm(p_time, 0.0, timeout);
}

/*
* Function name: query_poison_recover
* Description  : To add more information to the recover string, you should
*                mask this function to return that information. Do not
*                make a call to ::query_poison_recover!
* Returns      : string - the extra recover string.
*/
public string query_poison_recover()
{
    string a = query_power_level()+"";
    return a;
}

/*
* Function name: init_posion_recover
* Description  : To add more information to the recover string, you should
*                mask this function to process that information after you
*                have added it with query_poison_recover().
* Arguments    : string arg - the extra recover string.
*/
public void init_poison_recover(string arg)
{
    if (!arg)
	arg = 0;

    set_power_level(atoi(arg));
}

public string stat_object()
{
    float time_left = 0.0;
    mixed arr;

    if (a_time &&
      sizeof(arr = get_alarm(a_time)))
    {
	time_left = arr[2];
    }

    return ::stat_object() +
    "Time      : " + ftoa(p_time) + "\n" +
    "Time left : " + ftoa(time_left) + "\n" +
    "Interval  : " + ftoa(interval) + "\n" +
    "Strength  : " + strength + "\n" +
    "Type      : " + type + "\n" +
    "Silent    : " + silent + "\n" +
    "Level     : " + query_power_level() + "\n";
}

