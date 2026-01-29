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
    set_short("Main hall in the brewery");
    set_long("Entering the huge main hall of the brewery is quite a sight. Metal "+
             "in different colors is twisted all over in a mishmash of pipelines flowing with "+
             "beer and dwarfspirits to different machines and to storage. A delicate stone "+
             "portal leads to an office southwards. From the north the sounds and smells of "+
             "brewing flows towards you from some sort of machinery room. Further east you "+
             "can see a stockpile of kegs stashed away. Pipes are lead through in the roof "+
             "to the storage room, ending in taps that fills kegs of the wonderful liquids "+
             "brewed here.\n");

    add_exit(IRON + "brew3","west",0);
    add_exit(IRON + "brew5","east",0);
    add_exit(IRON + "brew6","south","@@no_go");
    add_exit(IRON + "brew1","north",0);

    reset_dwarf_room();
}


int
no_go()
{
    write("You hear a loud explosion from the south! You better not go that way.\n");
    return 1;
}