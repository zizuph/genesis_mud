/* By Sarr */
#include "defs.h"
inherit ROAD_ROOM;

string *allowed = ({
    COMMON_NPC_DIR + "high_priest",
    COMMON_NPC_DIR + "labourer",
    COMMON_NPC_DIR + "mason",
    STEEDS_DIR + "carthorse",
});

void
create_room()
{
    ::create_room();
    set_short("On a dirt road in Drakmere");
    set_long("You are on a little dirt path that leads from the main "+
    "road at the north to the back entrance to the stone keep to the south.\n");
    add_item("guard","Unmoving and firm.\n");
    add_item(({"entrance","door"}),
        "It is a large banded wooden door that leads into the keep.\n");
    add_exit(KEEP_DIR + "backstage","south","@@block",0,0);
    add_exit(DRAKMERE_DIR + "road12","north",0,0,0);
    CLOCK->add_event(this_object());
}

int
block()
{
    if (TP->query_drakmere_guard() || member_array(MASTER_OB(TP), allowed) >= 0)
        return 0;
    write("A shutter on the door opens as you approach.\n");
    write("Someone on the other side says: You may not enter this way. " +
      "Go around to the front if you have business in the keep.\n");
    return 1;
}

mixed
query_waypoint_direction(string waypoint)
{
    if (waypoint == "drakmere" || waypoint == "road")
        return "north";
    if (waypoint == "keep")
        return "south";
    return 0;
}
