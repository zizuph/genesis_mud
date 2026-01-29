#pragma strict_types

// I N C L U D E D   F I L E S
#include "/d/Krynn/common/defs.h"
#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include "local.h"

inherit FORESTBASE;

object hob1, hob2, hob3, hob4, raz;

void
reset_kurinost_room()
{
    if(!objectp(hob1))
    {
        hob1 = clone_object(RSLIVING + "hobgoblin2");
        hob1->arm_me();
        hob1->set_stats(({120, 100, 120, 100, 100, 180}));
        hob1->heal_hp(10000);
        hob1->move(TO, 1);
    }
    if(!objectp(hob2))
    {
        hob2 = clone_object(RSLIVING + "hobgoblin2");
        hob2->arm_me();
        hob2->set_stats(({120, 100, 120, 100, 100, 180}));
        hob2->heal_hp(10000);
        hob2->move(TO, 1);
    }
    if(!objectp(hob3))
    {
        hob3 = clone_object(RSLIVING + "hobgoblin2");
        hob3->arm_me();
        hob3->set_stats(({120, 100, 120, 100, 100, 180}));
        hob3->heal_hp(10000);
        hob3->move(TO, 1);
    }
    if(!objectp(hob4))
    {
        hob4 = clone_object(RSLIVING + "hobgoblin2");
        hob4->arm_me();
        hob4->set_stats(({120, 100, 120, 100, 100, 180}));
        hob4->heal_hp(10000);
        hob4->move(TO, 1);
    }
    if(!objectp(raz))
    {
        raz = clone_object(RSLIVING + "razogh");
        raz->set_stats(({180, 160, 190, 100, 100, 180}));
        raz->heal_hp(10000);
        raz->move(TO, 1);
    }
}

public void
create_kurinost_room()
{
    set_short("@@short_desc");
    set_long("@@long_desc");

    add_item(({"path", "dirt path", "freshly carved path",
        "carved path"}),
        "A dirt path ends here before the " +
        "the edge of the forest kingdom of the Silvanesti elves.\n");
    add_item(({"forest", "forest kingdom", "silvanesti", "kingdom",
        "fabled forest", "elven kingdom"}),
        "Like a vast green blanket, the immense forest of Silvanesti " +
        "is visible in all directions, except north. From the western " +
        "horizon, as far south as your eyes can see, to the far eastern " +
        "horizon.\n");
    add_item(({"aspen trees", "trees", "beautiful trees", "tree", "aspens",
        "aspen", "feet of the aspen trees", "groves", "grove"}),
        "Before you rise the beautiful aspen trees that make up the " +
        "border of the elven kingdom of Silvanesti. These trees have " +
        "been fashioned and coaxed through centuries into groves of " +
        "wonder and enchantment by the elves that live here.\n");
    add_item(({"hedge","great hedge"}),
        "Surrounding the edge of the Silvanesti forest is a high, thickly " +
        "tangled growth of thorny hedges and vines. Futile " +
        "attempts have been made to cut it down and burn it away, however " +
        "it appears to grow back at a phenomenal rate, making it an " +
        "impassable barrier.\n");

    add_exit(RSROOMS + "forest_path2", "northwest", "@@ascend_path");

    KURINOSTMAP;

    reset_kurinost_room();
}

string
short_desc()
{
    return "at the edge of the forest of Silvanesti before a great hedge";
}

string
long_desc()
{
    return long_close_desc() + "The path ends here before a great " +
        "hedge, a massive wall of thickly tangled thorny vines and " +
        "plants.\n";
}

int
ascend_path()
{
    write("You walk up the slope.\n");
    return 0;
}


