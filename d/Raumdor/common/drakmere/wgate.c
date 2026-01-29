/* The west gates of Drakmere, by Sarr */
/* 2018-02-14 Malus: Make gates into door object */ 
#include "defs.h"
inherit STD_ROOM;

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
        "The huge iron gates are in front of you to the east, leading "+
        "into the city. Guards stand on top of the tower, patroling "+
        "around. The city walls stretch north and south from here. To "+
        "your west is the road back into the plains.\n");
    add_item("plains","They stretch all around you, save to the "+
    "northwest, where it meets the Kolpharian and Worldsrim mountains.\n");
    add_exit(ROAD_DIR + "road17","west");
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
        gate = clone_object("/d/Raumdor/common/drakmere/obj/west_gate_outer");
        gate->move(TO, 1);
    }
    gate->autoclose(0.0);
}

mixed
query_waypoint_direction(string waypoint)
{
    if (waypoint == "road")
        return "west";
    if (waypoint == "drakmere")
        return "east";
    return 0;
}

int *
query_coordinates()
{
    return ({60, 2, 0});
}
