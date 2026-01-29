/*  ship between Oranea and Gont Port
 *  Coded by Amelia April 25, 1998
 */

inherit "/d/Genesis/ship/ship";

#include "/sys/macros.h"
#include "/sys/stdproperties.h"
#include "defs.h"

object the_captain;

#define ORANEA_PIER ORANEA_LINE + "oranea_pier"

void
create_ship()
{
    if (!IS_CLONE)
	return;
    setuid();
    seteuid(getuid());
    set_deck(ORANEA_LINE + "deck");
    the_captain = clone_object(ORANEA_LINE + "captain");
    set_captain(the_captain);
    set_places_to_go(({ORANEA_LINE + "west_pier3",
	ORANEA_LINE + "water1",
	ORANEA_LINE + "water2",
	ORANEA_LINE + "water3",
	ORANEA_PIER,
	ORANEA_LINE + "water3",
	ORANEA_LINE + "water2",
	ORANEA_LINE + "water1",
      }));
    set_time_between_stops(({25,
	3,
	3,
	3,
	25,
	3,
	3,
	3,
      }));
    set_ticket_id("_gont_port_oranea_");
    set_name("ship");
    add_name("coracle");
    add_name("boat");
    set_short("small white coracle");
    set_long(break_string("This is a small white coracle. "+
	"It is a shallow-drafted rounded boat, which is constructed "+
	"from white bark stretched over a pine frame. You see "+
	"that a pair of oars are fixed to the oarlocks, which "+
	"must be what propels the boat. Painted on the bow of the "+
	"small craft in red paint are the words The Dragonet.\n", 70));
    set_board_enabled(1);
}
