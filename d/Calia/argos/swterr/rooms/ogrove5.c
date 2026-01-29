/* Olive grove - olives can be picked here
**
** Date    Coder    Action
** ------- -------- ----------------------
** 12/93   Zima     Created
** 8/24/95 Zima     Cleaned up/recoded picking of olives
**
*/
inherit "/std/room";
#include <stdproperties.h>
#include <macros.h>
#include "defs.h"
#include "ogrove.h" /* allows picking of olives */
 
object oliveman=0;
 
void reset_room() {
    NumOlives = MAX_OLIVES;
    if (oliveman) return;
    oliveman=clone_object(NPC_DIR+"oliveman");
    oliveman->equip_me();
    oliveman->move(THIS);
    tell_room(THIS, QCTNAME(oliveman)+" sneaks up on you.\n");
}
 
 
/* room definition */
void create_room() {
   set_short("An olive grove");
   set_long(
       "You walk through a grove of olive " +
       "trees, their branches laden with their green fruit. " +
       "The trees are neatly set in rows, each one well trimmed. " +
       "You may walk through the grove to the north and west.\n");
 
   add_item("trees",
            "Olive trees, set neatly in rows, laden with olives.\n");
   add_item("olives",
            "Clustered on the limbs of the trees, they seem ready to pick.\n");
 
   /* exits */
   add_exit(ROOM_DIR+"ogrove4","west",0);
   add_exit(ROOM_DIR+"ogrove3","north",0);
   set_alarm(1.0,0.0,"reset_room");
}
