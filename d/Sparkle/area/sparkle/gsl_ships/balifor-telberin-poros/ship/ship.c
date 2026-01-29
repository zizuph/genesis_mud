/*  ship between Calia and Earthsea
 * coded by Amelia (1/98)
 * Converted to Balifor-Telberin-Poros,
 * Tapakah, 05/2009
 */

#include "/sys/macros.h"
#include "/sys/stdproperties.h"
#include "/d/Genesis/gsl_ships/ships.h"
#include "../ship.h"

inherit STDSHIP;

void
create_ship()
{
  ::create_ship();
  setuid();
  seteuid(getuid());
  set_cabin(CABIN);
  set_deck(DECK);

  set_name("ship");
  add_name("boat");
  add_name("yawl");
  set_short("ancient black yawl");
  set_long("A long black yawl. It is a two-masted "+
           "fore-and-aft-rigged sailing vessel with a mizzen "+
           "mast stepped aft of the taller mainmast. "+
           "The sails are a worn dark grey. On the side of the "+
           "ship by the prow are painted the words THE ALBATROSS.\n");
  set_board_enabled(1);
  set_ship_line(MASTER_OB(this_object()), 
                CAPTAIN, TICKET, 
                ({ BALIFOR_PIER, TELBERIN_PIER, POROS_PIER }) );
  
}
