/* ship between Oranea and Gont Port
 * Coded by Amelia April 25, 1998
 */

#pragma strict_types

#include <macros.h>
#include <stdproperties.h>
#include "../ship.h"
#include "/d/Genesis/gsl_ships/ships.h"

inherit STDSHIP;

public void
create_ship()
{
  ::create_ship();

    setuid();
    seteuid(getuid());

    set_deck(DECK);
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
    set_ship_line(MASTER_OB(this_object()), 
                  CAPTAIN, TICKET, 
                  ({ GONT_PIER, THWIL_PIER, }));
    
}
