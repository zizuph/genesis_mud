#include "/d/Ansalon/common/defs.h"
#include "../local.h"
#include <macros.h>
#include <stdproperties.h>

inherit KALAMAN_IN;

void
reset_kalaman_room()
{
    return;
}

create_kalaman_room()
{
    set_long("@@long_descr");
    set_short("Upper floor of the palace of Kalaman");

    add_item(({"spiral staircase","staircase"}),
      "A graceful spiral staircase makes its way down to the ground " +
      "floor of the palace.\n");
    add_item(({"great doors","doors"}),
      "To your north a pair of great doors open onto the " +
      "Council Hall of the palace.\n");
    add_item(({"council hall","circular council hall","hall"}),
      "To your north is the circular Council Hall of the palace, " +
      "where the Council of Kalaman as well as the Lord of Kalaman " +
      "meet over matters of state.\n");

    add_exit(CITY + "p5","north",0);
    add_exit(CITY + "p3","down",0);

    reset_kalaman_room();
}

string
long_descr()
{
    return "You stand on the upper floor of the palace of Kalaman. " +
    "To your north a pair of great doors open into the circular " +
    "Council Hall of the palace. A spiral staircase leads down " +
    "from here to the ground floor.\n";
}
