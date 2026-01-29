/* /d/Calia/argos/farmstead/rooms/field.c
**   A field at the farmstead east of Argos
**   Here can be found a couple items needed to complete the farmstead quest
**
**   History:
**   Date       Coder       Action
**   --------   ----------  ---------------------------------
**   2/21/20    Brine       Created
**   4/23/21    Brine       Fix to allow players of the ogre race to perform
**                          the harvest command needed for the quest
**
*/

#pragma strict_types

inherit  "/std/room";

#include <stdproperties.h>
#include <macros.h>
#include <wa_types.h>
#include <ss_types.h>
#include "defs.h"

// variables
int crops_harvested;
int patch_picked;
string* crop_strings = ({ "wheat", "crop", "crops", "wheats" });

void
create_room()
{
    seteuid(getuid());

    set_short("An overgrown wheat field");

    set_long(
        "This overgrown field appears to have once been a productive wheat "
        + "field, but now it's more shrubs than crops. In the southwestern "
        + "corner a line of rocks trace out a patch of weeds.\n"
    );

    add_item(
        ({
            "field", "wheat field", "overgrown field", "overgrown wheat field"
        }),
        long()
    );

    add_item(
        ({ "shrub", "shrubs" }),
        "Shrubs have taken over much of the field.\n"
    );

    add_item(
        ({
            "corner", "corners", "southwestern corner", "south western corner"
        }),
        "A line of rocks trace out a patch of weeds in the southwestern "
        + "corner.\n"
    );

    add_item(
        crop_strings,
        "Although the field has been neglected for a long time, there are "
        + "still some patches where harvestable wheat grows.\n@@crop_desc"
    );

    add_item(
        ({ "patch", "weeds", "patch of weeds", "dandelions" }),
        "This is a vegetable patch that has not been attended to for a long "
        + "time. No doubt at some point it contained produce of some sort, "
        + "now it seems to be mostly weeds and dandelions.\n@@patch_desc"
    );

    add_item(
        ({ "rock", "rocks", "line", "line of rocks", "boundary" }),
        "Round, fist-sized rocks are laid out next to each other in a line, "
        + "forming the boundary for a patch of weeds.\n"
    );

    add_exit(ROOM_DIR + "farmyard", "farmyard");

    reset_room();
}

void
reset_room()
{
    crops_harvested = 0;
    patch_picked = 0;
}

/*
 * Function name: crop_desc
 * Description  : Display information to the examining player based on whether
 *                the crops have been harvested since last room_reset or not.
 * Returns      : The string to be displayed to the player
 */
string
crop_desc()
{
    return crops_harvested
        ? "It seems that someone has very recently harvested the good crops.\n"
        : "You could probably harvest some if you had the right tool.\n";
}

/*
 * Function name: patch_desc
 * Description  : Allow the player to pick a turnip needed for a local quest,
 *                  or display a message if it was recently picked.
 * Returns      : The string to be displayed to the player
 */
string
patch_desc()
{
    if (!patch_picked)
    {
        patch_picked = 1;
        object turnip = clone_object(OBJ_DIR + "turnip");
        turnip->move(TP, 1);
        return "You find a turnip!\n";
    }
    return "It seems that someone has recently rummaged through the patch.\n";
}

/*
 * Function name: get_wielded_scythe
 * Description  : A function to determine whether the player wields the correct
 *                  item for harvesting crop
 * Returns      : The wielded item, or 0 if the correct item wasn't wielded
 */
object
get_wielded_scythe(object who)
{
    /*  The scythe is two-handed, but ogres can wield it in one hand, thus
        we must check for all possible wielded combinations */
    object* wielded = who->query_weapon(-1);

    foreach(object wep: wielded) {
        if (MASTER_OB(wep) == (WEAPON_DIR + "scythe")) return wep;
    }

    return 0;
}

/*
 * Function name: harvest
 * Description  : A custom command added through init(), allowing the player
                  to harvest some crop, needed to complete a quest
 * Returns      : int 1/0 - success/failure
 */
int
harvest()
{
    object scythe = get_wielded_scythe(TP);
    if (scythe)
    {
        if (crops_harvested)
        {
            notify_fail("All the good crops have been recently harvested!\n");
            return 0;
        }

        /* Determine how well the player could swing the scythe, based on
           their polearm skill. Purely cosmetic */
        string how_swing;
        int polearm_skill = TP->query_skill(SS_WEP_POLEARM);

        switch (polearm_skill)
        {
            case 0..19:
                how_swing = "clumsily ";
                break;
            case 20..29:
                how_swing = "awkwardly ";
                break;
            case 30..39:
                how_swing = "";
                break;
            case 40..59:
                how_swing = "capably ";
                break;
            case 60..79:
                how_swing = "elegantly ";
                break;
            default:
                how_swing = "masterfully ";
        }

        write(
            "You " + how_swing + "arc your " + scythe->short() + " through "
            + "the crops, reaping plants and separating straw from grain in "
            + "one fell swoop.\n"
        );
        tell_room(
            TO,
            QCTNAME(TP) + " " + how_swing + "arcs " + TP->query_possessive()
            + " " + scythe->short() + " through the crops, reaping plants "
            + "and separating straw from grain in one fell swoop.\n",
            TP
        );
        crops_harvested = 1;
        object crop = clone_object(OBJ_DIR + "straw");
        crop->move(TO, 1);
        return 1;
    }

    notify_fail("You are not wielding the right tool to harvest crops.\n");
    return 0;
}

void
init()
{
    ::init();
    add_action(harvest, "harvest");
}
