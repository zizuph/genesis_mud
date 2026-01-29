/*
 * /d/Gondor/common/obj/bandage_shadow.c
 *
 * This shadow is added to a player that has been helped by the surgeon
 * who removed a scar from him/her. It makes sure that you do not enter
 * combat and that do not try to wield/wear something there.
 *
 * It is cloned from /d/Gondor/common/npc/surgeon_haldira.c
 *
 * /Mercade, 5 May 1994
 *
 * Revision history:
 */

inherit "/std/shadow";

#include <wa_types.h>
#include "/d/Gondor/defs.h"

static object bandage = 0;
static int    scar    = -1;

/*
 * Function name: disrupt_bandage
 * Description  : When someone wields or wears something on a part that
 *                is covered by the bandage, disrupt it.
 */
void
disrupt_bandage()
{
    bandage->disrupt_bandage();
}

/*
 * Function name: scar_to_weapon
 * Description  : This function turns the scar location into a weapon
 *                location, in this case the hands.
 * Returns      : int - W_LEFT or W_RIGHT if the scar is on a weapon
 *                    location, else 0.
 */
int
scar_to_weapon()
{
    switch(scar)
    {
    case 32:
	return W_LEFT;
    case 64:
	return W_RIGHT;
    default:
	return 0;
    }
}

/*
 * Function name: wield
 * Description  : When someone tries to wield something, this function is
 *                called. If you wield something on the scar location,
 *                you will disrupt the bandage. Other than that, the
 *                normal functionality is passed through.
 * Arguments    : object weapon - the weapon to wield.
 * Returns      : int - the normal return value.
 */
public int
wield(object weapon)
{
    int wielded = query_shadow_who()->wield(weapon);

    if (wielded &&
	(weapon->query_attack_id() & scar_to_weapon()))
    {
	tell_object(query_shadow_who(), "Wielding the " + weapon->short() +
	    " disrupts the bandage on your " + bandage->scar_to_part() +
	    " and since the skin has not fully recovered yet, the scar " +
	    "on it remains.");

	disrupt_bandage();
    }

    return wielded;
}

/*
 * Function name: scar_to_armour
 * Description  : This function turns the scar location into an armour
 *                location.
 * Returns      : int - the armour location.
 */
int
scar_to_armour()
{
    switch(scar)
    {
    case   1:
    case   2:
	return A_LEGS;
    case   4:
    case 128:
    case 256:
    case 512:
	return A_HEAD;
    case   8:
	return A_L_ARM;
    case  16:
	return A_R_ARM;
    case  32:
	return A_L_HAND;
    case  64:
	return A_R_HAND;
    default:
	return 0;
    }
}

/*
 * Function name: wear
 * Description  : When a player wears something over a location that is
 *                covered by the bandage, the bandage gets disrupted.
 *                The other functionaly is passed on like normal.
 * Arguments    : object armour - the armour to wear.
 * Returns      : int - the normal return value.
 */
public int
wear(object armour)
{
    int worn = query_shadow_who()->wear(armour);

    if (worn &&
	(member_array(scar_to_armour(), armour->query_slots()) != -1))
    {
	tell_object(query_shadow_who(), "Wearing the " + armour->short() +
	    " disrupts the bandage on your " + bandage->scar_to_part() +
	    " and since the skin has not fully recovered yet, the scar " +
	    "on it remains.");

	disrupt_bandage();
    }

    return worn;
}

/*
 * Function name: attack_object
 * Description  : When you attack someone, you disrupt the bandage. The
 *                functionality of combat is preserved.
 * Arguments    : object victim - the living we attack.
 */
public void
attack_object(object victim)
{
    query_shadow_who()->attack_object(victim);

    query_shadow_who()->LCATCH_MSG("Attacking ", " you disrupt the bandage " +
	"on your " + bandage->scar_to_part() + ". The unpredictable " +
	"movements of combat disrupt the wound and leave you with an " +
	"ugly scar.", victim);

    disrupt_bandage();
}

/*
 * Function name: still_in_combat
 * Description  : When someone else attacks you, you have a short time to
 *                get the hell out of there or you will disrupt the
 *                bandage.
 * Arguments    : object enemy - the enemy that attacked us.
 */
void
still_in_combat(object enemy)
{
    if (!objectp(enemy))
    {
	return;
    }

    if (query_shadow_who()->query_attack() != enemy)
    {
	return;
    }

    query_shadow_who()->LCATCH_MSG("Since you do not evade combat directly " +
	"after ", " attacked you, your sudden movements disrupted the wound " +
	"and leave you with an ugly scar.", enemy);

    disrupt_bandage();
}

/*
 * Function name: attacked_by
 * Description  : When someone attacks us, we have about 15 seconds to get
 *                the hell out before combat disrupts the wound.
 * Arguments    : object enemy - the attacker.
 */
public void
attacked_by(object enemy)
{
    query_shadow_who()->attacked_by(enemy);

    set_alarm(15.0, 0.0, "still_in_combat", enemy);
}

/*
 * Function name: remove_no_scar_bandage_shadow
 * Description  : Remove this object.
 */
nomask void
remove_no_scar_bandage_shadow()
{
    destruct();
}

/*
 * Function name: query_no_scar_bandage_shadow
 * Description  : This function identifies the shadow as such. 
 * Returns      : int 1 - always.
 */
nomask int
query_no_scar_bandage_shadow()
{
    return 1;
}

/*
 * Function name: set_bandage_object_and_scar
 * Description  : When the shadow is initialized, this function sets the
 *                objectpointer to the bandage that we are shadowing and
 *                the scar location involved.
 * Arguments    : object o - the bandage object.
 *                int i - the scar location.
 */
void
set_bandage_object_and_scar(object o, int i)
{
    bandage = o;
    scar = i;
}
