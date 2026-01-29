#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/silvanesti/kurinost/local.h"
#include <ss_types.h>
#include <macros.h>
inherit KURINOST_OUT;

void
reset_kurinost_room()
{
    return;
}

create_kurinost_room()
{
    set_short("Dock at the Thon-Thalas River");
    set_long("@@long_descr");

    add_item(({"forest","tree","trees"}), "The trees here look "+
        "gnarled and ugly.  You are not sure why the forest "+
        "suddenly changes from gorgeous to grotesque, but you "+
        "are very certain that it is not natural.\n");
    add_item("road","Little more than a dirt path through the "+
        "forest, the road leads northeast to Alinost and continues "+
        "to Kurinost");
    add_item(({"underbrush","brush"}), "The underbrush seems to "+
        "have changed from bushes to brambles, making travel off "+
        "of the path dangerous, if not impossible.\n");
    add_item("river","The Thon-Thalas river is now slow moving "+
        "and muck-filled.  The river splits just before reaching "+
        "Silvanost, and rejoins itself after passing the capital "+
        "at the town of Balinost.\n");

    add_exit(KROOM + "ka24","northeast",0);

    reset_kurinost_room();
}

string
long_descr()
{
    return "You stand at the Thon-Thalas river.  Once a clear and "+
       "beautiful river, it now runs thick with ooze.  The river "+
       "flows south towards the heart of the Silvanesti nation, and "+
       "to its capital, Silvanost.  You seem to be unable to find a "+
       "way to travel south upon the river.  The Kurinost-Alinost "+
       "Road begins here and leads northeast towards both towns.\n";
}
