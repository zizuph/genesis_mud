/*
 * Made by unknown, updated by Cherek, Mar 2007
 */

#include "/d/Krynn/solace/lake/local.h";
#include <macros.h>

inherit SOLACE_INSIDE_BASE;

object cleric;

void
reset_solace_room()
{
    if (cleric)
    {
	return;
    }

    cleric = clone_object(NPC + "evil_cleric.c");

    cleric->equip_me();

    cleric->move(TO);

    tell_room(TO, "Out of a dark corner of the tent, a figure " +
      "suddenly appears.\n", cleric);
}

void
create_solace_room()
{
    set_short("In a tent");
    set_long("This tent is huge. There are bunks along the north and " +
      "south wall, most of which look as though they have been " +
      "occupied recently. There are footprints going in and out " +
      "of the tent. There is a slight path leading through " +
      "the hole in the tent wall and outside.\n");

    add_exit("campfire","out",0);

    add_item("tent",
      "It seems like a standard army tent. A big one though. \n");

    add_item("bunks",
      "The bunks are tidy and well-made in typical army fashion.\n");

    add_item(({"wall", "north wall", "south wall"}),
      "The walls of the tent are no more than a heavy cloth " +
      "draped over some poles.\n");

    add_item(({"cloth", "heavy cloth"}),
      "This cloth is very heavy, and moves only slightly due to the " +
      "howling wind outside.\n");

    add_item("poles",
      "They look very sturdy and easily supports the heavy cloth. \n");	     

    add_item("path",
      "A slight path on the ground. Probably made by the " +
      "inhabitants of this tent, walking in and out of here.\n"); 

    add_item("footprints",
      "Most of the footprints seem to be of human size.\n");

    reset_room();
}   


void
someone_arrives(object who, int from)
{
    tell_room(TO, QCTNAME(who) + " arrives.\n");
}

