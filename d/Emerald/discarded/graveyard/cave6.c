inherit "/std/room";
 
#include "/d/Emerald/defs.h"
 
 
void
create_room()
{
    set_short("Queen ant chamber");
    set_long( "The smell when you enter this room is overpowering "+
        "Its the same acrid, burning smell that you have come to expect of "+
        "area, but many times worse.\n" );
 
    add_prop(ROOM_I_LIGHT,0);
    add_prop(ROOM_I_INSIDE,1);
 
    add_exit(GRAVEYARD_DIR + "pass9","north",0,1);
 
    clone_object(GRAVEYARD_DIR + "obj/corpse")->move( TO );
 
    set_alarm( 1.0,0.0,"reset_room");
}
 
 
void
reset_room()
{
    object ant;
 
    ant = present ("ant");
    if (ant && ant -> query_name()!="corpse")
        return;
 
    ant=clone_object(GRAVEYARD_DIR + "npc/queen_ant");
    ant->move(this_object());
    tell_room(this_object(), QCTNAME(ant) + " arrives.\n");
}
