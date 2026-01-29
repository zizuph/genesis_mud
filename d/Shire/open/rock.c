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
 * added different types of rocks
 * -- Finwe feb 1999
 */

inherit "/std/object";

inherit "/lib/keep";
 
#include "/d/Shire/common/defs.h"
#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>
#include <formulas.h>
#include <cmdparse.h>
#include <stdproperties.h>
#include <comb_mag.h>
#include <tasks.h>

void
create_rock()
{

    int x,y;
    string *color, *size;

    color = (({"brown", "grey", "black", "white", "pale white", "beige"}));
    size  = (({"smooth", "sharp", "flecked", "cracked", "oval", "sharp"}));

    x = random(sizeof(size));
    y = random(sizeof(color));

    set_name(({"stone","rock"}));
    set_adj(({size[x],color[y]}));
    set_pname(({"stones","rocks"}));
    set_short("small rock");
    set_pshort("small rocks");
    set_long("This is a "+size[x]+" "+color[y]+" rock. " +
	    "It looks utterly useless.\n");

    add_prop(OBJ_I_VALUE, 2 );
    add_prop(OBJ_I_WEIGHT, 127);
    add_prop(OBJ_I_VOLUME, 250);
}

nomask void
create_object()
{
    create_rock();
    add_name("_prot_spell_ingr1_");
    if (!query_prop(OBJ_I_WEIGHT))
	add_prop(OBJ_I_WEIGHT, 300 + random(300));
}

init()
{
    ::init();
    add_action("do_throw","throw");
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


do_throw(string str)
{
    int dex;
    string tname, tobj, tmp, what;
    object tp, env;
    mixed target;

    tp = this_player();
    env = environment(tp);

    if (environment() != tp)
	return notify_fail("First get the " + short() + ".\n");

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
	TP->catch_msg("You prepare to throw the " + short() + " at " + QTNAME(target) + "!\n");
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

