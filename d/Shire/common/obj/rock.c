/*
 * Now, rocks are cool, you can do so lot with'em..
 * You should at least be able to throw them, and we
 * use them for spell ingredients. So, why not make an
 * inheritable rock object? Here it comes.. Code is mostly
 * stolen from Tricky's smallrock.c
 *
 * Sir Rogon.
 *
 * Now, what is the damage done with rocks? The heavier it is,
 * the more damage, but less easy to hit. A SS_WEP_MISSILE will
 * help, as will dexterity and strength.
 *
 * Corrected rock to prevent non-living items from hunting ;)
 *                                 Morinir 23/4 1996
 *
 * Rocks are now recoverable, keepable and in a heap.
 * They are cloned in the following locations:
    /d/Shire/eastroad/western/stonebows
    /d/Shire/eastroad/western/er9s
    /d/Shire/eastroad/western/er5s
    /d/Shire/eastroad/western/er2s
    /d/Shire/eastroad/western/er16n

 * -- Finwe May 2004
 */

inherit "/std/heap";
inherit "/lib/keep";
 
#include "defs.h"
#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>
#include <formulas.h>
#include <cmdparse.h>
#include <stdproperties.h>
#include <comb_mag.h>
#include <tasks.h>

string
long_description()
{
    return "The gray rock" + 
        ((num_heap() == 1) ? " is " : "s are ") + "small. " +  
        ((num_heap() == 1) ? "It looks " : "They look ") + "completely useless.\n";
}

void
create_rock()
{
    set_name( ({ "rock","stone" }) );
    set_adj( ({ "small", "gray" }) );
    set_short("small grey rock");
    set_long(long_description);
    set_keep(1);
}

nomask void
create_heap()
{
    set_heap_size(1);

    add_prop(HEAP_S_UNIQUE_ID, "shire_rock");

    /* Weight of a single heap item */
    add_prop(HEAP_I_UNIT_WEIGHT, 127);
    /* Volume of a single heap item */
    add_prop(HEAP_I_UNIT_VOLUME, 250);
    /* Value of a single heap item */
    add_prop(HEAP_I_UNIT_VALUE, 0);

    create_rock();

    add_name("_prot_spell_ingr1_");
    /* Uhm, no OBJ_I_WEIGHT for heaps. /Mercade
    if (!query_prop(OBJ_I_WEIGHT))
	add_prop(OBJ_I_WEIGHT, 300 + random(300));
     */
}

void
spell_attack(object tp, object target)
{
    int wc_pen, skill, weight, weight_allow, extra_diff;
    mixed res;
    string how;

    weight = query_prop(OBJ_I_WEIGHT);
    weight_allow = STR(tp) * 50;

    if (weight > weight_allow)
	extra_diff = weight * 100 / weight_allow;
    else
	extra_diff = 0;

    if (tp->resolve_task(TASK_ROUTINE + extra_diff, 
	({ TS_DEX, SS_WEP_MISSILE }),
	target, ({ TS_DEX, SS_AWARENESS })) < 0)
    {
	tp->catch_msg("You throw the " + short() + " at " + QTNAME(target) + 
	  " but miss " + HIM_HER(target) + ".\n");
	target->catch_msg(QCTNAME(tp) + " throws a " + short() + " at you "
	  + "but misses you.\n");
	say(QCTNAME(tp) + " throws a " + short() + " at " + QTNAME(target) + 
	  " but misses " + HIM_HER(target) + ".\n", ({tp,target}));
	tell_room(ENV(tp), "The " + short() +" falls on the floor.\n");
	move(ENV(tp)); /* And drop on the floor */
	return;
    }
    // Did hit! :-)

    skill = tp->query_skill(SS_WEP_MISSILE);
    if (skill < 7)
	skill = 7;

    wc_pen = weight / 50;

    if (wc_pen > 40) wc_pen = 40;
    if (wc_pen < 1) wc_pen = 1;

    res = target->hit_me(F_PENMOD(wc_pen, skill), W_BLUDGEON, tp, -1);

    if (res[0] > 40)
	how = " extremely hard.";
    else if (res[0] > 25)
	how = " very hard.";
    else if (res[0] > 12)
	how = " hard.";
    else
	how = ".";

    tp->catch_msg("You throw the " + short() + " at " + QTNAME(target) + 
      " and hit " + HIM_HER(target) + how + "\n");
    target->catch_msg(QCTNAME(tp) + " throws a " + short() + " at you "
      + "and hits you" + how + "\n");
    say(QCTNAME(tp) + " throws a " + short() + " at " + QTNAME(target) + 
      " and hits " + HIM_HER(target) + how + "\n", ({target,tp}));
    tell_room(ENV(tp), "The small rock falls to the ground.\n");
    move(ENV(tp)); /* And drop on the floor */
}

