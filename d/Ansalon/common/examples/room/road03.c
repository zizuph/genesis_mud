#include "/d/Ansalon/common/examples/local.h"

inherit EXOUTROOM;

void
create_example_room()
{
    set_short("A small road across a barren wasteland");
    set_long("@@long_descr");

    add_exit(EXROOM + "road02", "north", 0, 3);
    add_exit(EXROOM + "nowhere", "south", "@@construction");
    add_exit(EXROOM + "trail01", "east", "@@follow_trail", 2);
}


string
long_descr()
{
    return tod_descr1() + "You are standing on a small " +
        "road running across a barren wasteland. This " +
        "place really looks like a desert. Most of the " +
        "vegetation is either withering or dead. However, " +
        "off to the east there seems to be a small group " +
        "of living and well growing trees. " + tod_descr2() + 
        season_descr() + "There is a small trail going east " +
        "here. The main road continues north and southwards.\n";
}


int
construction()
{
    write("The road further south is blocked untill a " +
        "wizard of Ansalon opens it. Please try again " +
        "sometime in the future.\n");

    return 1;
}


int
follow_trail()
{
    write("You follow the narrow trail eastwards.\n");
    return 0;
}
