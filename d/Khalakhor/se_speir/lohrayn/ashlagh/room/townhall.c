// town hall entrance
inherit "/d/Khalakhor/std/room";
#include "defs.h"
#include <macros.h>
#define  NUMG 2
object *guard=allocate(NUMG);
 
public void reset_room()
{
   int i;
   for (i=0; i<NUMG; i++)
      if (!(guard[i]))
         {
         guard[i] = clone_object(NPC+"guard");
         guard[i]->equip_me();
         guard[i]->move(TO);
         tell_room(TO,QCNAME(guard[i])+" enters from the north.\n");
         }
}
 
public void create_khalakhor_room()
{
   set_short("village hall");
   set_long(
      "This is the meeting room village hall of Baile Ashlagh. A small "+
      "raised stage is built along the south wall, on which a coat-of-"+
      "arms is placed. Simple wood benches line the hall facing south, "+
      "with an aisle down the center. There are doorways to the offices "+
      "of the hall to the east and west, while the entrance to the hall "+
      "is to the north.\n");
 
   add_item(({"building","hall","room"}),
      "The town hall is made like all the other buildings of the "+
      "village, a wood-plank building painted in pastel yellow with "+
      "walls framed and crossed by heavy dark beams.\n");
   add_item("stage",
      "It is merely a small raised area where a speaker would stand, "+
      "built of wood and set along the south wall.\n");
   add_item(({"coat-of-arms","arms","emblem","seal"}),
      "It is a shield cast in purple displaying nine sailing ships. "+
      "Two claymores are crossed behind the shield, though the whole "+
      "emblem is only decorative. A streamer beneath the shield "+
      "has the words 'The Village of Baile Ashlagh in Lohrayn' "+
      "scripted upon it.\n");
   add_item(({"bench","benches","aisle"}),
      "They are simple long benches made of wood. They have no backs "+
      "and look very uncomfortable, probably a ploy to shorten the "+
      "length of meetings which take place here. They are arranged in "+
      "rows facing south, with an aisle down the center leading to "+
      "the stage.\n");
   add_item(({"doorway","doorways","office","offices"}),
      "There are two doorways probably leading to offices or other "+
      "rooms of the hall to the east and west.\n");
   add_item("entrance",
      "The entrance of the hall is to the north.\n");
   add_item(({"roof","ceiling","floor"}),
      "The roof of the hall made of high angled rafters covered with "+
      "wood planks, just like the floor.\n");
 
   add_exit("court2","north");
   add_exit("townhall1","west");
   add_exit("townhall2","east");
   reset_room();
}
