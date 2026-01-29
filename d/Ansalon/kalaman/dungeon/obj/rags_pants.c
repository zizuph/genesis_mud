/*
 * Prison Rags
 */
inherit "/std/armour";
#include <wa_types.h>
#include <formulas.h>
#include <stdproperties.h>
#include <macros.h>
#include "/d/Ansalon/kalaman/local.h"

void
create_armour()
{
    set_name("pants");
    add_name("_prison_rags_");
    set_ac(0);
    set_at(A_LEGS);
    set_am( ({ 5, -3, -2 }) );
    set_adj("dirty");
    set_short("pair of dirty pants");
    set_pshort("pairs of dirty pants");
    set_long("This is a pair of extremely thorn and dirty pants. They " +
      "might at some time have been quite ordinary pants but years of " +
      "usage and never any fixing has left them in a rather sad state.\n");
    add_prop(OBJ_I_VOLUME, 50);
    add_prop(OBJ_I_WEIGHT, 1);
    add_prop(OBJ_I_VALUE, 1);
    add_prop(KALAMAN_NOBUY,1);
}

