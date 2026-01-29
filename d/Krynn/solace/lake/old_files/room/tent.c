
#include "../local.h";
#include <macros.h>

inherit SOLACE_INSIDE_BASE;

object cleric;

void
reset_solace_room()
{
    if (cleric)
      return;
    cleric = clone_object(LIV + "evil_cleric.c");
    cleric->equip_me();
    cleric->move(TO);
    tell_room(TO, "Out of a dark corner of the tent, a figure " +
	      "suddenly appears.\n", cleric);
}

void
create_solace_room()
{
    set_short("In a Tent");
    set_long("Before you even get through the door, you realize that you " +
	     "should not have come in here. This tent is huge. There are " +
	     "bunks along the north and south wall, most of which look as " +
	     "though they have been occupied recently. There are footprints " +
        "going in and out of the tent. There is a slight path leading " +
             "through the hole in the tent wall and outside.\n");
    add_exit(ROOM + "campfire","out",0);
    add_item("wall",
	     "The walls of the tent are no more than a heavy cloth draped " +
	     "over some poles.\n");
    add_item("cloth",
	     "This cloth is very heavy, and moves only slightly due to the " +
	     "howling wind outside.\n");
    add_item("path",
             "A slight path on the ground. Probably made by the " +
             "inhabitants of this tent, walking in and out of here.\n"); 

    reset_room();
}   


void
someone_arrives(object who, int from)
{
   tell_room(TO, QCTNAME(who) + " arrives.\n");
}

