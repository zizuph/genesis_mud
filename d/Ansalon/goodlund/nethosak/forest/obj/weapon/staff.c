inherit "/std/weapon.c";
#include <stdproperties.h>
#include <macros.h>
#include <wa_types.h>
#include <ss_types.h>
#include <formulas.h>
#include "/d/Ansalon/common/defs.h"

void
create_weapon()
{
        set_name(({ "staff", "polearm" }));
        set_adj("vallenwood");
        set_short("vallenwood staff");
        set_long("This long staff is made of hard vallenwood. " +
                 "The weapon has been made smooth and the handle "+
                 "has been wrapped in soft leather, making it very "+
                 "easy and comfortable to wield it. The staff "+
                 "has a pointy end, making it possible to sink into "+
                 "the dirt, making it a great walking stick.\n");

        set_default_weapon(40, 35, W_POLEARM, W_BLUDGEON|W_IMPALE, W_BOTH);
        add_prop(OBJ_I_VOLUME, 8500);
        add_prop(OBJ_I_WEIGHT, 7000);
        add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(30,25) + 100);
}

