inherit "/std/room";
 
#include "/d/Emerald/defs.h"
 
void
reset_room()
{
    object ghoul , wraith ;
    int i , j ;
 
    wraith=present("wraith");
    if (wraith && wraith->query_name()!="corpse")
        return;
 
/*
    i = random(4);
    while (i-- > 0) {
        wraith=clone_object(NPC_DIR + "humanoids/wraith");
        wraith->move_living("into a room", this_object());
    }
 
    j = random(3);
    while (j-- > 0) {
        ghoul=clone_object(NPC_DIR + "humanoids/ghoul");
        ghoul->move_living("into a room", this_object());
    }
*/
}
 
void
create_room()
{
    object door;
 
    set_short("Inside grave");
    set_long( "This looks like it might be a rather comfortable "+
        "place to be - for a short time.  To the west you notice a small gap that"+
        " you might be able to crawl through.\n" );
    add_prop(ROOM_I_INSIDE, 1);
 
    door=clone_object(GRAVEYARD_DIR + "doors/door_b");
    door->move(this_object());
 
    add_exit(GRAVEYARD_DIR + "crawl1","west",0,1);
 
    set_alarm( 1.0,0.0,"reset_room");
}
