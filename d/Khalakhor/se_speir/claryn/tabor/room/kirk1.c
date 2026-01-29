/* Kirk of Tabor Sogh
**
** History:
** Date        Coder       Action
**----------   ----------- ----------------------------------
** 1/9/98      Zima        Created
**
*/
/* inherits/includes */
inherit "/d/Khalakhor/std/room";
#include "kirk.h"
 
/* room definition */
void create_khalakhor_room() {
   set_short("village kirk");
   set_long("   You are in the entrance of the humble kirk of Tabor Sogh, its "+
      "crude stone walls and thatched roof adorned only by two small "+
      "stained-glass windows, one on the north wall and another on the "+
       "south. A wooden pedestal sits below the window on the north wall. "+
      "Arched entrances lead out of the village kirk to the west and "+
      "further inside to the east.\n");
 
   INSIDE;
   add_item(({"wall","walls"}),"They are simple stone walls.\n");
   add_item("roof","It is a simple thatched roof.\n");
   add_item(({"window","windows"}),
      "Two small stained glass windows adorn the entrance, one on the "+
      "north wall and another on the south.\n");
   add_item(({"north window","north wall","first window"}),
      "The small stained-glass window on the north wall portrays the "+
      "image of a great angel standing in the clouds. His wings are "+
      "lifted high above his head, and he holds a long trumpet in "+
      "his hand.\n");
   add_item(({"south window","south wall","second window"}),
      "The small stained-glass window on the south wall portrays the "+
      "sun shining with rays radiating from it. Upon the face of the sun "+
      "is the emblem of a shamrock. An inscription is written along the "+
      "arched border of the window in the mosaic of colored glass.\n");
   add_item("inscription",
      "Part of the mosaic of the small window on the south wall, it "+
      "wraps around the top of the arched border of the window.\n");
   add_cmd_item("inscription","read",
      "Pray for Wisdom in the Mysteries of Ardaugh\n");
   add_item("pedestal",
      "It is a low unornate wooden pedestal set beneath the window along "+
      "the north wall.\n");
 
   add_exit("road_1_3", "west",0);
   add_exit("kirk5",    "east",0);
}
