inherit "/std/room";
 
#include "/d/Emerald/defs.h"
 
 
void
create_room()
{
    set_short("small cave");
    set_long( "This is a small rocky cave. Water trickles from "+
        "several small fissures in the roof and seeps through faults in the "+
        "floor.\n" );
 
    add_item(({"fissure","fissures"}), "There are many small "+
        "cracks in the roof through which water flows.\n" );
 
    add_prop(ROOM_I_INSIDE,1);
    add_prop(ROOM_I_LIGHT,0);
 
    add_exit(GRAVEYARD_DIR + "pass11","west",0,1);
 
    set_alarm( 1.0,0.0,"reset_room");
}
 
 
 
void
reset_room()
{
    object ant;
    int i;
 
    ant = present("ant");
    if (ant && ant -> query_name() != "corpse")
        return;
 
    for (i=0 ; i<3 ; i++)
    {
        ant = clone_object(GRAVEYARD_DIR + "npc/fire_ant");
        ant -> move(this_object());
        tell_room(this_object(),QCTNAME(ant) + " arrives.\n");
    }
}
