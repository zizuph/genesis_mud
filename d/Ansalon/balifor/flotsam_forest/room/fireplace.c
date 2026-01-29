#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/balifor/flotsam_forest/local.h"
#include <macros.h>

inherit FOREST_IN;

int door_open = 0;

void
reset_flotsam_room()
{
    return;
}

create_flotsam_room()
{
    set_short("Inside a large fireplace");
    set_long("@@long_descr");

    add_item(({"large stone fireplace","stone fireplace","large fireplace",
	"fireplace"}),"@@long_descr");
    add_item("ladder","An iron ladder has been attached to the inside " +
      "of the fireplace. It leads down under the farmhouse.\n");
    add_item(({"large grey stones","grey stones","stones"}),
      "Large grey stones make up the fireplace. The center stone on " +
      "the eastern wall seems to be loose.\n");
    add_item(({"eastern wall","center stone"}),"Hmm... it appears to " +
      "be loose. You notice a smudged hand print on it as well.\n");
    add_item(({"hand print","smudged hand print"}),"A smudged hand " +
      "print of what looks like a human hand.\n");

    add_exit(FROOM + "farm_room1","out",0);

    add_cmd_item(({"stone","large grey stone","grey stone",
	"center stone"}),({"push","pry","press"}),"@@open@@");

    reset_flotsam_room();
}

string
long_descr()
{
    return "You are inside a large stone fireplace. By the looks of things " +
    "it has not been used in a long time. It is made up of large grey " +
    "stones.\n";
}

string
open()
{
    seteuid(getuid(TO));
    if(door_open)
	write("Nothing happens.\n");
    else
    {
	tell_room(FROOM + "fireplace","A trapdoor at your feet " +
	  "slides open!\n");
	(FROOM + "hall")->secret_door_opens();
	door_open = 1;
	add_exit(FROOM + "hall","down");
	set_alarm(25.0,0.0,"secret_door_closes");
    }
    return "";
}

void
secret_door_closes()
{
    if(!door_open)
	return;
    tell_room(FROOM + "fireplace","The trapdoor at your feet " +
      "slides silently shut.\n");
    door_open = 0;
    remove_exit("down");
}