int
do_throw(string str)
{
    int dex;
    string tname, tobj, tmp, what;
    object tp, env;
    mixed target;

    tp = this_player();
    env = environment(tp);

    if (environment() != tp)
	return notify_fail("First get the " + short(tp) + ".\n");

    if (tp->query_prop(LIVE_O_SPELL_ATTACK))
	return notify_fail("You are busy attacking!\n");

    if (!str ||
      (!sscanf(str,"at %s",tmp) &&
	!sscanf(str,"%s at %s",what, tmp) &&
	!sscanf(str,"%s at %s",what, tmp)))
	return notify_fail("Throw at something or someone.\n");

    if (stringp(what) && !id(what))
	return notify_fail("Throw what?\n");

    str = lower_case(tmp);
    target = present(str, env);
    if (!target || !CAN_SEE(TP, target))
	return notify_fail("No '" + str + "' here.\n");

    if (target == tp)
	return notify_fail("Why would you want to throw at yourself?\n");

    if (NPATTACK(target))
	return notify_fail("You cannot attack that way here.\n");

    if (living(target))
    {
	if (!F_DARE_ATTACK(TP, target))
	    return notify_fail("Uh.. Eh. Nope, you simply dare not attack " + 
	      QTNAME(target) + "!\n");
	TP->catch_msg("You prepare to throw the " + short() + " at " +
        QTNAME(target) + "!\n");
	target->catch_msg(QCTNAME(tp) + " grins while aiming " + HIS_HER(tp) +
	  " " + short() + " at you!\n");
	tell_room(ENV(tp), QCTNAME(TP) + " grins while aiming " + HIS_HER(tp) + 
	  " " + short() + " at " + QTNAME(target) + ".\n", ({ tp, target }));
	TP->add_prop(LIVE_O_SPELL_ATTACK, TO);
	TP->attack_object(target);
	return 1;
    }
    else
    {
	tname = "the " + target->short();
	tobj  = "it";

	dex = tp->query_stat(SS_DEX);
	if (dex + random(dex) > 25)
	{
	    tp->catch_msg("You throw the "+short()+" at " + tname + " and hit "
	      + tobj + ".\n");
	    target->catch_msg(QCTNAME(tp) + " throws a "+short()+" at you "
	      + "and hits you.\n");
	    say(QCTNAME(tp) + " throws a "+short()+" at " + tname + " and hits "
	      + tobj + ".\n",({target,tp}));

	    //	    tp->attack_object(target);
	    //	    target->hit_me(F_PENMOD(7,7),W_IMPALE,tp,0);
	}
	else
	{
	    tp->catch_msg("You throw the "+short()+" at " + tname + 
	      " but miss " + tobj + ".\n");
	    target->catch_msg(QCTNAME(tp) + " throws a "+short()+" at you "
	      + "but misses you.\n");
	    say(QCTNAME(tp) + " throws a "+short()+" at " + tname + 
	      " but misses " + tobj + ".\n",({tp,target}));
	}

	TO->move(ENV(TP));

	return 1;
    }
}

void
init()
{
    ::init();
    add_action(do_throw, "throw");
}

/*
void init_recover(string arg)
{
    init_keep_recover(arg);
}

string query_recover()
{
    return MASTER + ":" + query_keep_recover();
}
*/

/* The following are necessary for an autoloading heap.  If you
 * don't need an autoloading heap, you don't need to include these
 * at all.
 */

/* 
 * This is called when an autoloading object is reloaded.  We use
 * it to restore the heap to it's correct size.
 */
void
init_arg(string arg)
{
    set_heap_size(atoi(arg));
}

/*
 * This is called when the player is logging out.  We use it to
 * store the size of the heap so that we can restore it to the right
 * amount when the player logs back in.
 */
string
query_auto_load()
{
    return MASTER + ":" + num_heap();
}

