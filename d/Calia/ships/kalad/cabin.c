/* Calia-Kalad ship cabin.
   Coded by Digit.

   History:
            13/7/95       Typo corrected              Maniac
             01/9/95        Typos Corrected            Digit
*/

#pragma save_binary

inherit "/d/Genesis/ship/cabin";

#include <stdproperties.h>
#include "ship.h"
#include <macros.h>

void
create_cabin()
{
    set_cabin_sound("The walls creak from the pressure of the water "+
        "outside.\n");
	set_short("The captain's cabin");
    set_long("This appears to be the captain's cabin. It is very small "+
        "and only contains a bed of sorts. Everything here, like above "+
        "is painted a dark black which almost seems to absorb light.\n");

    add_item("bed","The bed is nothing more than a large pile of "+
        "leathery skins bound together with some type of thread. It "+
        "does not appear to be comfortable at all.\n");

    add_item("thread","Upon closer examination it appears the thread is "+
        "actually human hair!\n");

	add_prop(ROOM_I_INSIDE,1);
    add_prop(ROOM_I_LIGHT,0);
	add_exit(SHIPS+"deck.c", "up", 0,0);

}

void
enter_inv(object ob, object from)
{
	::enter_inv(ob,from);
	if (interactive(ob))
		{
        write("You feel as if hundreds of eyes are watching you as you "+
            "venture down the ladder into the darkness.\n");
		}
}
