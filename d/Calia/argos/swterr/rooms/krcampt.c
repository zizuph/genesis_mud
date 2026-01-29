/* Kretan encampment along the dirt road of SWTERR
**
** History
** Date       Coder        Action
** -------- -------------- --------------------------------------------
** 1994     Zima           Coded
** 1/25/97  Zima           removed soldiers, added object reduction
*/
inherit "/std/room";
#include "defs.h"
inherit REDUCE_OBJ_MOD;
#include <stdproperties.h>
#include <macros.h>
 
#define NUM 4
object *npc=allocate(NUM);
 
void make_npc(int i) {
    string path;
    if (npc[i]) return;
    switch(i) {
       case 0:  path=KRCAMP_DIR+"monsters/dcomder/dcomder2";         break;
       case 1:  path=KRCAMP_DIR+"monsters/ensign/ensign0";           break;
       case 2:  path=NPC_DIR+"krcnoble";                             break;
       case 3:  path=DEPHTEMP_DIR+"monsters/krcprsts";               break;
       default: path=KRCAMP_DIR+"monsters/soldier/soldier2";         break;
    }
    npc[i]=clone_object(path);
    npc[i]->equip_me();
    npc[i]->move(THIS);
    tell_room(THIS, QCNAME(npc[i])+" enters the tent.\n");
}
 
void reset_room() {
   int i;
   for (i=0; i<NUM; i++) make_npc(i);
    reduce_objects();
}
 
/* room definition */
void create_room() {
   set_short("Inside a tent");
   set_long(
       "You step inside a round canvas tent. A pole in the center " +
       "of the tent supports the top making it into the shape of " +
       "a cone. A small table and chair are the only furnishings in this " +
       "sparse shelter. The entrance to the tent is open to the east.\n");
 
   add_item("pole","A tall wooden pole supporting the top of the tent.\n");
   add_item("top",
      "The pole supporting the top makes a cone above the circular tent.\n");
   add_item("chair",
      "It is a simple wooden chair. It doesn't look very comfortable.\n");
   add_item("entrance","It is open to the east.\n");
   add_item("table",
      "It is a small wooden table, not what you would expect to be the " +
      "desk of a great leader, but it is sufficient for a camp.\n");
   add_prop(ROOM_I_INSIDE,1);
 
   /* exits */
   add_exit(ROOM_DIR+"krcamp1","east",0);
   reset_room();
}
