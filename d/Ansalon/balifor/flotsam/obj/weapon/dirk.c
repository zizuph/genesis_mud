inherit "/std/weapon";

#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>

create_weapon()
{
    set_name("dirk");
    add_name("knife");
    add_pname("knives");
    set_adj("ordinary"); 
    set_short("ordinary dirk");    set_long("This is an ordinary dirk, often carried by " +
      "sailors and adventurers.\n");
    set_default_weapon(15,8,W_KNIFE,W_IMPALE,W_ANYH);
    add_prop(OBJ_I_VOLUME, 360);
    add_prop(OBJ_I_WEIGHT, 700);
}

