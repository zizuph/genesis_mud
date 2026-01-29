inherit "/std/room";
 
#include "/d/Emerald/defs.h"
 
 
void
create_room()
{
    set_short("Turning tunnel");
    set_long( "You have entered a dark tunnel that turns a corner"+
        ", making it impossible to see what lies ahead.\n" );
 
    add_prop(ROOM_I_INSIDE,1);
    add_prop(ROOM_I_LIGHT,0);
 
    add_exit(GRAVEYARD_DIR + "pass17","northwest",0,1);
    add_exit(GRAVEYARD_DIR + "pass15","southwest",0,1);
 
    set_alarm( 1.0,0.0,"reset_room");
}
 
 
void
reset_room()
{
    object wraith;
    int i;
 
    wraith = present("wraith");
    if (wraith && wraith->query_name()!="corpse")
        return;
 
    for ( i=0 ; i<3 ; i++)
    {
        wraith=clone_object(GRAVEYARD_DIR + "npc/wraith");
        wraith->move(this_object());
        tell_room(this_object(), QCTNAME(wraith) + " drifts in.\n");
    }
}
