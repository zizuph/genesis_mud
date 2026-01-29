
/*  Armour coded by Arren, June 93 */

inherit "/std/armour";

#include "/sys/wa_types.h"
#include <stdproperties.h>
#include <macros.h>
#include <formulas.h>
#include "/d/Gondor/defs.h"

create_armour()
{
    set_name("leggings");
    set_adj("chainmail");
    add_adj(({"Rohirrim","mail","pair of"}));
    set_short("pair of chainmail leggings");
    set_pshort("pairs of chainmail leggings");
    set_long(BS("This pair of Rohirrim chainmail leggings "+
    "will protect the legs and feet.\n"));

    set_default_armour(25, A_LEGS | A_FEET, (({-2,3,-1})), 0);

    add_prop(GONDOR_M_ROHIRRIM_NO_SELL, 1);
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_ARMOUR(25, A_LEGS));
    add_prop(OBJ_I_VOLUME, 1700);
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(25)+random(100)-50);
}
