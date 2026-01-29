/* ARGOS - SWTERR - Western Bridge from Marble Road (NWTERR)) to Dirt Road
**
** History:
** Date      Coder      Action
** --------- ---------- --------------------------------
** 11/10/95  Zima       Created
**
*/
/* inherits/includes */
inherit  "/std/room";
#include <stdproperties.h>
#include <macros.h>
#include "defs.h"
 
void create_room() {
   set_short("On an arched bridge");
   set_long(
      "You are standing at the crest of an arched bridge made of sturdy "+
      "beams of oak. The wide river which the bridge spans flows beneath "+
      "you, filling your ears with its torrential rush. The bridge leads "+
      "north onto a marble road, and south to a dirt road, each following "+
      "the flow of the river along their respective banks.\n");
 
   add_item("bridge",
      "It is a study oak bridge, slightly arched in the middle, which "+
      "spans the width of the river.\n");
   add_item(({"road","roads","dirt road","marble road"}),
      "The road on the north bank of the river is made of long slabs of "+
      "white marble, a regal highway along the river's northern bank. "+
      "Its counterpart along the southern bank is a dusty disappointment "+
      "to its illustrious northern twin.\n");
   add_item("river",
      "The river is very wide, and seems deep with its rushing torrents. "+
      "It flows swiftly below your feet, its rush like a constant "+
      "lullaby.\n");
 
   /* exits */
   add_exit(NWTERR_DIR+"rooms/r18","north",0);
   add_exit(ROOM_DIR+"r18","south",0);
}
