/* Start trapdoor. ~solace/puzzle/doors/start_trapdoor */

inherit "/std/door";

#include "../defs.h"

void create_door()
{
    set_name("start_trapdoor");
    set_door_name(({"trapdoor", "strong trapdoor", "iron-bound trapdoor",
        "strong iron-bound trapdoor"}));

    set_door_desc("A thick wooden trapdoor bound by strips of iron to for "+
        "strength. It is hinged to the floor so that it can be opened and "+
        "closed.\n");

    set_open(0);
    set_locked(0);

    set_door_id("azazel_trapdoor");
    set_other_room(LOCATIONS + "azazel");

    set_open_command("open");
    set_close_command("close");
    set_pass_command(({ "d", "down" }));

    set_open_desc("an iron-bound wooden trapdoor lies open on the floor.\n");
    set_closed_desc("an iron-bound wooden trapdoor lies closed on the floor.\n");

    set_open_mess(({"heaves the trapdoor open", "The trapdoor in the ceiling "+
        "is heaved open by someone in the room above you"}));

    set_close_mess(({"heaves the trapdoor shut", "The trapdoor in the ceiling "+
        "is heaved shut by someone in the room above you"}));
}

void let_them_open_door(string arg)
{
    ::open_door(arg);
}

void let_them_close_door(string arg)
{
    ::close_door(arg);
}

int open_door(string arg)
{
    object door1, door2;

    door2 = present("start_door", E(TO));
    door1 = present("ent_door", find_object(LOCATIONS + "entrance"));

    if(member_array(arg, query_door_name()) == -1)
        return 0;

    if(!query_open())
    {
        door1->do_close_door();
        door2->do_close_door();

        tell_room(E(door1), "The strong metal door to the north slams shut.\n");
        tell_room(E(door2), "The strong metal door to the south slams shut.\n");
    }

    let_them_open_door(arg);
    return 1;
}

int close_door(string arg)
{
    object door1, door2;

    door2 = present("start_door", E(TO));
    door1 = present("ent_door", find_object(LOCATIONS + "entrance"));

    if(member_array(arg, query_door_name()) == -1)
        return 0;

    if(query_open())
    {
        door1->do_open_door();
        door2->do_open_door();

        tell_room(E(door1), "The strong metal door to the north creaks open.\n");
        tell_room(E(door2), "The strong metal door to the south creaks open.\n");
    }

    let_them_close_door(arg);
    return 1;
}
