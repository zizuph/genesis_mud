inherit "/std/room";
 
#include "/d/Emerald/defs.h"
 
 
void
create_room()
{
    set_short("Tomb");
    set_long( "This area looks like it was the burial area of "+
        "a mighty leader. A stone sarcophagus lies on a plinth in the "+
        "centre of the room, its thick lid lying smashed on the floor.\n" );
 
    add_item("plinth", "A raised stone platform in the centre of"+
        " the room. Around the edge of it are carved scenes of battle from "+
        "years long gone, before evil was driven to the fringes of the fair "+
        "land of Emerald.\n" );
 
    add_item(({"sarcophagus","lid"}), "A thick walled stone coffin"+
        ", lying on a small plinth. The lid of the sarcophagus lies smashed "+
        "on the ground, you wonder what power it would take to break such "+
        "an item.\n" );
 
    add_prop(ROOM_I_INSIDE,1);
    add_prop(ROOM_I_LIGHT,0);
 
    add_exit(GRAVEYARD_DIR + "pass17","south",0,1);
 
    set_alarm( 1.0,0.0,"reset_room");
}
 
void
reset_room()
{
    object lord;
 
    lord = present("lord");
    if(lord && lord->query_name()!="corpse")
        return;
    lord=clone_object(GRAVEYARD_DIR + "npc/skeleton_lord");
    lord->move(this_object());
    tell_room(this_object(),QCNAME(lord)+" arrives.\n");
}
