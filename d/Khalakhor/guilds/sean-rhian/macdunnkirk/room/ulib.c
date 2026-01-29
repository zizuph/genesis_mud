// Kirk of Port City - Abbey Library base room - upper level (private)
//
// History:
// Date        Coder       Action
//----------   ----------- ----------------------------------
// 4/10/98     Zima        Created
// 7/19/98     Zima        Recoded
//
//
inherit "/d/Khalakhor/std/room";
#include "defs.h"
#include <stdproperties.h>
 
object shelf;
 
void create_library(string windir, string extra, int has_shelf)
{
   set_short("Library of the abbey");
   set_long(
      "   You are in the library of the upper level of the abbey, a place "+
      "filled with mysteries and knowledge. The smell of old parchment "+
      "and scrolls fills your notrils, summoning a presence of ancient "+
      "wisdom in you. An ornate chandelier hangs overhead, heavily laden "+
      "with dozens of candles brightly lighting the chamber. A stained "+
      "glass window is set in the "+windir+"ern wall"+extra+".\n");
 
   INSIDE;
   add_item(({"walls","room","chamber","library"}), "@@query_long");
   add_item(({"chandelier","chain","candles","light"}),
      "Suspended by a thick gold chain from the central point of the "+
      "vaulted ceiling high above you is an ornate chandelier filled with "+
      "dozens of burning candles, their graceful flickering flames filling "+
      "the chamber with a subtle light.\n");
   add_item("window",
      "It is a tall thin window with a pointed arch top, like those "+
      "of the corridor. Its opaque panes are set in a lattice of "+
      "diamond-shaped cream colored glass.\n");
   add_cmd_item(({"air","books","smell","room","scrolls","parchment"}),
      ({"smell","sniff","inhale"}),
      "You breathe in deeply filling your senses with the smell of "+
      "old parchment and scrolls.\n");
   if (has_shelf)
      {
      shelf = clone_object(SR_OBJ+"bookshelf");
      shelf->move(TO);
      }
}
