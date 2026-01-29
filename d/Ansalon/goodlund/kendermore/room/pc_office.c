#include "../local.h"
#include "/d/Ansalon/common/defs.h"
#include <macros.h>

inherit KENDERMORE_IN;
inherit STREET_DESC;

void
reset_kendermore_room()
{
    return;
}

void
create_kendermore_room()
{
    set_short("A small waiting room");

    set_long("You stand in a simple room. The room appers to be the entrance "+
        " to an office. " +
        "The front door stands to the southeast, and another door leads " + 
        "further into the office to the north. Other the " + 
        "doors and a small window in the east wall, the room is " + 
        "sparsely decorated.\n");
    add_item("doors", "There are two of them, one to the north, and one " + 
        "to the southeast.\n");
    add_item(({"back door", "north door"}), "It stands propped open with " + 
        "a heavy stone.\n");
    add_item(({"southeast door", "front door"}), "It leads out to the " + 
        "street.\n");
    add_item(({"street", "window", "small window"}), "Open shutters are " + 
        "attached to the window, and you can see out into the street.\n");
    add_item("street", "@@street_descr@@\n");
    add_item(({"wall", "walls"}), "They are made of unadorned wood. You " +
             "see a curtain covering the west wall.\n");
    add_item(({"curtain", "curtains"}), "It covers the west wall, which "+
	     "appears to lead into the waiting room.\n");
    add_cmd_item(({"behind curtain", "through curtain"}), ({"move", "enter"}), "@@move_curtain@@");

    add_exit(KROOM + "street53", "southeast", 0);
    add_exit(KROOM + "pc_boffice", "north", "@@in_message");

    reset_kendermore_room();
    return;
}

string
move_curtain()
{
  write("You enter through the curtain into the waiting room.\n");
  TP->move_living("through the curtain into the waiting room", KROOM+"waiting1", 1, 0);
  return "";
}

int
in_message()
{
    write("You walk through the open door into the doctor's office.\n");
    return 0;
}
