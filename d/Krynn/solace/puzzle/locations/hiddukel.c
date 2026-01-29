/* The Hiddukel room. ~solace/puzzle/locations/hiddukel */

#include "../defs.h"

inherit ROOM_DEFS;

#define NOT_RESET ({ "entrance", "hiddukel" })

string *names_and_dirs = ({ });

string query_room_dir_from_name(string name);

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

void set_random_exits()
{
    int i, j;
    string *room_dirs, *room_names;

    names_and_dirs = ({ });

    room_dirs = EXIT_CMDS[12..18];
    room_names = exclude_array(CENTRAL_ROOMS, 2, 3);

    while(sizeof(room_dirs) > 0)
    {
        i = random(sizeof(room_dirs));
        j = random(sizeof(room_names));

        add_exit(LOCATIONS + room_names[j], room_dirs[i], 0, 1);

        names_and_dirs += ({ ({ room_names[j], room_dirs[i] }) });

        room_names = exclude_array(room_names, j, j);
        room_dirs = exclude_array(room_dirs, i, i);
    }

    add_exit(LOCATIONS + "paladine", "southeast", 0, 1);
}

void change_puzzle_exits(string room)
{
    int i;
    object obj;
    string *exits, tmp;

    obj = find_object(LOCATIONS + room);

    exits = obj->query_exit_cmds();

    if(sizeof(exits))
    {
        for(i = 0; i < sizeof(exits); i++)
            obj->remove_exit(exits[i]);
    }

    tmp = query_room_dir_from_name(room);

    obj->add_exit(LOCATIONS + "hiddukel", tmp, 0, 1);
}

void reset_puzzle_room()
{
    int i;
    object obj;
    string *rooms, *exits;

    clear_room();
    reset_neighbours();

    exits = query_exit_cmds();

    if(sizeof(exits))
    {
        for(i = 0; i < sizeof(exits); i++)
            remove_exit(exits[i]);
    }

    set_random_exits();

    rooms = exclude_array(CENTRAL_ROOMS, 2, 3);

    for(i = 0; i < sizeof(rooms); i++)
        change_puzzle_exits(rooms[i]);

    room_add_object(WEAPONS + "hammer");
}

void create_puzzle_room()
{
    set_short("The Hiddukel room");
    set_long("This room is large and round and made from the same coarse grey "+
        "stone as the areas above. There are eight peak-arched doorways "+
        "leading in the four main map directions and their subsidiaries. "+
        "Between each doorway is a small barred alcove from which the soft "+
        "flickering glow of torch light illuminates the room. In the exact "+
        "centre of the room is a winding spiral staircase leading up to ");

    add_item("hiddukel room", "You are standing in it. (Look around).\n");

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

    room_add_object(DOORS   + "hiddukel_trapdoor");
}

string query_room_dir_from_name(string name)
{
    int i;
    mixed tmp, dir_from_hid;

    for(i = 0; i < sizeof(names_and_dirs); i++)
    {
        tmp = names_and_dirs[i][0];

        if(tmp == name)
            break;
    }

    dir_from_hid = names_and_dirs[i][1];

    for(i = 0; i < sizeof(ROOM_OPPOSITES); i++)
    {
        tmp = ROOM_OPPOSITES[i][0];

        if(tmp == dir_from_hid)
            break;
    }

    return ROOM_OPPOSITES[i][1];
}
