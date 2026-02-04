inherit "/std/room";

#include <stdproperties.h>
#include <macros.h>
#include "/d/Terel/common/terel_defs.h"     
#include "tomb.h"

create_room()
{
    set_short("creek");
    set_long(
       "The creek forks away from the brook and gets considerably narrower " +
       "here.  It trickles down to nothing and dries up leaving a muddy " +
       "trail that leads up a hill to the west.\n"
    );

    add_prop(ROOM_I_INSIDE, 0);

    add_exit(TOMBDIR + "creek_incline", "west", 0);
    add_exit(TOMBDIR + "stream02", "southeast", 0);    
}


