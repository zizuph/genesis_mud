#include "default.h"

inherit CASTLE_ROOM;

void
create_room()
{
   set_short("Passage");
   set_long("This part of the passageway is empty and "+
         "void of anything decorative. The walls are all made of huge blocks "+
	"of stone.\n");

   add_item(({"blocks","block","stone","walls","marble"}),"The stone "+
      "appears to be low grade marble.\n");

   add_exit(CASTLE_DIR + "3k9","northeast");
}
