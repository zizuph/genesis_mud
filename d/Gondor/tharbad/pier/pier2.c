inherit "/d/Gondor/common/room";
#include <stdproperties.h>
#include <macros.h>

#include "/d/Gondor/defs.h"

void
create_room()
{
   set_short("A ruined pier in Tharbad, in the south of Eriador");
   set_long(BSN("You stand on an old decrepit pier beside the Greyflood River. "+
         "Now and then, ships from far away dock here, but since Tharbad is "+
         "deserted, you could wait for days and still not see a ship. "+
         "Northeast are the fords, and to the southwest, the riverbank stretches into "+
         "the distance."));
   add_exit(THARBAD_DIR + "pier/pier1","northeast",0,2);
   add_exit(THARBAD_DIR + "pier/pier3","southwest",0,2);
   add_item(({"pier","piers","river","riverbank"}), BSN(
         "This barely functional pier meets the river Greyflood near the city "+
         "of Tharbad.  The river flows southwest towards the sea."));
}

