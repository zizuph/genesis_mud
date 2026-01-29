#include "/d/Ansalon/common/defs.h"
#include "../local.h"
#include <macros.h>
#include <stdproperties.h>
#include <ss_types.h>

inherit DWARF_OUT;

void
reset_dwarf_room()
{
    return;
}

create_dwarf_room()
{
    set_short("Entrance to the brewery");
    set_long("The entrance of the Brewery is neat and clean except for a few barrels that "+
             "has been placed here as a welcoming for the guests. The woven carpet on the "+
             "floor seems tidy with less spots and marks than one could expect in a brewery. "+
             "No furniture, save for a bar, can be seen here. A sweet smell of tobacco "+
             "reaches your nose from the trapdoor to the west. Strange bangs and noise "+
             "disturbs the silence here, coming from the main hall to the east. \n");

    add_exit(IRON + "tavern","west",0);
    add_exit(IRON + "brew4","east",0);

    reset_dwarf_room();
}

