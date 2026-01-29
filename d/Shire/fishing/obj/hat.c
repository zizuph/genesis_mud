inherit "/std/armour";
#include "/d/Shire/common/defs.h"
#include <stdproperties.h>
#include <wa_types.h>
#include <formulas.h>
#include <macros.h>

void create_armour()
{
    set_name("hat");
    add_adj(({"wide-brimmed","straw"}));
    set_short("wide-brimmed straw hat");
    set_pshort("wide-brimmed straw hats");
    set_long("This hat is made from pieces of straw woven together. It does not offer much protection in a fight, but would probably keep the sun off your neck and out of your face.\n");
    set_ac(5);
    set_am( ({ 0, 0, 0}) );
    set_at(A_HEAD);
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(5) - random(2));
    add_prop(OBJ_I_WEIGHT, 100 + random(50));
    add_prop(OBJ_I_VOLUME, 100 + random(20));
}
