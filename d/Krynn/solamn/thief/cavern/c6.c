/* created by Aridor 02/09/94 */

#include "../local.h"

inherit ROOM_BASE

#define WHOAMI  1 /*I am this blocklocation*/

int found = 0; /*0 step is there, 1 step is missing*/
int how_many;

void 
reset_thief_room()
{
    found = 0;
}

void
create_thief_room()
{
    set_short("Top of a staircase");
    set_long("This is a narrow staircase winding down and a hallway " +
	     "leading east.\n");
    
    add_exit(CAVERN + "b6","down");
    add_exit(CAVERN + "c7","east");
    
    DARK;
    
    add_item(({"hallway"}),
	     "It is a stone hallway leading to the east from here.\n");
    add_item(({"staircase","walls","wall"}),
	     "It's carved from the rock@@dwarf_sees@@.@@loose_step@@\n");
    add_item(({"step","steps","loose step"}),"@@exa_step");
    add_item(({"missing step","hole"}),"@@exa_no_step");
    add_cmd_item(({"stone block","block","loose block","loose stone block",
		     "step","loose step"}),
		 ({"take","pry","yank","pull","tear","get"}),
		 "@@take_step_from_stair");
    add_item("stonemasonry",
	     "You notice that a caring dwarf must have put a lot of effort " +
	     "into this staircase. The wall is perfectly circular and it " +
	     "is a pleasure to look at it and be honored to be able to " +
	     "descend in it.\n");

}

string
dwarf_sees()
{
    if (TP->query_race() == "dwarf")
      return ", and you notice that this is some excellent dwarven " +
	"stonemasonry here";
    else
      return ", probably of dwarven origin";
}

string
loose_step()
{
    if (found == 0)
      return " Apparently, one of the steps is loose.";
    return " There is an entire step missing.";
}

string
exa_step()
{
    if (found == 0)
      return "This step is a single block of stone, but it wasn't fixed " +
	"into the stairs, but instead has just been placed on it.\n";
    return "Well, there is one missing.\n";
}

string
exa_no_step()
{
    if (found == 0)
      return "A step missing?? No, they're all there.\n";
    return "There is a step missing. You just have to take a bigger step " +
      "to pass it.\n";
}

string
take_step_from_stair()
{
    object form;
    NF("What?\n");
    if (found > 0)
      return 0;
    write("You take the step from the stairs, leaving a big hole.\n");
    SAYBB(" takes a block of stone out of the stairs!");
    form = clone_object(OBJ + "formblock");
    form->add_name("step");
    restore_object(NUMBER_SOLVED);
    if (how_many % NUM_BLOCK_LOCATIONS == WHOAMI)
      form->set_produce(OBJ + "cogwheel");
    else
      form->set_produce(PRODUCE[random(sizeof(PRODUCE))]);
    if (form->move(TP))
      {
	    write("You are unable to carry the formblock and drop it.\n");
	    form->move(TO,1);
      }
    found = 2;
    return "";
}
