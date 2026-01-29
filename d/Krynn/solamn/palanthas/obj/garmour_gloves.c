/* Mortis 09.2014
 *
 * Protective gloves worn by the constabulary in Palanthas.
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
    set_name("gloves");
    set_adj("studded");
    add_adj(({"grey"}));
    set_short("pair of studded grey gloves");
    set_pshort("pairs of studded grey gloves");
    set_long("Common issue gloves for guardsmen, they are grey leather with "
    + "white-enameled iron studs.\n");

    set_alarm(0.5, 0.0, &setup_gear());
}

void
setup_gear()
{
    set_ac(7);
    set_am(({1, -1, 0}));
    set_at(A_HANDS);

    add_prop(OBJ_I_VOLUME, 600 + random(100));
    add_prop(OBJ_I_WEIGHT, 800 + random(200));
    add_prop(OBJ_I_VALUE, 110 + random(50));
    add_prop(VK_NOBUY, 1);
}