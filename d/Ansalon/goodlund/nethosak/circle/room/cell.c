#include "/d/Ansalon/goodlund/nethosak/circle/local.h"
#include "/d/Ansalon/common/defs.h"
#include <stdproperties.h>
#include <macros.h>

inherit GUILD_IN;

void
create_guild_room()
{    

    //THE BRIEF DESCRIPTION OF THE ROOM
    set_short("The Cell.");

    //STANDARD DATE AND TIME DESCR + FULL DESCR.
    set_long("This is an extremely small room, which is also spherical, due to the "+
       "roots that cover the walls, ceiling and floor. There are no features "+
       "in this room, but the intricate pattern of dark roots. The walls "+
       "seem to absorb also every sound in the room."+
       "You are sure to notice the location of the narrow passage, to make "+
       "sure that you can crawl back.\n");

    //AN ITEM THAT THE PLAYER CAN EXAMINE AND SEARCH.
    add_item(({"passage", "hole"}),
       "You can see the small passage you crawled through to get here. "+
       "You can crawl back, if you want.\n");

    //THE EXITS OUT OF THE ROOM.
    add_exit(GROOM + "the_nest","south",0);
}