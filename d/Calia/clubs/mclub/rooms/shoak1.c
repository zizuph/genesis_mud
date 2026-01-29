/*
**  MCLUB - Memorial Shrine, Circle of oaks around the base of the hill
**
**  History:
**  Coder        Date                       Action
**  ---------- --------  -----------------------------------------------------
**  Zima       7/29/95   Created
**
*/
inherit "/std/room";
#include <stdproperties.h>
#include <macros.h>
#include "defs.h"
 
object caretaker=0;
 
void reset_room() {
    object TO=this_object();
    if (caretaker) return;
    caretaker=clone_object(NPC_DIR+"caretaker");
    caretaker->equip_me();
    caretaker->move(TO);
    tell_room(TO, QTNAME(caretaker)+" walks down the path.\n");
}
 
 
create_room() {
   set_short("On a circular path");
   set_long(
      "You walk around the base of the hill along the path to yet "+
      "another great oak set apart from the thick forest which grows "+
      "around the hill. The stone walls of the shrine seem an "+
      "impregnable fortress built atop the hill, too steep to climb "+
      "here. The path continues to the west and southeast.\n");
   add_item("grass","It carpets the steeps sides of the hill.\n");
   add_item("flowers","They are wild violets growing on the sides "+
                      "of the hill.\n");
   add_item("hill",
      "It is a steep round hill, its sides covered with lush grass and "+
      "small purple flowers.\n");
   add_item("shrine",
      "It is a small shrine of some sort which has been built on top of "+
      "the hill. The hill is to steep to reach the shrine from here.\n");
   add_item(({"woods","forest","trees"}),
      "The hill is surrounded by a thick forest of tall trees, some of "+
      "which have been cleared to make a path around the base of the hill.\n");
   add_item("oak",
      "Separated from the rest of the forest, this sturdy oak grows alone "+
      "in the center of the cleared path around the hill. Its canopy reaches "+
      "high above you providing a cooling shade. Its height and girdth tell "+
      "you it has been here since ancient times.\n");
   add_item(({"path","paths"}),
      "It circles the round hill, leading southwest and east.\n");
 
   add_exit(ROOM_DIR+"shoak12","west",0);
   add_exit(ROOM_DIR+"shoak2","southeast",0);
   set_alarm(1.0,0.0,"reset_room");
}
