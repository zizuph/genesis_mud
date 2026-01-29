/* 
 * /d/Kalad/common/guilds/sh_walkers/rooms/tunnel1.c
 * Purpose    : Tunnel leading into the Shadow Walkers' guildhall.
 * Located    : 
 * Created By : Rico 23.05.96
 * Modified By: 
 */ 

#include "../defs.h"

inherit "/std/room.c";
inherit SHADOW + "std/room_std.c";

#define  POSSESSIVE(x)   x->query_possessive()

void
create_room()
{
   ::create_room();

   set_short("\nDark tunnel");
   set_long ("\n@@from_direction@@"+
      "This tunnel is rather low ceilinged and you need to "+
      "lean over slightly so you don't bump your head.  Flickering "+
      "shadows caused by the torches make you feel a touch uneasy.  "+
      "\n\n");

   add_item(({ "dark", "darkness", "black", "blackness" }), 
      "\nAll you see is a big black void.  There isn't enough light "+
      "being cast by the torches to see very far at all.  You are "+
      "able to notice that the tunnel declines toward the northeast."+
      "That directions seems to be relatively clear of obstacles, "+
      "though.  You should be able to traverse it without much "+
      "difficulty.\n\n");
   add_item(({ "old dusty ladder", "old ladder", "dusty ladder", 
      "ladder" }), "It trails up into the darkness.  You are unable "+
      "to make out just how high it goes.  After testing it, you "+
      "conclude that it's sturdy enough to support your weight.\n\n");
   add_item("tunnel", "It is rather cramped, but still large enough "+
      "move around in.  It leads off into the darkness toward the "+
      "northeast.\n");

   add_prop(ROOM_I_HIDE, 10);

   /*  Take off 3 fatigue points for going ne (long and hard tunnel).*/
   add_exit((SHADOW + "rooms/tunnel2"), "northeast", 0, 3);

   /*  Add a couple of objects into the room.  */
   room_add_object(SHADOW + "obj/ladder");
   room_add_object(SHADOW + "obj/obj_torch");
}

/*
 *  Function Name :  init
 *  Description   :  Define permittable actions.
 */
void
init()
{
   ::init();
   
   add_action("do_climb", "climb");
   add_action("do_test",  "test");

   return;
}

/*
 *  Function Name :  do_climb
 *  Description   :  Substitute for add_exit which will permit the
 *                   player to climb a ladder up to destination.
 *  Returns       :  Strings upon success.
 */
int
do_climb(string str)
{
   if((str == "ladder"||(str == "old ladder")||(str == "up")||
      (str == "dusty ladder")||(str == "old dusty ladder"))||
      (str == "up ladder")||(str == "up old ladder")||
      (str == "up dusty ladder")||(str == "up old dusty ladder"))
   {
      say(QCTNAME(this_player()) + " carefully starts up the "+
         "ladder...  ");
      write("The old ladder creaks as you carefully climb up "+
         "it to the entrance.\n");
      this_player()->move_living("up the ladder and disappears "+
         "into the darkness above", SHADOW + "rooms/entrance");
      this_player()->add_fatigue(-3);

      return 1;
   }

   write("\n\tClimb what ?\n\n");

   return 1;
}

/*
 *  Function Name :  do_test
 *  Description   :  Permit the actor to 'test' an object. 
 *  Returns       :  String upon success.
 */
int
do_test(string str)
{
   if((str == "ladder")||(str == "old ladder")||(str == "rail"))
   {
      say("\n" + QCTNAME(this_player()) + " gives the ladder a shake"+
         ".  " + capitalize(this_player()->query_pronoun()) + 
         " leans upon the dusty ladder for a moment, making sure it "+
         "will support " + POSSESSIVE(TP) + " weight.\n\n");

      write("\nAfter testing the old ladder you feel confidant that it "+
         "is still strong enough to support your weight.\n\n");

      return 1;
   }

   write("\tTest what ?\n\n");

   return 1;
}

/*
 *  Function Name :  from_direction
 *  Description   :  To give a direction specific string in the room's
 *                   long descrip.
 *  Returns       :  Direction dependant strings.
 */
string
from_direction()
{
   object last = this_player()->query_prop(LIVE_O_LAST_ROOM);

   if(!last)
      return "";

   if(last == find_object(SHADOW + "rooms/entrance"))
   {
      return "As you let your eyes take in the gloomy darkness, "+
         "you are able to make out that the tunnel declines toward "+
         "the northeast.  That direction seems to be relatively "+
         "clear of obstacles, though.  You should be able to "+
         "traverse it without too much difficulty.  You could take "+
         "the old, dusty ladder back up to the entrance.\n\n";
   }
   else if(last == find_object(SHADOW + "rooms/tunnel2"))
   {
      return "As you approach the end of the tunnel you pause to "+
         "catch your breath.  The old, dusty ladder you used to "+
         "enter this dark and gloomy place is here leading up to "+
         "the entrance.  Or, if you are so inclined, you could turn "+
         "around and go back down the tunnel.\n\n";
   }
   else 
   {
      return "";
   }
}

