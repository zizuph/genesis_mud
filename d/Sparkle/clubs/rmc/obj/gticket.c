/*
 * RMC Golden Ticket
 *
 * Change History: 
 * Created  - Conan Apr 1995
 * Exploit fix by Lunatari 20060717
 * You can only have one ticket at the time now.
 * Ported to new ship system
 * Tapakah, 10/2008
 */
#include <stdproperties.h>
#include "../defs.h"
#include "/d/Genesis/gsl_ships/ships.h"

inherit STDTICKET;
 
void
create_object()
{
  ::create_ticket();
  set_name("ticket");
  add_name("rich_ticket");
  set_adj("golden");

  set_long("The ticket are covered with a thin layer of gold and has the "+
    "logo of The Rich Men's Club.\n");

  add_prop(OBJ_I_VALUE, 17280);
  // add_prop(OBJ_I_VALUE, 100); 
  /* Temporary to fix exploit, Cotillion */
  add_prop(OBJ_I_NO_DROP, 1);
  add_prop(OBJ_M_NO_SELL, "This ticket is not sellable.\n");
  set_price(17280);
}

public void
enter_env(object dest, object old)
{
  ::enter_env(dest, old);
  remove_name(TICKET_ID);
  if (present(TICKET_ID, ENV(TO))) {
    tell_room(ENV(TO),
              "The tickets melt together in some mysterious way.\n");
    set_alarm(1.0,0.0, &remove_object());
    return;
  }
  add_name(TICKET_ID);
}
