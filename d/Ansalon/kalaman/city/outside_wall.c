#include "/d/Ansalon/common/defs.h"
#include "../local.h"
#include <macros.h>
#include <stdproperties.h>

inherit CITY_OUT;

#define OTHER_ROOM CITY + "r33"
#define SECRET_DOOR KOBJ + "secret_doorb"

int dAlarm_id1;
object door;

void remove_door();

void
reset_kalaman_room()
{
    return;
}

create_kalaman_room()
{
    set_long("@@long_descr");
    set_short("To the south of the wall surrounding Kalaman");

    add_item(({"kalaman","city of kalaman","city"}),
      "To your north rises the great wall that surrounds the " +
      "city of Kalaman.\n");
    add_item(({"great wall","wall"}),
      "To your north rises the great wall surrounding Kalaman. " +
      "You notice a hidden stone panel set into the wall.\n");
    add_item(({"hidden stone panel","stone panel","panel"}),
      "A hidden stone panel has been set into the wall. " +
      "You could probably push it.\n");

    add_exit(CITY + "o1","east",0);
    add_exit(CITY + "o14","northwest",0);
    add_exit(PLAINS + "1a","south",0);


    reset_kalaman_room();
}

int
no_go()
{
    write("Around the corner you see a few guards patrolling that part of the " +
      "wall. You decide its best not to draw any attention to yourself sneaking " +
      "around at the base of the wall, seeing that there are numerous archers " +
      "up above you.\n");
    return 1;
}

string
long_descr()
{
    return "You stand to the south of the great wall surrounding " +
    "the city of Kalaman. " +tod_descr1()+
    "\n";
}

init()
{
    ::init();
    ADA("push");
}

#include "secret_door.h";
