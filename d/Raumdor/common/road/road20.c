/* The roads of Raumdor, by Sarr */
#include "defs.h"
inherit STD_ROOM;


void
create_room()
{
    ::create_room();
    set_short("On the roads of Raumdor");
    set_long("You are on a old worn road that runs east into the city "+
    "gates. All around you, you see flat plains, fields and "+
    "rock hills. The air is cold and stale, and you can almost feel "+
    "the bleakness that envelopes this place. The road is dirt in "+
    "some places, and made of cobblestone in other places. " +
    "The gatehouse of the city is just to the north.\n");
    add_item("road","It is old and worn, made of dirt and stone.\n");
    add_item("plains","They stretch all around you, save to the "+
    "northwest, where it meets the Kolpharian and Worldsrim mountains. "+
    "You can see a city to the south and east of you.\n");
    add_item("gatehouse","It is large, with guards on top.\n");
    add_item("city","It is a large walled city.\n");
    add_item("hills","They roll on for as far as you can see.\n");
    add_item("gates","Huge iron gates that block out unwanted visitors.\n");
    add_exit(DRAKMERE_DIR + "sgate","north",0,1);
    add_exit(ROAD_DIR + "road21","southeast","@@block",1);
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
    return ({66, -5, 0}); 
}
