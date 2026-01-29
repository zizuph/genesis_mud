#include "/d/Ansalon/goodlund/nethosak/circle/local.h"
#include "/d/Ansalon/common/defs.h"
#include <stdproperties.h>
#include <macros.h>

inherit GUILD_IN;

void
create_guild_room()
{    

    //THE BRIEF DESCRIPTION OF THE ROOM
    set_short("The Weapon House.");

    //STANDARD DATE AND TIME DESCR + FULL DESCR.
    set_long("You feel very much at peace when you enter this room."+
       "Before you are two rows of seats at either side, and in the middle of "+
       "the room is a long isle leading further north into the temple. A "+
       "strong scent of dried flowers hang in the air. The floor is covered "+
       "by moss and low grass making in soft to the touch. "+
       "At the far end of the temple, you can make out a large obelisk shape."+
       "A feeling of calm decends upon you as you enter the room. The room "+
       "is...\n");

    //THE EXITS OUT OF THE ROOM.
    add_exit(GROOM + "weapon_house","east",0);
    add_exit(GROOM + "temple_obelisk","north",0);
}