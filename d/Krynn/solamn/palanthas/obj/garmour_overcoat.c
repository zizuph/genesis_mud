/* Mortis 092.2014
 *
 * Heavy chainmail overcoat worn by the constabulary in Palanthas.
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
    set_name("overcoat");
    add_name("coat");
    set_adj("heavy");
    add_adj(({"chainmail"}));
    set_short("heavy chainmail overcoat");
    set_long("Sturdy, double-steel rings have been used in the construction "
    + "of this coat for added protection around the chest and thighs. Leather "
    + "pauldrons cover the shoulders, and leather side plates extend down "
    + "past the thighs for all over protection. It makes the wearer look "
    + "beefy and imposing.\n");

    set_alarm(0.5, 0.0, &setup_gear());
}

void
setup_gear()
{
    set_ac(8);
    set_am(({0, -1, 1}));
    set_at(A_ROBE);

    add_prop(OBJ_I_VOLUME, 3500 + random(550));
    add_prop(OBJ_I_WEIGHT, 1600 + random(800));
    add_prop(OBJ_I_VALUE, 475 + random(220));
    add_prop(VK_NOBUY, 1);
}
