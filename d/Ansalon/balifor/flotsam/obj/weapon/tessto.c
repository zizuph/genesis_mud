/* This file has some bits taken from Jeremiahs 
*code of Verminaards mace.*/

#include <stdproperties.h>
#include <ss_types.h>
#include <wa_types.h>
#include <macros.h>
#include <options.h>
#include <tasks.h>
#include <formulas.h>
#include <filter_funs.h>
#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/balifor/flotsam/local.h"

inherit "/std/weapon";
inherit "/lib/keep";

int wielding_type;

void
create_weapon()
{
    set_name("tessto");
    add_name("club");
    set_short("spiked steel tessto");
    set_long("The tessto is a six foot long studded club with a loop " +
      "of rope at its hilt. Traditionally a weapon of wood crafted " +
      "and used by the great Bloodsea minotaurs, this weapon has " +
      "been redesigned into a well balanced steel version, but is " +
      "still rather heavy and would need great strength to wield " +
      "offensively. Even so, you get the feeling that minotaurs " +
      "would have little trouble changing their grip on this weapon " +
      "and wielding it one handed!\n");

    set_default_weapon(44,49, W_CLUB, W_BLUDGEON, W_BOTH);
    add_prop(OBJ_M_NO_BUY, 1);
    add_prop(OBJ_I_IS_MAGIC_WEAPON, 1);
    add_prop(MAGIC_AM_MAGIC, ({ 80, "enchantment"}));
    add_prop(MAGIC_AM_ID_INFO, ({"The spiked steel tessto seems " +
	"to be magical.\n",1,"It has been enchanted so that it is " +
	"much lighter than a normal weapon of its size, but even " +
	"so only someone of forceful strength can actually wield it.\n",
	10,"Its large size makes it impossible to be wielded by " +
	"the smaller races, namely dwarves, gnomes, goblins, and " +
	"kenderkin. \n",20,"It has been enchanted so that it strikes " +
	"with great accuracy and does great damage to foes.\n",35}));


    add_prop(OBJ_I_VOLUME, 1500);
    add_prop(OBJ_I_WEIGHT, 25000);
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(50,35) + random(500));

    set_likely_dull(1);
    set_likely_corr(1);
    set_likely_break(1);

    set_wf(TO);
    set_pm(({-3,0,3}));

    seteuid(getuid(TO));
}


void
wield_message1()
{
    if(E(TO) != wielder)
	return;
    wielder->catch_msg("The spikes on the tessto glow red " +
      "as you wield this mighty weapon.\n");

    tell_room(E(wielder),"The spikes of " + QTNAME(wielder) +
      "'s tessto glow red as " + PRONOUN(wielder) +
      " wields the mighty weapon.\n", wielder);
}




mixed 
wield(object what)
{
    if(TP->query_stat(SS_STR) <= 119)
	return "You are not strong enough to to wield the spiked steel tessto.\n";

    if(member_array(TP->query_race_name(), ({"goblin","hobbit","dwarf",
        "halfling","gnome"})) != -1)
	return "You are too short to wield the spiked steel tessto!\n";
    
    set_alarm(1.0, 0.0, wield_message1);
    return 0;
}

/* tell_watcher is rumored to exist in each living. We shall try this.
 *
static void
tell_watcher(string str, object enemy)
{
    object me,*ob;
    int i;

    me = query_wielded();
    ob = FILTER_LIVE(all_inventory(environment(me))) - ({ me });
    ob -= ({ enemy });
    for (i = 0; i < sizeof(ob); i++)
	if (!ob[i]->query_option(OPT_BLOOD) && CAN_SEE_IN_ROOM(ob[i]))
	{
	    if (CAN_SEE(ob[i], me))
		ob[i]->catch_msg(str);
	    else
		tell_object(ob[i], "Someone is hit by someone.\n");
	}
}
*/

