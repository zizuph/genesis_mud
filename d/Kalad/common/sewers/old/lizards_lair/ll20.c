/*	Created by: 	Sir Toby, 97-07-02
 *	Purpose:	Lizards lair.
 *	Location:	/d/Kalad/common/sewers/ll20.c
 *	Modified:	
 */

#pragma strict_types

inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
#include "/d/Kalad/common/sewers/lizards_lair/path.h"
string check_read_skill();


void
create_room()
{
::create_room();

   set_short("Inside a room under the city of Kabal");
   set_long("You find yourself in a guard room. It is decorated " +
	    "with a tapestry on the east wall. At the north wall " +
	    "stands a huge desk and on the west wall stands a bed. " +
	    "Above the desk you see some carved letters. " +
	    "The ground is clean in this room. " + "@@dwarf_check" );

   add_item("ground", "The ground is cut out of rock and it is clean.\n");
   add_item( ({"wall","walls","rock wall","rock walls"}),
	     "The east wall is decorated with a tapestry and on the " +
	     "north wall is some letters carved.\n");
   add_item("ceiling","The ceiling is cut directly out of the rock.\n");
   add_item("bed","The bed is made of wood and it looks like a mess.\n");
   add_item("desk","The desk is made of wood and it is clean and not " +
	    	   "full of papers as one could have supposed.\n");
   add_item( ({"letters","carving","carvings"}), "@@check_read_skill");

   add_cmd_item( ({"smell","sniff"}),"air",
		"The air smells damp and feel moisty in your nostrils.\n");

   clone_object("/d/Kalad/common/sewers/doors/captdoor")->move(TO);
   set_noshow_obvious(1);

   add_prop(ROOM_I_INSIDE,1);
   add_prop(ROOM_I_LIGHT,0);

return;
}


/* 	Function returns different things wether or not the player 
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


/*	Function checks for players read skill and returns text 
 *	according to the read skill.
 */


string
check_read_skill()
{
    switch(TP->query_skill(SS_LANGUAGE))
       {
          case 0..20:
  	 return "You read: c...a.d.r Dr...s p.iv... q..t..s.\n";
         break;

         case 21..100:
	 return "You read: Commander Drezt's private quarters.\n" +
		"                 KEEP OUT!\n";
	 break;

	default:
	return "You can not get anything out of the carvings.\n";
	}
	
}

