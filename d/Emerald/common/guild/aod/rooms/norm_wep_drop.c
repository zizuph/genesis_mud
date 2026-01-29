/*
 *  /d/Emerald/common/guild/aod/rooms/norm_wep_drop.c
 * 
 *  This is the droproom for non-glowing weapons for the Army of
 *  Darkness guild.
 *
 *  Created December 2006, by Cooper Sherry (Gorboth)
 */
#pragma strict_types
#include "../defs.h"

inherit AOD_ROOM_DIR + "drop_room";

#include <language.h>

/* definitions */
#define            FALL_LOCATION (AOD_ROOM_DIR + "glow_arm_drop")


/* prototypes */
public void        create_drop_room();
public void        enter_inv(object ob, object from);
public void        continue_fall(object ob, object from);

/*
 * Function name:        create_drop_room
 * Description  :        set up the room with area defaults
 */
public void
create_drop_room()
{
    set_short("a droproom beside a pile of non-glowing weapons");
    set_em_long("The switchbacks here are almost as wide enough"
      + " to accommodate a horse and carriage - further evidence"
      + " that they were constructed for ogre use. Here, the"
      + " (literal) drop room system for the Army of Darkness"
      + " seems to be geared toward non-glowing weapons. A large"
      + " pile of them has accumulated on a ledge beside the"
      + " switchbacks which travel both above and below.\n");

    add_item( ({ "pile", "large pile", "pile of weapons",
                 "weapon pile", "pile of non-glowing weapons",
                 "large weapon pile", "large pile of non-glowing weapons",
                 "weapon", "non-glowing weapon", "weapons",
                 "non-glowing weapons" }),
        "This ledge appears to be where non-glowing weapons that are"
      + " dropped off of the ravine by members of the Army pile up."
      + " Sadly, all of these ones were broken by the fall. Perhaps"
      + " there are others lying around here that fared better.\n");
    add_item( ({ "broken weapon", "broken weapons" }),
        "A highly imperfect system, this seems to be! Ah well, what"
      + " can be expected of ogres?\n");

    add_droproom_items();

    add_spike("norm_wep_drop");

    add_exit("glow_arm_drop", "down");
    add_exit("glow_wep_drop", "up");
} /* create_drop_room */


/*
 * Function name:        enter_inv
 * Description  :        Called when objects enter this container or when
 *                       an object has just changed its weight/volume/light
 *                       status. In this case, we want to move anything
 *                       non-living to the proper droprooms.
 * Arguments    :        ob: The object that just entered this inventory
 *                       from: The object from which it came.
 */
public void
enter_inv(object ob, object from)
{
    set_alarm(1.0, 0.0, &continue_fall(ob, from));
    ::enter_inv(ob, from);
} /* enter_inv */


/*
 * Function name:        continue_fall
 * Description  :        determine whether or not the object is
 *                       supposed to continue falling to a
 *                       different droproom.
 * Arguments    :        object ob - the object
 *                       object from - where it came from
 */
public void
continue_fall(object ob, object from)
{
    if (living(ob) ||
        ob->id("_aod_trophy_spike") ||
        ob->id("coin") ||
        environment(ob) != this_object())
    {
        return;
    }

    if (ob->check_weapon())
    {
        tell_room(this_object(), capitalize(LANG_THESHORT(ob)) + " skids"
          + " along the ledge and comes to rest beside the pile of"
          + " non-glowing weapons.\n");
        return;
    }

/*    tell_room(this_object(), capitalize(LANG_THESHORT(ob)) + " bounces"
      + " bounces off a rock and disappears into the ravine.\n");
    tell_room(FALL_LOCATION, capitalize(LANG_ADDART(ob->short()))
      + " tumbles into the area from above.\n");*/
    tell_room(this_object(), capitalize(LANG_THESHORT(ob))
      + " bounces off a rock and disappears into the ravine.\n");
    tell_room(FALL_LOCATION, capitalize(LANG_ASHORT(ob))
      + " tumbles into the area from above.\n");      
    ob->move(FALL_LOCATION);
} /* continue_fall */