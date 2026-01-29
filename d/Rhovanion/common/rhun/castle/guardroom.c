
inherit "/d/Rhovanion/lib/room";

#include <stdproperties.h>
#include "/d/Rhovanion/farlong.h"

reset_room()
{
    if(!(present("_SW_guild_guard_")))
    {
	clone_object(SWG+"guild_guard")->move(TO);
    }
}

create_room()
{
    set_short("Cavernous basement");
    set_long("The cavernous basement extends here, rough-hewn walls "+
	"apparently formed by nature or by magic.  The area is lit "+
	"by some unseen force.  You feel eerie, and a bit cold.  "+
	"In every shadowed corner, you seem to sense a presence, "+
	"waiting and watching.\n");
	
    AE(RHUN+"castle/runeroom","north");
    AE(RHUN+"castle/basement","south");

    IN;
    
    reset_room();
}

