/* This is a guild start room.  Note that default start locations
 * need to be registered with /secure/master.c.  See an archwizard
 * to have your start location registered.
 */

#pragma strict_types
#pragma save_binary

#include "../guild.h"
#include "/d/Ansalon/taman_busuk/sanction/local.h"

inherit SANCINROOM;
inherit "/lib/guild_support";

void
create_sanction_room()
{
    set_short("barracks of the Red Dragonarmy");
    set_long("You stand within a large tent filled with " +
      "temporary bunks, the sleeping quarters of those soldiers " +
      "of the Red Dragonarmy stationed within Sanction. You may "+
      "'start here' if you are a member of this army. This is also "+
      "a good place for meditation. Through the bunks to your north " +
      "the tent continues, while to your east you may exit " +
      "the tent.\n");

    add_item(({"tent","large tent","barracks","sleeping quarters"}),
      "This large tent is the sleeping quarters of the soldiers " +
      "of the Red Dragonarmy stationed within Sanction.\n");
    add_item(({"temporary bunks","bunks"}),
      "Many bunks, designed so that they can be easily disassembled " +
      "whenever the army wishes to break camp and move elsewhere, fill this " +
      "tent. They are neatly made, making it clear this army is " +
      "well disciplined and tidy, if nothing else.\n");

    add_exit(SRED + "r3","east",0);
    add_exit(SRED + "board","north",0);

}

int
start(string str)
{
    if (str != "here") 
    {
	NF("Start here?\n");
	return 0;
    }

    if(TP->query_dragonarmy_division() != "red")
    {
	write("You are not a member of this guild!\n");
	return 1;
    }

    if(TP->set_default_start_location(DRAGONARMY_RED_STARTLOC))
    {
	write("You now start here with your fellow soldiers!\n");
    }
    else
    {
	write("Sorry, some problem prevents you from starting here.\n");
    }

    return 1;
}

void
init()
{
    ::init();

    add_action(start, "start");
    init_guild_support();
}
