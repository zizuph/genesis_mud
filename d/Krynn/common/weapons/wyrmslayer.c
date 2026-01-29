/*
Wyrmslayer.c
------------

Coded ..........: 95/04/23
By .............: Jeremiah

Revision history: Morrigan, 97/03/26:
                  Aridor,   97/10/16: Added /lib/keep
      Auberon and Kessie,   01/07/12: Updated info and powers.
                  Navarre,  07/08/16: Upgraded to fit the effort for obtaining
		                      it, and to be more up to date with today's
				      weapons.
		  Navarre,  09/04/26: Lowering the speed on the weapon.
				      
This weapons looks very much like Wyrmsbane (Redeemer), except that
it is a little larger. It normaly functions as a two handed sword.
Like Wyrmsbane, Wyrmslayer is immune to the imprisoning effect of a 
dying baaz draconian. The sword causes double damage against any
dragon or draconian. In addition, a player wielding Wyrmslayer
gains a 15 % resistance bonus to all saves against dragon breath attacks
as well as spells cast by them. Wyrmslayer does have the disconcerting
tendency to buzz aggressively whenever it is brought within 3'
of a true dragon (not draconian). This buzzing sound is loud enough
to be heard clearly and always awakens a sleeping dragon.

*/

inherit "/std/weapon";
inherit "/lib/keep";

#include <ss_types.h>
#include <wa_types.h>
#include <formulas.h>
#include <stdproperties.h>
#include <macros.h>
#include <filter_funs.h>
#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/pax/local.h"

object wielder;
int id = 100 + random(25);

void
create_weapon()
{
    set_name("wyrmslayer");
    add_name(({"blade", "sword"}));
    set_adj(({"ancient", "two-handed"}));
    set_short("@@short_desc@@");
    set_pshort("ancient two-handed swords");
    set_long("@@long_desc@@");

    set_default_weapon(45, 45, W_SWORD, W_SLASH | W_IMPALE, W_BOTH);
    set_likely_break(0);
    set_likely_dull(0);
    set_likely_corr(0);
    set_wf(TO);
    add_prop(OBJ_M_NO_BUY, 1);
    add_prop(OBJ_I_IS_MAGIC_WEAPON, 1);
    add_prop(OBJ_S_WIZINFO,
      "This is the ancient sword of Kith-kanan, crafted during " +
      "the Second Dragon War in Silvanesti. This weapon is highly" +
      "magical. It deals double damage when fighting dragonkin, " +
      "such as dragons or draconians and its edges will never " +
      "blunt\n");
    add_prop(MAGIC_AM_ID_INFO,
      ({"This weapon is magically enchanted.\n", 5,
	"The blade was forged during the Second Dragon War " +
	"by elven weaponsmiths in Silvanesti.\n", 25,
	"The blade is named Wyrmslayer and is especially " +
	"usefull against dragonkin in all of its forms.\n", 55}));
    add_prop(MAGIC_AM_MAGIC,({80,"enchantment"}));
    add_prop(OBJ_I_VOLUME, 3500);
    add_prop(OBJ_I_WEIGHT, 7000);
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(45,45) + 1000 + random(1000));
}

int
identify(object ob)
{
    int race = (ob->query_race() == "elf" ? 3 : 2);
    int wis = ob->query_stat(SS_WIS);
    int skill = ob->query_skill(SS_APPR_OBJ);

    if ((wis + skill / 3 * race) > id)
	return 1;
    else
	return 0;
}

string
long_desc()
{
    if (identify(TP))
	return "You look upon Wyrmslayer, the mighty blade of the "+
	"ancient elven hero and king, Kith-Kanan! The blade was "+
	"forged in Silvanesti during the second Dragon War and "+
	"remained in the royal house until Kith-Kanan led his "+
	"followers to Qualinesti. He is said to have been buried "+
	"with the sword.\n";
    else
	return "An excellently crafted two-handed sword. The blade "+
	"is remarkably well balanced and light, obviously a "+
	"masterpiece of weaponry. It is covered in the delicate "+
	"patterns and runes the elves love, leading you to believe "+
	"that it is elven in origin.\n";
}

string
short_desc()
{
    if (identify(TP))
	return "Wyrmslayer";
    else
	return "ancient two-handed sword";
}

varargs mixed
query_magic_protection(string prop, object protectee = previous_object())
{

    if (protectee == query_wielded())
      {
      if (prop == MAGIC_I_RES_FIRE)
        return ({ 15, 1}); /* additive */
      if (prop == MAGIC_I_RES_COLD)
        return ({ 15, 1}); /* additive */
      if (prop == MAGIC_I_RES_ACID)
        return ({ 15, 1}); /* additive */
      if (prop == MAGIC_I_RES_ELECTRICITY)
        return ({ 15, 1}); /* additive */
      if (prop == MAGIC_I_RES_POISON)
        return ({ 15, 1}); /* additive */
      }
    else
      return ::query_magic_protection(prop, protectee);
}

