/* A knife on the ground */

inherit "/std/weapon";
#include "/sys/stdproperties.h"
#include "/sys/wa_types.h"
#include "/sys/formulas.h"
#include <macros.h>

void
create_weapon()
{
    set_name("knife"); set_pname("knives");
    set_short("small kitchen knife"); set_pshort("small kitchen knives");
    set_adj("small");
    set_adj("kitchen");
    set_long("It is a very simple looking knife, probably taken from a cook.\n");
    
    set_default_weapon(9,10,W_KNIFE,W_SLASH,W_LEFT,0);
    add_prop(OBJ_I_WEIGHT,400);
    add_prop(OBJ_I_VOLUME,200);
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(9,10)+random(10)-5);
}
