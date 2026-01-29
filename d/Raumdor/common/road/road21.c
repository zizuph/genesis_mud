/* The roads of Raumdor, by Sarr */
#include "defs.h"
inherit STD_ROOM;


void
create_room()
{
    ::create_room();
    set_short("On the roads of Raumdor");
    set_long("This is a placeholder. Hopefully you are a wizard.\n");
    add_exit(ROAD_DIR + "road20","northwest","@@block",1);
}

int
block()
{
    write("A series of barricades stand between the hills and " +
        "across the road, preventing passage southeast.\n");
    return 1;
}


int *
query_coordinates()
{
    return ({68, -6, 0}); 
}
