/*
 * The poison cloud created by the sulambar spell
 *
 * Olorin, 12-jan-1994
 * - Added logging of players being poisoned to /d/Gondor/log/curses
 *   Elessar, Oct 11th 1995
 */
#pragma strict_types

inherit "/std/object";

#include <filter_funs.h>
#include <macros.h>
#include <poison_types.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <tasks.h>

#include "/d/Gondor/defs.h"
#include "/d/Gondor/common/guild2/spells/spell_defs.h"

//	Prototypes.
void     test_run_away(object victim);

//	Global variables.
static int     gDisperse,
gPoison;

void
create_object()
{
    set_name("cloud");
    add_name(({"poison cloud", "poison","_Morgul_Sulambar_Cloud"}));
    add_adj(({"poison", "yellow", "stinking"}));
    set_short("pale yellow cloud");
    set_pshort("pale yellow clouds");
    set_long(BSN("A pale yellow cloud is hanging in the air here. " +
	"It fills the area with an incredible stench reminding you " +
	"of foul eggs and carbide."));

    add_prop(OBJ_I_WEIGHT, 50);
    add_prop(OBJ_I_VOLUME, 1000000);
    add_prop(OBJ_M_NO_GET, "@@no_get");
    add_prop(OBJ_S_WIZINFO,"@@wizinfo");
}

public int
query_time_left()
{
    mixed   call = get_alarm(gDisperse);

    if (sizeof(call))
	return ftoi(call[2]);
    return 0;
}

string
no_get()
{
    object tp = this_player();

    say(QCTNAME(tp) + " is waving around in the empty air like a fool.\n", tp);

    return "You try to get a grip on the cloud.\n" +
    "But all you manage is to wave around in the air stupidly.\n";
}

void
do_poison(object victim)
{
    object  poison;
    int     result,
    poison_res;

    if ((!victim->query_prop(MORGUL_I_SULAMBAR_RES)) &&
      (!victim->query_prop(LIVE_I_UNDEAD)))
    {
	victim->catch_msg("When you take a breath, the stinking cloud makes you feel dizzy.\n");
	tell_room(ENV(TO), QCTNAME(victim) + " suddenly looks quite pale and sick.\n", victim);
    }

    poison_res = victim->query_magic_res(MAGIC_I_RES_POISON);
    victim->add_prop("_tmp_magic_i_res_poison", poison_res);
    set_alarm(2.0, 0.0, &victim->remove_prop("_tmp_magic_i_res_poison"));
    // Can the victim withstand the poisoning?
    // The strange treatment of the property is necessary to prevent
    // a runtime error in find_drm()
    if ((result = victim->resolve_task(TASK_DIFFICULT,
	  ({ TS_CON, SKILL_AVG, SS_ELEMENT_EARTH, SS_FORM_ABJURATION, SKILL_END,
	    "_tmp_magic_i_res_poison" })) > 0) || 
      victim->query_prop(MORGUL_I_SULAMBAR_RES) ||
      victim->query_prop(LIVE_I_UNDEAD))
    {
#if DEBUG
	victim->catch_msg("DEBUG: poison " + result + "\n");
#endif
	return;
    }

#if DEBUG
    victim->catch_msg("DEBUG: poison " + result + "\n");
#endif
    result *= -1;
    if (result <  50)
	result =  50;
    if (result > 100)
	result = 100;

    if (victim->query_npc())
	set_alarm(2.0, 0.0, &test_run_away(victim));

    if (random(4) &&
      (objectp(poison = present("Morgul_Sulambar_Poison", victim))))
    {
	if (poison->query_interval() > 5)
	{
	    //          victim->catch_msg("You have been poisoned!\n");
	    if (poison->query_strength() > 100)
		poison->set_interval(MAX(poison->query_interval()-1, 5));
	    else
		poison->set_strength(poison->query_strength()
		  + result/2 + random(result));
	}
	return;
    }

    seteuid(getuid());
    poison = clone_object(MORGUL_S_SULAMBAR_POISON);
    poison->set_time(2 * query_time_left() + 720 + 3*result);
    poison->set_strength(result + random(result));
    poison->move(victim);
    poison->start_poison();
    if (victim->query_npc())
	return;
    log_file("curses", victim->query_name() + " poisoned by Sulambar cloud in "
      + file_name(environment(victim)) + ". " + ctime(time()) + ".\n", 0);
    return;
}

void
init()
{
    ::init();
    do_poison(TP);
}

void
do_try_poison(int interval)
{
    object *victims;
    int     i, s;

    victims = FILTER_LIVE(all_inventory(ENV(TO)));

    for (i = 0, s = sizeof(victims); i < s; i++)
	do_poison(victims[i]);

    interval++;
    if (!gPoison || !sizeof(get_alarm(gPoison)))
	gPoison = set_alarm(itof(interval/2 + random(interval)), 0.0,
	  &do_try_poison(interval));
}

void
do_start_disperse()
{
    tell_room(ENV(TO), "The pale yellow cloud seems to get thinner.\n");
}

void
do_disperse()
{
    tell_room(ENV(TO),
      "The pale yellow cloud gets thinner and thinner.\n" +
      "It seems to have completely disappeared now, and you can breathe more freely again.\n");
    remove_object();
}

string
wizinfo()
{
    return "This is a poison cloud courtesy of the Morgul Mages.\n" +
    "It will disperse in "+query_time_left()+" seconds.\n";
}

void
test_run_away(object victim)
{
    int     r;

    if (!objectp(victim) || !present(victim, ENV(TO)))
	return;

    r = victim->query_stat(SS_CON) * 100 / victim->query_base_stat(SS_CON);
    r = 100 - r;
    r *= 2;

    if (random(100) < r)
	victim->run_away();
}

varargs void
set_time(int time, int interval)
{
    if ((!time) || (time < 60))
	time = 60;
    if (!interval)
	interval = 20;
    gDisperse = set_alarm(itof(time), 0.0, do_disperse);
    set_alarm(itof(time - 20), 0.0, do_start_disperse);
    gPoison   = set_alarm(itof(interval/2 + random(interval)), 0.0, 
      &do_try_poison(interval));
}


