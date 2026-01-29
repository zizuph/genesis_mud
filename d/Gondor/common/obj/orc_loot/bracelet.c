/*  Armour coded by Arren, January 94 */
/* A jewelry found on the random orc. */

inherit "/std/armour";

#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include "/sys/formulas.h"
#include "/d/Gondor/defs.h"

create_armour()
{
    set_name("bracelet");
    add_name(({ "jewelry" }));
    set_adj("silvery");
    add_adj(({ "cheap", "bronze" }));
    set_short("silvery bracelet");
    set_long(BSN("This is some cheap silvery bracelet, not much of armour, "+
    "but maybe worth something to a trader. Below the thin silver "+
    "coating there can be seen bronze."));

    set_default_armour(1, A_L_ARM, ({ 0, 0, 0 }), 0);

    add_prop(OBJ_I_WEIGHT, 200);
    add_prop(OBJ_I_VOLUME, 200);
    add_prop(OBJ_I_VALUE, 150 + random(75));
}
