/* Mortis 09.2014
 *
 * Standard greaves worn by the constabulary in Palanthas.
 *
 */

inherit "/std/armour";
inherit "/lib/keep";

#include <macros.h>
#include <wa_types.h>
#include "../local.h"

#define VK_NOBUY                    "_vkeep_shop_no_buy"

void setup_gear();

public void
create_armour()
{
    set_name("greaves");
    set_adj("plate");
    add_adj(({"chain", "and"}));
    set_short("pair of plate and chain greaves");
    set_pshort("pairs of plate and chain greaves");
    set_long("Very fine and small steel rings have been used in the "
    + "construction of these greaves. Leather straps line the inner thighs "
    + "keeping the fitting snug, while thin steel plates line the outer for "
    + "stiff protection.\n");

    set_alarm(0.5, 0.0, "setup_gear");
}

void
setup_gear()
{
    set_ac(30 + random(2));
    set_am(({-2, 0, 2}));
    set_at(A_LEGS);

    add_prop(OBJ_I_VOLUME, 4700 + random(1450));
    add_prop(OBJ_I_WEIGHT, 3300 + random(2000));
    add_prop(VK_NOBUY, 1);
}