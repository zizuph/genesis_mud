/* Master Bedroom For Icewall Coded by Steve
* and fixed up real nice by Stevenson
*
* Navarre April 30th 2009: Updated code to reload the bin on reset.
*/

#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/icewall/local.h"
#include <macros.h>
#include "/sys/money.h"
inherit ICEINROOM;

object door, trash;
int found;

void reset_icewall_room(); /* prototype */

void create_icewall_room()
{
   set_short("Master Bedroom");
   set_long(BS(
         "This is the master bedroom.  The room is very dusty and you reckon" 
         +" that its been a long time since this room has seen any action.  "
         +"A picture on the wall is mysteriously clean.  There is a closet in the"
         +" east wall and a pair of double doors in the west.",75));
   
   add_item(({"picture"}),
      "The picture depicts a Knight of Solamnia fighting a huge white dragon.\n"
      +"The dragon is holding a glowing prismatic sphere.  It appears that the\n"
      +"eyes of the dragon are watching you and not the knight.\n");
	add_item("closet", "@@closet_desc");
   
   add_cmd_item("bed","search","@@give_surprise");
   
   add_exit(ICE_CAST2_R + "hall4_2.c", "west");
   add_exit(ICE_CAST2_R + "closet.c", "east");
   
   door = clone_object(ICE_CAST_O + "masddoor1.c");
   door->move(TO);
   door->set_key(MASKEY);
   
   door = clone_object(ICE_CAST_O + "closetdoor.c");
   door->move(TO);
   door->set_key(CLOSKEY);

   reset_icewall_room();
}

void reset_icewall_room()
{
  object kender_box;

  found = 0;
   
  if(trash)
  {
    trash->remove_object();
  }
  trash = clone_object(ICE_CAST_O+"litter_bin");
  kender_box = clone_object("/d/Krynn/icewall/castle/obj/kender_box");
  kender_box->move(trash, 1);
  trash->move(TO, 1);
}

string give_surprise() {
   if (!found) {
      MONEY_MAKE_SC(5)->move(TP);
      found = 1;
      return "You find 5 silver coins under the mattress.\n";
   }
   return "You find nothing under the mattress.\n";
}

string closet_desc()
{
	if(door->query_open())
		return("The closet is set in the east wall of the room. " +
		"Although the doors are open, it's hard to make " +
		"out what's inside without actually going east, into " +
		"the closet itself.\n");
	else
	return("It's hard to judge a closet by its closed door.\n");
}

