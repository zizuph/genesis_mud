inherit "/std/armour";
#include <wa_types.h>
#include <formulas.h>
#include <stdproperties.h>
#include <macros.h>

create_armour()
{
    set_name("jerkin");
    set_short("leather jerkin");
    set_long("This leather jerkin is fashioned in a way " +
      "similar to a waistcoat, allowing freedom of movement " +
      "and a little bit of protection.\n");
    set_ac(4);
    set_am(({0,0,0}));
    set_at(A_ROBE);
    add_prop(OBJ_I_VALUE, 150);
    add_prop(OBJ_I_VOLUME, 400);
    add_prop(OBJ_I_WEIGHT, 500);
}
