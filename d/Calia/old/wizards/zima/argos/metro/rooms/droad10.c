/*
**   ARGOS - Metro - Dueteros road
**
**   History:
**   Date       Coder      Action
**   --------   ---------- ---------------------------------
**   1/30/95    Zima       Created
**
*/
/* inherits/includes */
inherit "/std/room";
#include <stdproperties.h>
#include <macros.h>
#include "defs.h"
 
void create_room() {
   set_short("Deuteros Road");
   set_long(
       "An ornately decorated building sits to the west, blue banners "+
       "hanging from either side of its entrance, above which an "+
       "inscription is written in bold letters. There is a high "+
       "iron fence surrounding the area to the east, with an "+
       "arched gate leading inside. Other shops and buildings "+
       "line the Deuteros road which leads north and south.\n");
 
   add_item("fence",
       "It is a high iron fence with spikes atop each post to " +
       "discourage anyone from scaling it. A gate leads inside "+
       "the fence to the east.\n");
   add_item("gate",
       "It is an arched entrance through the fence to the east.\n");
   add_item(({"road","roads","street","streets"}),
       "Deuteros road runs north and south between the shops and other "+
       "businesses.\n");
   add_item(({"shops","establishments","buildings","enterprises"}),
       "They are one-level buildings constructed of marble, lining "+
       "the street on the both sides like white cubes. The building "+
       "directly east and the one directly west have an official "+
       "look to them, with banners hanging next to and inscriptions "+
       "written above their entrances.\n");
   add_item(({"banner","banners"}),
       "The banners hang from poles which angle from their bases on "+
       "the wall of the building to the west. They are made of "+
       "blue silk and bear the royal arms, a shield emblazoned with a "+
       "winged horse surmounted by a crown with three jewels.\n");
   add_item("inscription",
       "Sculpted into the marble in sharp letters above the entrance "+
       "to the building, it reads: ROYAL BANK OF ARGOS.\n");
   add_cmd_item("inscription", "read",
       "Sculpted into the marble in sharp letters above the entrance "+
       "to the building, it reads: ROYAL BANK OF ARGOS.\n");
 
   /* exits */
   add_exit(ROOM_DIR+"droad9",  "north",0);
   add_exit(ROOM_DIR+"droad11", "south",0);
   add_exit(ROOM_DIR+"depot",   "east",0);
   add_exit(ROOM_DIR+"bank",    "west",0);
}
