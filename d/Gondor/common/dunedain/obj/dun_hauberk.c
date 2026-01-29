/*
 * The hauberk of the Guard of the Tower
 *
 * Olorin, 9-nov-1994
 */
#pragma save_binary

inherit "/d/Gondor/common/dunedain/obj/dun_armour";

#include <wa_types.h>

#include "/d/Gondor/defs.h"

void
create_dunedain_armour()
{
    set_name("hauberk");
    add_name(({"ringmail", "mail", }));
    set_short("black steel hauberk");
    set_pshort("black steel hauberks");
    set_adj(({"black", "steel"}));
    set_long(BSN("A hauberk black as jet, its rings forged of steel. "
      + "This armour is worn by the Guard of the Tower of Minas "
      + "Tirith."));

    set_default_armour(32, A_BODY, 0, 0);
}
