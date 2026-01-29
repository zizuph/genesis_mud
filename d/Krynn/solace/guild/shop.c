/*
Shop by Tricky, adapted to the Solamnian Guild by Nick. (ages ago...)
Closed by Percy, 5/93
Secret access to old store by Aridor, 9/94
Removed all shop commands, Aridor, 9/94
Changed access to store, Mucalytic 6/95
Altered again by Mucalytic May the 20th '96.
*/

#include "local.h"
#include "guild.h"
#include "/sys/macros.h"
#include "/d/Krynn/common/defs.h"

inherit INSIDE_BASE;

int check_west();

void create_solace_room()
{
   set_short("The old Guild shop");
   set_long("You find yourself in a run-down old room with a dust-laden "+
	    "counter and squeaky floorboards. This used to be the old guild "+
	    "shop, but there seems to be nothing here now; it was obviously " +
	    "all moved out a long time ago. You can see exits to the east " +
	    "and west. The former leads to the Grand Hall of the Paladine " +
	    "and the latter seems to be boarded over with shutters.\n");
   /*"You also notice another new-looking exit leading northwards.\n");*/
   
   add_exit(TDIR + "hall1", "east", 0, 1);
   add_exit(TDIR + "store", "west", "@@check_west", 1);
/* add_exit(PARENT + "puzzle/locations/entrance", "north", 0, 1); */
   
   add_item(({"counter", "dust-laden counter"}), "The counter is made from "+
      "a dark, strong-looking wood but is scratched, battered and piled "+
      "with dust.\n");
   add_item(({"floorboards", "squeaky floorboards"}), "The floorboards are "+
      "hard to see because of the dust blanketing them, but they make a "+
      "terrible noise when you step on them.\n");
   add_item("shutters", "Someone seems to have nailed shutters across the "+
      "exit to the west. It looks all closed. You notice a narrow opening "+
      "right at the bottom, near the floor though.\n");
   add_item("opening","You think it might be possible to squeeze through if " +
	    "you make yourself very very thin.\n");
}

void init()
{
   ::init();
   
   add_action("enter_opening", "enter");
   add_action("enter_opening", "squeeze");
}

int
enter_opening(string str)
{
    string prep = "'under' / 'through' / 'into' ";
    string msg = "[the] [narrow] 'shutters' / 'opening'";
    int hgt = TP->query_prop(CONT_I_HEIGHT), vol = TP->query_prop(OBJ_I_VOLUME);
    int avg = TP->query_average_stat();
    
    if(!str) return 0;

    NF("What?\n");
    if((query_verb() == "enter" && parse_command(str, TP, msg)) ||
       (query_verb() == "squeeze" && parse_command(str, TP, prep + msg)))
    {
	if((vol / hgt) < 300 || avg < 26 + random(5))
	{
	    write("You squeeze through the hole.\n");
	    say(QCTNAME(TP)+" lies flat on the floor and squeezes "+
		OBJECTIVE(TP)+"self under the shutters.\n");
	    
	    TP->move_living("into the opening", TDIR + "store",1 ,0);
	}
	else
	{
	    write("You are too big to fit through!\n");
	    say(QCTNAME(TP)+" lies flat on the floor and gets up again, "+
		"grumbling unhappily.\n");
	}
	return 1;
    }
    else
      return 0;
}

int check_west()
{
	write("You can't just walk through that shuttered opening!\n");
	return 1;
}
