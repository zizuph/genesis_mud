/* Ashlar, 4 Oct 97 */

inherit "/std/armour";
inherit "/lib/keep";

#include <wa_types.h>
#include <formulas.h>
#include <stdproperties.h>
#include <macros.h>
#include "../local.h"
#include "/d/Ansalon/common/defs.h"

#define ARMOUR_CLASS    26

void
create_armour()
{
    set_name("helm");
    set_adj("steel");
    set_short("steel helm");
    set_pshort("steel helms");
    set_ac(ARMOUR_CLASS);
    set_at(A_HEAD);
    set_long("This is a steel helm. It is flared at the neck and has a " +
    "cruel spike set on top of it.\n");
    add_prop(OBJ_I_VOLUME, 1000);
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_ARMOUR(ARMOUR_CLASS, A_HEAD));
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(ARMOUR_CLASS));
}

