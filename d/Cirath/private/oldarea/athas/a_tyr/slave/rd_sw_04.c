/* rd_sw_04: South end of Northern Stadium Way, Serpine-2/12/96. */
 
#pragma strict_types
 
inherit "/std/room";
#include "defs.h"
#include "/d/Cirath/std/block.h"
 
void
create_room()
{
    ::create_room();
    set_short("south end of northern Stadium Way");
    set_long("Though most who enter through the northern Champions "
        +"Gate turn down Templar Road rather than here, a small "
            +"trickle of souls still make their way south to the arena "
            +"along this route. An even smaller number head west, into "
            +"the brickyards of the city, and most of those are "
            +"slaves. A mighty wall looms to east, over which peers "
            +"the Golden Tower of Kalak.\n");
 
    add_item(({"gate","champions gate", "caravans"}), "You can make "
            +"out tremendous activity as caravans enter from other "
            +"parts of Athas and fan out west into the city proper.\n");
    add_item(({"trickle", "souls", "soul"}), "Between arena tourists, "
            +"spectators, and those wishing (or forced) to try their "
            +"luck within, it's a rather motley array.\n");
    add_item(({"slave", "slaves", "number", "smaller number"}),
             "They have miserable expressions on their faces, as if "
            +"they are moving towards their doom.\n");
    add_item(({"brickyard", "brickyards"}), "Under a cloud of stone "
            +"dust and a miasma of baking mud, countless slaves labor "
            +"to create the building blocks of Tyr.\n");
    add_item("arena", "Second only to the Ziggurat in size, the "
            +"huge stony structure looms over you like a predator.\n");
    add_item(({"tower", "golden tower", "golden tower of kalak"}),
             "Made of rare golden granite from Walis, the top of "
            +"Kalak's home can just be seen over the wall's edge.\n"
            +"You have the uneasy sensation of being watched.\n");
    add_item(({"wall", "mighty wall"}), "The mighty structure of stone "
        +"separates the 'Golden City' where the Templars and Kalak "
            +"dwell, from the main areas of Tyr.\n");
 
    OUTSIDE
    ADD_SUN_ITEM
    ADD_ZIG_ITEM
 
    add_exit(TZ_SLAVE+"rd_sw_05.c", "north", 0, 1); 
    add_exit(STADIUM+"n_stadium.c", "south", "@@block_exit@@", 1);
    add_exit(TZ_SLAVE+"zgbuild2.c", "west", 0, 1);
}
