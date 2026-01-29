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
#include "ogrove.h" /* allows picking of olives */
 
void reset_room() { NumOlives=MAX_OLIVES; }
 
void create_room() {
   set_short("An olive grove");
   set_long(
       "Rows of neatly set olive trees surround you on all sides, "+
       "their branches laden with their green fruit. Paths through "+
       "the grove lead north, west and east.\n");
 
   add_item("trees",
            "Olive trees, set neatly in rows, laden with olives.\n");
   add_item("olives",
            "Clustered on the limbs of the trees, they seem ready to pick.\n");
 
   /* exits */
   add_exit(ROOM_DIR+"ogrove7","north",0);
   add_exit(ROOM_DIR+"ogrove3","west",0);
   add_exit(ROOM_DIR+"ogrove8","east",0);
   reset_room();
}
