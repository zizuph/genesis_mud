/* A stick  */

inherit "/std/weapon";
#include "/sys/stdproperties.h"
#include "/sys/wa_types.h"
#include "/sys/formulas.h"
#include <macros.h>

create_weapon()
{
    set_name("stick");
    set_pname("sticks");
    add_name("club");
    add_pname("clubs");
    set_short("wooden stick");
    set_pshort("wooden sticks");
    set_adj("big");
    add_adj("wooden");
    set_long(break_string("It is a big wooden stick. You might be able to use it as a club.\n",75));
    
    set_default_weapon(10,10,W_CLUB,W_BLUDGEON,W_ANYH,0);
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(10,10)+random(40)-20);
}
