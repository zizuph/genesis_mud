/*
**  ARGOS - Metro - Thespian Guild Central Hall
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
 
#define NUM_THESP 3
#define NUM_APPR  1
object *thespian=allocate(NUM_THESP);
object *apprentice=allocate(NUM_APPR);
 
void make_thespian(int i) {
    if (thespian[i]) return;
    thespian[i]=clone_object(NPC_DIR+"thespian");
    thespian[i]->equip_me();
    thespian[i]->move(THIS);
    tell_room(THIS, QCNAME(thespian[i])+" enters the room.\n");
}
 
void make_apprentice(int i) {
    if (apprentice[i]) return;
    apprentice[i]=clone_object(NPC_DIR+"thesp_app");
    apprentice[i]->equip_me();
    apprentice[i]->move(THIS);
    tell_room(THIS, QCNAME(apprentice[i])+" enters the room.\n");
}
 
void reset_room() {
   int i;
   for (i=0; i<NUM_THESP; i++) make_thespian(i);
   for (i=0; i<NUM_APPR; i++) make_apprentice(i);
}
 
 
create_room() {
   set_short("Thespian Guild of Argos");
   set_long(
      "A short stage runs the length of this chamber along its eastern "+
      "wall, several props scattered across its floor. Judging from the "+
      "lack of seating and the relative lack of ornamentation, you "+
      "guess this place must serve for the practice of theatrics rather "+
      "than presentation. Two paintings hang in the back of the room, "+
      "on either side of a doorway which leads west. There are two "+
      "entrances to the chamber leading outside, one to the north "+
      "and the other to the south.\n");
 
   add_item("stage",
      "It is a simple wooden stage which rises a few inches above the "+
      "floor. It runs the length of the eastern wall.\n");
   add_item("props",
      "Just a few costumes, masks and a chair scattered about on "+
      "the stage.\n");
   add_item("costumes",
      "They are wadded up in a pile laying on the stage.\n");
   add_item("chair","A simple wooden chair sits on the stage, a prop.\n");
   add_item(({"paintings","painting"}),
      "The painting on the left portrays a beautiful woman with "+
      "soft curly hair and a delicate neck. She wears an elaborate "+
      "jeweled comb in her hair. A small inscription on the frame "+
      "reads: THESPIA - NATE MATERA.\n"+
      "The painting on the right is of a husky bearded man with "+
      "stern blue eyes. He is dressed in a maroon robe elabortely "+
      "bordered in gold and embroidered with actor's masks over the "+
      "breasts. A small inscription on the frame reads: DRAMATICUS - "+
      "GRAND MASTER.\n");
   add_item("doorway","It leads to another chamber to the west.\n");
   add_item(({"entrance","entrances"}),
      "One entrance leads outside to the south, the other to the "+
      "north.\n");
 
   add_prop(ROOM_I_INSIDE,1);
 
   add_exit(ROOM_DIR+"amph4", "north", 0);
   add_exit(ROOM_DIR+"aroad15","south", 0);
   add_exit(ROOM_DIR+"thesp2", "west",  0);
   reset_room();
}
