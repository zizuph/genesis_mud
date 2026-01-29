/* rd_cw_05: Caravan Way section 5. */

inherit "/std/room";
#include "defs.h"
#include "/d/Cirath/std/block.h"

void
create_room()
{
    set_short("eastern caravan way");
    set_long ("It is all one can do to remain still as large throngs "+
              "of people head back and forth along Caravan Way. Many "+
              "head west towards Tyr's trade district, while others go "+
              "east towards the Iron Square. Only the rarest few head "+
              "south or north, into the slums and the Minthor House "+
              "repectively.\n");
    add_item(({"throng", "throngs", "people"}), "They come from every "+
              "race, profession, and creed in Athas: From slave to "+
              "noble, halfling to half-giant, and all between.\n");
    add_item(({"house", "minthor house"}), "A huge stately mansion, it "+
              "is headquarters to the richest family in Tyr.\n");
    OUTSIDE
    ADD_SUN_ITEM;
    ADD_ZIG_ITEM;

    add_exit(TZ_MINTHOR+"minthor1.c", "north", "@@block_exit@@", 1);
    add_exit(TZ_CARAVAN+"rd_cw_07.c", "east", 0, 1);
    add_exit(TZ_WARREN+"rd_cw_06.c", "south", 0, 1);
    add_exit(TZ_CARAVAN+"rd_cw_04.c", "west", 0, 1);
}
