/* ship between Oranea and Gont Port
 * Coded by Amelia April 25, 1998
 */

#pragma strict_types

inherit "/d/Genesis/ship/ship";

#include <macros.h>
#include <stdproperties.h>

public void
create_ship()
{
    if(!IS_CLONE)
    {
        return;
    }

    setuid();
    seteuid(getuid());

    set_deck("/d/Earthsea/ships/thwil_line/deck");
    set_captain(clone_object(
        "/d/Earthsea/ships/thwil_line/captain"
    ));
    set_places_to_go(({
        "/d/Earthsea/ships/thwil_line/west_pier3",
        "/d/Earthsea/ships/thwil_line/water1",
        "/d/Earthsea/ships/thwil_line/water2",
        "/d/Earthsea/ships/thwil_line/water3",
        "/d/Earthsea/roke/thwil/h7",
        "/d/Earthsea/ships/thwil_line/water3",
        "/d/Earthsea/ships/thwil_line/water2",
        "/d/Earthsea/ships/thwil_line/water1",
    }));
    set_time_between_stops(({
        25, 3, 3, 3, 25, 3, 3, 3
    }));
    set_ticket_id("_gont_port_oranea_");
    set_name("ship");
    add_name("coracle");
    add_name("boat");
    set_short("small white coracle");
    set_long("This is a small white coracle. It is a " +
        "shallow-drafted rounded boat, which is constructed " +
        "from white bark stretched over a pine frame. You see " +
        "that a pair of oars are fixed to the oarlocks, which " +
        "must be what propels the boat. Painted on the bow of the " +
        "small craft in red paint are the words The Dragonet.\n");
    set_board_enabled(1);
}
