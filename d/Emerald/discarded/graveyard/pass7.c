inherit "/d/Emerald/std/dir_room";
 
#include "/d/Emerald/defs.h"
 
#define DP(LABEL) ("@@dir_phrase|" + LABEL + "@@")
#define SOUTH GRAVEYARD_DIR + "pass8"
#define NORTH GRAVEYARD_DIR + "pass6"
 
 
void
create_room()
{
    set_short("Bad smelling passage");
    set_long( "The smell in this area of the caves is getting "+
        "quite bad, and acrid smell that irritates your nose and throat. "+
        "The passage continues to the "+DP("direction")+" where the air seems "+
        "to be getting "+DP("air")+".\n" );
 
    add_dir_phrase("direction", NORTH, "south");
    add_dir_phrase("direction", SOUTH, "north");
    add_dir_phrase("direction", 0, "north");
 
    add_dir_phrase("air", NORTH, "worse");
    add_dir_phrase("air", SOUTH, "better");
    add_dir_phrase("air", 0, "better");
 
    add_prop(ROOM_I_INSIDE,1);
    add_prop(ROOM_I_LIGHT,0);
 
    add_exit(GRAVEYARD_DIR + "pass6","north",0,1);
    add_exit(GRAVEYARD_DIR + "pass8","south",0,1);
 
    set_alarm( 1.0,0.0,"reset_room");
}
 
 
void
reset_room()
{
    object ant;
 
    ant=present("ant");
    if (ant && ant->query_name() != "corpse")
        return;
 
    ant = clone_object(GRAVEYARD_DIR + "npc/ant");
    ant->move(this_object());
    ant -> move_object(this_object());
    tell_room(this_object(), QCTNAME(ant) + " scurries in.\n");
}
