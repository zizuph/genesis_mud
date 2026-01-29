
#include <wa_types.h>

inherit "/std/weapon";

void
create_weapon()
{
    set_short("plain steel dagger");
    set_name("dagger");
    set_adj("plain");
    add_adj("steel");
    set_long("This is a plain solid dagger, made from steel " +
	     "without ornaments. It has been designed to be " +
	     "functional, nothing more.\n");
    set_default_weapon(12,8,W_KNIFE,W_SLASH | W_IMPALE, W_ANYH);
}
