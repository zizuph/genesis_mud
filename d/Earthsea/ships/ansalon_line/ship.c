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
    set_cabin(ANSALON_LINE + "cabin");
    set_deck(ANSALON_LINE + "deck");
    the_captain = clone_object(ANSALON_LINE + "captain");
    set_captain(the_captain);
    set_places_to_go(({ANSALON_LINE + "west_pier2",
	ANSALON_LINE + "water1",
	ANSALON_LINE + "water2",
	ANSALON_LINE + "water3",
	ANSALON_LINE + "water4",
	ANSALON_LINE + "water5",
	ANSALON_PIER,
	ANSALON_LINE + "water5",
	ANSALON_LINE + "water4",
	ANSALON_LINE + "water3",
	ANSALON_LINE + "water2",
	ANSALON_LINE + "water1",
      }));
    set_time_between_stops(({ 20,
	2,
	2,
	2,
	2,
	2,
	20,
	2,
	2,
	2,
	2,
	2,
      }));
    set_ticket_id("_gont_ansalon_");
    set_name("ship");
    add_name("boat");
    add_name("yawl");
    set_short("ancient black yawl");
    set_long(break_string("A long black yawl. It is a two-masted "+
	"fore-and-aft-rigged sailing vessel with a mizzen "+
	"mast stepped aft of the taller mainmast. "+
	"The sails are a worn dark grey. On the side of the "+
	"ship by the prow are painted the words THE ALBATROSS.\n",70));
    set_board_enabled(1);
}
