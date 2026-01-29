/*
**  ARGOS - Metro - Thespian Guild
**
**  History:
**  Coder        Date                       Action
**  ---------- --------  -----------------------------------------------------
**  Zima       8/15/95   Created
**
*/
inherit "/std/room";
#include <stdproperties.h>
#include <macros.h>
#include "defs.h"
 
#define NUM_THESP 2
object *thespian=allocate(NUM_THESP);
object master;
 
void make_thespian(int i) {
    if (thespian[i]) return;
    thespian[i]=clone_object(NPC_DIR+"thespian");
    thespian[i]->equip_me();
    thespian[i]->move(THIS);
    tell_room(THIS, QCNAME(thespian[i])+" enters the room.\n");
}
 
void make_master() {
    if (master) return;
    master=clone_object(NPC_DIR+"thespmstr");
    master->equip_me();
    master->move(THIS);
    tell_room(THIS, QCNAME(master)+" enters the room.\n");
}
 
void reset_room() {
   int i;
   for (i=0; i<NUM_THESP; i++) make_thespian(i);
   make_master();
}
 
 
create_room() {
   set_short("Thespian Guild of Argos");
   set_long(
      "This is the back room of the Thespian Guild of Argos where the "+
      "acting order keeps its costumes and props. The western wall is "+
      "lined with a set of tall wardrobes, while a long table sits "+
      "along the northern wall. A tall mirror stands in the southeastern "+
      "corner of the chamber.\n");
 
   add_item("costumes","They are kept in the wardrobes.\n");
   add_item("props","They are stored in the wardrobes.\n");
   add_item(({"wardrobe","wardrobes"}),
      "Tall wardrobes made of steady oak line the western wall. "+
      "The various costumes and props are stored securely in "+
      "them, their doors locked to prevent theft.\n");
   add_item("table",
      "It is a long table sitting next to the northern wall. "+
      "You see a couple of masks, combs and some small jars "+
      "on top.\n");
   add_item(({"mask","masks"}),
      "They are typical actor's masks, one with the face of a hideous "+
      "creature and the other with the face of a king with a crown.\n");
   add_item(({"comb","combs"}),
      "They are just two combs on top of the table.\n");
   add_item(({"paint","jars","face paint"}),
      "The little jars sitting on the table contain various hues of "+
      "face paint, which the actors apply with their fingers.\n");
   add_item("mirror",
      "It is a rather large rectangular mirror, wide enough for "+
      "two or three to examine themselves before a show.\n");
 
   add_prop(ROOM_I_INSIDE,1);
 
   add_exit(ROOM_DIR+"thesp1","east",0);
   reset_room();
}
