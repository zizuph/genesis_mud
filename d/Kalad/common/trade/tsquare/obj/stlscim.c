inherit "/std/weapon";
#include "/sys/stdproperties.h"
#include <wa_types.h>

void
create_weapon()
{
set_name( ({"scimitar", "sword"}) );
set_short("steel scimitar");
set_pshort("steel scimitars");
set_adj( ({"steel"}) );
set_long("This is a finely crafted weapon of steel, made from the "
        +"steel mined in the mountains near Kabal.\n");
set_hit (25);
set_pen (30);
set_wt(W_SWORD);
set_dt(W_SLASH | W_IMPALE);
set_hands(W_ANYH);
add_prop(OBJ_I_VALUE,600);
}
