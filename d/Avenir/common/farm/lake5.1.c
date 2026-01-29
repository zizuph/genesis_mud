#include "defs.h"
inherit (THIS_DIR + "lake_base.c");

void reset_room();

void
create_room()
{

    make_the_room();
    add_exit("reed","northwest", "@@reed|northwest", 1, 1);
    add_exit("reed","west", "@@reed|west", 1, 1);
    add_exit("reed","southwest", "@@reed|southwest", 1, 1);
    add_exit("reed","south", "@@reed|south", 1, 1);
    add_exit("lake4.2","northeast", 0, 1, 1);
    add_exit("lake4.1","north", 0, 1 ,1);
    add_exit("lake5.2","east", 0, 1, 1);
    add_exit("lake6.1","southeast", 0, 1, 1);
    add_prop(ROCK, 1);
    add_prop(LAKE, 1);
    reset_room();

}

void
reset_room()
{


}

// bug fix 2009-05-25 Ophelia
// room was missing default drift method
string
query_default_drift()
{
    return "north";
}
