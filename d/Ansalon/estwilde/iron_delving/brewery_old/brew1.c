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
    set_short("Machinery room");
    set_long("Bubbling sounds, strange smells and small fires makes this room a marvel for "+
             "any drinker alive. Big tanks leads fluids to here and there, strange machines "+
             "and distillers sends out puffs of strange smells. The heat here is comfortable, "+
             "but the moist makes it a bit sticky. Pipelines in the roof leads the finished "+
             "liquids out southwards to the main hall. Without an onerous examination, one "+
             "can clearly see that not only excellent dwarven craftmanship is involved in "+
             "the makings of theese machines, but gnomish inventions seems to have been put "+
             "in use here. Somehow, they actually work.\n");

    add_exit(IRON + "brew4","south",0);

    reset_dwarf_room();
}

