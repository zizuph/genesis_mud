inherit "/d/Gondor/common/room";
#include "/sys/stdproperties.h"
#include "/d/Gondor/defs.h"
#include "/d/Gondor/pelargir/citdefs.h"

void
create_room()
{
    set_short("in the garden district of Pelargir");
    set_long(BSN("This is a small stretch of city road on "+
       "the western edge of the garden district. Just to the west "+
       "of here, nestled against the city wall, is one of the city "+
       "barracks. To the east the street continues back into the "+
       "garden district where fine houses line the streets."));
    add_item("barracks",BSN("The barracks is a rather small "+
       "building jostled up next to the city wall."));
    add_item(({"house","houses"}),BSN("Though you aren't in "+
       "a position to get a close look at them, the houses "+
       "all seem to be of high quality and intricate design."));
    COBBLE;
    GADMIRAL;
    add_exit(PELAR_DIR + "street/xroad2","east",0);
    add_exit(PELAR_DIR + "street/xroad4","west", "@@block_road@@");
}

int
block_road()
{
    write("You cannot go there yet!\n");
    return 1;
}

