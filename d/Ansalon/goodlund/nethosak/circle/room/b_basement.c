#include "/d/Ansalon/goodlund/nethosak/circle/local.h"
#include "/d/Ansalon/common/defs.h"
#include <stdproperties.h>
#include <macros.h>

inherit GUILD_IN;

void
create_guild_room()
{    

    //THE BRIEF DESCRIPTION OF THE ROOM
    set_short("Basement of the Bronze Tower");

    //STANDARD DATE AND TIME DESCR + FULL DESCR.
    set_long("This room is circular and about 10 meters across and covered in solid "+
       "bronze. At the far west end of the room is a small set of stairs "+
       "leading up. East is a small wooden door. You can hear a low constant "+
       "humming sound coming from an unknown direction. The air is heavy and "+
       "dry, making you gasp slightly.\n");

    //AN ITEM THAT THE PLAYER CAN EXAMINE AND SEARCH.
    add_item(({"room", "walls", "tower"}),
       "There are polished bronze all about you. It is slightly warm to the "+
       "touch. No markings or ornamentation can be seen anywhere on the "+
       "bronze.\n");

    //AN ITEM THAT THE PLAYER CAN EXAMINE AND SEARCH.
    add_item(({"door"}),
       "It is a small wooden door, set in the east side of the wall. "+
       "It has no keyhole or handles. You can see a small puddle of murky "+
       "water at the bottom of the door.\n");

//AN ITEM THAT THE PLAYER CAN EXAMINE AND SEARCH.
    add_item(({"stairs"}),
       "A small set of stairs leading up, made from solid bronze like "+
       "everything else in this room.\n");

//THE EXITS OUT OF THE ROOM.
    add_exit(GROOM + "the_nest","east",0);
    add_exit(GROOM + "b_level1","up",0);
}