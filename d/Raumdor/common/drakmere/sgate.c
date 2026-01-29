#include "defs.h"
inherit STD_ROOM;
/* The west gates of Drakmere, by Sarr */

void reset_room();
object gate;
object guard;
object guard2;


void
create_room()
{
    ::create_room();
    set_short("In the gatehouse of Drakmere");
    set_long("You are now inside the gatehouse of the city of Drakmere. "+
        "The huge iron gates are in front of you to the north; they lead "+
        "into the city. Guards stand here, protecting the city from "+
        "unwanted guests. Guards stand on top of the tower, patroling "+
        "around. The city walls stretch east and west from here. To "+
        "your south is the road back into the plains.\n");
    add_item("plains","They stretch all around you, save to the "+
        "northwest, where it meets the mountains.\n");
    add_exit(ROAD_DIR + "road20","south");
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

    if (!gate)
    {
        gate = clone_object("/d/Raumdor/common/drakmere/obj/south_gate_outer");
        gate->move(TO, 1);
    }
    gate->autoclose(0.0);
}

int *
query_coordinates()
{
    return ({66, -4, 0});
}
