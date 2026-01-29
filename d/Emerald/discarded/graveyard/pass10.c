inherit "/std/room";
 
#include "/d/Emerald/defs.h"
 
 
void
create_room()
{
    set_short("dark winding passage");
    set_long( "You are walking along a dark, damp passage. "+
        "Water trickles from a crack in the roof, forming puddles on the "+
        "floor.\n" );
 
    add_item(({"puddle","puddles","floor"}), "The floor of this "+
        "room is littered with small murky puddles.\n" );
 
    add_item("crack", "A small crack overhead, which has a "+
        "constant stream of water falling from it.\n" );
 
    add_prop(ROOM_I_INSIDE,1);
    add_prop(ROOM_I_LIGHT,0);
 
    add_exit(GRAVEYARD_DIR + "cave5","southwest",0,1);
    add_exit(GRAVEYARD_DIR + "pass11","southeast",0,1);
 
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
    ant -> move(this_object());
    tell_room(this_object(), QCTNAME(ant) + " arrives.\n");
}
