inherit "/d/Gondor/rohan/horn/helmsdeep.c";

#include "/d/Gondor/defs.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include "/d/Gondor/rohan/horn/hd_defs.h"

public int	block();

void create_helmsdeep_room()
{
    set_short_desc("A field behind Helm's wall");
    set_extra_long("A field inside the wall. The cliffs on either side "+
    "of the gorge rise like mighty towers. To the south a path leads "+
    "further up the gorge, and another path goes east to the Deeping-wall. "+
    "Broad stairs are to the north. ");

    GORGE;
    H_WALL;
    PATH;
    MOUNTAINS;
    add_item("cliffs",BS("The crow-haunted cliffs are steep and high, "+
    "impossible to climb.\n"));
    add_item("stairs","The stairs lead up to the rear-gate of the keep.\n");
    add_item(({"crows","crow"}),BS("The crows are so far up the "+
    "cliffs that they only look like black specks.\n"));

    add_exit(ROH_DIR+"horn/gorge/stairs","north",0,2);
    add_exit(ROH_DIR+"horn/gorge/ins_wall1","east",0);
    add_exit(ROH_DIR+"horn/gorge/to_caves","south",block);
}

int
block()
{
    write(BSN("The path to the caves is closed by orders from "+
    "Erkenbrand, master of Westfold."));
    return 1;
}

