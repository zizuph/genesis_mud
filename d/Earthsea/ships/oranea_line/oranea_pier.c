#pragma strict_types

/*
*
* Coded by Porta 971018.
*/

inherit "/d/Earthsea/std/room.c";
inherit "/d/Earthsea/lib/room_tell";

#include "defs.h"

void
create_earthsea_room()
{
    set_short("Stone pier");
    set_long(break_string(
	"This is a limestone pier, which "+
	"does not appear to have been built by human hands, but rather "+
	"from the working of sea on stone. It is pitted and grooved where "+
	"the stone has worn away, and it extends some distance into the "+
	"sea. The cove is crowded with small fishermen's boats, "+
	"and you also see a cargo ship at anchor a bit further out. "+
	"Dark-blue waves splash across the pier from time to time. "+
	"The air here is cloudy with a blue mist, making it "+
	"difficult to see the surroundings clearly. "+
	"A rock cliff stands directly to your "+
	"south which is crowned with a forest. There is a trail "+
	"going up carved into the rock. At some distance to the "+
	"east you make out the shape of Gont with its great mountain "+
	"topped with snow.\n", 70));
    add_my_desc("A sign chiseled into the limestone.\n");
    add_item("sign",
      "The sign has words which you can read.\n");
    add_item((({"Gont", "shape of Gont"})),
      "Further to the east you can see the island of Gont and its "+
      "famous mountaintop.\n");
    add_item("pier", "The pier is constructed of limestone, apparently "+
      "formed from the action of sea on stone.\n");
    add_item("limestone", "The white rock appears luminous "+
      "against the blue mist and water.\n");
    add_item((({"mountain", "low mountain"})),
      "The mountain is shrouded in blue mist, but you can make out its "+
      "outline, which resembles a dragon.\n");
    add_item((({"boats", "fishermen", "fishermen's boats"})),
      "Fishermen cast their nets from small boats, while seagulls "+
      "hover all around them.\n");
    add_item("ship",
      "A small coracle from Gont Port stops regularly at this pier. "+
      "Further out in the cove, you see a cargo ship at anchor.\n");

    add_item("cove", "The limestone pier shelters the cove "+
      "to the southeast from the larger waves.\n");
    add_item("cliff", "There is a cliff directly to your south, "+
      "and a rugged trail is carved into the limestone leading up.\n");
    add_item((({"sea", "blue sea"})),
      "The dark blue waters of the North Sea surround this pier, "+
      "which extends out to the east.\n");
    add_item((({"mist", "blue mist"})),
      "A soft blue cloud of mist wraps around everything, obscuring "+
      "your view.\n");
    add_cmd_item("sign", "read",
      "The sign reads:\n\n"+
      "     Boatline:  The Dragonet\n"+
      "     Destination:  Gont Port\n"+
      "     Captain:  Dravid\n"+
      "     Fare: only 12cc\n" +
      "\n\n");
    set_tell_time(120);
    add_tell("A large blue wave washes across the pier.\n");

/*
    add_exit("/d/Earthsea/oranea/rooms/beach07", "northwest");
*/
    add_exit("/d/Earthsea/oranea/rooms/beach08", "east", "@@block@@");
    add_exit("/d/Earthsea/oranea/rooms/oranea_path01", "up");

}

int
block()
{
    this_player()->catch_msg("That part of the beach is flooded by sea " +
      "water right now.\n");
    return 1;
}

void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
    if (interactive(ob))
	start_room_tells();
}

