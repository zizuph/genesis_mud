/* Argos Road - bridge
** History
** Date        Coder         Action
** -------- ---------------  ------------------------------------------
** 11/18/96 Zima             Created
*/
/* inherits/includes */
inherit "/std/room";
#include <stdproperties.h>
#include <macros.h>
#include "defs.h"
 
#define NUM 2
object guard=allocate(NUM);
 
void make_guard(int i) {
    if (guard[i]) return;
    guard[i]=clone_object(NPC_DIR+"guard");
    guard[i]->equip_me();
    guard[i]->move(THIS);
    tell_room(THIS, QCNAME(guard[i])+" walks onto the bridge.\n");
}
 
void reset_room() {
   int i;
   for (i=0; i<NUM; i++) make_guard(i);
}
 
void create_room() {
   set_short("On a bridge over a rushing river");
   set_long(
     "The river roars below you as you make your way across this elegant "+
     "marble bridge. The bridge arches slightly as it spans the torrents, "+
     "artistically sculpted with a rampant winged horse on its surface. "+
     "A banner flies from a pole set at the western foot of the bridge.\n");
 
   add_item("river",
      "It rushes by below you, washing over small boulders set in the "+
      "river's bed.\n");
   add_item("road",
      "The road leads off the bridge to the east and west.\n");
   add_item("bridge",
      "It is a skillfully sculpted marble bridge, no common footpath to "+
      "cross the river. It is obviously meant to be a work of art as "+
      "well as a path across the torrents.\n");
   add_item(({"horse","winged horse","surface"}),
      "The surface of the bridge is sculpted with a rampant winged horse, "+
      "an enchanting and powerful creature.\n");
   add_item("banner",
      "It is a large blue banner made of silk, fluttering in the wind "+
      "atop a tall pole. The banner bears a regal emblem on it.\n");
   add_item("pole",
      "A tall pole made of marble, it holds aloft a large banner.\n");
   add_item("block",
      "It is a large block of marble at the foot of the bridge, serving "+
      "as a base for the banner pole and a cornerstone of the bridge. "+
      "A regal emblem is sculpted into its front face.\n");
   add_item("emblem",
      "It is the royal arms of the kingdom of Argos, a shield emblazoned "+
      "with a rampant winged horse, above which is a crown with three "+
      "jewels.\n");
 
   add_exit("r14","west",0);
   add_exit("r14a","east",0);
   reset_room();
}
