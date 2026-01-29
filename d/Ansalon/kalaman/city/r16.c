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
    set_short("On a cobbled road beside the palace walls");
    set_long("@@long_descr");

    add_item(({"palace walls","walls","wall"}),
      "Of similar grey stone to that wall surrounding the city, " +
      "this wall stands more to seperate the palace from the " +
      "main roads of Kalaman than for protection. Some creepers here have climbed " +
      "there way over the wall here.\n");
    add_item("creepers","Hardy creepers have crawled their way over from the other side " +
      "of the wall down to almost the ground on this side of the wall.\n");
    add_item(({"palace","spires"}),
      "Looking over the wall you see the spires of the palace of Kalaman, " +
      "the home of the Lord of the city, as well as the place where " +
      "his council sits.\n");
    add_item_city();

    add_exit(CITY + "r13","east",0);
    add_exit(CITY + "r17","northwest",0);

    add_cmd_item(({"wall","creepers"}),"climb","@@climb_wall");
    reset_kalaman_room();
}

string
long_descr()
{
    return "You stand on a road that runs around the wall of the " +
    "palace of the local lord of Kalaman. " + tod_descr1() + season_road() +
    "The road continues to the northwest and east.\n";
}

string
climb_wall()
{
    write("You climb the creepers over the wall " +
      "and into the palace grounds.\n");
    say(QCTNAME(TP) + " disappears over the wall to the " +
      "north.\n");
    tell_room(CITY + "garden",QCTNAME(TP)+ " arrives from " +
      "over the wall to the south.\n", 0);

    TP->move_living("M",CITY + "garden",1,0);
    return "";
}
