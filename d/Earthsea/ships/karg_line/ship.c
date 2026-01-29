/*  ship between Earthsea and karg island
 * coded by Ged , 6/10/2001
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
    set_deck(KARG_LINE + "deck");
    the_captain = clone_object(KARG_LINE + "captain");
    set_captain(the_captain);
    set_places_to_go(({BEACH_PIER,
        KARG_LINE + "water0",
        KARG_LINE + "water1",
        KARG_LINE + "water1",
        KARG_LINE + "water2",
        KARG_LINE + "water2",
        KARG_LINE + "water2",
        KARG_LINE + "water3",
        KARG_LINE + "water3",
        KARG_LINE + "water3",
        KARG_LINE + "water4",
        KARG_LINE + "water4",
        KARG_LINE + "water5",
        KARG_PIER,
        KARG_LINE + "water5",
        KARG_LINE + "water4",
        KARG_LINE + "water4",
        KARG_LINE + "water3",
        KARG_LINE + "water3",
        KARG_LINE + "water3",
        KARG_LINE + "water2",
        KARG_LINE + "water2",
        KARG_LINE + "water2",
        KARG_LINE + "water1",
        KARG_LINE + "water1",
        KARG_LINE + "water0",
      }));
    set_time_between_stops(({ 25,
        2,
        2,
        2,
        2,
        2,
        2,
        2,
        2,
        3,
        3,
        3,
        3,
        25,
        3,
        3,
        3,
        3,
        2,
        2,
        2,
        2,
        2,
        2,
        2,
        2,
      }));
    set_name("boat");
    set_adj("small");
    add_adj("camuflaged");
    set_short("small camuflaged boat");
    set_ticket_id("_gont_karg_");
    set_long("You see small boat , you wonder whether you should "+
      "board it. It's camuflaged , so karg warships won't spot it and "+
      "it looks fast enough to leave those warships behind.n");

    set_board_enabled(1);
}

