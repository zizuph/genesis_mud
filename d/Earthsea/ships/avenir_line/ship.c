/* ship between Earthsea and Avenir
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
    set_deck(AVENIR_LINE + "deck");
    set_ticket_id("_gont_avenir_");
    the_captain = clone_object(AVENIR_LINE + "captain");
    set_captain(the_captain);
    set_places_to_go(({AVENIR_LINE + "east_pier1",
	AVENIR_LINE + "water1",
	AVENIR_LINE + "water2",
	AVENIR_LINE + "water3",
	AVENIR_WATER + "cave1",
	AVENIR_WATER + "cave2",
	AVENIR_PIER,
	AVENIR_WATER + "cave2",
	AVENIR_WATER + "cave3",
	AVENIR_LINE + "water3",
	AVENIR_LINE + "water2",
	AVENIR_LINE + "water1",
      }));
    set_board_enabled(1);
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
    set_name("ship");
    add_name("boat");
    add_name("barque");
    set_short("square-rigged cedar barque");
    set_adj(({"square-rigged", "cedar"}));
    add_name("boat");
    set_long(break_string("A square-rigged cedar "+
	"barque. The long curved hull is set close to the water "+
	"and it has a square-rigged sail made of silk and speckled with "+
	"silver stars. The bow of the barque "+
	"curves up gracefully. You see the words THE SEA "+
	"WITCH carved into the reddish wood of the prow.\n", 70));
    add_item((({"prow", "bow"})),
      "The bow of the barque is curved up very high, like "+
      "the tail of a dragon.\n");

}
