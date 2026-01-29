
inherit "/std/weapon";

#include <wa_types.h>
#include <stdproperties.h>

nomask
create_weapon() 
{
    set_name("tooth");
    set_pname("teeth");
    set_adj("shark");
    set_short("shark tooth");
    set_pshort("shark teeth");
    set_long("This is a tooth from a great white shark.  It is very "+
        "sharp.\n");
    set_default_weapon(10, 10, W_KNIFE, W_SLASH, W_ANYH);
    add_prop(OBJ_I_VOLUME,450);
	add_prop(OBJ_I_WEIGHT,1400);
	add_prop(OBJ_I_VALUE, 200);
}
