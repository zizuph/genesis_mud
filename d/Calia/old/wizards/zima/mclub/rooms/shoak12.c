/*
**  MCLUB - Memorial Shrine, Circle of oaks around the base of the hill
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
   set_short("At the base of a hill");
   set_long(
      "You are standing on the northern side of a steep hill hidden within "+
      "the woods. A large oak grows "+
      "here in solitude, separated from the surrounding forest. A set of "+
      "steps lead south up the hill into an entrance of the shrine, while "+
      "the path encircles the hill to the west and east.\n");
 
   add_item("hill",
      "It is a steep round hill, its sides covered with lush grass and "+
      "small purple flowers.\n");
   add_item("grass","It carpets the steeps sides of the hill.\n");
   add_item("flowers","They are wild violets growing on the sides "+
                      "of the hill.\n");
   add_item("shrine",
      "It is a small shrine of some sort which has been built on top of "+
      "the hill. A set of steps lead up the side of the hill to the south "+
      "into an entrance to the structure.\n");
   add_item(({"woods","forest","trees"}),
      "The hill is surrounded by a thick forest of tall trees, some of "+
      "which have been cleared to make a path around the base of the hill.\n");
   add_item("oak",
      "Separated from the rest of the forest, this sturdy oak grows alone "+
      "in the center of the cleared path around the hill. Its canopy reaches "+
      "high above you providing a cooling shade. Its height and girdth tell "+
      "you it has been here since ancient times.\n");
   add_item("steps",
      "Logs have been set into the side of the hill to make a set of "+
      "steps leading up the hill to the south into an entrance of the "+
      "shrine. They are crude but allow ascension to the top.\n");
   add_item("entrance",
      "The entrance to the shrine is marked by a pointed arch, a set "+
      "of steps leading up to it.\n");
   add_item(({"path","paths"}),
      "It encircles the hill to the west and east.\n");
 
   add_exit(ROOM_DIR+"shoak11","west",0);
   add_exit(ROOM_DIR+"shoak1", "east",0);
   add_exit(ROOM_DIR+"shvestn","steps","@@steps");
}
 
int steps() {
   write("You climb the steps up the hill to the south.\n");
   return 0;
}
