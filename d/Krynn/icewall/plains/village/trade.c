/*Created by Macker 7/11/94*/
#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/icewall/local.h"
#include <macros.h>
inherit VILLAGE_INROOM;

object cleric;

void
create_village_room()
{
   set_short("Cleric's Place");
   set_long(
      "This is where the cleric of the ice folk forges the mysterious " +
      "icy weapons and armours. Judging from the sleeping furs " +
      "on the ground in the corner, you decide that he probably " +
      "lives here too.\n");
   
   add_item( ({"building", "room"}),
      "This building has only one room. The walls are made of " +
      "packed, frozen snow. Why don't you look around?\n");
   add_item( ({"hide", "door", "entrance"}), "It is not actually a door. " +
      "It is a heavy animal hide hanging from above the doorway. " +
      "It is moved aside each time someone enters or leaves the building.\n");
   add_item("village", "You are in the village, you silly person. Just look around!\n");
   add_item(({"fur", "furs", "sleeping fur", "sleeping furs"}),
      "These sleeping furs look rather old and tattered.\n");
   add_item("corner", "There are some sleeping furs here.\n");
   
   
   add_exit(VILLAGE + "village_4.c", "south");
   set_alarm(0.1,0.0,"reset_room");
}

void
reset_village_room()
{
   object cleric;
   
   if ( !P("raggart", TO) && !P("cleric", TO) ) {
      cleric = clone_object(PLAINS_L + "cleric");
      cleric->move(TO);
      tell_room(TO, QCNAME(cleric) + " arrives.\n");
   }
}
