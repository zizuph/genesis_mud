/*  ship between Calia and Earthsea
 * coded by Amelia (1/98)
 */

inherit "/d/Genesis/ship/ship";

#include "/sys/macros.h"
#include "/sys/stdproperties.h"
#include "defs.h"

object the_captain;


void
create_ship()
{
    if (!IS_CLONE)
	return;
    setuid();
    seteuid(getuid());
    set_cabin(CALIA_LINE + "cabin");
    set_deck(CALIA_LINE + "deck");
    the_captain = clone_object(CALIA_LINE + "captain");
    set_captain(the_captain);
    set_places_to_go(({CALIA_LINE + "west_pier1",
	CALIA_LINE + "water1",
	CALIA_LINE + "water2",
	CALIA_LINE + "water3",
	CALIA_LINE + "water4",
	CALIA_LINE + "water5",
	CALIA_PIER,
	CALIA_LINE + "water5",
	CALIA_LINE + "water4",
	CALIA_LINE + "water3",
	CALIA_LINE + "water2",
	CALIA_LINE + "water1",
      }));
    set_time_between_stops(({ 25,
	3,
	3,
	3,
	3,
	3,
	25,
	3,
	3,
	3,
	3,
	3,
      }));
    set_ticket_id("_gont_calia_");
    set_name("ship");
    add_name("boat");
    add_name("ketch");
    set_short("white-sailed ketch");
    set_long("A long white-sailed ketch. It is a two-masted "+
      "fore-and-aft-rigged sailing vessel with a mizzen "+
      "or jigger mast stepped aft of a taller mainmast. "+
      "The sails are pure white with a silver hawk painted "+
      "on the mainsail. On the side of the boat by the prow "+
      "you see burned into the teak the words THE SEA HAWK.\n");
    set_board_enabled(1);
}
