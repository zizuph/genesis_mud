/*
 *  /d/Emerald/common/guild/aod/rooms/glow_arm_drop.c
 * 
 *  This is the droproom for glowing armours for the Army of
 *  Darkness guild.
 *
 *  Created December 2006, by Cooper Sherry (Gorboth)
 */
#pragma strict_types
#include "../defs.h"

inherit AOD_ROOM_DIR + "drop_room";
inherit "/d/Genesis/specials/lib/item_recovery_lib"; 

#include <language.h>

/* definitions */
#define            FALL_LOCATION (AOD_ROOM_DIR + "norm_arm_drop")


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
    set_short("a droproom beside a pile of glowing armours");
    set_em_long("The switchbacks are forced to zig and zag quite"
      + " regularly here due to the sheer angle of the ravine"
      + " wall. Just to the side, a large pile of glowing armours"
      + " has built up. Quite handy how things seem to be"
      + " landing in specific piles around here! The switchbacks"
      + " lead both up and down the ravine.\n");

    add_item( ({ "pile", "large pile", "pile of armours",
                 "armour pile", "pile of glowing armours",
                 "large armour pile", "large pile of glowing armours",
                 "armour", "glowing armours", "armours",
                 "glowing armours" }),
        "This ledge appears to be where glowing armours that are"
      + " dropped off of the ravine by members of the Army pile up."
      + " Sadly, all of these ones were broken by the fall. Perhaps"
      + " there are others lying around here that fared better.\n");
    add_item( ({ "broken armour", "broken armours", "broken armor",
                 "broken armors" }),
        "A highly imperfect system, this seems to be! Ah well, what"
      + " can be expected of ogres?\n");

    add_droproom_items();

    add_spike("glow_arm_drop");

    add_exit("norm_arm_drop", "down");
    add_exit("norm_wep_drop", "up");

    set_enable_logging(1);
    set_enable_recovery(1);

    init_database();    
    set_alarm(0.0, 0.0, &recover_objects_from_database());
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

    if (from == this_object())
    {
        return;
    }
    
    add_rack_entry(ob);
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

    if (ob->check_armour() && ob->check_recoverable())
    {
        tell_room(this_object(), capitalize(LANG_THESHORT(ob)) + " skids"
          + " along the ledge and comes to rest beside the pile of"
          + " glowing armours.\n");
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


/* 
 * Function name: leave_inv
 * Description:   Called when objects leave this container or when an
 *                object is about to change its weight/volume/light status.
 * Arguments:     ob: The object that just left this inventory.
 *                to: Where it went.
 */
public void
leave_inv(object ob, object to)
{
    ::leave_inv(ob, to);
    
    if (to == this_object() || !objectp(to))
    {
        // Not actually leaving this container, just return
        return;
    }
    
    remove_rack_entry(ob);
} /* leave_inv */