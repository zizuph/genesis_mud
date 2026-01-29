/*	Created by:	Sir Toby, 97-06-23
 *	Location:	Northern end of sewers, just inside 
 *			secret door.
 *	Modified:
 */

inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
#include "/d/Kalad/common/sewers/lizards_lair/path.h"


void
create_room()
{
::create_room();

   hear_bell = 1;

   set_short("An underground room");
   set_long("This is a damp and dry underground room. The walls are " +
	    "made out of bricks that look like they could fall apart " +
	    "any time. Even though this place looks old and worn " +
	    "down it seems to be in use as there is no dust at all " +
	    "in here. From the ceiling you can smell a faint scent of " +
	    "fresh air. In the northeast corner you see a pile of " +
	    "bricks in front of a gaping hole leading into a dark tunnel.\n");

   add_item( ({"wall","walls","brick wall","brick walls"}),
	    "The brick walls seem very old and they truly look like " +
	    "they would fall apart any time. There is a gaping hole " +
	    "in the walls to the northeast.\n");
   add_item("ceiling","The ceiling is made of mud and supported by " +
		      "wooden beams. Other than that you see nothing " +
		      "else of interest.\n");
   add_item( ({"beam","beams","wooden beam","wooden beams"}),
	    "They are regular wooden beams.\n");
   add_item( ({"pile","pile of bricks"}),"It is just a pile of " +
	    "bricks.\n");
   add_item( ({"hole","gaping hole"}),"The gaping hole leads into " +
	    "a dark tunnel.\n");
   add_item( ({"tunnel","dark tunnel"}),"You would have to enter the " +
	    "tunnel to see what is in it.\n");

   add_cmd_item("air",({"smell","sniff"}),"The air smell slightly " +
	  	"of frech air.\n");

   add_prop(OBJ_S_SEARCH_FUN,"search_ceiling");
   add_prop(ROOM_I_INSIDE,1);
   add_prop(ROOM_I_LIGHT,0);


//   add_exit("ms1.c", secret south later here...=)
   add_exit(PATH + "ll1.c","northeast",0,1);
   set_noshow_obvious(1);
}


string
search_ceiling(object me, string arg)
{
   if(arg != "ceiling")
      return "";
   
   if(TP->query_skill(SS_AWARENESS) < 30)
      return "";

   add_exit("/d/Kalad/common/caravan/caravan_gate","up",0,1,2);
   set_alarm(12.0,0.0,"remove_exit","up");

return "You search carefully and discover an exit leading up!\n";
}

