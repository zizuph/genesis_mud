inherit "/d/Gondor/rohan/horn/helmsdeep.c";

#include "/d/Gondor/defs.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include "/d/Gondor/rohan/horn/hd_defs.h"

void create_helmsdeep_room()
{

    set_short_desc("The inner courtyard of the Hornburg");
    set_extra_long( "The southeast corner of the inner courtyard. "+
    	"A stairway leads up to the top of the inner wall, and "+
	"the courtyard extends west and northwest, winding "+
	"round the tower to the north. ");

    set_inside_keep(1);
    GUARDS;
    WALL;
    TOWER;
    WINDOWS;
    COURTYARD;
    COBBLESTONES;
    STAIRS;
    GORGE;
    CLIFFS;
    MOUNTAINS;
    INNER_WALL;

    add_exit(ROH_DIR+"horn/burg/inner_court1","west",0);
    add_exit(ROH_DIR+"horn/burg/inner_court3","northwest",0);
    add_exit(ROH_DIR+"horn/on_walls/i_wall3","up",0,2);
}

