#pragma save_binary
#pragma strict_types

#include <stdproperties.h>
#include "/d/Genesis/gsl_ships/ships.h"
#include "../ship.h"

inherit STDSHIPROOM;

void
create_room()
{
  ::create_shiproom();
    set_short("A cabin inside the galleon");
    set_long("You stand in a small cabin. This is merely a " +
	"shelter from the wind, and you find nothing of interest here. " +
	"A small doorway leads out to the deck." +
	"\n");

    add_exit(DECK, "fore", 0);
    add_exit(DECK, "out", 0, 1, 1);
    add_exit(DECK, "deck", 0, 1, 1);

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
