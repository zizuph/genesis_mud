#include "defs.h"
inherit (THIS_DIR + "lake_base.c");

void reset_room();

void
create_room()
{

    make_the_room();
    add_exit("lake4.1","northwest", 0, 1, 1);
    add_exit("lake6.1","south", 0, 1, 1);
    add_exit("lake4.2","north", 0, 1, 1);
    add_exit("lake4.3","northeast", 0, 1, 1);
    add_exit("lake5.1","west", 0, 1, 1);
    add_exit("lake5.3","east", 0, 1, 1);
    add_exit("lake6.2","southeast", 0, 1, 1);
    add_exit("lake5.1","southwest", "@@reed|northwest", 1, 1);
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
    return "northwest";
}
