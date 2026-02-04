//removed link-room cloning - Lilith Jul 2008
inherit "/std/room";

#include <stdproperties.h>
#include <macros.h>
#include "/d/Terel/common/terel_defs.h"     
#include "tomb.h"

create_room()
{
    set_short("dark ravine");
    set_long("A vicious wind blows through the ravine, robbing "+
        "you of your breath and kicking up fine snow crystals "+
        "that blind your eyes with tears.\n");

    add_item("ground", 
	"The ground is hard with frost.\n");
    add_item(({"ravine", "gash"}),
        "Your eyes cannot penetrate the darkness which leads north "+
        "into the mountain.\n");
    
    add_prop(ROOM_I_INSIDE, 0);
    add_prop(ROOM_I_LIGHT, -1);

    add_exit(TOMBDIR + "forest04", "south");
    add_exit(TOMBDIR + "forest05", "north");

}


