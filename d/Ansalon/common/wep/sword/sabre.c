#pragma strict_types
inherit "/std/weapon";
inherit "/lib/keep";
#include <wa_types.h>
#include <stdproperties.h>

void
create_weapon()
{
    set_name(({"sword","sabre"}));
    set_adj("dull");
    add_adj("metal");  /* added by Gorboth, July 2007 */
    set_short("dull sabre");
    set_long("This is a heavy, slightly curved, one-edged " +
	"sword, that has gone slightly dull due to lack of " +
	"tending.\n");
    set_default_weapon(20,15,W_SWORD,W_SLASH | W_IMPALE, W_ANYH);
    update_prop_settings();
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT)/11);
}
