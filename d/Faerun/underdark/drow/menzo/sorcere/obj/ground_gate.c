/*
 *  faerun/underdark/upper/menzo/sorcere/obj/ground_gate.c
 *
 *  The door used on the ground level entrance. 
 *
 *  Created by Midnight, 15-2-2004
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

    set_door_desc("This polished marble gate is constructed out of " +
                  "light grey marble. Flamedance gemstones forms the " +
                  "rune of Sorcere in the middle of the marble gate. " +
                  "They seem to burn from within, which gives the " +
                  "runic symbol a brighter glow than the bluish hue " +
                  "of the rest of the tower.\n");
}

/*
 * Function name: configure_ground_door
 * Description  : Set up this door
 * Arguments    : direction - in which direction do we pass through this 
 *              : door, use full names, such as west, southwest etc
 *              : door id - the id of the door, sould be the same as in the
 *              : other room
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
    set_door_name(({"marble gate", "gate", direction + " gate"}));
    set_door_id(door_id);
    set_pass_command(direction_names);
    set_other_room(other_side);
}