// file name:        Deck
// creator(s):       Cirion, April 1997
// last update:
// purpose:          Deck of the Union tomb ship
// note:
// bug(s):
// to-do:
inherit "/d/Genesis/ship/deck";
#include "/d/Avenir/common/ships/ship.h"

void
create_deck()
{
    set_short("on the deck of the slender ship");
    set_long("The deck of the small ship is constructed from "
        + "thin, delicate lathes. The wood is all tinted a "
        + "deep green hue.\n");

    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_LIGHT, 1);
    set_bump_sound("The ship softly comes to a halt.\n");
    set_deck_sound(VBFC_ME("sounds"));
}

string
sounds()
{
    return "The ship glides quietly along the still water.\n";
}

