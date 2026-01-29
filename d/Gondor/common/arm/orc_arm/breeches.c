/*  Armour coded by Arren, November 93 */

inherit "/std/armour";

#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <formulas.h>

#include "/d/Gondor/defs.h"

void
create_armour()
{
    set_name("pair of breeches");
    add_name("breeches");
    set_pname("pairs");
    add_pname("breecheses");
    set_adj("hairy");
    add_adj(({ "long", "orc", "beast" }));
    set_short("pair of hairy breeches");
    set_pshort("pairs of hairy breeches");
    set_long(BSN(
        "Long hairy breeches made of some unknown beast-fell. "
      + "They smell disgustingly."));

    set_default_armour(10, A_LEGS, ({ -1, 0, 1 }), 0);

    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_ARMOUR(10, A_LEGS)); 
    add_prop(OBJ_I_VOLUME, 900);
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(10)+random(20)-10);
}
