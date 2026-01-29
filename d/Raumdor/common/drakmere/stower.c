#include "defs.h"
inherit STD_ROOM;
/* By Sarr */

object guard;
object guard2;
object guard3;
object guard4;

void reset_room();

void
create_room()
{
    add_prop(ROOM_I_INSIDE, 1);
    ::create_room();
    set_short("Inside the south guard tower");
    set_long("You are now within the south guard tower. It is a large "+
    "room with guards wandering about. Along the walls are torches, as "+
    "well as racks for armours and weapons. A table stands off to the "+
    "side, with food and drinks on it. There is a spiral staircase that "+
    "leads up to the top level of the tower.\n");
    add_item("table","You see food and drinks on it, some half eaten.\n");
    add_item("racks","They hold the guard's weapons and armours.\n");
    add_item("torches","They light up the area when it is dark.\n");
    add_item("staircase","A stone staircase that spirals up.\n");
    add_exit(DRAKMERE_DIR + "stower2","up",0);
    add_exit(DRAKMERE_DIR + "road11","west",0);
    reset_room();
}

void
reset_room()
{
    if(!guard)
    {
        guard = clone_object(DRAKMERE_NPC_DIR + "dguard_s");

        guard->move_living("xxx",TO);
    }
    if(!guard2)
    {
        guard2 = clone_object(DRAKMERE_NPC_DIR + "dguard_s");

        guard2->move_living("xxx",TO);
    }
    if(!guard3)
    {
        guard3 = clone_object(DRAKMERE_NPC_DIR + "dguard_s");

        guard3->move_living("xxx",TO);
    }
    if(!guard4)
    {
        guard4 = clone_object(DRAKMERE_NPC_DIR + "dguard_s");

        guard4->move_living("xxx",TO);
    }

}

int *
query_coordinates()
{
    return ({67, -3, 0});
}
