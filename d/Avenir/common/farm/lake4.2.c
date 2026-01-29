#include "defs.h"
inherit (THIS_DIR + "lake_base.c");

void reset_room();

void
create_room()
{

    make_the_room();
    add_exit("reed","northwest", "@@reed|northwest", 1, 1);
    add_exit("lake5.2","south", 0, 1, 1);
    add_exit("lake3.1","north", 0, 1, 1);
    add_exit("lake4.3","east", 0, 1, 1);
    add_exit("lake4.1","west", 0, 1, 1);
    add_exit("lake3.2","northeast", 0, 1, 1);
    add_exit("lake5.3","southeast", 0, 1, 1);
    add_exit("lake5.1","southwest", 0, 1, 1);
    add_prop(ROCK, 1);
    add_prop(LAKE, 1);
    reset_room();

}

void
reset_room()
{


}

int
boathouse(string str)
{
    if (!environment(this_player())->id("boat"))
        return 0;
    write("The reed is thinner here and doesnt stop anyone " +
        "from passing through.\n");
    return 0;
}
 
string
query_default_drift()
{
    return "west";
}
