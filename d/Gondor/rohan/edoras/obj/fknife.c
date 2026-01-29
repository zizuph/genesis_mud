/* A knife on the ground */

inherit "/std/weapon";
inherit "/lib/keep.c";

#include "/sys/stdproperties.h"
#include "/sys/wa_types.h"
#include "/sys/formulas.h"
#include <macros.h>

void
create_weapon()
{
    set_name("knife");
    set_pname(({"knives", "weapons", }));
    set_short("small knife");
    set_pshort("small knives");
    set_adj("small");
    set_long("It is a very simple looking knife, quite deadly though.\n");
    
    set_default_weapon(9,10,W_KNIFE,W_SLASH,W_LEFT,0);
    add_prop(OBJ_I_WEIGHT,400);
    add_prop(OBJ_I_VOLUME,200);
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(9,10)+random(10)-5);
}
