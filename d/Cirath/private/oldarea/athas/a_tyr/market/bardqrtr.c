/* bardqrtr: The Bard's Quarter of Tyr, Serpine 12/24/96. */
 
#pragma strict_types
 
inherit "/std/room";
#include "defs.h"
#include "/d/Cirath/std/block.h"
 
void
create_room()
{
    ::create_room();
    set_short("the Bard's Quarter");
    set_long("Shaded my numerous tarps and canopies, the Bard's Quarter "
            +"of Tyr is not a mechant's quarter exactly, as it "
        +"specializes more in services than goods. And in spite of "
            +"the more entertaining abilities of the typical bard, these "
            +"services tend to be more on the less savory side. Most who "
            +"pass this way hide their faces with a dark hood, but few "
            +"bother guarding their purse: It is life, not money that is "
            +"at risk in this place. To the north is an odd building with "
            +"a carving of large finger on the front door, while heading "
            +"roughly south will take one into the Shadow Square.\n");
 
    add_item(({"tarps","tarp","canopy","canopies"}),
             "Mostly made of hide and leather.\n");
    add_item(({"building","odd building","carving","finger"}),
             "A very odd building, but several dark figures are "
            +"coming and going through its door.\n");
 
    OUTSIDE
 
    add_exit(TZ_MARKET+"housfngr.c", "north", "@@block_exit@@", 1);
    add_exit(TZ_MARKET+"shdwsqre.c", "south", 0, 1);
    add_exit(TZ_MARKET+"shdwsqrw.c", "southwest", 0, 1);
    add_exit(TZ_MARKET+"shdwsqrn.c", "west", 0, 1);
 
    reset_room();   
}
