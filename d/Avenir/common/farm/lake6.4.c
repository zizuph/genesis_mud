#include "defs.h"
inherit (THIS_DIR + "lake_base.c");

void reset_room();

void
create_room()
{

    make_the_room();
    add_exit("lake5.4","northwest", 0, 1, 1);
    add_exit("lake6.3","west", 0, 1, 1);
    add_exit("lake5.6","northeast", 0, 1, 1);
    add_exit("lake5.5","north", 0, 1, 1);
    add_exit("lake6.5","east", 0, 1, 1);
    add_exit("lake7.3","south", 0, 1, 1);
    add_exit("reed","southeast", "@@reed|southeast", 1, 1);
    add_exit("lake7.2","southwest", 0, 1, 1);
    add_prop(MILL, 1);
    add_prop(TOWER, 1);
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

/*
This is the map over the lake:

                                      M
                                     1.1
                           2.1       2.2        2.3
                3.1        3.2       3.3        3.4         3.5
BH----  4.1     4.2        4.3       4.4        4.5         4.6     4.7 R
                                      X
        5.1     5.2        5.3       5.4        5.5         5.6     5.7
                6.1        6.2       6.3        6.4         6.5
                           7.1       7.2        7.3
                                     8.1
                                     AH

AH   = Abandoned house
R    = Rock
M    = Mill
BH   = Boathouse
X    = Sunken boat

*/
