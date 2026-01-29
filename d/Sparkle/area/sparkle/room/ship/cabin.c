#pragma save_binary
#pragma strict_types

inherit "/d/Genesis/ship/cabin";

#include <stdproperties.h>

#include "../../defs.h"

object ship;

void
create_cabin()
{
    set_short("A cabin inside the galleon");
    set_long(break_string("You stand in a small cabin. This is merely a " +
        "shelter from the wind and you find nothing of interest here. " +
        "A small doorway leads out north." +
        "\n", 70));

    add_exit("deck", "north", 0);

    add_prop(ROOM_I_INSIDE, 1);

    set_cabin_sound("@@sounds");
}

string
sounds()
{
    if (random(2))
        return "The ship sways slightly in the wind.\n";

    return "The ship is rocking gently with the waves.\n";
}

