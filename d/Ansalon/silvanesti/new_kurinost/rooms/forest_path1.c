#pragma strict_types

// I N C L U D E D   F I L E S
#include "/d/Krynn/common/defs.h"
#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include "local.h"

inherit FORESTBASE;

void
reset_kurinost_room()
{
    return;
}

public void
create_kurinost_room()
{
    set_short("@@short_desc");
    set_long("@@long_desc");

    add_item(({"path", "dirt path", "freshly carved path",
        "carved path"}),
        "A dirt path leads from the encampment to your northwest to " +
        "the edge of the forest kingdom of the Silvanesti elves.\n");
    add_item(({"forest", "forest kingdom", "silvanesti", "kingdom",
        "fabled forest", "elven kingdom"}),
        "Like a vast green blanket, the immense forest of Silvanesti " +
        "is visible in all directions, except north. From the western " +
        "horizon, as far south as your eyes can see, to the far eastern " +
        "horizon.\n");
    add_item(({"aspen trees", "trees", "beautiful trees", "tree", "aspens",
        "aspen", "feet of the aspen trees"}),
        "Before you rise the beautiful aspen trees that make up the " +
        "border of the elven kingdom of Silvanesti. These trees have " +
        "been fashioned and coaxed through centuries into groves of " +
        "wonder and enchantment by the elves that live here.\n");
    add_item(({"encampment", "fortified encampment", "camp"}),
        "Nestled close beneath the coastal cliffs, hidden in eternal " +
        "shadow, a camp stretches out before you. You estimate that " +
        "the entire camp is about fourty meters across. Reaching " +
        "high above the shade of the camp a slender white tower " +
        "stands tall enough to catch pale light from the sun or " +
        "two moons.\n");

    add_exit(RSROOMS + "dcamp4x6", "northwest", "@@ascend_path");
    add_exit(RSROOMS + "forest_path2", "east");

    KURINOSTMAP;

    reset_kurinost_room();
}

string
short_desc()
{
    return forest_path_short_desc();
}

string
long_desc()
{
    return long_close_desc() + "A freshly carved path leads " +
        "east towards the forest here, and up a slope to your " +
        "northwest towards a fortified encampment.\n";
}

int
ascend_path()
{
    write("You walk up the slope towards the fortified encampment.\n");
    return 0;
}


