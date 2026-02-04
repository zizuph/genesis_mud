/* entrance.c */
/* janus 920817 */
inherit "/std/room";
#include <ss_types.h>
#include <macros.h>

create_room()
{

  set_short("Entrance");
  set_long(break_string("You are in a glade in the mystic forest. " +
	"To the north there is a large hedge, going from left to right as " +
	"far as you can see. In the center of the hedge is a large entrance" + 
	" half closed with an ornate shining grating.\n",70));
  add_exit("/d/Terel/janus/garden/ggate", "north",0);
  
   add_exit("/d/Terel/ships/glade","southwest",0);
  
  add_item(({"grating","gate"}), break_string("The silvery grating seems " +
      "to be of a very good workmanship. Unfortunately your grasp of " + 
      "metallurgy isn't good enough to determine the material. The " + 
      "gate seems to be stuck in an half open position. " +
      "In the middle of the gate is a wooden plaque. Standing this " + 
      "close to the gate you feel warm air blowing from the garden, " + 
      "it must cost a fortune to heat this place. \n",70));
  add_item(({"hedge"}), break_string("A huge very well kept hedge. Must " + 
				     "take forever to trim it. \n",70));
  add_cmd_item(({"plaque","wooden plaque"}),({"read","exa"}),
         ({"@@do_sign","@@do_sign"}));
}
do_sign()
{
          return("On the plaque you can read the following:\n"+
	   "  \n"+
	   "Welcome to Janus Stately Home and Gardens. \n"+ 
	   "No picnic allowed in the area or feeding any of \n"+
           "the creatures. Further information can be found on signs \n"+
           "inside the garden. \n" +
     "Enjoy your stay.\n");
}
