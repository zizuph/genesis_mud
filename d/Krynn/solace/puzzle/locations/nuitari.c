/* The Nuitari room. ~solace/puzzle/locations/nuitari */

#include "../defs.h"

inherit ROOM_DEFS;

void reset_puzzle_room()
{
    found = 0;

    room_add_object(OBJECTS + "cage");
    room_add_object(NPCS + "india_rubber_man");
}

void create_puzzle_room()
{
    set_short("The Nuitari room");
    set_long("This room is quite large. The walls are regular and seem to "+
        "be made of large blocks of grey stone. A warm glow comes from a "+
        "lantern hanging above the arched doorway which seems to be the only "+
        "exit; leading north. The floor is covered in a mosaic of patterned "+
        "tiles.\n");

    add_item(({"doorway", "arched doorway", "exit"}), "An exit from this "+
        "room to the room north of here. You see nothing more of interest.\n");

    add_item("lantern", "The lantern is made of an unrecognisable black "+
        "metal paned with rainbow-hued semi-transparent glass. The flicker"+
        "ing flame within casts a warm glow about the surroundings. The "+
        "lantern is attached to the wall above the doorway.\n");

    add_item(({"large blocks of grey stone", "stone", "blocks", "grey stone",
        "large blocks", "walls"}), "The blocks of stone are a light grey in "+
        "colour and serve as the walls of this room. A darker ring of the "+
        "same stone runs all around the room about mid-way up.@@xtra_desc@@\n");

    add_item(({"tiles", "mosaic", "patterned tiles"}), "The tiles are small "+
        "coloured squares of stone layed together to form a mosaic of a dark "+
        "terrible scene: You see a vast bleak landscape overcast by black "+
        "clouds of grotesque flying monstrosities bearing down on a group "+
        "of white-clad knights who seem to be struggling for their lives. "+
        "The legend below it states: 'Frontline Assembly'.\n");

    add_search(({"large blocks of grey stone", "stone", "blocks", "grey stone",
        "large blocks", "walls"}), "press one of", "", "gasp in suprise when "+
        "it slowly spins round to reveal", OBJECTS + "circle");

    reset_puzzle_room();
}

string xtra_desc()
{
    return(found ? " You notice that one of these stones spins on a vertical "+
        "axis and one side has a spherical shape carved out of it." : "");
}
