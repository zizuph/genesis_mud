/*
 * The surcoat of the Guard of the Tower
 *
 * Olorin, 18-nov-1994
 */
#pragma save_binary

inherit "/d/Gondor/guilds/bnumen/obj/bnumen_armour";

#include <wa_types.h>

#include "/d/Gondor/defs.h"

void
create_bnumen_armour()
{
    set_name("surcoat");
    set_short("black surcoat");
    set_adj(({"black", "short", "embroidered", }));
    set_long(BSN("A short surcoat of black, to be worn above a mail, "
      + "broidered on the breast in silver with the token of the "
      + "White Tree of Minas Tirith. "
      + "This armour is worn by the Guard of the Tower of Minas "
      + "Tirith."));

    set_default_armour( 4, A_ROBE, 0, 0);
}
