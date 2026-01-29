/* Slashing guild sword, with combat descs
 *   Cirion 040196
 * Changed: Manat Nov'02: Changed did_hid to match mudlib change
 *          Lilith Oct 2021: added name "longsword"
 */
#pragma strict_types
#include "../defs.h"

inherit "/std/weapon";

#include <macros.h>
#include <options.h>
#include <formulas.h>
#include <language.h>
#include <wa_types.h>
#include <stdproperties.h>

#define HIT	39
#define PEN	40

public string *randadj = ({ "narrow", "bronze-hafted",
    "thick-handled", "thin", "slender", "shiny", "steel"
});


public void
create_weapon()
{
    string myadj = one_of_list(randadj);

    set_name("blade");
    add_name(({"sword", "longsword"}));
    set_adj(myadj);
    set_short(myadj + " longsword");
    set_long("This sword has a long sharp blade, ending with "+
	"a razor sharp point. The blade is of a strange alloy of "+
	"steel and some darker metal, and the handle is very long, "+
	"nearly half as long as the blade itself, to balance out "+
	"the entire weapon.\n");

    set_default_weapon(HIT, PEN, W_SWORD, (W_SLASH | W_IMPALE), W_LEFT, TO);
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(HIT, PEN));

    add_prop(OBJ_I_WEIGHT, 4000);
    add_prop(OBJ_I_VOLUME, 2000);
}

public int
wield(object to)
{
    write("You grasp the long handle of "+ LANG_THESHORT(to) +".\n");
    say(QCTNAME(TP) +" grasps the long handle of "+
	LANG_ASHORT(to) +".\n");
    return 1;
}

/* Definitions to make combat messages easier */
#define ME      QTNAME(me)
#define CME     QCTNAME(me)
#undef HIS
#define HIS     me->query_possessive() + " "
#define EN      QTNAME(enemy)
#define CEN     QCTNAME(enemy)
#define EHIS    enemy->query_possessive() + " "
#define WEP     short()

#define TM(x)   me->catch_msg(x+".\n")
#define TE(x)   enemy->catch_msg(x+".\n");
#define TW(x)   me->tell_watcher(x+".\n", enemy)

/*
 * Function name: did_hit
 * Description:   Tells us that we hit something. Should produce combat
 *                messages to all relevant parties. If the weapon
 *                chooses not to handle combat messages then a default
 *                message is generated.
 * Arguments:     aid:   The attack id
 *                hdesc: The hitlocation description.
 *                phurt: The %hurt made on the enemy
 *                enemy: The enemy who got hit
 *		  dt:	 The current damagetype
 *		  phit:  The %success that we made with our weapon
 *		  dam:   The actual damage caused by this weapon in hit points
 * Returns:       True if it handled combat messages, returning a 0 will let
 *		  the normal routines take over
 */
