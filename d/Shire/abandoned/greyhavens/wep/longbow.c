/*
/d/Shire/greyhavens/wep/longbow.c

The standard longbow Sindar guards wield.
Based on the Ranger short bow.

by Palmer, Dec 03, 2003

*/

inherit "/std/bow";
#include <formulas.h>
#include <macros.h>
#include "/d/Shire/sys/defs.h"

public void
create_bow()
{
    set_short("black longbow");
    set_name("longbow");
    add_name("bow");
    set_adj("black");
    set_long("The bow is quite tall making it a good bow " +
	     "long distance shots. It is about five feet tall and made " +
	     "out of ironwood. The handle is made of seal skin and is " +
	     "quite comfortable.\n" +
	     "There is a small note attached to the bow.\n");
    add_item("note", "On a small patch of leather someone has written:\n\n" +
	     "aim target [in location]    - Aims bow at target, hit\n" +
	     "                              location is optional.\n\n" +
	     "fire                        - Fires arrow at aimed target.\n\n" +
	     "shoot target [in location]  - Aims and fires at target.\n\n" +
	     "unload                      - Unloads the arrow and relaxes\n" +
	     "                              aim at a target.\n\n" +
	     "secondary [command]         - Specifies the command to\n" +
	     "                              perform if you should run\n" +
	     "                              out of arrows.\n\n" +
	     "string bow                  - Puts a new string on a bow.\n\n" +
	     "unstring bow                - Removes the bowstring from\n" +
	     "                              a bow.\n\n");
    add_prop(OBJ_I_WEIGHT, 2100);
    add_prop(OBJ_I_VOLUME, 3250);
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(38, 35));
    set_hit(40);
    set_pen(40);
}

/*
 * Function name: tell_others_load
 * Description  : Produces messages to spectators when the player loads his
 *                launch_weapon. This method is meant to be overridden by
 *                launch_weapon implementations.
 *
 * Arguments    : archer:     The player loading his weapon.
 *                target:     The target player is aiming at.
 *                projectile: The projectile we are loading.
 *                adj_string: Description of the adjecent location.
 */
public void
tell_others_load(object archer, object target,
		 object projectile, string adj_desc)
{
    if (ENV(archer) == ENV(target))
    {
        tell_bystanders_miss(QCTNAME(archer) + " nocks " +
			     LANG_ADDART(projectile->singular_short()) +
			     " and draws " + archer->query_possessive() +
			     " " + short() + ", aiming carefully at " +
			     QTNAME(target) + ".\n",

			     QCTNAME(archer) + " nocks " +
			     LANG_ADDART(projectile->singular_short()) +
			     " and draws " + archer->query_possessive() +
			     " " + short() +
			     ", aiming at something.\n",

			     0, 0, archer, target, ENV(archer));
    }
    else
    {
        tell_bystanders_miss(QCTNAME(archer) + " nocks " +
			     LANG_ADDART(projectile->singular_short()) +
			     " and draws " + archer->query_possessive() +
			     " " + short() +
			     ", aiming carefully at " + QTNAME(target) +
			     " " + adj_desc + ".\n",

			     QCTNAME(archer) + " nocks " +
			     LANG_ADDART(projectile->singular_short()) +
			     " and draws " + archer->query_possessive() +
			     " " + short() +
			     ", aiming carefully at something " +
			     adj_desc + ".\n",

			     0, 0, archer, target, ENV(archer));
    }
}


/*
 * Function name: tell_target_load
 * Description  : Produces a message to the player when he is loading his
 *                launch_weapon.
 *
 * Arguments    : archer:     The player loading his weapon.
 *                target:     The target player is aiming at.
 *                projectile: The projectile we are loading.
 */
public void
tell_target_load(object archer, object target, object projectile)
{
    if (ENV(archer) == ENV(target) &&
	CAN_SEE(target, archer) && CAN_SEE_IN_ROOM(target))
    {
        tell_object(target, archer->query_The_name(target) +
            " pulls " + LANG_ADDART(projectile->singular_short()) +
            " from " + HIS_HER(archer) + " quiver with lightning speed, nocks it" +
		    " and draws " + archer->query_possessive() + " " +
		    short() + ", aiming it at you.\n");

        if (archer->query_race() == "grey-elf")
            tell_object(target, "\n" + archer->query_The_name(target) +
            " utters a prayer.\nThe tip of " + LANG_ADDART(projectile->singular_short()) +
            " begins glowing with a holy aura.\n\n");

    }
}


