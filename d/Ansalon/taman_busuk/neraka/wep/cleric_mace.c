/*
 * Cleric mace
 *
 */

#include <stdproperties.h>
#include <ss_types.h>
#include <wa_types.h>
#include <macros.h>
#include <options.h>
#include <formulas.h>
#include <filter_funs.h>
#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/balifor/flotsam/local.h"

inherit "/std/weapon";
inherit "/lib/keep";

#define HIT     45
#define PEN     50

create_weapon()
{
    set_name("mace");
    add_name("club");
    set_adj("clawed");
    set_short("clawed mace");
    set_long("The clawed mace has a long description.\n");

    set_hit(HIT);
    set_pen(PEN);
    set_wt(W_CLUB);
    set_dt(W_BLUDGEON | W_SLASH);
    set_hands(W_BOTH);
    
    add_prop(OBJ_M_NO_BUY, 1);
    add_prop(OBJ_I_IS_MAGIC_WEAPON, 1);
    add_prop(MAGIC_AM_MAGIC, ({ 80, "enchantment"}));
    add_prop(MAGIC_AM_ID_INFO,
    ({
        "The clawed mace is enchanted in strange ways.\n", 1,
    }));
    add_prop(OBJ_S_WIZINFO,
        "Wizinfo here.\n");

    add_prop(OBJ_I_VOLUME, 1500);
    add_prop(OBJ_I_WEIGHT, 8000);
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(45,50) + random(1500));

    set_wf(TO);
    set_pm(({0,-3,3}));

    setuid();
    seteuid(getuid());
}


void
wield_message1()
{
    object w;

    w = query_wielded();
    if (!w || !living(w))
        return;
    
    w->catch_tell("The spikes on the tessto glow red " +
      "as you wield this mighty weapon.\n");

    tell_room(environment(w),
        "The spikes of " + QTNAME(w) +
        "'s tessto glow red as " + PRONOUN(w) +
        " wields the mighty weapon.\n", w);
}

mixed 
wield(object what)
{
    set_alarm(1.0, 0.0, "wield_message1");
    return 0;
}

public mixed
did_hit(int aid,string hdesc,int phurt,object enemy,int dt,int phit,int dam)
{
    ::did_hit(aid, hdesc, phurt, enemy, dt, phit, dam);

    switch(phurt)
    {
        case -1:
        case -2:
        	if (!wielder->query_option(OPT_GAG_MISSES))
    	    {
                wielder->catch_msg("You swing your " + short() + " at " +
                QTNAME(enemy) + " but miss.\n");
            }
            if (!enemy->query_option(OPT_GAG_MISSES))
            {
                enemy->catch_msg(QCTNAME(wielder) + " swings the " + short() +
                " at you but misses.\n");
            }
            wielder->tell_watcher_miss(QCTNAME(wielder) + " swings the " +
            short() + " at " + QTNAME(enemy) + " but misses.\n", enemy);
            break;

    case 0:
	wielder->catch_msg("You scratch " + QTNAME(enemy) + " with " +
	"the " + short() + ".\n");
	enemy->catch_msg(QCTNAME(wielder) + " scratches you with the " +
	short() + ".\n");
	wielder->tell_watcher(QCTNAME(wielder) + " scratches " + QTNAME(enemy) +
	" with the " + short() + ".\n", enemy);
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
	  " the " + hdesc + " of " + QTNAME(enemy) + " into a " +
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
