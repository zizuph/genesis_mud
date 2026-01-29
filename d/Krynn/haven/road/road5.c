/* Road to Haven by Morrigan */

#include "/d/Krynn/haven/local.h"

inherit ROADBASE;

void
create_road()
{
    add_my_desc("The road to Haven turns south here, as you gain some "+
      "distance from Twin Peaks, which are barely visible to the far "+
      "north now. The Kharolis mountains loom closer to the west than "+
      "they have so far on the road, and you see that they get closer "+
      "still to the south, forming a valley only about a mile wide "+
      "between them.\n");

    add_exit(RDIR + "road6", "south", "@@valley");
    add_exit(RDIR + "road4", "northeast");

    OUTSIDE;
}

int
valley()
{
    write("You travel south, into the narrow valley "+
      "between the Kharolis mountains, and the smaller range which "+
      "lines Darken Wood to your east.\n");
    return 0;
}

