inherit "/std/weapon";
#include <wa_types.h>
#include <stdproperties.h>
#include <formulas.h>
#include <macros.h>

void
create_weapon()
{
    set_name("axe");
    set_adj("small");
    add_adj("metal");  /* added by Gorboth, July 2007 */

    set_short("small axe");
    set_default_weapon(20, 22, W_AXE, W_SLASH, W_ANYH);
    set_long("It's a small battleaxe, small but yet sharp.\n");
    add_prop(OBJ_I_VOLUME, 258);
}
