inherit "/std/weapon";
inherit "/lib/keep";

#include "/d/Ansalon/common/defs.h"
#include <wa_types.h>
#include <ss_types.h>
#include <macros.h>
#include <options.h>
#include <formulas.h>

#include "../../local.h"

#define WEAPON_HIT 20
#define WEAPON_PEN 34

object wielder;

void
create_weapon()
{
    set_name("dagger");
    add_name("carnage");
    // set_pname("daggers");
    set_adj("black");
    add_adj("double-bladed");
    set_short("black double-bladed dagger");
    set_long("This vicious looking weapon consists of two " +
      "blades, a double-edged slashing blade on one end of " +
      "the leather-wrapped handle, and a thin steel piercing " +
      "blade on the other end. Along the slashing blade is " +
      "some writing that glows slightly.\n");
    add_cmd_item("writing","read","@@read_runes");
    add_prop(OBJ_I_IS_MAGIC_WEAPON, 1);
    add_prop(MAGIC_AM_MAGIC,({ 50, "enchantment"}));
    add_prop(MAGIC_AM_ID_INFO,({"This dagger has " +
	"been enchanted by the evil elven sorcerer Satania Caltian. " +
	"It has been created with the darkest magics, and seems " +
	"to have a personality of its own, refusing to allow " +
	"anyone who is not truely evil to wield it. " +
	"Its enchantments make it as deadly as a good sword.\n",15}));

    set_hit(WEAPON_HIT);
    set_pen(WEAPON_PEN);
    set_wt(W_KNIFE);
    set_dt(W_IMPALE | W_SLASH);
    set_hands(W_ANYH);
    set_wf(TO);

    add_prop(OBJ_I_WEIGHT, 1000);
    add_prop(OBJ_I_VOLUME, 1000);
    add_prop(OBJ_I_VALUE,F_VALUE_WEAPON(WEAPON_HIT,WEAPON_PEN));

    seteuid(getuid(TO));
}

int
read_runes()
{
    if(TP->query_skill(SS_LANGUAGE) < 20)
    {
	write("You are unable to work out what the writing on " +
	  "the black double-bladed dagger says.\n");
	return 1;
    }
    write("Along the slashing blade of the black double-bladed " +
      "dagger has been scribed in the elven Silvanesti " +
      "language 'I name thee Carnage! May you live up to your " +
      "name'.\n");
    return 1;
}

void
wield_message()
{
    if(E(TO) != wielder)
	return;
    wielder->catch_msg("The black double-bladed dagger humms in " +
      "your hand as you wield it.\n");

}

mixed
wield(object what)
{
    if(TP->query_alignment() > -300)
	return "The black double-bladed dagger refuses to allow " +
	"you to wield it.\n";

    wielder = TP;
    set_alarm(1.0, 0.0, "wield_message");
}

mixed
unwield(object what)
{
    return 0;
}

public varargs int
did_hit(int aid, string hdesc, int phurt, object enemy, int dt, int phit, int dam)
{

    object blinding;

    ::did_hit(aid, hdesc, phurt, enemy, dt, phit, dam);

    if (!objectp(wielder) || !objectp(enemy))
	return 0;

    switch(phurt)
    {
    case -1:
    case -2:
	if (!wielder->query_option(OPT_GAG_MISSES))
	{
	    wielder->catch_tell("You miss " +enemy->query_the_name(wielder)+ " with your " +
		short() + ".\n");
	}
	if (!enemy->query_option(OPT_GAG_MISSES))
	{
	    enemy->catch_tell(wielder->query_the_name(enemy) + " misses you with " +
		POSSESSIVE(wielder) + " " + short() + ".\n");
	}
	wielder->tell_watcher_miss(QCTNAME(wielder) + " misses " +
	    QTNAME(enemy) + " with " +POSSESSIVE(wielder)+ " " +short()+ ".\n",
	    enemy);
	break;


    case 0..7:
	wielder->catch_tell("You slice a shallow wound in the " +
	  hdesc + " of " +enemy->query_the_name(wielder)+ ".\n");
	enemy->catch_tell(wielder->query_The_name(enemy) + " slices a shallow " +
	  "wound in your " +hdesc+ " with " +POSSESSIVE(wielder)+
	  " " +short() + ".\n");
	wielder->tell_watcher(QCTNAME(wielder) + " slices a shallow wound " +
	  "in the " +hdesc+ " of " +QTNAME(enemy)+ " with " +
	  POSSESSIVE(wielder)+ " " + short() + ".\n",enemy);
	break;

    case 8..29:
	wielder->catch_tell(enemy->query_The_name(wielder) + " flinches as you " +
	  "cut " +OBJECTIVE(enemy)+ " with your " +short()+ ".\n");
	enemy->catch_tell("You flinch as " +wielder->query_the_name(enemy)+ 
	  " cuts you with " +POSSESSIVE(wielder)+ " " +short()+
	  ".\n");
	wielder->tell_watcher(QCTNAME(enemy) + " flinches as " +QTNAME(wielder)+
	  " cuts " +QTNAME(enemy)+ " with the " +short() + ".\n",enemy);
	break;

    case 30..89:
	wielder->catch_tell("Reversing your stroke, you pierce " +
	  "a nasty wound in the " +hdesc+ " of " +enemy->query_the_name(wielder)+
	  " with your " +short()+ ".\n");
	enemy->catch_tell(wielder->query_The_name(enemy) + " reverses " +POSSESSIVE(wielder)+
	  " stroke with " +POSSESSIVE(wielder)+ " " +short()+
	  ", piercing your " +hdesc+ " and creating a nasty wound.\n");
	wielder->tell_watcher(QCTNAME(wielder) + " reverses " +POSSESSIVE(wielder)+
	  " stroke with " +POSSESSIVE(wielder)+ " " +short()+
	  ", piercing a nasty wound in the " +hdesc+ " of " +
	  QTNAME(enemy)+ ".\n",enemy);
	break;

    default:
	wielder->catch_tell("You disembowel " +enemy->query_the_name(wielder)+ 
	  " with your " +short()+ ".\n");
	enemy->catch_tell(wielder->query_The_name(enemy)+ " skillfully " +
	  " disembowels you with " +POSSESSIVE(wielder)+ " " +short()+
	  "!\n");
	wielder->tell_watcher(QCTNAME(wielder) + " disembowels " +
	  QTNAME(enemy)+ " with " +POSSESSIVE(wielder)+ " " +short()+
	  "!\n",enemy);
	break;

    }
    return 1;
}
