#include "/d/Ansalon/common/examples/local.h"

inherit EXOUTROOM;

void
create_example_room()
{
    set_short("A narrow trail across a barren wasteland");
    set_long("@@long_descr");

    add_exit(EXROOM + "road03", "west", "@@follow_trail", 2);
}


string
long_descr()
{
    return tod_descr1() + "You are standing in front of a small " +
        "group of well growing trees. A contrast to the else barren " +
        "land around you. large bushes grow between the trees, " +
        "making it impossible to see what might hide within this " +
        "oasis. " + tod_descr2() + season_descr() + "The trail leads " +
        "westwards across the wasteland, but right here it seems to " +
        "disappear between the bushes.\n";
}

int
follow_trail()
{
    write("You follow the narrow trail westwards.\n");
    return 0;
}
