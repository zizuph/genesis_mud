/* shdwsqrn: north section of Shadow Square, Serpine 12/24/96. */
 
#pragma strict_types
 
inherit "/std/room";
#include "defs.h"
inherit "/d/Cirath/std/Cirath_magic_room_std";
#include "/d/Cirath/common/mobber.h"


void
reset_room()
{
    bring_room_mob("traders", TYR_NPC+"mrkt_mob.c", 1);
}
 
void
create_room()
{
    ::create_room();
    set_short("north section of Shadow Square");
    set_long("It is impossible to enter the north section of Shadow "
            +"Square and not be consumed with hunger. Grains, drinks, "
            +"and even imported fruits fill boxes and sacks, or are "
            +"stacked on the wooden planks that serve as stalls. "
            +"Compared to this wonder there seems little reason to "
            +"head out of the Square to the west, to the Bard's Quarter "
            +"off east, or deeper into the Square to the south and "
            +"southeast.\n");
 
    add_item(({"grains","drinks","fruits","fruit","drink","grain"}),
             "A closer look reveals that the food is actually in "
            +"pretty poor shape, thanks to its advanced age. But the "
            +"coatings sure make it all look shiny!\n");
    add_item(({"stall","stalls","wooden plank","wooden planks","plank"}),
             "Small, easy to set up, and easier to break down: These "
            +"are the ideal booths for a merchant of Shadow Square.\n");
    add_item(({"quarter","bard's quarter","northern paths","northern path"}),
             "The bards of Athas are renowned as much for their "
             +"skill at assassination and poison as their entertaining.\n");
 
    OUTSIDE
    ADD_SUN_ITEM
    ADD_ZIG_ITEM
 
    add_exit(TYR_MARKET+"bardqrtr.c", "east", 0, 1);
    add_exit(TYR_MARKET+"shdwsqre.c", "southeast", 0, 1);
    add_exit(TYR_MARKET+"shdwsqrw.c", "south", 0, 1);
    add_exit(TYR_MARKET+"rd_mr_05.c", "west", 0, 1);
 
    reset_room();   
}
