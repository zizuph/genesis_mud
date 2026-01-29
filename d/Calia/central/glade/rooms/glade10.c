//ROOM: Triel glade 10

// INCLUSIONS AND DEFINITIONS

inherit "/std/room";

#include <stdproperties.h>
#include <macros.h>
#include <defs.h>

// ROOM DEFINITION

void
create_room()

{
    set_short("triel glade");
    set_long("You are currently swimming in a warm pool of water.\n");
    add_prop(ROOM_I_TYPE, ROOM_IN_WATER);
    add_exit(GLADE_ROOMS + "glade6", "northeast", 0);

void
create_splash_room();
}

void

water_splashed(object where, object who)

{

    tell_room(this_object(), QCTNAME(who) + " makes a " + 
         "huge splash in the pool and some of the water hits you!\n");

}

int

do_splash(string str)

    int i;
    string *exit_rooms;
    write("You splash around in the water!\n");
    say(QCTNAME(this_player()) + " splashes around in the water!\n");
    exit_rooms = query_exit_rooms();
    for (i = 0; i < sizeof(exit_rooms); i++)
    exit_rooms[i]->water_splashed(this_object(), this_player());
    return 1; 
}

void
init()
{
    ::init();
    add_action(do_splash, "splash");




}
