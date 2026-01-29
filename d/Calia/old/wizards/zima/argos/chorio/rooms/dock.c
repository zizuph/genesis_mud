/* Dock
**
** History:
** Date        Coder       Action
**----------   ----------- ----------------------------------
** 1/30/97     Zima        Created
**
*/
/* inherits/includes */
inherit "/std/room";
#include <stdproperties.h>
#include <macros.h>
#include "defs.h"
 
/* room definition */
void create_room() {
   set_short("On a river dock");
   set_long(
      "You are standing on a small river dock, the swift river flowing "+
      "tranquilly beneath you on its journey east. A small wooden shack "+
      "sits to the east, fishing nets draped across its front as "+
      "decoration. Just to the north you see an old cobblestone road "+
      "and a small village built on the gentle slopes of a large hill. "+
      "A small sign is posted here.\n");
 
#include "csroad.h"
 
   add_item("dock",
      "It is a small wooden dock which extends out over the water. Small "+
      "boat which navigate the river commonly land here.\n");
   add_item("shack",
      "It is a small house made of wooden boards, a rustic little "+
      "shack draped with fishing nets. Its probably a warehouse, an "+
      "office, or perhaps the home of one of the local shipmen.\n");
   add_item(({"net","nets"}),
      "The nets are draped over the front of the shack. Given the holes "+
      "and tears in them, you understand why they are good for nothing "+
      "other than nostalgic docoration.\n");
   add_item("sign",
      "It is a small wooden sign, painted white with a sun burst emblem "+
      "on it. There are words written on it.\n");
   add_cmd_item("sign","read",
      "It says: Welcome to the port of the village of Chorio Hagios!.\n"+
      "Below that a note has been attached: Transport to Argos has been "+
      "suspended due to the war.\n");
 
   add_exit("csroad01", "north",0);
   add_exit("dockhouse","east",0);
}
