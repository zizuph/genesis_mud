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
    set_deck(SPARK_LINE + "deck");
    the_captain = clone_object(SPARK_LINE + "captain");
    set_captain(the_captain);
    set_places_to_go(({SPARK_LINE + "east_pier2",
	SPARK_LINE + "water1",
	SPARK_LINE + "water2",
	SPARK_LINE + "water3",
	SPARK_LINE + "water4",
	SPARK_LINE + "water5",
	SPARK_PIER,
	SPARK_LINE + "water5",
	SPARK_LINE + "water4",
	SPARK_LINE + "water3",
	SPARK_LINE + "water2",
	SPARK_LINE + "water1",
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
    set_name("ship");
    add_name("boat");
    add_name("sloop");
    add_adj("silver-sailed");
    set_short("silver-sailed sloop");
    set_ticket_id("_gont_sparkle_");
    set_long(break_string("A silver-sailed sloop. "+
	"This is a single-masted, fore-and-aft rigged "+
	"sailing vessel with a short silver "+
	"bowsprit. It has a large triangular silver sail with "+
	"a great blue spinnaker sail set on a spar. The hull "+
	"is painted black, and the words THE OSPREY emblazon "+
	"the prow.\n", 70));
    add_item((({"spinnaker sail", "sails", "blue spinnaker",
	  "silver sail", "triangular sail" })),
      "The ship is rigged with two sails, a large silver "+
      "mainsail and a billowing blue spinnaker sail.\n");
    add_item((({"hull", "prow"})),
      "The hull and prow are painted black, but the name "+
      "of the ship is painted in silver on the prow.\n");
    add_item((({"bowsprit", "silver bowsprit"})),
      "The bowsprit projects from the front of the ship like "+
      "a beak.\n");
    add_item("spar",
      "The metal pole that supports the spinnaker.\n");


    set_board_enabled(1);
}
