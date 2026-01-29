/* Weapon for the hermit in the Entwash.  Gorboth, Oct 1995 */

inherit "/std/weapon";

#include <formulas.h>
#include <macros.h>
#include <stdproperties.h>
#include <wa_types.h>

#include "/d/Gondor/defs.h"

void
create_weapon()
{
    set_name("thighbone");
    set_pname("thighbones");
    add_name(({"club", "bone"}));
    set_short("splintered thighbone");
    set_pshort("splintered thighbones");
    set_adj("old");
    set_long(BSN("This looks to have been the thighbone of some"
      + " bipedal creature. It is splintered along one end, making"
      + " it easy to grasp for use as a weapon."));

    set_default_weapon(10,10,W_CLUB,W_BLUDGEON,W_ANYH,0);
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(5,5)+random(20)-5);
}
