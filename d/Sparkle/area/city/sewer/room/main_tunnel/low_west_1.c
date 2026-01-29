/*
 *  /d/Sparkle/area/city/sewer/room/main_tunnel/low_west_1.c
 *
 *  This is a main tunnel room of the sewers of Sparkle.
 *
 *  Aeg
 */
#pragma strict_types

/* Includes */
#include <macros.h>
#include <language.h>
#include <stdproperties.h>
#include "../defs.h"

/* Defines */
#define            FALL_LOCATION (SEWER_MAIN_TUNNEL + "pump")

/* Inheritance */
inherit MAIN_TUNNEL_BASE;


/* Global Variables */


/* Prototypes */
public void             init();
public void             create_tunnel_room();
public void             enter_inv(object ob, object from);
public void             continue_fall(object ob, object from);

/* 
 * Function name:       init
 * Description  :       Standard init function to add actions
 * Arguments    :       none
 * Returns      :       void/nothing
 */
public void 
init() 
{
    ::init();  
} /* init */

/* 
 * Function name:       create_tunnel_room
 * Description  :       This function overrides the one in the base class
 * Arguments    :       none
 * Returns      :       void/nothing
 */
public void
create_tunnel_room()
{
    /* Descriptions Section */
    set_short("Lower main tunnel");
    set_long("The subterranean environment, being poorly lit, does not "
           + "instantly paint a complete picture. Allowing your eyes to "
           + "adjust "
           + "to the scene, darkness yields and details are revealed. "
           + "A tunnel extends upward and downward with classic "
           + "architecture. The walls and ceiling are crafted "
           + "with a post and lintel architecture style and are "
           + "in imperfect shape. The floor is made of stone and is "
           + "covered with downward flowing sewage."
           + "\n\n");
 
    /* Room Item Section */                           

    /* Properties Section */

    
    /* Exits Section */
    add_exit(SEWER_MAIN_TUNNEL + "low_west_2", "west", 0);
    add_exit(SEWER_MAIN_TUNNEL + "pump", "east", 0);
    
    
}   /* create_sewer_room */



/*
 * Function name:        enter_inv
 * Description  :        Called when objects enter this container or when
 *                       an object has just changed its weight/volume/light
 *                       status. In this case, we want to move anything
 *                       non-living to the proper room.
 * Arguments    :        ob: The object that just entered this inventory
 *                       from: The object from which it came.
 */
public void
enter_inv(object ob, object from)
{
    set_alarm(4.0, 0.0, &continue_fall(ob, from));
    ::enter_inv(ob, from);
} /* enter_inv */


/*
 * Function name:        continue_fall
 * Description  :        determine whether or not the object is
 *                       supposed to continue falling to a
 *                       different room.
 * Arguments    :        object ob - the object
 *                       object from - where it came from
 */
public void
continue_fall(object ob, object from)
{
    if (living(ob) ||
        environment(ob) != this_object())
    {
        return;
    }
    
    tell_room(this_object(), capitalize(LANG_THESHORT(ob)) + 
        " floats downstream.\n");
    tell_room(FALL_LOCATION, capitalize(LANG_ADDART(ob->short()))
      + " floats in from upstream.\n");
    ob->move(FALL_LOCATION);


} /* continue_fall */



