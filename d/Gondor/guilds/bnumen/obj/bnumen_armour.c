/*
 * The armour of the Guard of the Tower
 *
 * Olorin, 9-nov-1994
 */
#pragma save_binary

inherit "/std/armour";

#include <formulas.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"

#define BNUMEN_SHOP		(BNUMEN_DIR + "rooms/bnumen_shop")
#define BNUMEN_STORE		(BNUMEN_DIR + "rooms/bnumen_store")

void
create_bnumen_armour()
{
}

nomask void
create_armour()
{
    int     val,
            w;

    add_name("_bnumen_armour");
    create_bnumen_armour();

    val = F_VALUE_ARMOUR(arm_ac);
    val *= (100 + random(20) - 10);
    val /= 100;
    add_prop(OBJ_I_VALUE, val);
    w = F_WEIGHT_DEFAULT_ARMOUR(arm_ac, arm_at);
    w *= (100 + random(30) - 15);
    w /= 100;
    add_prop(OBJ_I_WEIGHT, w);
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT) / 4);

    add_prop(OBJ_M_NO_BUY, "@@check_sell@@");
    add_prop(OBJ_M_NO_SELL, "@@check_sell@@");
}

mixed
check_sell()
{
    object  room = ENV(TO);
    string  file;

    while (!(room->query_prop(ROOM_I_IS)))
        room = ENV(room);

    file = file_name(room);

    if ((file == BNUMEN_SHOP) || (file == BNUMEN_STORE))
        return 0;

    return BSN(
        "This armour can neither be sold nor bought, except "
      + "at the Armoury in the House of the Black Numenoreans in Minas "
      + "Tirith.");
}
