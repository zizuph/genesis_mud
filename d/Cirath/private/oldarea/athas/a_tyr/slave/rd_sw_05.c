/* rd_sw_05: north end of Northern Stadium Way, Serpine-2/13/96. */
 
#pragma strict_types
 
inherit "/std/room";
#include "defs.h"
#include "/d/Cirath/std/block.h"
 
void
create_room()
{
    ::create_room();
    set_short("north end of northern Stadium Way");
    set_long("A constant flow of travelers move between nearby "
            +"Champions gate and Templar Road, which heads west "
            +"towards the Iron Square of Tyr. Only a few head directly "
            +"south towards the arena, and virtually none go east "
            +"towards one of the gates into 'The Golden City' of "
            +"Tyr's government.\n");
    add_item(({"traveler", "travelers"}), "Humans, thri-kreen, mul, "
            +"elf, or otherwise: They come from all over Athas to "
            +"visit the mighty city of Tyr.\n");
    add_item(({"gate", "champions gate"}), "The unadorned gate is the "
            +"primary route for caravans from the rest of Athas.\n");
    add_item("arena", "From here you can see that it is squarish and "
            +"almost as huge as the Ziggurat.\n");
 
    OUTSIDE
    ADD_SUN_ITEM
    ADD_ZIG_ITEM
 
    add_exit(TZ_SLAVE+"rd_sw_06.c", "north", "@@block_exit@@", 1); 
    add_exit(TZ_GATES+"gate_tn.c", "east", "@@block_exit@@", 1);
    add_exit(TZ_SLAVE+"rd_sw_04.c", "south", 0, 1);
    add_exit(TZ_SLAVE+"rd_tr_04.c", "west", 0, 1);
}
