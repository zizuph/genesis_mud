inherit "/d/Krynn/std/cabin";

#include <stdproperties.h>
#include "local.h"

void
create_cabin()
{
    set_short("The captain's cabin");
    set_long("This cabin is not large. Neither it is comfortable. A simple " +
	"cot, a desk with some charts, and a locked chest bear proof " +
        "that the captain of this vessel is a no-nonsense man of the sea. " +
        "A solid doorway leads out on the middle deck of the schooner.\n");

    add_item("desk", "A sturdy wooden desk. Some charts are spread upon it.\n");
    add_item(({"chart", "charts"}),
	    "The charts are nautical maps of Krynnish seas, marked in " +
	     "signs you cannot fathom out.\n");

    add_exit(TDIR + "deck", "out", 0);

    add_prop(ROOM_I_INSIDE, 1);

    set_cabin_sound("@@sounds");
}

sounds()
{

    if (random(2))
    return "The ship sways slightly in the wind.\n";

    return "The ship is rocking gently with the waves.\n";
}

