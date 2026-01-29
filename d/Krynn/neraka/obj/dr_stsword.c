inherit "/std/weapon";
#include <wa_types.h>
#include <stdproperties.h>
#include <formulas.h>
#include <macros.h>

void
create_weapon()
{
    set_name("sword");
    set_adj("standard");
    set_short("standard sword");
    set_default_weapon(21, 18, W_SWORD, W_SLASH | W_IMPALE, W_ANYH);
    set_long("This is the standard draconian sword, short but effective.\n");
    add_prop(OBJ_I_VOLUME, 470);
}
