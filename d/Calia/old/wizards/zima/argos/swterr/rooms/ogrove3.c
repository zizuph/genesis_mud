/* Olive grove - olives can be picked here
**
** Date      Coder    Action
** -------   -------- ----------------------
** 12/93     Zima     Created
** 8/24/95   Zima     Cleaned up/recoded picking of olives
** 11/16/95  Zima     Extended olive grove to the east to fill in area between
**                    grove and dirt road. (ogrove6-9.c)
*/
inherit "/std/room";
#include <stdproperties.h>
#include <macros.h>
#include "defs.h"
#include "ogrove.h" /* allows picking of olives */
 
void reset_room() {
   NumOlives=MAX_OLIVES;
}
 
void create_room() {
   set_short("An olive grove");
   set_long(
       "You walk through a grove of olive " +
       "trees, their branches laden with their green fruit. " +
       "The trees are neatly set in rows, each one well trimmed. " +
       "You may walk through the grove to the west, east and south.\n");
 
   add_item("trees",
            "Olive trees, set neatly in rows, laden with olives.\n");
   add_item("olives",
            "Clustered on the limbs of the trees, they seem ready to pick.\n");
 
   /* exits */
   add_exit(ROOM_DIR+"ogrove2","west",0);
   add_exit(ROOM_DIR+"ogrove6","east",0);
   add_exit(ROOM_DIR+"ogrove5","south",0);
   reset_room();
}
