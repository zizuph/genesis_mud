/* Olive grove - olives can be picked here
**
** Date      Coder    Action
** -------   -------- ----------------------
** 11/16/95  Zima     Created
*/
inherit "/std/room";
#include <stdproperties.h>
#include <macros.h>
#include "defs.h"
#define  NUM 2
object To=this_object();
object *vial=allocate(NUM);
object lamp=0;
 
void make_lamp() {
   if ((lamp)&&(present(lamp,To))) return;
   lamp=clone_object(METRO_DIR+"objects/brass_lamp");
   lamp->move(To);
}
void make_vial(int i) {
   if ((vial[i])&&(present(vial[i],To))) return;
   vial[i]=clone_object(METRO_DIR+"objects/glass_vial");
   vial[i]->fill_vial();
   vial[i]->move(To);
}
void reset_room() {
   int i;
   make_lamp();
   for (i=0; i<NUM; i++) make_vial(i);
}
 
void create_room() {
   set_short("In an old shed");
   set_long(
       "The dust from the rotting boards of this old wooden shed almost "+
       "chokes you. There is a large press of some kind in here, along "+
       "with a table covered with dust. It seems no one has been here "+
       "in a while.\n");
   add_prop(ROOM_I_INSIDE,1);
   add_item("dust",
      "It covers everything in here. You feel a sneeze coming on.\n");
   add_item("shed",
      "It is an old dilapidated wooden storage shed.\n");
   add_item("boards","They look old and rotten.\n");
   add_item("press",
      "It is a large contraption used to press olives into olive oil. "+
      "Unfortunately it is broken and looks like it hasn't been touched "+
      "in a long time.\n");
   add_item("table","It is just an old wooden table, covered with dust.\n");
 
   /* exits */
   add_exit(ROOM_DIR+"ogrove8","north",0);
   reset_room();
}
