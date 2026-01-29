#include "/d/Ansalon/common/examples/local.h"

inherit EXOUTROOM;

void
create_example_room()
{
    set_short("A small road across a barren wasteland");
    set_long("@@long_descr");

    add_exit(EXROOM + "road01", "north", 0, 3);
    add_exit(EXROOM + "road03", "south", 0, 3);
}


string
long_descr()
{
    return tod_descr1() + "You are standing on a small " +
        "road running across a barren wasteland. An " +
        "occasional withering tree, some small tangled " +
        "bushes or a lone formation of rock are all " +
        "that is within view from here. " + tod_descr2() +
        season_descr() + "The road continues in a " +
        "north-south direction.\n";
}
