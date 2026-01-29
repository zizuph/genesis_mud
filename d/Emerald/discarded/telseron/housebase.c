inherit "/std/room";
 
#include "/d/Emerald/defs.h"
 
public void
reset_house()
{
    object citizen;
 
    if (random(10) < 2)
        return;
    citizen = present("citizen", this_object());
    if (citizen && citizen->query_name() != "corpse")
        return;
    citizen = clone_here(TOWNSHIP_DIR + "npc/citizen");
    citizen->move_living("into a room", this_object());
}
 
public void
create_house()
{
}
 
nomask void
reset_room()
{
    reset_house();
}
 
nomask void
create_room()
{
    set_short("Inside small house");
    set_long( "You are inside a small house. It clearly looks as "+
             "if someone is living here. The place is quite tidy, but not "+
             "very large. In the centre of the room, there is a table with "+
             "some chairs, and by one of the walls, there is a bed.\n" );
 
    add_item( ({ "chair", "chairs" }), "The chairs are quite standard, the "+
              "type made by the town's carpenter.\n");
    add_item("table", "It is a small, round table.\n");
    add_item("bed", "It looks quite comfortable, although not your size.\n");
 
    add_prop(ROOM_I_INSIDE, 1);
 
    create_house();
 
    set_alarm( 1.0,0.0,"reset_room");
}
