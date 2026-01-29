/* The Morgoin room. ~solace/puzzle/locations/morgoin */

#include "../defs.h"

inherit ROOM_DEFS;

void reset_puzzle_room()
{
    found = 0;

    room_add_object(OBJECTS + "clock");
    room_add_object(OBJECTS + "armchair");
}

void create_puzzle_room()
{
    set_short("The Morgoin room");
    set_long("This room is large, rectangular, well-lit and resembles a "+
        "sitting room. Tapestries hang proudly on the walls above handsome "+
        "wood panelling and a floor covered with a deep maroon-coloured "+
        "carpet. Shaded reading lamps illuminate the immediate surroundings "+
        "and an arched doorway in the south wall provides an exit southward "+
        "to the adjacent room.\n");

    add_item(({"room", "sitting room"}), "You are standing in it. (Type "+
        "'look').\n");

    add_item(({"doorway", "arched doorway", "exit"}), "An exit from this "+
        "room to the room south of here. You see nothing more of interest.\n");

    add_item(({"lamps", "reading lamps", "shaded lamps", "shaded reading "+
        "lamps"}), "The lamps are fixed about three-quarters of the way up "+
        "each wall and produce pools of illumination against more shaded "+
        "areas.\n");

    add_item(({"floor", "carpet", "deep carpet", "maroon-coloured carpet",
        "deep maroon-coloured carpet"}), "The floor is covered from wall to "+
        "wall with a carpet into which your feet sink luxuriously. It is of "+
        "a warm colour and makes the room feel cosy and pleasant.\n");

    add_item(({"walls", "wall"}), "The upper portion of the walls are "+
        "smooth, plastered and painted an ochre hue. The lower portion are "+
        "panelled with a rich, dark wood that reaches down to a deep maroon-"+
        "coloured carpet. In the south wall is an arched doorway leading to "+
        "another of the rooms in this area.\n");

    add_item("tapestries", "The tapestries are rather peculiar. They show a "+
        "horrific scene of a burnt and blackened landscape from which palls "+
        "of smoke rise lazily. The flaming bodies of living corpses stagger "+
        "mindlessly though skeletal buildings, charred trees and diseased "+
        "fields. The legend below it states: 'Skinny Puppy'.\n");

    add_search(({"carpet", "deep carpet", "maroon-coloured carpet", "deep "+
        "maroon-coloured carpet"}), "search around the edges of", "", "find "+
        "beneath a loose floorboard,", OBJECTS + "triangle");

    reset_puzzle_room();
}
