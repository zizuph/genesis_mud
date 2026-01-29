/*
 * Ship Deck for shipline between Sparkle and Gelan in Calia
 *
 * Created by Petros, April 2009
 */

#pragma save_binary

#include <stdproperties.h>
#include "ship.h"

inherit STDSHIPROOM;

public void
create_room()
{
    create_shiproom();

	set_deck_sound("The ship cuts through the waves and "+
		"water splashes the deck.\n");
	set_short("The deck of the sloop");
	set_long("You are standing on the deck of a sleek sloop. "+
		"The deck is made of finely oiled planks of teak, "+
		"which are fitted together in a beautiful pattern. "+
		"The cracks are carefully caulked, and you can see "+
		"that this ship has been very well maintained. "+
		"Coils of rope and other ship's paraphernalia are "+
		"arranged in an orderly fashion. A long boom attaches "+
		"to the mainsail and mast and extends above your head. "+
		"The rail is polished brass and there is a figurehead "+
		"of a woman carved from teak at the bow. The stern "+
		"is curved, and the beam of the boat is fairly "+
		"narrow, giving it very sleek lines. There is a "+
		"hatch with a narrow ladder leading down.\n");
	add_item((({"brass", "rail", "polished brass"})),
		("The rail is made from polished brass and goes all "+
		"around the ship.\n"));
	add_item("figurehead", "The figurehead is a statue of a "+
		"woman who looks very much like Caliana.\n");
	add_item((({"hatch", "ladder"})),
		("The hatch is open and there is a ladder that "+
		"leads down to an area below, possibly the captain's "+
		"quarters.\n"));
	add_item((({"deck", "planks", "teak", "cracks"})),
		("The deck is made from planks of teak, a kind of wood "+
		"which resists rot. The cracks between the planks are "+
		"well caulked.\n"));
	add_item((({"ropes", "coils", "paraphernalia"})),
		("Standard ship's equipment, neatly arranged "+
		"to prevent slippage in case of rough weather.\n"));
	add_item((({"boom", "mast"})),
		("The boom is a long pole that extends off the "+
		"mast and supports the triangular-shaped sail.\n"));
	add_item((({"sail", "mainsail"})),
		("The large, triangular-shaped sail contains "+
		"the figure of a blue dolphin on it.\n"));

	add_prop(ROOM_I_INSIDE,0);
	add_prop(ROOM_I_IS, 1);
	add_prop(ROOM_I_LIGHT, 1);
    add_prop(ROOM_I_NO_TELEPORT,1);
    add_prop(ROOM_I_HIDE, -1);

    set_is_deck(1);	    
    add_exit("cabin", "down");
}
