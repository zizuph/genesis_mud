/*	Created by: 	Sir Toby, 97-07-02
 *	Purpose:	Lizards lair.
 *	Location:	/d/Kalad/common/sewers/ll23.c
 *	Modified:	
 */

#pragma strict_types

inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
#include "/d/Kalad/common/sewers/lizards_lair/path.h"


object guard;

void
reset_room()
{

   if (!guard)
      {
      guard = clone_object("/d/Kalad/common/sewers/npc/gl_lizard_guard.c");
      guard -> arm_me();
      guard -> move_living("M",TO);      
      }

   if (!guard)
      {
      guard = clone_object("/d/Kalad/common/sewers/npc/gl_lizard_guard.c");
      guard -> arm_me();
      guard -> move_living("M",TO);      
      }

    tell_room(TO, "Two guards arrives, hunger for blood " +
                   "in their eyes.\n");

}


void
create_room()
{
::create_room();

   set_short("Inside a room under the city of Kabal");
   set_long("You find yourself in a guard room. It is scanty decorated, " +
	    "only one drawer and a bed. It is cut directly out of the " +
	    "rock. The walls are covered with marks and drawings. The " +
	    "ground is very dirty. The only exit is west back into " +
	    "the tunnel. " + "@@dwarf_check" );

   add_item("ground", "The ground is cut out of rock and very dirty.\n");
   add_item( ({"wall","walls","rock wall","rock walls"}),
	     "The walls are cowered with marks and drawings.\n");
   add_item("ceiling","The ceiling is cut directly out of the rock.\n");
   add_item("marks","The marks is probably counting of days in service.\n");
   add_item("drawings","The drawings are roughly made and pictures " +
		       "female lizardmen mostly.\n"); 
   add_item("bed","The bed is made of wood and it looks like a mess.\n");
   add_item("drawer","The drawer is made of wood and seem to fall apart " +
		     "any minute.\n");

   add_cmd_item( ({"smell","sniff"}),"air",
		"The air smells damp and feel moisty in your nostrils.\n");

   add_exit(PATH + "ll18.c","west",0,1);
   set_noshow_obvious(1);

   add_prop(ROOM_I_INSIDE,1);
   add_prop(ROOM_I_LIGHT,0);

return;
}


/* 	Funktion returns different things wether or not the player 
 *  	is a dwarf 	
 */

string
dwarf_check()
{

    if(TP->query_race() == "dwarf")
        return "You notice that the ground " +
	       "is totally flat here and that you must be deep under " +
	       "the surface of Kabal.\n"; 

	return"\n";

}