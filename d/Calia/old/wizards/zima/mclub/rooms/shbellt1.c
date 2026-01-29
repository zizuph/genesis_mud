/*
**  MCLUB - Memorial Shrine, Bell Tower
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
   object door;
   set_short("A tower of the shrine");
   set_long(
      "You are standing at the bottom of a tower of the stone shrine, "+
      "at least the ceiling is twice the height of those of the rest "+
      "of the structure. A rather large but rusty old bell hangs in the "+
      "heights of the chamber, a rope dangling from it to the floor. "+
      "A set of wooden steps lead down into the ground to the west along "+
      "the southern wall.\n");
 
   add_item(({"tower","chamber"}),
      "This chamber is a short tower, made of the same stones as the "+
      "rest of the shrine. There is no ornamentation to this room, "+
      "except for the large bell which hangs above.\n");
   add_item("ceiling",
      "It rises twice as high as that of any other chamber of the shrine, "+
      "though calling this a tower might be a stretch. A large iron bell "+
      "hangs from it.\n");
   add_item("bell",
      "It is a large bell wich seems a little weathered, hanging at the "+
      "top of this short tower. A rope is tied to it.\n");
   add_item("rope",
      "It is tied to the bell and hangs down to the floor of the tower.\n");
   add_cmd_item("rope","pull","@@ring_bell");
   add_item("steps",
      "A set of wooden steps leads below ground toward the west.\n");
 
   add_prop(ROOM_I_INSIDE,1);
 
   door=clone_object(ROOM_DIR+"bdoorin"); /* doorway to belltower */
   door->move(this_object());
   add_exit(ROOM_DIR+"shconent","steps","@@steps");
}
 
int steps() { write("You take the steps down to the west.\n"); return 0; }

int ring_bell() {
   object TP=this_player();
   object TR=this_object();
   write("You pull down on the rope with a great heave.\n");
   tell_room(TR,QCTNAME(TP)+" pulls down on the rope with a great heave.\n",TP);
   tell_room(TR,"The bell tolls with a deep loud peal, ringing your ears.\n");
   return 1;
}
