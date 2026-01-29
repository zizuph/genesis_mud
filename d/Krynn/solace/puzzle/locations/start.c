/* The start room. ~solace/puzzle/locations/start */

#include "../defs.h"
#include "/sys/stdproperties.h"

inherit ROOM_DEFS;

void create_puzzle_room()
{
    set_short("A small ante-chamber");
    set_long("This is a small ante-chamber made from roughly-cut blocks of "+
        "stone. Two small barred alcoves at head-height in the walls contain "+
        "a lighted red-flamed torch which gives off a little light. ");

    add_item(({"ante-chamber", "chamber"}), "You seem to be standing in it!\n");

    add_item(({"stone", "blocks of stone", "roughly cut stone", "roughly cut "+
        "blocks of stone"}), "You don't see anything of particular interest "+
        "about them.\n");

    add_item(({"alcove", "alcoves", "barred alcoves","small alcoves", "small "+
        "barred alcoves", "two small barred alcoves"}), "Alcoves in the "+
        "walls. Each one is barred and contains a softly burning torch.\n");

    add_item(({"wall", "walls", "north wall"}), "The walls are made from "+
        "medium-sized blocks of cold grey stone. In the south wall is a "+
        "solidly built metal door and on the floor is an iron-bound "+
        "trapdoor.\n");

    add_item(({"torches", "red-flamed torches"}), "Softly glowing torches "+
        "crackling and giving off a red glow that lights the room enough "+
        "for you to be able to see properly. They are placed in barred "+
        "alcoves so nobody can reach in and take them.\n");

    room_add_object(DOORS + "start_door");
    room_add_object(DOORS + "start_trapdoor");
}
