/* The shield used by the guards in Vingaard Keep
 * by Teth, December 2, 1996
 * Modified June 19, 1998 to conform with updated man armour, Teth.
 */
/*
 * Added support for the commerce module in July 2002, by Boron
 * Added Keepable by Navarre 11th June 2006
 */
inherit "/std/armour";
inherit "/d/Genesis/lib/commodity";
inherit "/lib/keep";

#include <wa_types.h>
#include <formulas.h>

#include "../../local.h"

public void
create_armour()
{
    set_name("shield");
    set_pname("shields");
    add_name("armour");
    add_pname("armours");
    set_adj("solamnic");
    add_adj(({"heavy","steel"}));
    set_short("heavy solamnic shield");
    set_pshort("heavy solamnic shields");
    set_ac(34 + (random(2)));
    set_at(A_SHIELD);
    set_am( ({0,0,0}) );
    set_long("This heavy shield is made of Solamnian steel. " +
      "It is stamped, 'Vingaard Keep Armoury Standard Issue'. " +
      "This shield would be quite useful to someone fending " +
      "off attacks, even protecting the body and legs of the " +
      "wearer. It is an excellent shield, one of the best " +
      "available for purchase anywhere in the lands.\n");


    set_commodity_name ("s_shield"); // required to link this
                                  // object with the domain server
    set_commodity_value(F_VALUE_ARMOUR(34), 0);

    add_prop(OBJ_I_VOLUME, 4600);
    add_prop(OBJ_I_WEIGHT, 8000);
    add_prop(VK_NOBUY, 1);
}

public int *
query_shield_slots()
{
    return (::query_shield_slots() + ({ A_BODY, A_LEGS }) );
}
