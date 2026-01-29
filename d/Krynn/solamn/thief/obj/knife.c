/* created by Aridor, 03/15/94 */

inherit "/std/weapon";

#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>

create_weapon()
{
    set_name("knife");
    set_pname("knives");
    set_adj("large");
    set_short("large knife");
    set_pshort("large knives");
    set_long("This is a large knife, with a slim blade.\n");
    set_default_weapon(11, 8, W_KNIFE, W_IMPALE, W_ANYH);
    add_prop(OBJ_I_VOLUME, 50);
    add_prop(OBJ_I_WEIGHT, 500);
}

