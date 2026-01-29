/* A hatchet  */

inherit "/std/weapon";
#include "/sys/stdproperties.h"
#include "/sys/wa_types.h"
#include "/sys/formulas.h"
#include <macros.h>

create_weapon()
{
    set_name("hatchet");
    set_pname("hatchets");
    add_name("axe");
    add_pname("axes");
    set_short("small hatchet");
    set_pshort("small hatchets");
    set_adj("small");
    add_adj("steel");
    set_long(break_string("It is a small steel hatchet with a wooden handle. You might be able to use it as an axe.\n",75));
    
    set_default_weapon(10,10,W_AXE,W_SLASH,W_ANYH,0);
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(10,10)+random(40)-20);
}
