/*
**  MCLUB - Memorial Shrine, Inside gate to area
**
**  History:
**  Coder        Date                       Action
**  ---------- --------  -----------------------------------------------------
**  Zima       4/7/95    Created
**
*/
inherit "/std/room";
#include <stdproperties.h>
#include <macros.h>
#include "defs.h"
 
create_room() {
   object gate;
 
   set_short("Inside a gate");
   set_long(
      "You are standing inside a gate marked by a large stone arch over "+
      "a path in the forest. The path leads west beneath the arch and "+
      "east towards a clearing. A gentle breeze peacefully rustles the "+
      "leaves of the trees of the surrounding forest.\n");
 
   add_item("arch",
      "It is a large arch built over the path, framing the gate into "+
      "this part of the forest. The arch is built of smooth stones "+
      "which have been cut to fit perfectly into their places in "+
      "the architecture of the arch. An emblem is set in the keystone "+
      "at the top of the arch.\n");
   add_item("keystone",
      "It is the large stone at the top of the arch in the center. "+
      "An emblem is set in it.\n");
   add_item("emblem",
      "Sculpted into the keystone of the arch, the emblem is a "+
      "four-pointed star set within a circle.\n");
   add_item("path",
      "The wide path leads east and west through the trees.\n");
   add_item(({"woods","forest","trees"}),
      "Large trees crowd around the edges of the path, a thick forest "+
      "which of various types of trees, their canopy of branches and "+
      "leaves shading the forest's floor.\n");
   add_item("clearing",
      "The trees seem to have been cut away to make a clearing further "+
      "east.\n");
 
 
   gate=clone_object(ROOM_DIR+"gatein"); /* doorway to belltower */
   gate->move(this_object());
   add_exit(ROOM_DIR+"shoak9","east",0);
}
