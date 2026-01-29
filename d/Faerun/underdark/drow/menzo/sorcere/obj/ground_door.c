/*
 *  faerun/underdark/upper/menzo/sorcere/obj/ground_door.c
 *
 *  The door used on the ground level. Create an instance of it, and call
 *  the configure_ground_door function.
 *
 *  Created by Wully, 15-2-2004
 */
inherit "/std/door";
#include "defs.h"

/*
 * Function name: create_door
 * Description  : Construct our door
 */
void create_door()
{
    // We are closed by default
    set_open(0);

    set_door_desc("This sturdy looking door is constructed out of " +
                  "duskwood. It's been polished and oiled into a " +
                  "silvery grey finish. Duskwood is smoky gray when cut and " +
                  "as hard as iron. It is also resistant " +
                  "to fire, and smolder rather than blaze when set aflame.\n");
}

/*
 * Function name: configure_ground_door
 * Description  : Set up this door
 * Arguments    : direction - in which direction do we pass through this 
 *              :       door, use full names, such as west, southwest etc
 *              : door id - the id of the door, sould be the same as in the
 *              :       other room
 *              : other_side - the other side of this door
 */
void configure_ground_door(string direction, string door_id, 
    string other_side)
{
    mapping directions = ([ "west" : ({ "w", "west" }), 
                            "east" : ({ "e", "east" }),
                            "south" : ({ "s", "south" }),
                            "north" : ({ "n", "north" }),
                            "northeast" : ({ "ne", "northeast" }),
                            "southeast" : ({ "se", "southeast" }),
                            "northwest" : ({ "nw", "northwest" }),
                            "southwest" : ({ "sw", "southwest" }) ]);
    mixed   direction_names;

    // Find the right direction
    if(member_array(direction, m_indexes(directions)) != -1)
        direction_names = directions[direction];
    else
        direction_names = ({ direction });

    // Configure the door
    set_door_name(({"duskwood door", "door", direction + " door"}));
    set_door_id(door_id);
    set_pass_command(direction_names);
    set_other_room(other_side);
}