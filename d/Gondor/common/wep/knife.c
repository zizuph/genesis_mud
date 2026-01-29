/* A knife  */

inherit "/std/weapon";
inherit "/lib/keep";

#include <formulas.h>
#include <macros.h>
#include <stdproperties.h>
#include <wa_types.h>

#include "/d/Gondor/defs.h"

void
create_weapon()
{
    set_name("knife");
    set_pname("knives");
    set_short("sharp knife");
    set_pshort("sharp knives");
    set_adj("sharp");
    add_adj("steel");
    set_long("It is a very simple looking knife, with a wooden hilt and a sharp steel blade.\n");
    
    set_default_weapon(10,10,W_KNIFE,W_SLASH,W_ANYH,0);
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(10,10)+random(40));
}

