/*  Armour coded by Arren, January 94 */

inherit "/std/armour";

#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <formulas.h>

#include "/d/Gondor/defs.h"

void
create_armour()
{
    set_name("helmet");
    add_name("helm");
    set_adj("gruesome");
    add_adj(({ "beast", "steel", "orc" }));
    set_short("gruesome helmet");
    set_long(BSN("A steel helmet with a noseguard. From the top of the "+
    "helmet a snarling beast, cunningly wrought to look hideous, looks "+
    "down at you with bared fangs."));

    set_default_armour(22, A_HEAD, ({ 0, 0, 0 }), 0);

    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_ARMOUR(22, A_HEAD));
    add_prop(OBJ_I_VOLUME, 900);
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(22)+random(100)-50);
}
