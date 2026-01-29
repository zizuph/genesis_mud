/* Kirk Abbey - Stairs between upper/lower levels (upper)
**
** History:
** Date        Coder       Action
**----------   ----------- ----------------------------------
** 4/10/98     Zima        Created
**
*/
inherit "/d/Khalakhor/std/room";
#include <stdproperties.h>
#include "defs.h"
 
void create_khalakhor_room() {
   set_short("Stairway in the abbey");
   set_long(
      "   You are standing at the top of a spiral staircase in the abbey, "+
      "where a lone candle-laden candleabra stands dimly lighting the "+
      "steps which spiral down to the level below. A cooridor leads west "+
      "from here through the upper level of the abbey.\n");
 
   INSIDE;
   add_item(({"steps","stairs","staircase","stairway"}),
      "A set of wooden stairs spiral down to the lower level. They "+
      "look old but sturdy.\n");
   add_item(({"candelabra","candles"}),
      "The ornate candelabra stands along the northern walln wall, "+
      "made of gold and ornately "+
      "crafted with elegant twists and curves which branch out from "+
      "a tall central staff. Dozens of thick white candles flicker "+
      "in the holders of each, dimly lighting the stairway.\n");
   add_item("cooridor", "It leads west through the abbey.\n");
   add_exit("ucorr1",  "west");
   add_exit("kstairs", "down");
}
