/* Navarre 25th June 2006, made it keepable */

inherit "/std/weapon";
inherit "/lib/keep";
#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>

create_weapon()
{
    set_name("warhammer");
    set_adj("large");
    add_adj("iron");
    set_short("large iron warhammer");
    set_long("This is a large dwarven warhammer, crafted from "+
      "iron. It is rather heavy, and you have no doubt that when "+
      "this weapon hits someone, it is likely to hurt them.\n");
    set_default_weapon(25,34,W_CLUB,W_BLUDGEON,W_ANYH);
    add_prop(OBJ_I_VOLUME, 6000);
    add_prop(OBJ_I_WEIGHT, 6000);
}
