/* 
 * /d/Kalad/common/guilds/sh_walkers/rooms/entrance.c
 * Purpose    : The entrance to the Shadow Walkers.
 * Located    : 
 * Created By : Rico 23.May.96
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

   set_short("\nNich in the alley");
   set_long ("@@from_direction@@");

   add_item(({ "pit", "blackness", "pit of blackness" }), 
      "\nAll you see is a big black void.  There isn't enough "+
      "light to see to the back.  Thanks to almost poking your eye "+
      "out on the rail of an old ladder which trails up out of the "+
      "blackness, you realize there might be an easy solution to "+
      "discovering the secrets of the nich.\n\n");
   add_item(({ "old dusty ladder", "old ladder", "dusty ladder", 
      "ladder" }), "\nIt leads down into the blackness of a pit.  "+
      "Just how far down, you can't be certain.  Perhaps you should "+
      "test it...\n\n");
   add_item("rail", "\nIt's hard to see.  Even so you notice it is "+
      "a bit splintered.  Maybe you should test the ladder and make "+
      "sure it will hold before using it.\n\n");

/* Set this exit to the room_std until the new guild is done... */
    add_exit("/d/Kalad/common/trade/sewers/s8","out",0,-1);

   room_add_object(SHADOW + "obj/ladder");
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
 *                   player to climb a ladder down to destination.
 *  Returns       :  Strings upon success.
 */
int
do_climb(string str)
{
   if((str == "down ladder")||(str == "down old ladder")||
      (str == "down dusty ladder"))
   {
      say("\n" + QCTNAME(this_player()) + " uses the old ladder to "+
         "carefully climb down into the pit.  ");
      write("The old ladder creaks as you carefully climb down "+
         "into the dark pit.\n");
      this_player()->move_living("down the ladder",
         SHADOW + "rooms/tunnel1");

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
         " leans upon the duster ladder for a moment, making sure it "+
         "will support " + POSSESSIVE(TP) + " weight.\n\n");

      write("\nAfter testing the old ladder you feel confidant that it "+
         "is still strong enough to support your weight.\n\n");

      return 1;
   }

   write("\n\tTest what ?\n\n");

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

   if(last == find_object(SHADOW + "rooms/tunnel1"))
   {
      return "\nYou leave the gloomy tunnel behind and emerge "+
         "into a rather dark recess.  After wandering around "+
         "in the dark tunnel, you feel like you've stepped out "+
         "into broad daylight, but it's certainly far from "+
         "bright in here.\n\n";
   }
/*  Need to determine where the guild will connect to...  
    Also, this part of the code might need fixing according
    to the last room part of it.  I also want to add an
    awareness check so that the ladder isn't immediately
    obvious... for those who don't notice.. they fall and
    hurt themselves to varying degrees.
   else if(last == find_object("/d/Kalad/common/trade/sewers/s8"))
   {
      return "\nYou've entered a rather small cave. There is only "+
         "dim lighting here and you need to take a moment to let "+
         "your eyes adjust before you notice that you've come very "+
         "close to stepping off into a pit of blackness.\n\n";
   }
*/
   else 
   {
      return "";
   }
}

