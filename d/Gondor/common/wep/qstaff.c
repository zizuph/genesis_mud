/* A staff  */

inherit "/std/weapon";
#include "/sys/stdproperties.h"
#include "/sys/wa_types.h"
#include "/sys/formulas.h"
#include <macros.h>

create_weapon()
{
    set_name("staff");
    set_pname("staves");
    add_pname("staffs");
    add_name("polearm");
    set_short("wooden staff");
    set_pshort("wooden staves");
    set_adj("long");
    add_adj("wooden");
    set_long(break_string("It is a long wooden staff. You might be able to use it as a polearm.\n",75));
    
    set_default_weapon(10,10,W_POLEARM,W_BLUDGEON,W_BOTH,0);
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(10,10)+random(40)-20);
}
