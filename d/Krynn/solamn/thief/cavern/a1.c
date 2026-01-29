/* created by Aridor 02/09/94 */

#include "../local.h"

inherit ROOM_BASE

#define WHOAMI  0 /*I am this blocklocation*/

int found = 0; /*0 not found, 1 found, 2 hole in the wall*/
int how_many;

void 
reset_thief_room()
{
    found = 0;
}

void
create_thief_room()
{
    set_short("In a cavern");
    set_long("This is a rectangular bend in the cavern. Moss and algae " +
	     "are everywhere, but the hallway itself must have been " +
	     "carved by experts, straight walls, floor and ceiling " +
	     "prove this. Just no one seems to have cleaned here in ages.\n");
    
    add_exit(CAVERN + "a2","east");
    add_exit(CAVERN + "a4","south");
    
    DARK;
    add_prop(OBJ_I_CONTAIN_WATER, 50000);

    add_item("moss",
	     "The moss varies in color from yellow through red to brown, " +
	     "and covers most of the walls. It even hangs down from the " +
	     "ceiling. The moss is very damp and water is dripping from " +
	     "the overhanging parts.\n");
    add_item("algae",
	     "The algae are green and brown and grow on the floor of the " +
	     "cavern.\n");
    add_search(({"algae","floor","water"}),12,"/std/coins",-4); /* 4 copper coins */
    add_item("floor",
	     "The floor is very even here, but it's completely covered with " +
	     "algae and water.\n");
    add_item("ceiling",
	     "There is damp moss hanging from the ceiling, water dripping " +
	     "down.\n");
    add_item(({"wall","walls"}),
	     "The walls are very straight in both directions, east and " +
	     "south, but they're covered with moss.\n");
    add_item("water",
	     "The water on the floor is only a few inches deep, but algae " +
	     "are growing in it. The water is dripping down from moss " +
	     "hanging down from overhead.\n");
    add_item("hallway",
	     "You are standing in it.\n");
    add_item(({"stone block","block","loose block","loose stone block"}),
	     "@@block_there_and_found");
    add_item(({"hole","big hole","hole in the wall","big hole in the wall"}),
	     "@@hole_in_wall");
    add_cmd_item(({"moss from ceiling"}),
		 ({"tear","rip","yank","pull","take","get"}),
		 "@@tear_moss_ceiling");
    add_cmd_item(({"moss from wall","moss from walls"}),
		 ({"tear","rip","yank","pull","take","get"}),
		 "@@tear_moss_wall");
    add_cmd_item(({"moss"}),({"tear","rip","yank","pull","take","get"}),
		 "@@tear_moss");
    add_cmd_item(({"stone block","block","loose block","loose stone block"}),
		 ({"take","pry","yank","pull","tear","get"}),
		 "@@take_block_from_wall");
    reset_room();
}

string
tear_moss()
{
    write("Where do you want to tear the moss down from?\n");
    return "";
}

string
tear_moss_wall()
{
    if (found != 2)
      {
	  write("You tear some of the moss down from the wall, and there " +
		"could just be a loose stone block in the wall here.\n");
	  found = 1;
      }
    else
      write("You tear some of the moss down from the wall, but there is " +
	    "nothing underneath, though.\n");
    return "";
}

string
tear_moss_ceiling()
{
    write("You tear some of the moss down from the ceiling. There is " +
	  "nothing underneath, though.\n");
    return "";
}

string
block_there_and_found()
{
    if (found != 1)
      return "You find no stone block.\n";
    return "It actually seems to be a loose block of stone in the wall.\n";
}

string
take_block_from_wall()
{
    object form;
    NF("What?\n");
    if (found != 1)
      return 0;
    write("You pry the block of stone from the wall, leaving a big hole.\n");
    SAYBB(" removes a block of stone from the wall.");
    form = clone_object(OBJ + "formblock");
    restore_object(NUMBER_SOLVED);
    if (how_many % NUM_BLOCK_LOCATIONS == WHOAMI)
      form->set_produce(OBJ + "cogwheel");
    else
      form->set_produce(PRODUCE[random(sizeof(PRODUCE))]);
    if (form->move(TP)) /* error! */
      {
	  write("You are unable to carry the formblock and drop it.\n");
	  form->move(TO,1);
      }
    found = 2;
    return "";
}

string
hole_in_wall()
{
    if (found != 2)
      return "You find no big hole.\n";
    return "There seems to be a block of stone missing in the wall here.\n";
}
