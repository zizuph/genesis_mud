#include "/d/Ansalon/common/examples/local.h"

inherit EXOUTROOM;

void
create_example_room()
{
    set_short("A small road across a barren wasteland");
    set_long("@@long_descr");

    add_exit(EXROOM + "road02", "south", 0, 3);
}


string
long_descr()
{
    return tod_descr1() + "You are standing on a small " +
        "road running across a barren wasteland. Dried " +
        "out bushes, dead trees and various rock formations " +
        "are all that is to be seen in this deserted area. " +
        tod_descr2() + season_descr() + "The road seems " +
        "to end here, and can only be followed southwards.\n";
}
