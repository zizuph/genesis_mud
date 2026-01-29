/*
 *  /d/Emerald/common/guild/aod/rooms/norm_wep_drop.c
 * 
 *  This is the droproom for non-glowing armours for the Army of
 *  Darkness guild.
 *
 *  Created December 2006, by Cooper Sherry (Gorboth)
 */
#pragma strict_types
#include "../defs.h"

inherit AOD_ROOM_DIR + "drop_room";

#include <language.h>

/* definitions */
#define            FALL_LOCATION (AOD_ROOM_DIR + "misc_drop")


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
    set_short("a droproom beside a pile of non-glowing armours");
    set_em_long("The far wall of the ravine is closer here than"
      + " it was above, perhaps because the ravine is narrowing"
      + " here near to the bottom. The switchbacks run beside a"
      + " large pile of non-glowing armours here on their way"
      + " up and down the ravine.\n");

    add_item( ({ "far wall", "far wall of the ravine" }),
        "It is close. You could probably hit it with a stone.\n");
    add_item( ({ "bottom", "bottom of the ravine", "ravine bottom" }),
        "It is not far below. Go down if you want to reach it.\n");
    add_item( ({ "pile", "large pile", "pile of armours",
                 "armour pile", "pile of non-glowing armours",
                 "large armour pile", "large pile of non-glowing armours",
                 "armour", "non-glowing armour", "armours",
                 "non-glowing armours" }),
        "This ledge appears to be where non-glowing armours that are"
      + " dropped off of the ravine by members of the Army pile up."
      + " Sadly, all of these ones were broken by the fall. Perhaps"
      + " there are others lying around here that fared better.\n");
    add_item( ({ "broken armour", "broken armours" }),
        "A highly imperfect system, this seems to be! Ah well, what"
      + " can be expected of ogres?\n");

    add_droproom_items();

    add_spike("norm_arm_drop");

    add_exit("misc_drop", "down");
    add_exit("glow_arm_drop", "up");
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
    if (!ob)
        return;

    if (living(ob) ||
        ob->id("_aod_trophy_spike") ||
        ob->id("coin") ||
        environment(ob) != this_object())
    {
        return;
    }

    if (ob->check_armour())
    {
        tell_room(this_object(), capitalize(LANG_THESHORT(ob)) + " skids"
          + " along the ledge and comes to rest beside the pile of"
          + " non-glowing armours.\n");
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