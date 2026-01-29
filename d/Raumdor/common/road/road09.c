/* The roads of Raumdor, credit to Sarr */
#include "defs.h"
inherit ROAD_ROOM;

void
create_room()
{
    roadWest = "northwest";
    roadEast = "northeast";
    proximity = "fork";
    longPrefix = "You are at a fork in an old warn road that runs through " +
        "great plains.";
    ::create_room();
    set_short("At a fork in the road");
    add_exit(ROAD_DIR + "road08","northwest",0,2);
    add_exit(ROAD_DIR + "road18","southeast","@@block",1);
    add_exit(ROAD_DIR + "road10","northeast",0,1);

    clone_object(ROAD_DIR + "post1")->move(TO);
}

int
block()
{
    write("A series of wooden barricades stand between the hills and " +
        "across the road, leaving no space for passage to the southeast.\n");
    say(QCTNAME(TP)+" tries to go southwest, but fails\n");
    return 1;
}