mixed
wield(object what)
{
  int return_value = 0;

  if(TP->query_alignment() < 600)
  {
    if (identify(TP))
    {
      return "Deeming you unworthy, Wyrmslayer refuses you.\n";
    }
    else
    {
      return "Deeming you unworthy, the ancient blade refuses you.\n";
    }
  }

  if (identify(TP))
  {
    write("A feeling of awe spreads throughout your body as you "+
	  "grasp the hilt of Wyrmslayer, wielding it in both your hands.\n");
    say(QCTNAME(TP)+" grasps the hilt of Wyrmslayer, wielding it with " +
	"supreme confidence in both " + POSSESSIVE(TP)+" hands.\n");
    TP->add_magic_effect(TO);
    return_value = 1;
  }
  TP->add_prop(LIVE_I_QUICKNESS, TP->query_prop(LIVE_I_QUICKNESS)+35);
  wielder = TP;
  return return_value;
}


mixed
unwield()
{
  int return_value = 0;

    wielder = 0;

    if (identify(TP))
    {
	TP->remove_magic_effect(TO);
	query_wielded()->catch_tell("You release your hold on the Wyrmslayer.\n");
	say(QCTNAME(TP) + " releases " + TP->query_possessive() + 
            " hold on the ancient blade.\n");
	return_value = 1;
    }
    TP->add_prop(LIVE_I_QUICKNESS, TP->query_prop(LIVE_I_QUICKNESS)-35);
    return return_value;
}


/*
* Function name: tell_watcher
* Description:   Send the string from the fight to people that want them
* Arguments:     The string to send

static void
tell_watcher(string str, object enemy)
{
    object me,*ob;
    int i;

    me = query_wielded();
    ob = FILTER_LIVE(all_inventory(environment(me))) - ({ me });
    ob -= ({ enemy });
    for (i = 0; i < sizeof(ob); i++)
    if (ob[i]->query_option(OPT_BLOOD))
	    ob[i]->catch_msg(str);
}
*/



public mixed
did_hit(int aid, string hdesc, int phurt, object enemy, int dt, int phit, int dam)
{
    string dam_descr;

    ::did_hit(aid, hdesc, phurt, enemy, dt, phit, dam);

    if(QRACE(enemy) == "dragon")
    {
	if(!random(2))
	{
	    if (identify(wielder))
	    {
		wielder->catch_msg("A deep humming sound emanates from Wyrmslayer.\n");
	    }
	    else
	    {
		wielder->catch_msg("A deep humming sound emanates from your sword.\n");
	    }
	    tell_room(E(wielder), "A deep humming sound emanates from "+
		      QTNAME(wielder)+"'s sword.\n", wielder);
	}
    }

    if(QRACE(enemy) == "dragon" || QREALRACE(enemy) == "draconian")
    {
	if(phurt > 0)
	{
	    switch(phurt)
	    {
	    case 1..2:
		dam_descr = " barely nicks the ";
		break;

	    case 3..8:
		dam_descr = " slices into the ";
		break;

	    case 9..15:
		dam_descr = " strikes the ";
		break;

	    case 16..23:
		dam_descr = " slashes into the ";
		break;

	    case 24..34:
		dam_descr = " rips deeply into the ";
		break;

	    case 35..48:
		dam_descr = " leaves a gaping wound on the ";
		break;

	    case 49..60:
		dam_descr = " cuts to the bone of the ";
		break;

	    case 61..90:
		dam_descr = " almost severs the ";
		break;

	    default:
		dam_descr = " cleaves all the way through the ";
		break;
	    }

	    // more help against dragons than against draconians.
	    if(QRACE(enemy) == "dragon")
	    {
		enemy->heal_hp(-dam);
	    }
	    enemy->heal_hp(-dam); /*HERE WE DEAL DOUBLE DMG TO DRACOS*/

	    if (identify(wielder))
		wielder->catch_msg("Fighting with a fury of its own, "+
		  "Wyrmslayer"+dam_descr+hdesc+" of "+QTNAME(enemy)+".\n");
	    else
		wielder->catch_msg("Fighting with a fury of its own, "+
		  "your "+short()+dam_descr+hdesc+" of "+QTNAME(enemy)+".\n");

	    wielder->tell_watcher(QCTNAME(wielder) +"'s sword"+ dam_descr + hdesc +
	      " of " + QTNAME(enemy) + ".\n", enemy);

	    return 1;
	}
    }

    return 0;
}

