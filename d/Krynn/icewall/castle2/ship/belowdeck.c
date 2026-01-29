inherit "/d/Krynn/std/cabin";
#include "local.h"
#include <stdproperties.h>

void
create_cabin()
{
    set_short("Below the deck of the schooner");
    set_long("You stand below the deck of the schooner. There are a few " +
        "spartan cabins here, and a crew-sleeping area. To the middle, cargo " +
        "can be stored. It is as good as any hideout from the storms outside.\n");

    add_item("cargo", "There is none at this time.\n");
    add_item("cabins", "They are locked shut.\n");

    add_exit(TDIR + "deck", "up", 0);
    set_cabin_sound("@@sounds");

    add_prop(ROOM_I_INSIDE, 1);
    reset_room();
}

sounds()
{

    if (random(2))
        return "The ship sways slightly in the wind.\n";

    return "The ship is rocking gently with the waves.\n";
}
