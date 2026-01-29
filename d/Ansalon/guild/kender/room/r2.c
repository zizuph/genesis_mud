#include "/d/Ansalon/common/defs.h"
#include "../local.h"
#include <macros.h>
#include <stdproperties.h>

inherit KEN_IN;

void
reset_kendermore_room()
{
    return;
}

create_kendermore_room()
{
    set_short("@@short_descr");
    set_long("@@long_descr");

    add_item(({"giant oak tree","oak tree","tree"}),
      "You are standing within a giant oak tree. Wow.\n");
    add_item(({"trunk","hollowed trunk"}),
      "The hollowed trunk of the tree allows sunlight in from " +
      "high above. The curious could probably climb up to the " +
      "top of the hollow.\n");
    add_item("opening","An opening between the beginnings " +
      "of two huge roots is to your south.\n");
    add_item(({"twisted root","root"}),
      "A twisted root twirls downward like a stairway " +
      "to a room underneath you.\n");
    add_item(({"room","small room"}),
      "There is a small room down from here.\n");

    add_exit(KROOM + "r1","south",0);
    add_exit(KROOM + "r3","down","@@go_down");
    add_exit(KROOM + "r4","up","@@go_up");

    reset_kendermore_room();
}

int
go_down()
{
    write("You make your way down the twisty root...\n");
    return 0;
}

int
go_up()
{
    /*
	if(TP->query_race_name() != "kender")
	{
	    write("You are not curious enough to climb up " +
	      "there... you could break your neck!\n");
	    return 1;
	}
    */
    write("You scamper up the side of the hollow...\n");
    say(QCTNAME(TP) + " scampers up the side of the hollow.\n");
    return 0;
}


string
short_descr()
{
    return "Within the base of a giant oak tree";
}

string
long_descr()
{
    return "You stand within the hollow base of a giant " +
    "oak tree. Filtered sunlight streams down from high " +
    "above through the hollowed trunk of the tree. An opening " +
    "here leads out to the south, while a twisted root twirls " +
    "downward like a stairway to another small room. " +
    "\n";
}
