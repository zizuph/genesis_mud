inherit "/std/room";
 
#include "/d/Emerald/defs.h"
 
void
create_room()
{
    set_short("Twisting passage");
    set_long( "You are standing in a twisting tunnel under the "+
        "the graveyard.\n" );
 
    add_prop(ROOM_I_INSIDE,1);
    add_prop(ROOM_I_LIGHT,0);
 
    add_exit(GRAVEYARD_DIR + "pass15","southwest",0,1);
    add_exit(GRAVEYARD_DIR + "cave9","north",0,1);
 
    set_alarm( 1.0,0.0,"reset_room");
}
 
 
void
reset_room()
{
    object mummy;
 
    mummy = present("mummy");
    if (mummy && mummy->query_name()!="corpse")
        return;
 
    mummy=clone_object(GRAVEYARD_DIR + "npc/mummy.c");
    mummy->move(this_object());
    tell_room(this_object(),QCTNAME(mummy)+" arrives.\n");
}
