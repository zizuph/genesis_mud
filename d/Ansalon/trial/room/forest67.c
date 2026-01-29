#include "/d/Ansalon/trial/local.h"
#include <stdproperties.h>
inherit TRIAL_IN;

void
create_trial_room()
{
    set_short("On a dusty forest trail");
    set_long("@@long_descr"); 

    enable_reset(120);

	add_exit(TROOM + "forest66","west","@@if_open");
	/* 
	int ExitNr = random(7);
	
	if (ExitNr == 0)
		add_exit(TROOM + "forest66","east","@@if_open");
	if (ExitNr == 1)
		add_exit(TROOM + "forest66","west",0);
	if (ExitNr == 2)
		add_exit(TROOM + "forest66","north",0);
	if (ExitNr == 3)
		add_exit(TROOM + "forest66","south",0);
	if (ExitNr == 4)
		add_exit(TROOM + "forest66","northeast",0);
	if (ExitNr == 5)
		add_exit(TROOM + "forest66","northwest",0);
	if (ExitNr == 6)
		add_exit(TROOM + "forest66","southeast",0);
	if (ExitNr == 7)
		add_exit(TROOM + "forest66","southwest",0);
*/
    add_item(({"trees","oaktrees","pine trees", "pines"}),
     "The trees here consist of a mixture of pines "+
     "and oaktrees. Some of them look quite old "+
     "while others are fairly young.\n");
}

string
long_descr()
{ 
    return
    "You are standing on a small trail within a vast "+
    "emerald-green forest. The undergrowth here "+
    "consists of a wide variety of plant and herb "+
    "species. The trail continues to the north and "+
    "southwest.\n";
}

int
if_open()
{
    if ((TROOM + "forest66")->query_exit_direction() == "east")
      return 1;
    write("You find that it is impossible to leave the room as the door ends in a brick " +
	  "wall!\nYou push again, and suddenly you fall through the wall into another " +
	  "room, the wall slamming back into place behind you.\n");
    return 0;
}
