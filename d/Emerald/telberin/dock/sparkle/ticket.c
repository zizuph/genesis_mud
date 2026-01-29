/*
 *  /d/Emerald/telberin/dock/sparkle/ticket.c
 *
 *  This is the ticket for the Sparkle to Emerald line.
 *
 *  Created August 2007, by Cooper Sherry (Gorboth)
 */

#include <stdproperties.h>
#include <macros.h>
#include "/d/Genesis/gsl_ships/ships.h"

inherit STDTICKET;

/*
 * Function name:        create_object
 * Description  :        set up the object
 */

public void
create_object()
{
	create_ticket();
  set_name("ticket");
  add_name("Telberin to Sparkle Line");

  set_short("faintly glowing ticket");
  add_adj( ({ "faintly", "glowing" }) );

  set_long("Strangely, this ticket appears to be glowing slightly."
           + " It looks like the sort of ticket used in seafaring.\n");
  set_price(30);
  
  add_prop(OBJ_I_WEIGHT, 5);
  add_prop(OBJ_I_VOLUME, 5);
  add_prop(OBJ_I_VALUE, 24);
  
} /* create_object */

query_recover()   { return MASTER; }
