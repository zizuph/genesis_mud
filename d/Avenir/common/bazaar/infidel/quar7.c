// file name: quar7
// creator: Ilyian (October 9, 1995)
// last update:
// purpose: Quarters in the Infidel Hideout
// note: 
// bug(s):
// to_do:

inherit "/d/Avenir/common/bazaar/infidel/infidel";
#include "infidel.h"

void reset_room();
object female;

void
create_room()
{
   quar_long("I'll use set_long instead");
   
   set_long("This is a small room that appears to be "
           +"a larder. There are large shelves on the north "
           +"wall, and a high wooden table in the center of "
           +"the room.\n");
   set_short("larder");

   AI(({"shelf","shelves"}),"The shelves are high and "
           +"contain various parcels of food and other "
           +"useful items.\n");
   AI(({"food","parcel","parcels","item","items"}),"The "
           +"food on the shelves is wrapped in thick "
           +"paper in hopes that it will be preserved.\n");
   AI(({"table"}),"The table in the center of the room "
           +"is small and high, and seems to be where "
           +"food gets cut up and prepared for serving.\n");

   hall_exit("11","south");

   reset_room();
}

void
reset_room()
{
   if(!female)
     {
        female = clone_object(MON+"g_infidel");
        female->arm_me();
        female->move(TO);
        female->add_act("emote gets some food from the "
                       +"shelves.");
        female->add_act("emote cuts of a long stick of "
                       +"dried beef.");
        female->add_act("sigh"); 
     }
 
}
