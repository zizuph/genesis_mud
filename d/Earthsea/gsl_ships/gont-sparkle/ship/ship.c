/*  ship between Sparkle and Earthsea
 * coded by Amelia (1/98)
 * Ported by Tapakah 05/2009
 */

#include "/sys/macros.h"
#include "/sys/stdproperties.h"
#include "../ship.h"
#include "/d/Genesis/gsl_ships/ships.h"

inherit STDSHIP;


void
create_ship()
{
  ::create_ship();
  setuid();
  seteuid(getuid());
  set_deck(DECK);
  set_name("ship");
  add_name("boat");
  add_name("sloop");
  add_adj("silver-sailed");
  set_short("silver-sailed sloop");
  set_long("A silver-sailed sloop. "+
           "This is a single-masted, fore-and-aft rigged "+
           "sailing vessel with a short silver "+
           "bowsprit. It has a large triangular silver sail with "+
           "a great blue spinnaker sail set on a spar. The hull "+
           "is painted black, and the words THE OSPREY emblazon "+
           "the prow.\n");
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
  set_ship_line(MASTER_OB(this_object()), 
                  CAPTAIN, TICKET, 
                  ({ GONT_PIER, SPARKLE_PIER, }));
  
}
