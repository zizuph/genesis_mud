#include "/d/Ansalon/common/defs.h"
#include "../local.h"
#include <macros.h>
#include <stdproperties.h>

inherit CITY_OUT;
object g1,g2, column;

void
reset_kalaman_room()
{
    if(!objectp(g1))
    {
	g1 = clone_object(KNPC + "militiaman");
	g1->arm_me();
	g1->move(TO);
    }

    if(!objectp(g2))
    {
	g2 = clone_object(KNPC + "militiaman");
	g2->arm_me();
	g2->move(TO);
    }

    if(!objectp(column))
    {
	column = clone_object("/d/Genesis/obj/donation/column");
	column->move(TO);
    }
}

create_kalaman_room()
{
    set_short("A cobbled intersection in Kalaman");
    set_long("@@long_descr");

    add_item_city();
    add_item("crossroad",
      "You stand at a crossroad that heads off northeast, northwest " +
      "and to the southeast and southwest.\n");
    add_item(({"large building","building","steps"}),
      "This large building of two stories is of spartan yet " +
      "sturdy design. Steps lead up to a closed door to your south.\n");
    add_item(({"closed door","door"}),
      "A wooden door stands closed before you. A note is pinned to it.\n");
    add_item("note","A simple piece of paper with writing on it. Try reading it.\n");

    add_cmd_item("note","read","@@read_note");
    add_cmd_item(({"door","wooden door"}),"open","@@open_door");

    add_exit(CITY + "r1","northeast",0);
    add_exit(CITY + "r3","southeast",0);
    add_exit(CITY + "r4","northwest",0);
    add_exit(CITY + "r5","southwest",0);

    reset_kalaman_room();
}

string
long_descr()
{
    return "You have come to a crossroad in the city " +
    "of Kalaman. " +tod_descr1() + season_road() +
    "To your south is a large building with a closed door.\n";
}

string
open_door()
{
    write("You try and open the door, but it is barred shut.\n");
    say(QCTNAME(TP)+ " tries and opens the door, but it is " +
      "barred shut.\n");
    return "";
}

string
read_note()
{
    write("The note reads: \n" +
      "   The guildhall of the Kalaman militia has\n" +
      "   been closed temporarily.\n\n");
    say(QCTNAME(TP) + " reads a note pinned to the door to " +
      "the south.\n");
    return "";
}
