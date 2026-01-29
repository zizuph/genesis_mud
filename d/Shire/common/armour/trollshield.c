#include "rdefs.h"

inherit "/std/armour";

#include <stdproperties.h>
#include <macros.h>
#include <wa_types.h>
#include <formulas.h>

create_armour()
{
    set_name("shield");
    set_short("troll shield");
    set_long("A troll shield made of wood and steel.\n");
    set_ac(13);
    set_at(A_SHIELD);
    set_am( ({ 2, -1, -1}) );
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_ARMOUR(13,A_SHIELD) + 2800 );
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(13) + random(101) - 100);
    add_prop(OBJ_I_VOLUME, 1000);
}

#include "recover"
