
inherit "/d/Rhovanion/lib/room";

#include <stdproperties.h>
#include "/d/Rhovanion/defs.h"

create_room()
{
    set_short("Seaside");
    set_long("The sandy beach extends here from north to south. "+
	"Northward, it approaches the place where the River Carnen "+
	"empties into the Sea of Rhun. Off to the north and west "+
	"stands a large "+
	"town. There is no direct way to reach it from "+
	"here though, as a steep slope up from the beach and "+
	"thick brambles prevent you from moving westward.\n");
	
    add_exit(RHUN_DIR+"hills/s2", "north");
    add_exit(RHUN_DIR+"hills/s4", "south");
    
    add_item(({"beach","sand"}), 
        "The sandy beach leads away from here "+
	"to the north and south.\n");
    add_item("brambles", "Thick brambles stop you from heading "+
	"off the beach to the west.\n");
    add_item("slope", "A steep slope topped with brambles stands "+
	"to the west, effectively preventing you from moving "+
	"in that direction.\n");
    
}
