#include "defs.h"
#include "/sys/stdproperties.h";
#include <macros.h>
#include "/d/Earthsea/herbs/herb_sets/forest_herbs.h"
inherit THWIL_BASE_ROOM;
inherit "/d/Earthsea/herbs/specials/hs";

void create_thwil_room()
{
   set_short("Gate");
   set_long("You stand at the top of a steep hill. "+
      "The great building is to your immediate south. "+
      "Near one corner, you see a mean little portal of " +
      "wood. A big oak tree is majestically spreading its "+
      "lush green branches over you, making the place "+
      "an escape for the hot sun in its shadow. \n");
   
   
   add_item("tree",
	    "The huge oak seems to keep the house standing upright.\n");
   add_item("portal" ,
	    "Upon closer examination the door is made of polished horn " +
	    "through which the daylight shines dimly. The frame appears " +
	    "to be of ivory without joint or seam, as if carved from " +
	    "the tooth of a great beast. There's a small plaque on the " +
	    "portal.\n"); 
   add_item("plaque",
	    "Welcome to the House of the Wise, the School of Roke.\n"+
	    "               Enter if you can.\n");
   
   add_cmd_item("plaque", 
		"read", "Welcome to the House of the Wise, " +
		"the School of Roke.\n " +
		"               Enter if you can. \n");
   add_item("building", "It is an impressive stone building.\n");
   
   add_exit(THWIL + "a4" , "north" , 0, 2);

   add_prop(OBJ_I_SEARCH_TIME, 2);
   FOREST;
   set_up_herbs(select_herb_files(FOREST_HERBS), FOREST_LOCATIONS, 3);
}

void
init()
{
   ::init();
   add_action("enter_portal", "enter");
}

private object entering_player;

int
enter_portal()
{
   notify_fail("As you try to enter the portal a " +
         "darkness fills you. You can't see for a moment.\n");
   entering_player = this_player();
   set_alarm(2.0, 0.0, "guild_status");
   return 0;
}

void
guild_status()
{
   write("Suddenly, the darkness that surrounds you " +
      "transforms into void. You think you see something " +
      "at the other side of the void field... \n");
   say(QCTNAME(entering_player) + " looks bewildered for a moment.\n");
   set_alarm(2.0, 0.0, "guild_status_2");
}


void
guild_status_2()
{
   write("A forceful voice rasps to you through the void: " +
      "The Archmage of Earthsea has passed away. The Masters of " +
      "Roke are in session choosing a successor, until then "+
      "this guild is closed. \n");
}
