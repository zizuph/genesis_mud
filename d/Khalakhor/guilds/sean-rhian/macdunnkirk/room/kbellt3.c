/* Kirk of Port City - Belltower, upper level
**
** History:
** Date        Coder       Action
**----------   ----------- ----------------------------------
** 4/5/97      Zima        Created
**
*/
/* inherits/includes */
inherit  "/d/Khalakhor/std/room";
#define  INC_KHALSYS_DEFS
#include "defs.h"
#include <stdproperties.h>
 
/* room definition */
void create_khalakhor_room() {
   set_short("Belltower of the kirk");
   set_long(
      "   You are standing on a ledge which encircles the upper level of the "+
      "belltower, where the massive bells "+
      "of the kirk are suspened from a stout beam over your head. The walls "+
      "are a series of open arched windows, allowing the toll of the bells "+
      "to be heard throughout the village, and allowing you a great view "+
      "in all directions. A thick rope is tied to a long lever on the beam "+
      "and descends to the floor below. A gentle, damp breeze passes "+
      "through the belltower.\n");
 
   INSIDE;
   add_prop(SR_K1SECURE,1);
   add_item("view",
      "The open windows allow you a wonderful view of the village from "+
      "here, to the north, south, east and west.\n");
   add_item("north",
      "Looking north you see the roof of the kirk, a steep plane covered "+
      "with old wood shingles rising to a point in the center of the "+
      "kirk.\n");
   add_item("south",
      "Looking south you see some of the small buildings of the village, "+
      "and the port area along the harbour with its sailing vessels.\n");
   add_item("west",
      "Looking west, you see the cloistered garden next to the kirk, and "+
      "the abbey on the other side.\n");
   add_item("east",
      "Looking east, you see the small buildings and streets of the "+
      "quiet village, villagers and travellers making their way through "+
      "the narrow thoroughfares.\n");
   add_item(({"bell","bells"}),
      "They are massive bronze bells, attached to a stout beam set "+
      "across the top of the bell tower. They look very old and you "+
      "think they could make a deafening clang when rung.\n");
   add_item(({"beam","lever"}),
      "A very thick beam is set across the top of the tower, from which "+
      "the bells are suspended. The beam rotates on its ends so that "+
      "the bells can ring. A rope is attatched to a long lever on the "+
      "beam, descending to the floor of the tower below.\n");
   add_item("kirk",
      "It is a large stone structure, obviously religious in nature.\n");
   add_item(({"tower","belltower","chamber"}),
      "It is a large stone tower rising on the southwest corner of the "+
      "kirk.\n");
   add_item("steps",
      "A set of steep stone steps lead down to the lower levels of the "+
      "tower.\n");
   add_item("ledge",
      "The ledge runs along the four edges of the tower here, allowing "+
      "you to walk around.\n");
   add_item(({"window","windows","wall","walls"}),
      "The walls of the belfry are a set of open, arched windows, "+
      "allowing a gentle breeze to pass through.\n");
   add_item(({"rope","hole"}),
      "A thick rope is tied to the lever of the bells, and descends "+
      "to the floor of the tower below. It is tied too far out for "+
      "you to reach from here.\n");
   add_cmd_item("rope","pull","You can't reach it from here.\n");
   add_item("floor", "The stone floor is far below you.\n");
 
   add_exit("kbellt2","down");
}
