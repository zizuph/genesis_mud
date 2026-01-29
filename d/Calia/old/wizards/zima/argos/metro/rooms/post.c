/*
**   ARGOS - Metro - Post Office
**
**   History:
**   Date       Coder      Action
**   --------   ---------- ---------------------------------
**   8/12/95    Zima       Created
**
*/
inherit "/std/room";
#include <stdproperties.h>
#include "defs.h"
 
void create_room() {
   set_short("Royal Post Office of Argos");
   set_long(
      "This is the office of the Royal Postal Service of Argos, its "+
      "function recently expanded to include service to areas outside "+
      "of the valley. A long marble bar extends from the west to the "+
      "east end of the room, behind which a clerk waits to assist you. "+
      "A relief is sculpted into the northern wall, while entrances lead "+
      "out to the streets to the west and south.\n");
 
   add_item("bar",
      "Somewhat like a bar in a pub, though made of highly crafted "+
      "marble and used for the exchange of mail instead of drinks.\n");
   add_item("clerk",
      "Standing safely behind the bar, she actually looks like she's "+
      "asleep!\n");
   add_item("relief",
      "Sculpted on the northern wall behind the bar, the relief is of "+
      "a sheild emblazoned with a winged horse, surmounted by a "+
      "crown with three jewels, the arms of Argos.\n");
   add_item(({"entrance","entrances"}),
      "The west entrance leads onto Tritos road, while the south "+
      "leads onto Chipas.\n");
 
   /* room properties */
   add_prop(ROOM_I_INSIDE,1);
 
   add_exit(ROOM_DIR+"trroad10","west",0);
   add_exit(ROOM_DIR+"croad14", "south",0);
}
 
 
enter_inv(ob, from) {
   ::enter_inv(ob, from);
   if (from == this_object()) return;
   if (present("mailreader", ob)) return;
   clone_object("/secure/mail_reader")->move(ob);
}
 
leave_inv(ob, to) {
   object reader;
 
   ::leave_inv(ob, to);
   if (to == this_object()) return;
   reader = present("mailreader", ob);
   if (reader) reader->remove_object();
}
