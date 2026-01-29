/* Calia-Shire ship cabin.
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
        set_cabin_sound("You hear waves crashing against the hull "+
            "of the ship.\n");
	set_short("The captain's cabin");
    set_long("You are standing in Captain Sutec's cabin. You "+
        "see several maps unfolded on a wooden desk, and a gold "+
        "sextant on top of them. There is a bed in one corner of "+
        "the room, which is neatly made.\n");

    add_item("desk","The desk is made of solid oak and looks very "+
        "sturdy. There are several maps and a gold sextant lying on "+
        "top of it.\n");

    add_item(({"sextant","gold sextant"}),"It is a gold sexant "+
        "used for figuring out the position of an object in "+
        "relation to a map. It looks like it is worth quite a "+
        "bit and you decide not to mess with it.\n");

    add_item("maps","There are many maps of various lands scattered "+
        "about on the desk under a gold sextant. On a map of Calia, "+
        "you notice a circle drawn in an area southwest of the docks. "+
        "There are no other noticable features on any of the other "+
        "maps that you can see.\n");

    add_item("bed","The bed is merely two mattresses on the floor, "+
        "covered in fine silk blankets. It looks like it would be "+
        "very comfortable to lie on, but you decide you had better "+
        "not disturb it.\n");

    add_item("circle","There is a circle draw on the map in an area "+
        "southwest of the docks.\n");

	add_prop(ROOM_I_INSIDE,1);
	add_prop(ROOM_I_LIGHT,1);
        add_prop(ROOM_I_HIDE,-1);
	add_exit(SHIPS+"deck.c", "up", 0,0);

}

void
enter_inv(object ob, object from)
{
	::enter_inv(ob,from);
	if (interactive(ob))
		{
        write("You feel relieved to get out of the winds from "+
            "the deck of the ship.\n");
		}
}
