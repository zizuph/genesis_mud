#include <defs.h>
#include <ss_types.h>
inherit THWIL_BASE_ROOM;

void create_thwil_room()
{
   set_short("Pier");
   set_long("You are on a strange pier. "+
	    "To the west you see some rooftops scattered about, "+
	    "obviously the centre of Thwil.  To the east you behold "+
	    "the bay of Thwil in its full splendor. Small sailing "+
	    "vessels are cruising around in the bay. Hmmm...some of the " +
	    "ships are sailing against the wind, with bulging sails... "+
	    "A ladder leads down to the quay. "+
	    "The pier continues to the north and south. \n");
   add_item(({"vessel","vessels","harbour","bay"}),
	    "You have difficulties getting a good view of "+
	    "the small sailing vessels from here, but it "+
	    "seems that most of them are sailed by young "+
	    "men.");
   
   
   add_item("pier","It is a smooth well tended pier, funny not "+
	    "any rubbish at all in sight... \n");
   
   add_exit(THWIL + "h8" , "north" , 0);
   add_exit(THWIL + "h4" , "south" ,0);
   add_item("ladder", "The ladder looks well used. \n");
   add_item("quay", "The quay is for smaller fishing boats, " +
	    "the bigger ships use the pier. \n");
   BEACH;
}

init()
{
   ::init();
   
   add_action("climb","climb");
   add_action("climb", "use");
}

climb(string s)
{
   NF("Climb where?\n");
   if (s != "down" && s != "ladder")
      return 0;
   
   NF("You are not skilled enough in climbing and decide " +
      "against climbing down. \n");
   
   if(TP->query_skill(SS_CLIMB)<10)
      return 0;
   
   NF("You notice that the ladder is broken, and decide to wait until it is " +
      "repaired.\n");
   return 0;
   TP->move_living("down", THWIL + "quay");
   return 1;
}
