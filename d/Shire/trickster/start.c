/* The Trickster board and start room 
 * Dunstable March 23, 1995
 * Split into 2 rooms so that the board would be more user friendly ;)
 * This the the Trickster start room half of the file
 * Igneous Feb. 21, 1996
 * Added drop box for members 
 * Finwe, September 2002
 */

#pragma save_binary

inherit "/d/Shire/room";
/*
 * Sets flag in players from calling dragons into ME.
 * Disabled by request of Admin, June 2001
#include "/d/Gondor/common/lib/gs_include.c"
*/

#include "trickster.h"
#include "/d/Shire/common/defs.h"
#include "/sys/ss_types.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include <std.h>


void
create_room()
{
   
   set_short("Cramped living quarters");
   set_long("This dim dark room has several lumpy sacks in "+
      "the corners.  There is a readable sign on the wall.  " +
      "You can leave these cramped quarters by going east.\n");
   
   add_item(({"sack","lumpy sack","lumpy sacks","corner","corners"}),
      "These sacks look like places to sleep in, the lumpy ones appear "+
      "occupied.\n");
   
   add_cmd_item("sign","read","The sign reads: <start here>\n");
   clone_object("/d/Shire/trickster/obj/chest")->move(this_object(), 1);
   
   add_exit(TRICK_DIR + "boardroom","east",0,1);
   add_prop(ROOM_I_INSIDE,1);
   
}

void
init()
{
   ::init();
   
   add_action("start","start");
}


int
start(string str)
{
   if(str == "here" && (IS_MEMBER(this_player())))
      {
      TP->set_default_start_location("/d/Shire/trickster/start");
      write("You will awaken here when next you sleep.\n");
      return 1;
      
   }
   
   write("No, you idiot. Start here!\n");
   return 1;
}
