inherit "/std/room";
 
#include "/d/Emerald/defs.h";
 
 
void
create_room()
{
    set_short("Winding passage");
    set_long( "You are walking along a dark winding passage. To the "+
        "south, you think you see an insectoid shape move, but it might just "+
        "have been a shadow thrown from your light.\n" );
 
    add_prop(ROOM_I_INSIDE,1);
    add_prop(ROOM_I_LIGHT,0);
 
    add_exit(GRAVEYARD_DIR + "pass7","south",0,1);
    add_exit(GRAVEYARD_DIR + "cave3","west",0,1);
}
