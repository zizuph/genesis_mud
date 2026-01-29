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
    set_short("Bottom floor of a circular lookout tower");

    add_item("floor","Nothing unusual about this floor.\n");
    add_item(({"tower","circular tower","lookout tower"}),
      "@@long_descr");
    add_item(({"stone stairway","stairway","side"}),
      "A stone stairway circles up the side of the tower to a higher level " +
      "within the tower.\n");

    add_exit(WALL + "e5","west",0);
    add_exit(WALL + "s1","south",0);
    add_exit(WALL + "t4","up",0);

    reset_kalaman_room();
}

string
long_descr()
{
    return "You stand on the bottom floor of a circular tower " +
    "designed to give the defenders of the wall of Kalaman a better " +
    "view of their surroundings. A stone stairway circles up the side of " +
    "the tower.\n";
}
