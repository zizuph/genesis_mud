inherit "/d/Gondor/common/room";
#include "/sys/stdproperties.h"
#include "/d/Gondor/defs.h"
#include "/d/Gondor/pelargir/citdefs.h"

void
create_room()
{
    set_short("in the garden district of Pelargir");
    set_long(BSN("This is the garden district of Pelargir, mostly "+
       "populated by the wealthy. To the north lies one of the larger "+
       "houses, owned by one of the oldest families in Pelargir. To the "+
       "west a short road can take you to one of the city barracks, "+
       "and to the south more fine houses and a few shops await you "+
       "along the cobblestone street. East will lead you to the main "+
       "street of the city."));
    COBBLE;
    GADMIRAL;
    add_exit(PELAR_DIR + "homes/mangarden","north",0);
    add_exit(PELAR_DIR + "street/groad3","east",0);
    add_exit(PELAR_DIR + "street/xroad4","south", "@@block_road@@");
    add_exit(PELAR_DIR + "street/xroad4","west",  "@@block_road@@");
}

int
block_road()
{
    write("You cannot go there yet!\n");
    return 1;
}

