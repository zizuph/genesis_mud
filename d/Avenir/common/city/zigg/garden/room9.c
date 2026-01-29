// Ziggurat galleria (room9.c)
// creator(s):   Zielia 2006
// last update:
// purpose:
// note:
// bug(s):
// to-do:
#pragma strict_types

#include <composite.h>
#include "zigg.h"

inherit ZIG_GARDEN;

public void
zig_room(void)
{
    set_long("@@my_long");

    add_exit("room8", "north", "@@exit_string");
    add_exit("room10", "south", "@@exit_string");
}

public string
my_long(void)
{
    return "White and silver plants catch the glow from the Source "+
    "and lend a mellow, peaceful mood to this section of the terrace garden. "+
    "The air is heavy with sweet aromas of heliotrope, tuberoses and verbanas. "+
    "Fragrant moonflower vines climb up the Zigurrat's wall creating a backdrop "+
    "of large white blooms for a black stone bench. The many blooms appear to "+
    "float in the diffuse light, the dark green stems and heart-shaped leaves "+
    "fading into the dark stone. Over the narrow aqueduct that serves to "+
    "barricade the terrace edge sprawls a dream-like view of the Forbidden "+
    "City. Flower beds hold white irises, lilies, and zinnias. Silvery "+
    "olive trees grow in planters near a winding white flagstone path leading "+
    "to the "+ COMPOSITE_WORDS(query_obvious_exits()) +".\n";

}

public string query_trees(void) {   return "olive tree";    }

static void
garden_items(void)
{
    ::garden_items();

    add_views("From this side of the "+
      "Ziggurat you can see some of the High Lord Executioner's enclave "+
      "to the northeast, opulent noble houses circle the High Lord's "+
      "palace on the central hill.", "enclave, giving it");

    add_rock("painted a blue teardrop", ", the symbol of Zizuph");

    add_item(({"tree","silvery tree","olive tree","silvery olive tree",}),
      "The small, straggly trees grow in planters near the path. They have "+
      "thorny branches with oblong pointed leaves that are dark greyish-green "+
      "on top and pale with whitish scales below. They are adorned with "+
      "tiny yellow flowers and have an almost sickly sweet scent.\n");

    add_item(({"olive","olives","fruit","fruits",}), "The olive trees "+
      "seem devoid of fruit, bearing only tiny yellow flowers. Perhaps "+
      "they are only ornamental.\n");

    add_cmd_item(({"olive","olives",}), ({"pluck", "pick"}),
      "The olive trees seem devoid of fruit. Perhaps they are only "+
      "ornamental.\n");

    add_object(ZIG_RLG + "bench_r9", 1, 0 );
}

static void
garden_flowers(void)
{
    add_flower("heliotrope", "white");
    add_flower("tuberose", "white");
    add_flower("verbana", "white");
    add_flower("moonflower", "white");
    add_flower("iris", "white");
    add_flower("lily", "white");
    add_flower("zinnia", "white");

    ::garden_flowers();
}