public mixed
did_hit(int aid,string hdesc,int phurt,object enemy,int dt,int phit,int dam)
{
    object blinding;

    ::did_hit(aid, hdesc, phurt, enemy, dt, phit, dam);

    switch(phurt)
    {
    case -1:
    case -2:
	if (!wielder->query_option(OPT_GAG_MISSES))
	{
	    wielder->catch_msg("You swing your " + short() + " at " + QTNAME(enemy) +
	      " but miss.\n");
	}
	if (!enemy->query_option(OPT_GAG_MISSES))
	{
	    enemy->catch_msg(QCTNAME(wielder) + " swings the " + short() +
	      " at you but misses.\n");
	}
	wielder->tell_watcher_miss(QCTNAME(wielder) + " swings the " + short() +
	  " at " + QTNAME(enemy) + " but misses.\n", enemy);
	break;

    case 0:
	wielder->catch_msg("You barely scratch " + QTNAME(enemy) + " with " +
	  "the " + short() + ".\n");
	enemy->catch_msg(QCTNAME(wielder) + " barely scratches you with the " +
	  short() + ".\n");
	wielder->tell_watcher(QCTNAME(wielder) + " barely scratches " + 
	    QTNAME(enemy) + " with the " + short() + ".\n", enemy);
	break;

    case 1..4:
	wielder->catch_msg("You graze the " + hdesc + " of " +
	  QTNAME(enemy) + " with a savage swing of your " + 
	  short() + ".\n");
	enemy->catch_msg(QCTNAME(wielder) + " grazes your " + hdesc +
	  " with a savage swing of the " + short() + ".\n");
	wielder->tell_watcher(QCTNAME(wielder) + " grazes the " + hdesc +
	  " of " + QTNAME(enemy) + " with a savage swing of the " +
	  short() + ".\n",enemy);
	break;

    case 5..9:
	wielder->catch_msg("You pound the " + hdesc + " of " +
	  QTNAME(enemy) + " mightily with your " + short() + ", bruising " + POSSESSIVE(enemy) +
	  " " + hdesc + " moderately.\n");

	enemy->catch_msg(QCTNAME(wielder) + " pounds your " + hdesc + " with a " +
	  "mighty swing of the " + short() + ", bruising it moderately.\n");
	wielder->tell_watcher(QCTNAME(wielder) + " pounds the " + hdesc +
	  " of " + QTNAME(enemy) + " with the " + short() + 
	  ", bruising it moderately.\n",enemy);
	break;

    case 10..19:
	wielder->catch_msg("You hurt " + QTNAME(enemy) + " badly with " +
	  "a wicked blow of your " + short() + ", tearing bloody trails " +
	  "along " + POSSESSIVE(enemy) + " " + hdesc +
	  " with its spikes.\n");
	enemy->catch_msg(QCTNAME(wielder) + " hurts you badly with " +
	  "the " + short() + ", tearing bloody trails along your " +
	  hdesc + " with its spikes.\n");
	wielder->tell_watcher(QCTNAME(wielder) + " hurts " + QTNAME(enemy) +
	  " badly with the " + short() + ", tearing bloody trails " +
	  "along their " + hdesc + " with its spikes.\n",enemy);
	break;

    case 20..29:
	wielder->catch_msg("You tear bloody chunks from the " +
	  hdesc + " of " + QTNAME(enemy) + " with the spikes " +
	  "of your " + short() + ".\n");
	enemy->catch_msg(QCTNAME(wielder) + " tears bloody chunks " +
	  " from your " + hdesc + " with the " + short() +
	  "!\n");
	wielder->tell_watcher(QCTNAME(wielder) + " tears bloody chunks " +
	  "from the " + hdesc + " of " + QTNAME(enemy) + " with " +
	  "the " + short() + "!\n",enemy);
	break;

    case 30..49:
	wielder->catch_msg("You hammer the " + hdesc + " of " +
	  QTNAME(enemy) + " with a powerful swing of your " +
	  short() + ", breaking many bones.\n");
	enemy->catch_msg(QCTNAME(wielder) + " hammers your " + hdesc +
	  " with a powerful swing of the " + short() + ", breaking many " +
	  "of your bones!\n");
	wielder->tell_watcher(QCTNAME(wielder) + " hammers the " + hdesc + 
	  " of " + QTNAME(enemy) + " with a powerful swing of the " +
	  short() + ", breaking many bones!\n",enemy);
	break;

    case 50..69:
	wielder->catch_msg("You violently crush the " + hdesc + 
	  " of " + QTNAME(enemy) + " into a shapeless bloody mass " +
	  "with your " + short() + ".\n");
	enemy->catch_msg(QCTNAME(wielder) + " violently crushes your " +
	  hdesc + " into a shapeless bloody mass with the " + short() + ".\n");
	wielder->tell_watcher(QCTNAME(wielder) + " violently crushes " +
	  "the " + hdesc + " of " + QTNAME(enemy) + " into a " +
	  "shapeless bloody mass with the " + short() + ".\n",enemy);
	break;

    case 70..89:
	wielder->catch_msg("You smash the " + hdesc + " of " +
	  QTNAME(enemy) + " into the ground, mortally wounding " +
	  OBJECTIVE(enemy) + " " +
	  "with a devastating swing of your " + short() + ".\n");
	enemy->catch_msg(QCTNAME(wielder) + " smashes your " +
	  hdesc + " into the ground with a devastating blow of the " +
	  short() + ". Things are starting to look dimmer, and " +
	  "you are on the verge of falling into a deep darkness.\n");
	wielder->tell_watcher(QCTNAME(wielder) + " smashes the " + hdesc +
	  " of " + QTNAME(enemy) + " into the ground with a " +
	  "devastating swing of the " + short() + ".\n",enemy);
	break;

    default:
	wielder->catch_msg("You hear the sickening sound of bones " +
	  "breaking, as your " + short() + " massacres the " + hdesc + 
	  " of " + QTNAME(enemy) + ". The spikes penetrate deep " +
	  "into " + POSSESSIVE(enemy) + " flesh, leaving blood " +
	  "flowing from deep gaping wounds in the shattered limb.\n");
	enemy->catch_msg("You hear the sickening sound of your bones " +
	  "breaking as " + QTNAME(wielder) + " massacres your " + 
	  hdesc + " with " + POSSESSIVE(wielder) + " " + short() + 
	  " The spikes penetrate deep into your flesh, leaving blood " +
	  "flowing from deep gaping wounds in the shattered limb.\n");
	wielder->tell_watcher("You hear the sickening sound of bones breaking " +
	  "as " + QTNAME(wielder) + " massacres the " + hdesc +
	  " of " + QTNAME(enemy) + " with " + POSSESSIVE(wielder) + 
	  " " + short() + ". The spikes penetrate deep into the " +
	  "flesh of " + QTNAME(enemy) + ", leaving blood flowing " +
	  "from the shattered limb.\n", enemy);
	break;

    }


    return 1;
}


