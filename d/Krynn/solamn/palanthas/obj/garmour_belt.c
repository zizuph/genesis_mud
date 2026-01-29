/* Mortis 09.2014
 *
 * Protective belt worn by the constabulary in Palanthas.
 *
 */

#include <macros.h>
#include <wa_types.h>
#include "../local.h"

inherit "/std/armour";
inherit "/lib/keep";

#define VK_NOBUY                    "_vkeep_shop_no_buy"

void setup_gear();

public void
create_armour()
{
    set_name("belt");
    set_adj("studded");
    add_adj(({"grey"}));
    set_short("studded grey belt");
    set_pshort("studded grey belts");
    set_long("Common issue belt for guardsmen, it is grey leather with "
    + "white-enameled iron studs.\n");

    set_alarm(0.5, 0.0, &setup_gear());
}

void
setup_gear()
{
    set_ac(4);
    set_am(({1, -1, 0}));
    set_at(A_WAIST);

    add_prop(OBJ_I_VOLUME, 100 + random(20));
    add_prop(OBJ_I_WEIGHT, 200 + random(40));
    add_prop(OBJ_I_VALUE, 60 + random(50));
    add_prop(VK_NOBUY, 1);
}