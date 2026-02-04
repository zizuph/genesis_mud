#include <stdproperties.h>
inherit "/std/object";

create_object()
{
     ::create_object();

      set_name("cornerstone");
      add_prop(OBJ_I_NO_GET, "It's firmly secured to the ground.\n");
      set_short("cornerstone");
      set_long(
          "The cornerstone is covered with the following\n" +
	  "inscriptions which may be read with 'read <number>'\n\n" +

		 "(1) The Ancient Order \n"+
		 "(2)  DARKNESS \n"+
		 "(3) A Magic Flame \n"+
		 "(4) MISSING! \n"+
		 "(5) PLEASE HELP! \n"+
		 "(6) entertainments! \n"+
		 "(7) my wondrous home \n"+
		 "(8) Help Wanted \n"+
		 "(9) Know ye... \n"+
		 "(10) The Enchanted Garden \n"+
		 "(11) A darkness has befallen us \n"+
		 "(12) An Undead Horror \n"
      );
}
		  