varargs void
remove_broken(int silent = 0)
{
    if (calling_function() == "item_expiration_break") 
        ::remove_broken(silent);

    return;
}


int
set_dull(int du)
{
    return 0;
}

int
change_handle(string str)
{

    if (str != "grip")
    {
	NF("Change what? The grip?\n");
	return 0;
    }

    if (E(TO) != TP)
    {
	NF("Perhaps you should pick "+short()+" up first!\n");
	return 0;
    }

    if (query_wielded())
    {
	NF("You can not change the grip on the handle of the "+short()+" when you are "+
	  "wielding it.\n");
	return 0;
    }

    if(TP->query_race_name() != "minotaur")
    {
	write("You try and change your grip on the tessto to wield it one-handed, however "+
	  "find it too awkward. Only a minotaur would know how best to wield this weapon in "+
	  "one hand.\n");
	return 1;
    }

    if (wielding_type == 1)
    {
	wielding_type = 0;
	set_hands(W_BOTH);
	//        TP->update_weapon(TO);
	write("You change the handle back from one-handed to two-handed.\n");
	say(QCTNAME(TP) + " changes "+HIS(TP)+" grip around the handle of "+
	  "the "+short()+".\n");
	return 1;
    }

    if (TP->resolve_task(TASK_DIFFICULT, ({TS_STR, SS_AWARENESS})) > 0)
    {   /* Success */
	wielding_type = 1;
	set_hands(W_ANYH);
	//        TP->update_weapon(TO);
	write("You change the handle from two-handed to one-handed.\n");
	say(QCTNAME(TP) + " changes "+HIS(TP)+" grip around the handle of "+
	  "the "+short()+".\n");
	return 1;
    }
    else
    {
	write("You fail to wield the weapon in one hand.\n"+ 
	  "You feel exhausted.\n");
	TP->add_fatigue(-50);
    }
    return 1;
}

void
leave_env(object from, object to)
{
    ::leave_env(from,to);
    wielding_type = 0;
    set_hands(W_BOTH);
    //    TO->update_weapon(TO);
}

void
init()
{
    ::init();
    add_action(change_handle, "change");


}
