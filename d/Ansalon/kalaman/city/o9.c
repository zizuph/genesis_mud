#include "/d/Ansalon/common/defs.h"
#include "../local.h"
#include <macros.h>
#include <stdproperties.h>

inherit CITY_OUT;

void
reset_kalaman_room()
{
    return;
}

create_kalaman_room()
{
    set_long("@@long_descr");

    set_short("To the southeast of the wall surrounding Kalaman");
    add_item("wall","To your northwest rises the wall surrounding the city " +
      "of Kalaman.\n");
    add_item(({"city","kalaman"}),
      "You can't see much of it. A wall is in the way.\n");
    add_item(({"small path","path"}),
      "A small path, hardly noticeable, follows the edge of the wall.\n");

    add_exit(CITY + "o10","northeast",0);
    add_exit(CITY + "o8","southwest",0);

    reset_kalaman_room();
}

string
long_descr()
{
    return "You stand to the southeast of the wall surrounding the city of Kalaman. " +
    tod_descr1() +
    "A small path seems to follow the edge of the wall.\n";
}
