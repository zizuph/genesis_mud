/*
 *  faerun/underdark/upper/menzo/sorcere/obj/third_door.c
 *
 *  The door used on the third floor in Sorcere. 
 *  Create an instance of it, and call
 *  the configure_ground_door function.
 *
 *  Created by Midnight, 8-3-2004
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
                  "silverwood. It's been polished and oiled into a " +
                  "smooth finish. There's a metallic shine to the wooden " +
                  " surface of the door.\n");
}

/*
 * Function name: configure_second_door
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
    set_door_name(({"silverwood door", "door", direction + " door"}));
    set_door_id(door_id);
    set_pass_command(direction_names);
    set_other_room(other_side);
}