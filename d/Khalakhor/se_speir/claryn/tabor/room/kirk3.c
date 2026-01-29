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
   set_long(
      "   This is the eastern chamber of the kirk, its crude stone walls "+
      "adorned with three small stained-glass windows, one each on the "+
      "north, east and south walls. Two candelabrum sit in the corners "+
      "of the chamber, while there is a small wooden pedestal beneath "+
      "each of the three windows. An arch marks the entrance to the "+
      "central chamber to the west.\n");
 
   INSIDE;
   add_item(({"wall","walls"}),"They are simple stone walls.\n");
   add_item("roof","It is a simple thatched roof.\n");
   add_item(({"window","windows"}),
      "Three small stained glass windows adorn the walls of the chamber, "+
      "the first on the north, the second on the south and the third on "+
      "the east.\n");
   add_item(({"north window","north wall","first window"}),
      "It is a small stained-glass window set in the north wall. "+
      WINDESC[4]+"\n");
   add_item(({"south window","south wall","second window"}),
      "It is a small stained-glass window set in the south wall. "+
      WINDESC[5]+"\n");
   add_item(({"east window","east wall","third window"}),
      "It is a small stained-glass window set in the east wall. "+
      WINDESC[6]+"\n");
   add_item(({"pedestal","pedestals"}),
      "A low unornate wooden pedestal sets beneath each of the three "+
      "windows.\n");
   add_item("arch",
      "It marks the entrance to the chamber to the west.\n");
   add_item(({"candle","candles","candelabrum","candelabra"}),
      "Two inornate candelabrum stand in the corners of the room, each "+
      "with nine candles set in its brass branches.\n");
 
   add_exit("kirk5","west");
}