public varargs int
did_hit(int aid, string hdesc, int phurt, object enemy, int dt, int phit, int dam)
{
    object me = query_wielded();

    /* Call the parent function so the weapon's hit counter
     * can be updated */
    ::did_hit(aid, hdesc, phurt, enemy, dt, phit, dam);

    /* I don't like plural hitloc ids, it limits
     * the possible messages too much */
    if (hdesc == "legs")
    {
	if (random(2))
	    hdesc = "left leg";
	else
	    hdesc = "right leg";
    }

    /* Is it dead & does it have a 'neck'? */
    if (!enemy->query_hp() &&
	(interactive(enemy) || function_exists("create_monster", enemy)))
    {
	TM("You slash through the air with a final cut of your "
	  +WEP+".\n"+CEN+" stands rooted to the spot for a moment, "
	  +"then falls to the ground with a severed neck");
	TE(CME+" slashes right through your throat with "+HIS+WEP);
	TW(CME+" slashes through the air with a final cut of "
	  +HIS+WEP+".\n"+CEN+" stands rooted to the spot for a moment, "
	  +"then falls to the ground with a severed neck");
	return 1;
    }

    /* Message based on the % amount of hp damage we did to him */
    switch(phurt)
    {
    case -2: // Parry
	TM("Your "+WEP+" is parried by "+EN);
	TE(CME+" swings "+HIS+WEP+" at you, but you parry it successfully");
	TW(CME+" swings "+HIS+WEP+" but "+EN+" parries it successfully");
	break;
    case -1: // Dodge
	TM("Your "+WEP+" whistles as it slices through thin air");
	TE(CME+" swings "+HIS+WEP+" at you, slicing through "
	  +"thin air");
	TW(CME+" swings "+HIS+WEP+" through thin air");
	break;
    case 0:
	TM("You swing your "+WEP+" at "+EN+", barely missing");
	TE(CME+" barely misses you with "+HIS+WEP);
	TW(CME+" barely misses "+EN+" with "+HIS+WEP);
	break;
    case 1 .. 4:
	TM("You slash at "+EN+" with your "+WEP+", opening a small "
	  +"scratch on "+EHIS+hdesc);
	TE(CME+" slashes at you with "+HIS+WEP+", opening a small "
	  +"scratch in your "+hdesc);
	TW(CME+" slashes at "+EN+" with "+HIS+WEP+", opening a small "
	  +"scratch on "+EHIS+hdesc);
	break;
    case 5 .. 9:
	TM("You slice open a shallow wound in the "+hdesc+" of "
	  +EN+" with your "+WEP);
	TE(CME+" slices open a shallow wound in your "+hdesc
	  +" with "+HIS+WEP);
	TW(CME+" slices open a shallow wound in the "+hdesc+" of "
	  +EN+" with "+HIS+WEP);
	break;
    case 10 .. 19:
	TM("You make a long graze along the "+hdesc+" of "+EN
	  +" with your "+WEP);
	TE(CME+" makes a long graze along your "+hdesc+" with "
	  +HIS+WEP);
	TW(CME+" makes a long graze along the "+hdesc+" of "+EN
	  +" with "+HIS+WEP);
	break;
    case 20 .. 29:
	TM("You cut into "+EN+"'s "+hdesc+" with your "+WEP);
	TE(CME+" cuts into your "+hdesc+" with "+HIS+WEP);
	TW(CME+" cuts deep into "+EN+"'s "+hdesc+" with "+HIS+WEP);
	break;
    case 30 .. 49:
	TM("You slash a deep wound along "+EN+"'s "+hdesc+" with "
	  +"your "+WEP);
	TE(CME+" slashes a deep wound along your "+hdesc+" with "
	  +HIS+WEP);
	TW(CME+" slashes a deep wound along "+EN+"'s "+hdesc
	  +"with "+HIS+WEP);
	break;
    case 50 .. 69:
	TM("You drive the blade of your "+WEP+" deep into the "
	  +hdesc+" of "+EN);
	TE(CME+" drives the blade of "+HIS+WEP+" deep into your "
	  +hdesc);
	TW(CME+" drives the blade of "+HIS+WEP+" deep into the "
	  +hdesc+" of "+EN);
	break;
    case 70 .. 89:
	TM("You bury your "+WEP+" deep into "+EN+"'s "+hdesc);
	TE(CME+" buries "+HIS+WEP+" deep into your "+hdesc);
	TW(CME+" buries "+HIS+WEP+" deep into the "+hdesc
	  +" of "+EN);
	break;
    default:
	TM("With an incredible slash of your "+WEP+", you nearly "
	  +"sever "+EN+"'s "+hdesc+" in half");
	TE("With an incredible slash of "+HIS+WEP+", "+ME
	  +" nearly severs your "+hdesc+" in half");
	TW("With an incredible slash of "+HIS+WEP+", "+ME
	  +" nearly severs "+EN+"'s "+hdesc+" in half");
	break;
    }

    return 1;
}
