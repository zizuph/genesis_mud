/* 
   Example room to demonstrate a messaging example, 
   in this case for splashing water.
*/ 

#include <stdproperties.h>
#include <macros.h>

inherit "/std/room"; 



void
create_splash_room()
{
}


void
create_room()
{
    set_short("Simple water room");
    set_long("A simple water room.\n");  
    add_prop(ROOM_I_TYPE, ROOM_IN_WATER); 
    create_splash_room(); 
}


void
water_splashed(object where, object who)
{
    tell_room(this_object(), QCTNAME(who) + " makes a " +
              "huge splash nearby and some of the water " +
              "hits you!\n");
    /* Might also want to make use of where, who knows. */ 
}


int
do_splash(string str)
{
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
