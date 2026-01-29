/*
**  MCLUB - Memorial Shrine, Lower Level, Library and Board Room
**
**  History:
**  Coder        Date                       Action
**  ---------- --------  -----------------------------------------------------
**  Zima       5/5/95     Created
**  Zima       7/25/95    A board is added which is to be used as a book
**                        shelf, the notes are writings of the members.
*/
inherit "/std/room";
#include <stdproperties.h>
#include <macros.h>
#include "defs.h"
 
/* prototypes */
void    load_board();
 
create_room() {
   set_short("Library of the conclave");
   set_long(
      "You are in the library of the conclave, the repository of the "+
      "writings of those who abide here and a place for meditation and "+
      "remembrance. A small desk and chair sit next to the eastern wall, "+
      "a pillar candle on the desktop.\n");
 
   add_item(({"room","chamber","library"}),
      "It is one of the stone chambers built beneath the ground "+
      "of the shrine.\n");
   add_item("conclave","It is the lower level of the stone shrine.\n");
   add_item("desk",
      "It is a simple wooden desk sitting next to the eastern wall. "+
      "A candle sits on top of it lighting the room.\n");
   add_item("chair",
      "It is a simple wooden chair next to the desk.\n");
   add_item("candle",
      "It is a thick pillar candle sitting on the desk, lighting the room.\n");
 
   add_prop(ROOM_I_INSIDE,1);
 
   add_exit(ROOM_DIR+"shconcon","south",0);
   load_board();
}
 
void load_board() {
    object bb;
    seteuid(getuid(this_object()));
    bb = clone_object(ROOM_DIR+"lboard/board");
    bb->move(this_object());
}
 
