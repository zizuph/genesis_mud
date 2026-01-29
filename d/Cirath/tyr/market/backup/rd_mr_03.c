/* rd_mr_03: east end of Market Road, Serpine 12/24/96. */
 
#pragma strict_types
 
inherit "/std/room";
#include "defs.h"
#include "/d/Cirath/std/block.h"
 
void
create_room()
{
    ::create_room();
    set_short("east end of Market Road");
    set_long("The east end of Market Road abruptly emerges here from "
            +"the chaos that is Shadow Square before surrendering to "
            +"Stadium Way to the east. The echo of traders advertising "
            +"their wares and customers trying to wrangle a better deal "
            +"is somewhat distracting, but the smells and color seem to "
            +"pull you closer. Tucked away just to the north is a shop "
            +"with a symbol of a spool and thread on its low arched "
            +"door.\n");
 
    add_item(({"symbol","spool","thread"}),
             "A common symbol of tailors and weavers.\n");
    add_item(({"door","low arched door"}), "It is not all that much "
            +"higher then the head of a tall dwarf.\n");
    add_item(({"square","shadow square","traders","trader","customer","customers"}),
             "You can't make them out clearly from here.\n");
 
    OUTSIDE
    ADD_SUN_ITEM
    ADD_ZIG_ITEM
 
    add_exit(TYR_MARKET+"tailor.c","north","@@block_exit@@",1);
    add_exit(TYR_MARKET+"rd_sw_01.c","east",0,1);
    add_exit(TYR_MARKET+"shdwsqre.c","west",0,1);
}
