/* By Sarr */
/* 2018-02-14 Malus: Make gates into door object */ 
#include "defs.h"
inherit ROAD_ROOM;

object gate;
object guard;
object guard2;
void reset_room();


void
create_room()
{
    ::create_room();
    set_short("On a dirt road in Drakmere");
    set_long("You are on a dirt road in the west part of the city of "+
    "Drakmere. Directly to the west lies the west gatehouse, and "+
    "to the north, the guard tower. Looking up along the tower and "+
    "walls, you see guards patroling around. The road continues "+
    "east into the heart of the city, and south to a large keep.\n");
    add_exit(DRAKMERE_DIR + "road13","east",0,0,0);
    add_exit(DRAKMERE_DIR + "wtower","north",0,0,0);
    add_exit(DRAKMERE_DIR + "road22","south",0,0,0);
    add_item(({"keep"}),"A large stone keep, where the royalty live. "+
    "You will probably find the Lord of Drakmere himself in there somewhere.\n");
    add_item(({"gatehouse"}),"A rather large looking gate with armed "+
    "guards standing on top.\n");
    add_item(({"tower"}),"A tall tower where the guards sometimes "+
    "eat and sleep.\n");
    add_item(({"walls","wall"}),"Huge stone walls surround the city, "+
    "keeping it safe from the creatures outside. Guards patrol around, "+
    "keeping a vigilant eye for danger.\n");
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
        gate = clone_object("/d/Raumdor/common/drakmere/obj/west_gate_inner");
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
    if (waypoint == "keep")
        return "south";
    return 0;
}
