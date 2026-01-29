/* The shaitan room. ~solace/puzzle/locations/shaitan */

#include "../defs.h"

inherit ROOM_DEFS;

void reset_puzzle_room()
{
    if(member_array("south", query_exit_cmds()) != -1)
        remove_exit("south");

    room_add_object(OBJECTS + "tube");
}

int query_south_exit()
{
    if(member_array("south", query_exit_cmds()) == -1)
        return 0;
    else
        return 1;
}

void create_puzzle_room()
{
    set_short("The Shaitan room");
    set_long("You find yourself in a cave-like room in which shadows dance "+
        "and flicker about you from a smoky torch in the north wall. In the "+
        "south wall you notice @@doorway_desc@@. A small hole in the ceiling "+
        "acts as an escape for the smoke from the torch. The only @@word@@"+
        "exit from here seems to be an arched doorway leading northwest.\n");

    add_item("doorway", "@@doorway_check_desc");

    add_item(({"metal", "curved metal", "shiny metal", "shiny curved metal"}),
        "@@metal_desc");

    add_item("shadows", "You notice nothing special about them. They seem "+
        "to be caused by the flame of the torch.\n");

    add_item(({"arched doorway", "exit"}), "An exit from this room to "+
        "the room northeast of here. You see nothing more of interest.\n");

    add_item(({"hole", "small hole"}), "The hole in the ceiling is just "+
        "smaller than your fist and probably leads up to ground-level as "+
        "an exhaust for the torch smoke.\n");

    add_item("ceiling", "It is made of the same dirty yellow stone as the "+
        "walls and has nothing to remark about except for a small hole in "+
        "the middle of it to let smoke out.\n");

    add_item(({"torch", "smoky torch"}), "The torch seems not to be of a "+
        "magical nature; it produces plenty of smoke which rises too the "+
        "ceiling and disappears through a small hole. You notice nothing "+
        "more of interest about it.\n");

    add_item(({"wall", "walls"}), "The walls seem to have been carved "+
        "right out of the dirty yellow stone without an attempt at "+
        "creating a uniform surface. An exit leads northwest though an "+
        "arched doorway @@doorway_desc_item@@. A torch bracketed to the "+
        "north provides light.\n");

    add_exit(LOCATIONS + "azazel", "northwest", 0, 1);

    reset_puzzle_room();
}

string word()
{
    return(query_south_exit() ? "other " : "");
}

string doorway_check_desc()
{
    if(query_south_exit())
        return "A large rectangular doorway in the south wall.\n";
    else
        return "An exit from this room to the room northeast of here. You "+
            "see nothing more of interest.\n";
}

string metal_desc()
{
    if(query_south_exit())
        return "You find no metal.\n";
    else
        return "A bizarre area of the south wall where the stone has been "+
            "cut away and a covered flush by a sheet of shiny metal.\n";
}

string doorway_desc()
{
    if(query_south_exit())
        return "a doorway leading to another room";
    else
        return "that a large rectangular area is not stone but shiny curved "+
            "metal. It looks quite strange";
}

string doorway_desc_item()
{
    if(query_south_exit())
        return "and another frameless doorway leads southwards";
    else
        return "and a section of the south wall seems to be made from "+
            "solid curved metal";
}
