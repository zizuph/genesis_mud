inherit "/std/armour";
#include <wa_types.h>
#include <formulas.h>
#include <stdproperties.h>
#include <macros.h>
#include "/d/Ansalon/kalaman/local.h"



void
create_armour()
{
    set_name("leggings");
    set_ac(20);
    set_at(A_LEGS);
    set_am( ({ 5, -3, -2 }) );
    set_adj("chainmail");
    set_short("pair of chainmail leggings");
    set_pshort("pairs of chainmail leggings");
    set_long("This is a pair of chainmail leggings that typically compliment " +
      "platemail.\n");
    add_prop(OBJ_I_VOLUME, 450);
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_ARMOUR(20, A_LEGS));
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(20));
    add_prop(KALAMAN_NOBUY,1);
}

