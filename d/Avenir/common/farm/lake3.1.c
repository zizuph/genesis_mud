#include "defs.h"
inherit (THIS_DIR + "lake_base.c");

void reset_room();

void
create_room()
{

    make_the_room();
    add_exit("reed","northwest", "@@reed|northwest", 1, 1);
    add_exit("reed","west", "@@reed|west", 1, 1);
    add_exit("reed","north", "@@reed|north", 1, 1);
    add_exit("lake4.1","southwest", 0, 1, 1);
    add_exit("lake4.2","south", 0, 1, 1);
    add_exit("lake2.1","northeast", 0, 1, 1);
    add_exit("lake3.2","east", 0, 1, 1);
    add_exit("lake4.3","southeast", 0, 1, 1);
    add_prop(ROCK, 1);
    add_prop(LAKE, 1);
    reset_room();

}

void
reset_room()
{


}

string
query_default_drift()
{
    return "southwest";
}
