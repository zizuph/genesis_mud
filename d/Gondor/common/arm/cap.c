/*  Armour coded by Arren, November 93 */

inherit "/std/armour";

#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <formulas.h>

#include "/d/Gondor/defs.h"

void
create_armour()
{
    set_name("cap");
    set_pname("caps");
    set_adj("black");
    add_adj("orc");
    set_short("black cap");
    set_pshort("black caps");
    set_long(BSN("A black cap with an iron rim. It is made of iron hoops "+
    "covered in leather with a beaklike nose-guard."));

    set_default_armour(13, A_HEAD, ({ -1, 2, -1 }), 0);

    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_ARMOUR(13, A_HEAD));
    add_prop(OBJ_I_VOLUME, 500);
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(13)+random(50)-25);
}
