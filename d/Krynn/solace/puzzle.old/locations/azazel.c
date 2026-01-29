/* The azazel room. ~solace/puzzle/locations/azazel */

#include "../defs.h"

inherit ROOM_DEFS;

#define NOT_RESET ({ "entrance", "azazel" })

void reset_neighbours()
{
    int i;
    string *tmp, *rooms = ({ });

    tmp = get_dir(LOCATIONS + "*.c");

    for(i = 0; i < sizeof(tmp); i++)
        rooms += ({ extract(tmp[i], 0, strlen(tmp[i]) - 3) });

    for(i = 0; i < sizeof(rooms); i++)
    {
        if(member_array(rooms[i], NOT_RESET) == -1)
        {
            (LOCATIONS + rooms[i])->clear_room();
            (LOCATIONS + rooms[i])->reset_puzzle_room();
        }
    }
}

void reset_puzzle_room()
{
    clear_room();
    reset_neighbours();

    room_add_object(WEAPONS + "hammer");
}

void create_puzzle_room()
{
    set_short("The Azazel room");
    set_long("This room is large and round and made from the same coarse grey "+
        "stone as the areas above. There are eight peak-arched doorways "+
        "leading in the four main map directions and their subsidiaries. "+
        "Between each doorway is a small barred alcove from which the soft "+
        "flickering glow of torch light illuminates the room. In the exact "+
        "centre of the room is a winding spiral staircase leading up to ");

    add_exit(LOCATIONS + "eblis",    "south",     0, 1);
    add_exit(LOCATIONS + "abaddon",  "east",      0, 1);
    add_exit(LOCATIONS + "balthus",  "west",      0, 1);
    add_exit(LOCATIONS + "diabolus", "north",     0, 1);
    add_exit(LOCATIONS + "mammon",   "northeast", 0, 1);
    add_exit(LOCATIONS + "shaitan",  "southeast", 0, 1);
    add_exit(LOCATIONS + "mephisto", "northwest", 0, 1);
    add_exit(LOCATIONS + "asmodeus", "southwest", 0, 1);

    add_item("azazel room", "You seem to be standing in it. (Look around).\n");

    add_item(({"coarse stone", "coarse grey stone"}), "You don't see anything "+
        "of particular interest about it.\n");

    add_item(({"alcove", "alcoves", "barred alcoves","small alcoves", "small "+
        "barred alcoves", "two small barred alcoves"}), "Alcoves in the "+
        "walls. Each one is barred and contains a softly burning torch.\n");

    add_item(({"torches", "red-flamed torches"}), "Softly glowing torches "+
        "crackling and giving off a red glow that lights the room enough "+
        "for you to be able to see properly. They are placed in barred "+
        "alcoves so nobody can reach in and take them.\n");

    add_item(({"doorways", "peaked-arched doorways", "eight peak-arched "+
        "doorways"}), "The entrances to eight other rooms from here. The "+
        "doorways are high and arch round in a curve until they meet at an "+
        "angle at the top. All around the edges of each doorway are small "+
        "carvings of little demon figures with horns, wings and pointed "+
        "tails, all engaged in similarly evil activities.\n");

    add_item(({"staircase", "winding staircase", "spiral staircase", "winding "+
        "spiral staircase"}), "A turret of stone in the middle of the room "+
        "winding like a large grey snail shell up to the ceiling where it "+
        "ends at a trapdoor. There must be many steps leading up this "+
        "staircase, as the room is quite large.\n");

    reset_puzzle_room();

    room_add_object(DOORS   + "azazel_trapdoor");
}
