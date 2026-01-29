#include "default.h"

inherit CASTLE_ROOM;

void
create_room()
{
   set_short("Passage");
   set_long("This is an old guard room, with chairs and "+
         "tables all rotted away into black heaps on the floor. There is "+
         "an exit leading east where an old door used to be, the wood "+
         "having rotted off the hinges.\n");

   add_item(({"chairs","tables","heaps","chair","table"}),"The chairs "+
      "and tables are all rotted away now.\n");
   add_item("hinges","The hinges are red with rust now.\n");

   add_exit(CASTLE_DIR + "3k2","north",);
   add_exit(CASTLE_DIR + "shop","east",);
   add_exit(CASTLE_DIR + "3k7","southwest",);
}
