/*  ship between Gont Port and Shire Harbour
 *  Coded by Ged 17/08/2001
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
    set_deck(SHIRE_LINE + "deck");
    the_captain = clone_object(SHIRE_LINE + "captain");
    set_captain(the_captain);
    set_places_to_go(({SHIRE_LINE + "shire_pier",
        SHIRE_LINE + "water1",
        SHIRE_LINE + "water2",
        SHIRE_LINE + "water3",
        SHIRE_LINE + "water4",
        SHIRE_LINE + "water5",
        SHIRE_PIER,
        SHIRE_LINE + "water5",
        SHIRE_LINE + "water4",
        SHIRE_LINE + "water3",
        SHIRE_LINE + "water2",
        SHIRE_LINE + "water1",
      }));
    set_time_between_stops(({25,
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
    set_ticket_id("_gont_port_shire_");
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

