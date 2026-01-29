inherit "/d/Gondor/common/lib/town";
#include "/d/Gondor/defs.h"

void
create_room()
{
    hillside = "north";
    height = 2;
    road = 2;
    density = 3;
    extraline = "On the west side of the staircase, a little stream " +
        "rushes downhill in a stone canal that disappears under " +
	"the pavement to the north. "+
        "The Edoras Post-office lies to the west. To your east there " +
        "is a big house made of stone and wood. That is the local " +
        "pub, the Proud Stag. The stairs lead up to a square " +
        "to the south and towards the gates to the north.";
    add_exit(EDORAS_DIR + "square1","south",0);
    add_exit(EDORAS_DIR + "ingate","north",0);
// Post Office open all day and night, Olorin, 8-nov-1994
    add_exit(EDORAS_DIR + "p_office","west", 0);
    add_exit(EDORAS_DIR + "pspub","east",0);
    make_the_room();
    add_item(({"canal","little canal","stream","little stream","river"}),BSN(
        "The little stream splashes and bubbles on its way to the " +
        "Snowstream, which runs along just outside town."));
}

int
postopen()
{
    object  clock = find_object(CLOCK);
    string  time = clock->query_time_of_day();
    if (time == "night")
    {
        write("The Post-office is closed at night. Please come back in the morning.\n");
        return 1;
    }
    return 0;
}
