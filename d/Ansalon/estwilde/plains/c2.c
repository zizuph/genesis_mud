#include "/d/Ansalon/common/defs.h"
#include "../local.h"
#include <macros.h>
#include <stdproperties.h>

inherit DWARF_IN;

#define DOOR_ROOM "/d/Ansalon/estwilde/plains/c1"

object trap;

void
reset_dwarf_room()
{
    if(!objectp(trap))
   {
    trap = clone_object(EOBJ + "false_coin");
    trap->move(TO);
   }
}

create_dwarf_room()
{
    set_short("@@short_descr");
    set_long("@@long_descr");
    add_item(({"ancient stone walls","stone walls","walls"}),
      "Ancient walls of stone rise to a low ceiling in this "+
      "cairn.\n");
    add_item(({"ceiling","low ceiling"}),
      "Just above your head is the ceiling of the cairn. It is "+
      "low, typical of dwarven design.\n");
    add_item(({"cairn","ancient dwarven cairn","dwarven cairn"}),
      "You stand within the resting place of a dwarven warrior "+
      "of the Neidar clan.\n");
    add_item(({"floor","dust"}),
      "The floor here is covered with dust. You doubt anyone has "+
      "been here for a long time.\n");
    add_item("stairway","A stairway, cloaked in cobwebs, leads down "+
      "into the depths of the cairn.\n");
    add_item("cobwebs","Thick cobwebs drape themselves from "+
      "the ceiling to the floor here like an ancient "+
      "shawl.\n");

    DARK;

    add_cmd_item(({"coin", "gold coin", "coins", "all"}),
      ({"get","take"}),"@@set_off_trap");
    add_cmd_item(({"trap","coin","gold coin"}), "disarm",
      "@@disarm_trap");
    add_exit(ROOM + "c1","east",0);
    add_exit(ROOM + "c3","down","@@go_down");

    reset_dwarf_room();
}

string
disarm_trap()
{
    return "The best way to not set off the trap, is " +
    "to leave it alone.\n";
}

string
set_off_trap()
{
    string str;
    if(DOOR_ROOM->query_open_door())
      str = ", and then an ominously loud 'thud' to your " +
    "east.";
    else
      str = ".";


    write("You reach down to pick up the gold coin, but " +
    "when you try and grab it, notice it is nothing more " +
    "than a craftily designed dwarven pressure pad. You hear " +
    "a 'click'" + str + "\n");
    say(QCTNAME(TP)+ " reaches down to pick up the gold coin, " +
    "but finds it is nothing more than an elaborate dwarven trap!" +
    " You hear a 'click'" + str + "\n");

    DOOR_ROOM->close_door();

    return "";
}

int
go_down()
{
    write("You push your way through the cobwebs as "+
      "you make your way down the stairway...\n");
    return 0;
}

string
short_descr()
{
    return "before a stairway cloaked with cobwebs within " +
    "an ancient dwarven cairn";
}

string
long_descr()
{
    return "You stand within the ancient stone walls "+
    "of a dwarven cairn. Dust of the ages lies thick "+
    "on the floor here, undisturbed for many years. "+
    "A stairway cloaked with cobwebs leads down deeper into "+
    "the cairn here."+
    "\n";
}
