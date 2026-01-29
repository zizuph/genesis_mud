inherit "/std/weapon";
#include <wa_types.h>
#include <stdproperties.h>
#include <formulas.h>
#include <macros.h>

void
create_weapon()
{
    set_name("sword");
    set_adj("sharp");
    add_adj("metal");  /* added by Gorboth, July 2007 */

    set_short("sharp sword");
    set_default_weapon(27, 27, W_SWORD, W_SLASH | W_IMPALE, W_ANYH);
    set_long("It's bloodstained, just like if it came right off a battle.\n");
    add_prop(OBJ_I_VOLUME, 700);
}
