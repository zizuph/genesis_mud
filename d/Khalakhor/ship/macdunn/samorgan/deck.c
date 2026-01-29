/**********************************************************************
 * - deck.c                                                         - *
 * - Deck of ship                                                   - *
 * - Created by Damaris@Genesis 03/2001                             - *
 * - Updated by Damaris@Genesis 08/2005                             - *
 **********************************************************************/

#pragma save_binary
#pragma strict_types

inherit "/d/Genesis/ship/deck";
#include "local.h"
#include <stdproperties.h>
#include "/d/Khalakhor/sys/terrains.h"

public void create_deck()
{
	set_short("on the deck of the "+SHIP_NAME);
	set_long("   This sturdy ship is named the "+SHIP_NAME+". "+
	"Constructed of heavy wood beams, it has a massive central "+
        "mast with voluminous sails, all designed to weather storms "+
        "and pull the heavy vessel through the waters quickly.\n");

        add_item(({"deck","area"}),"@@query_long");
        add_item(({"ship","vessel","small vessel",SHIP_NAME, "bella diaz"}),
        "This is the ship that transports passengers and cargo "+
        "between the village of SaMorgan and Port MacDunn in the "+
        "land of Khalakhor.\n");
        add_item("mast",
        "The central mast of the ship is massive. You wonder how "+
        "the ship doesn't topple over from its weight. Obviously "+
        "designed to withstand powerful winds, it rises high above "+
        "the deck laden with large sails.\n");
        add_item("sails",
        "The large white sails hanging from the mast seem to be made of "+
        "wool and are very voluminous. You imagine a heavy wind in "+
        "those sails on that mast could carry the ship very quickly "+
        "and safely.\n");
        add_cmd_item(({"air","in the air"}),({"smell","breathe"}),
        "The air smells of sea salt.\n");
        add_item("sky","The sky above is partially cloudy.\n");
        
        add_exit(THIS_DIR + "cabin", "cabin", 0);
        add_prop(ROOM_I_TERRAIN_TYPE, TERRAIN_SHIPDECK);
        set_deck_sound("@@sounds");
}

public string sounds()
{
	if(random(3))
	return "The ship glides through the cold waters at top speed.\n";
	return "The ship rises slightly as it slices through a huge wave.\n";
}
