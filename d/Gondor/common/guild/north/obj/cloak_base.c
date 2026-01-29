/*
 * The base code for the cloaks of the Rangers of the North
 * By Rastlin.
 * Modified by Elessar, 1998.
 *
 *    Incognito removed 29 November 2006 by Toby. 
 *    Admin forbid it for players this night.
 */
#pragma save_binary
#pragma strict_types

#define HE(x)     ((x)->query_pronoun())
#define HIS(x)    ((x)->query_possessive())
#include "/d/Gondor/defs.h"
#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <state_desc.h>
#include <formulas.h>

inherit "/std/armour";

object gShadow = 0;
string Colour;

/* Prototypes */
void set_colour(string str);

public void
create_robe()
{
    set_colour("grey");
}

public nomask void
create_armour()
{
    create_robe();

    set_af(TO);
    seteuid(getuid());

    set_default_armour(3, A_ROBE, 0, 0);

    add_prop(OBJ_I_VOLUME, 400);
    add_prop(OBJ_I_WEIGHT, 300);
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(3));
}

/*
 * Function name: wear
 * Description:   Called from the armour when worn
 * Arguments:     what - The object worn.
 * Returns:       True if it went ok, a string or -1 otherwise
 */
public mixed
wear(object what)
{
    if (what != TO)
        return -1;

    write("You wrap the " + short() + " around your shoulders.\n");
    say(QCTNAME(TP) + " wears " + LANG_ADDART(short()) + ".\n");

    return 1;
}

/*
 * Function name: remove
 * Description:   Called when the robe is removed
 * Arguments:     what - The object being removed
 * Returns:       False or -1.
 */
public mixed
remove(object what)
{
    if (what != TO)
        return -1;

 /*   if (gShadow)
        gShadow->remove_shadow();
  *7
    return 0;
}

/*
 * Function name: hood_player
 * Description:   This will put on the hood for the player.
 *                Make sure all the tests are done before
 *                calling this function.
 * Arguments:     player - The player object
 */
public void
hood_player(object player)
{

    gShadow = clone_object(RANGER_NORTH_DIR + "obj/hood_shadow");
    gShadow->set_colour(Colour);
    gShadow->shadow_me(player);
    //player->add_prop("_RoN_incognito_", 1);
}

/*
 * Function name: wear_hood
 * Description:   Wear the hood.
 * Arguments:     str - The proper string to wear the hood.
 * Returns:       True or false.
 */
public int
wear_hood(string str)
{
    if (!str || !strlen(str) || str != "hood")
        return 0;

    if ((query_worn() != TP) || gShadow)
        return 0;

    write("You pull the hood of your cloak low down over your face.\n");
    say(QCTNAME(TP) + " pulls " + HIS(TP) + " hood over " +
	HIS(TP) + " head, hiding " + HIS(TP) + " face.\n");

    if ((!TP->query_wiz_level()) && (TP->query_guild_name_occ() != "Rangers of the North"))
        return 1;
    hood_player(TP);

    return 1;
}

/*
 * Function name: remove_hood
 * Description:   Remove the worn hood.
 * Arguments:     str - The proper string to remove the hood.
 * Returns:       True or false.
 */
public int
remove_hood(string str)
{
    if (!str || !strlen(str) || str != "hood")
        return 0;

    if ((query_worn() != TP) || !gShadow)
        return 0;

    write("You remove the hood, and once again reveal your face.\n");
    //TP->remove_prop("_RoN_incognito_");
    say(QCTNAME(TP) + " removes " + HIS(TP) + " hood from " +
	HIS(TP) + " face.\n");

    //gShadow->remove_shadow();

    return 1;
}

public void
init()
{
    ::init();

    if (TP != ENV(TO))
        return;

    add_action(wear_hood, "wear");
    add_action(remove_hood, "remove");
}

/*
 * Function name: leave_env
 * Description:   Called when the robe leaves its environment.
 *
public void
leave_env(object from, object to)
{
    if (gShadow)
        gShadow->remove_shadow();

    ::leave_env(from, to);     
}
*/

public void
set_colour(string str)
{
    Colour = str;
}

/*
 * Function name:
 * Description:
 * Arguments:
 * Returns:
 */

