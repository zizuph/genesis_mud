/*
 * The helm of the Guard of the Tower
 *
 * Olorin, 16-nov-1994
 */
#pragma save_binary

inherit "/d/Gondor/guilds/bnumen/obj/bnumen_armour";

#include <wa_types.h>

#include "/d/Gondor/defs.h"

void
create_bnumen_armour()
{
    set_name("helm");
    set_short("high-crowned winged helm");
    set_pshort("high-crowned winged helms");
    set_adj(({"high-crowned", "winged", }));
    set_long(BSN("A high-crowned helm with small raven-wings on either "
      + "side, set with a silver star in the center of the circlet. "
      + "This armour is worn by the Guard of the Tower of Minas "
      + "Tirith."));

    set_default_armour(25, A_HEAD, 0, 0);
}
