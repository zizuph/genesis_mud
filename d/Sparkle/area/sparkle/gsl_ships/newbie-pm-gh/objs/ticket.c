/* File:          /d/Khalakhor/ship/macdunn/sparkle/ticket.c
 * Creator:       Teth
 * Date:          April 12, 1997
 * Modifications: Converted from Khalakhor/Ansalon run.
 *                Khail - November 28/97.
 * Purpose:       The ticket to ride the Khalakhor-Sparkle ship.
 * Related Files: /d/Khalakhor/ship/macdunn/
 *                /d/Khalakhor/ship/macdunn/sparkle/
 *                /d/Khalakhor/open/SHIPLINES
 * Ship rerouted to Newbie line via Macdunn/Grey Havens, Tapakah, 05/2009
 * Comments:
 */

#pragma save_binary
#pragma strict_types

#include <stdproperties.h>
#include "/d/Genesis/gsl_ships/ships.h"

#define TICKET_VALUE 30

inherit STDTICKET;

public void
create_object()
{
    set_name("ticket");
    add_name("newbieportmacdunngreyhavens");
    add_adj("wrinkled");
    set_long("This wrinkled ticket grants passage on the Sgian Dubh, " +
             "the ship that runs circle line between Port Macdunn, Gelan " +
             "Sparkle and Grey Havens.\n");
    add_prop(OBJ_I_VALUE, TICKET_VALUE);
    add_prop(OBJ_I_WEIGHT, 1);
    add_prop(OBJ_I_VOLUME, 5);
  set_price(TICKET_VALUE);
}

public void
init()
{
  ::init();
  //  add_action("check_passengers", "check");
}
