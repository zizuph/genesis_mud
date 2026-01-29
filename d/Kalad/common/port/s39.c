#include "default.h"
inherit PORT_ROOM;

object ob1;
object ob2;
object ob3;

void
create_port_room()
{
    add_prop(ROOM_I_INSIDE,1);
    set_short("Entrance room of the Halfling Brewery");
    set_long("You are standing in the grand entrance room of The Halfling "+
      "Brewery. The strong, earthy smell of beer fills the room with its "+
      "wonderful scent. To the west is a large plank wall, forming a "+
      "separate room. Looking to the east you can see a wooden archway, "+
      "and beyond that, another larger room.\n");
    add_item(({"large plank wall","large wall","plank wall","wall"}),
      "Set within the wall is a small door.\n");
    add_item(({"small door","door"}),"An ordinary, albeit small door. "+
      "A plaque hangs upon it.\n");
    add_item("plaque","@@plaque");
    add_cmd_item("plaque","read","@@plaque");
    add_item(({"wooden archway","archway"}),"An opening in the east "+
      "that leads to another room.\n");
    add_exit(PORT + "s38", "west");
    add_exit(PORT + "s26", "north");
    add_exit(PORT + "s40", "east");
    reset_room();
}

plaque()
{
    return "Manager's Office - DO NOT DISTURB -\n";
}

reset_room()
{
    if(!ob1)
    {
	ob1 = clone_object(PORT + "npc/hbguard");
	ob1 -> move_living("xxx", TO);
    }

    if(!ob2)
    {
	ob2 = clone_object(PORT + "npc/hbguard");
	ob2 -> move_living("xxx", TO);
    }

    if(!ob3)
    {
	ob3 = clone_object(PORT + "npc/hbseller");
	ob3 -> move_living("xxx", TO);
	ob1 -> team_join(ob2);
	ob1 -> team_join(ob3);
    }

}

