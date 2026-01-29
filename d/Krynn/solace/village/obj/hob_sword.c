inherit "/std/weapon";
#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>

void
create_weapon()
{
    set_name("sword");
    set_adj("evil");
    set_long("It's a sword from an evil hobgoblin.\n");
    set_default_weapon(25, 26, W_SWORD, W_SLASH | W_IMPALE, W_ANYH);

    add_prop(OBJ_I_VOLUME, 2500);
}

string 	query_recover() { return MASTER + ":" + query_wep_recover(); }
void	init_recover(string arg) { init_wep_recover(arg); }
