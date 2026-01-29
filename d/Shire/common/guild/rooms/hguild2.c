inherit "/std/room";

#include "defs.h"
#include "/sys/macros.h"
#include "/sys/stdproperties.h"

object board;

create_room() {
   if (!present("board")) { /* Clone our own board if necessary */
      board = clone_object(HIN_DIR + "bull2");
      board->move(this_object());
   }
   set_short("Shire domain room");
   set_long("This ancient room is a meeting place for the "+
                  "wizards of the Shire.  Here many weighty decisions "+
                  "are made, and many frivolous jokes told.  A plaque on the "+
                  "wall attracts your interest.  South is the entrance "+
                  "to Tech's tower and to the west is the Middle Earth "+
                  "discussion room, where you can learn more about "+
                  "Tolkien's world. East is the domain's meeting room.\n");

   add_exit(HINROOM_DIR + "partydisp","west",0);
   add_exit("/d/Gondor/ME_ideas", "southeast", 0);
   add_exit(COMMON_DIR + "domain_entr","south",0);
   add_exit("/d/Shire/workroom","east",0,1);

   add_prop(ROOM_I_INSIDE,1);
}
