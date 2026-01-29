/* Kirk of Port City - Abbey garden
**
** History:
** Date        Coder       Action
**----------   ----------- ----------------------------------
** 1/18/98     Zima        Created
**
*/
#define  INC_KHALSYS_DEFS

#include <macros.h>
#include "defs.h"

inherit  ROOM+"kgardbase";
 
/* room definition */
void
create_khalakhor_room ()
{
   setup_garden_room();
   set_long((query_std_long())+"There is a circular pool here, with "+
      "a large boulder in the center, upon which stands a statue of "+
      "a robed figure, water pouring out of a basin it holds, flowing "+
      "over the boulder into the pool.\n");
 
   add_item(({"statue","figure","pot"}),
      "The statue standing on the boulder is that of a robed figure, "+
      "its head and face cowled so that you can not make out its "+
      "face. He holds a large basin tipped steeply over, water pouring "+
      "gently out.\n");
   add_item("boulder",
      "It is a large granite boulder, seemingly flat on the bottom, "+
      "worn smooth by the flow of water. It sits in the center of "+
      "the pool and acts as a pedestal for the statue.\n");
   add_item("pool",
      "It is a circular pool bordered by rounded stones. A large "+
      "boulder sits in the middle of it, on top of which is a statue. "+
      "Water pours out continuously from the statue filling the pool, "+
      "though its level of clear water never seems to rise.\n");
  add_item("water",
      "The water looks pure and cool as it flows down from the basin "+
      "in the hands of the statue into the pool.\n");
 
   add_exit("kgarden4","north");
}

int
drink (string cmd)
{
   string verb=query_verb();
   notify_fail(capitalize(verb)+" what from what?\n");
   if (!stringp(cmd)) return 0;
   if (!parse_command(cmd,({(all_inventory(TP))}),
      "[water] 'from' 'pool'"))
      return 0;
   if (!(TP->drink_soft(100))) {
      write("You seem unable to drink anything from the pool.\n");
      return 1;
   }
   write("You "+verb+" water from the cool clear pool.\n");
   tell_room(TO,QCTNAME(TP)+" "+verb+"s water from the cool clear pool.\n",
             TP);
   return 1;
}

void
init ()
{
   ::init();
   add_action(&drink(),"drink");
   add_action(&drink(),"sip");
   add_action(&drink(),"taste");
}
