inherit "/std/armour";
#include <wa_types.h>
#include <formulas.h>
#include <stdproperties.h>
#include <macros.h>

void
create_armour()
{
    set_name("armour");
    set_default_armour(25, A_BODY);
    add_adj( ({ "black", "body" }) );
    set_short("black body armour");
    set_long("In this piece of armour a draconian would feel safe.\n");
    add_prop(OBJ_I_VOLUME, 3040);
}

