/*
**  ARGOS - Metro - Empty commercial building used by rebels for hideout
**
**  History:
**  Coder        Date                       Action
**  ---------- --------  -----------------------------------------------------
**  Zima       8/24/95    Created
**  Zima       7/15/96    Deployed new kretan NPCs
**
*/
inherit "/std/room";
#include <stdproperties.h>
#include <macros.h>
#include "defs.h"
#define NUM 4
object npc=allocate(NUM);
 
void make_npc(int i) {
    string path;
    if (npc[i]) return;
    switch(i) {
       case 0:  path=KRCAMP_DIR+"monsters/dcomder/dcomder1";         break;
       case 1:  path=KRCAMP_DIR+"monsters/ensign/ensign0";           break;
       default: path=KRCAMP_DIR+"monsters/soldier/soldier1";         break;
    }
    npc[i]=clone_object(path);
    npc[i]->equip_me();
    npc[i]->move(THIS);
    tell_room(THIS, QCNAME(npc[i])+" comes out of hiding.\n");
}
 
void reset_room() {
   int i;
   for (i=0; i<NUM; i++) make_npc(i);
}
 
create_room() {
   set_short("An empty shop");
   set_long(
      "Cobwebs hang in the corners of this empty shop, dust covering "+
      "the walls and floor. It seems this place has been unoccupied "+
      "for a while, except for some footprints in the dust. The "+
      "boards which once barred the entrance to the east have been "+
      "torn away, allowing you to exit there.\n");
 
   add_prop(ROOM_I_INSIDE,1);
 
   add_item(({"shop","room"}),"It an empty shop which needs cleaning.\n");
   add_item("cobwebs",
      "Lines of dust which form spider-like webs hang in the long "+
      "undisturbed corners of the room.\n");
   add_item("dust",
      "It covers the walls and floor.\n");
   add_item(({"footprints","floor"}),
      "There are some recently made footprints in the dust of the floor.\n");
   add_item("boards",
      "Now torn down, they were nailed over the entrance to board off "+
      "this place.\n");
   add_item("entrance",
      "It is to the east, no longer barred by the boards which have "+
      "been torn away from it.\n");
 
   add_exit(ROOM_DIR+"troad9","east");
   reset_room();
}
