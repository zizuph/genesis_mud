/*                                   */
/*    Part of the Market in Kalad.   */
/*                                   */
/*              -Rico 20.12.94       */
/*                                   */

#include "/d/Kalad/defs.h"
#include <stdproperties.h>
#include <filter_funs.h>
#include <macros.h>

inherit MRKT_PATH(marketStd);

int pres, i;

object *ob;

object obj;

create_room()
{
   ::create_room();
   
   set_short("Fortune Teller's lobby");
   set_long("    You have enterred the fortune teller's "+
      "hut. This is where you wait until the gypsy is "+
      "ready to see you. The walls are adorned with "+
      "colorful tapestries depicting and there is an "+
      "ornately carved bench along the side of the "+
      "tent. The fortune teller's assistant is "+
      "sitting at her small desk looking bored.\n");
   
   add_item(({ "tapestries", "colorful tapestries" }),
      "These are probably close to the most intriguing "+
      "wall tapestries you have ever seen with your own "+
      "eyes. Not only are they very colorful, but they "+
      "depict strange sights to behold. Anything and "+
      "everything from goblin battles to picnic outings "+
      "to astrological phenomena.\n"+
      "    As you study the tapestries a bit more "+
      "intently, you get the impression that the "+
      "scenes depicted on them are somehow... "+
      "moving! This is strange indeed! You begin to "+
      "wonder if the tapestries tell some sort of "+
      "story... Too bad you don't have more time to "+
      "watch them right now.\n");
   add_item(({ "bench", "carved bench" }), 
      "This bench is of a rich design. Perhaps you "+
      "shouldn't risk upsetting the gypsy by sitting "+
      "your filthy self in it. Then again, what else "+
      "could it be here for except for advice seekers "+
      "to sit and wait?\n");
   add_item(({ "desk", "assistant", "small desk" }),
      "Compared to the tapestries and the bench, this "+
      "desk is very plain. The fortune teller's assistant "+
      "is sitting at it watching you with bored eyes. "+
      "There is a small sign set upon the corner of the "+
      "desk.\n");
   add_item(({ "sign", "small sign" }), 
      "Perhaps you should read it?\n");
   
   add_exit(MRKT_PATH(fteller01), "north", "@@query_move", 2,1);
   add_exit(MRKT_PATH(m01), "southeast");
   add_exit(MRKT_PATH(m02), "south");
   add_exit(MRKT_PATH(m03), "southwest");
   add_exit(MRKT_PATH(m06), "east");
   
   set_alarm(1.0, 0.0, "reset_room");
}

void
init()
{
   ::init();
   
   add_action("read", "read");
   add_action("purchase", "purchase");

   return;
}

int
read(string str)
{
   if((str=="sign")||(str=="small sign"))
      {
      write("To see the great and renowned fortune "+
         "teller just <purchase> a ticket. It will "+
         "cost you 20 silver coins. A very reasonable "+
         "sum.\n");      
      say(QCTNAME(this_player()) + " takes a moment to "+
         "read the small sign on the desk.\n");
   }
   write("Read what? The sign?");
   return 1;
}

int
purchase(string str)
{
   if((str=="ticket"))
      {
      if(!obj)
         {
         write("You cannot purchase a ticket since the "+
            "assistant is not present.\n");
         return 1;
      }
      write("You pay the assistant 20 silver coins and "+
         "receive a ticket to see the fortune teller.\n");
      say(QCTNAME(this_player()) + " purchases a ticket "+
         "to see the fortune teller.\n");
   }
   write("Purchase what? A ticket?");
   return 1;
}

reset_room()
{
   if(!obj)
      {
      obj = clone_object(MRKT_PATH(npc/assistant));
      obj -> move_living("xxx", TO);
   }
}

query_move()
{
   object *ob;
   int pres, i;
   
   ob = FILTER_LIVE(all_inventory(this_room()));
   pres = 0;
   for(i = 0; i < sizeof(ob); i++)
   {
      if(ob[i]->query_name() == "ticket")
         {
         pres = 1;
       }
   }
   if(pres = 1)
      {
      write("The assistant says: You have no ticket! "+
         "If you want to see the fortune teller, you "+
         "must purchase a ticket first!\n");
      say(QCTNAME(this_player()) + " tried to go see "+
         "the fortune teller without a ticket! What "+
         "cheapskate!\n");
   }
   return pres;
}

