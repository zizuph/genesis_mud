#include "outroom.h"

create_outroom() 
{
  set_short("Stunted tree");
  set_long("You are standing at the foot of the stunted tree.\n"+
	   "Steep slopes prevent you from going south and east, and a scree to the\n"+
	   "west stops you from going west. The tree seems far too stunted to climb up. ");
  add_item("tree", "It's too stunted to climb.\n");
  add_item(({"slopes", "scree"}),
      "Slopes and scree prevents all directions except north.\n");

  add_tell("climb", "[the] 'tree'",
       "(You) tr(y) to climb the stunted tree, but it is simply too weak to hold [your] weight.\n");
  add_tell("climb", "[the] [west] [east] 'slope'",
      "(You) climb[s] partway up the very steep slope{, but the feel some rocks give " +
      "way under your feet}. (You) tumble[s] down to where [you] started, luckily not injured.\n");
  add_tell("kick", "[the] [stunted] [old] 'tree'",
      "(You) kick[s] the tree.\n"+
      "The tree trembles in shock.\n");

  add_neg("water", "[the] 'tree'", "Ain't we kind? :-)\n");
  add_neg("cut", "[the] 'tree'", "Now, what on earth for?\n");
  NORTH("under_wall");
}

		  
		    
