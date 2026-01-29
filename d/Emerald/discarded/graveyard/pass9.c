inherit "/std/room";
 
#include "/d/Emerald/defs.h"
 
 
void
create_room()
{
    set_short("Cold passage");
    set_long( "You are standing in a cool twisting passage "+
        "running north and south.\n" );
 
    add_prop(ROOM_I_LIGHT,0);
    add_prop(ROOM_I_INSIDE,1);
 
    add_exit(GRAVEYARD_DIR + "cave5","north",0,1);
    add_exit(GRAVEYARD_DIR + "cave6","south",0,1);
 
    set_alarm( 1.0,0.0,"reset_room");
}
 
 
void
reset_room()
{
    object ant;
 
    ant = present("ant");
    if (ant && ant->query_name()!="corpse")
        return;
 
    ant = clone_object(GRAVEYARD_DIR + "npc/fire_ant");
    ant->move(this_object());
    tell_room(this_object(),QCTNAME(ant) + " arrives.\n");
}
