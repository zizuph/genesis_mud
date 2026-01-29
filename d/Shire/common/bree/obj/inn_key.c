/* An wooden key for a hotel room in the Old Guesthouse. Olorin 920929 */
/* Ruthlessly stolen by Dunstable for use in the Prancing Pony. */
/* September, 1994 */
inherit "/std/key";

#include <stdproperties.h>

create_key()
{
    ::create_key();

    set_name("key");
    add_name("inn_key");
    set_pname("keys");
    set_short("wooden key");
    set_pshort("wooden keys");
    set_adj(({"wooden", "short"}));
    set_long(break_string("It's a short wooden key. It doesn't look as if one "
    	+ "could use it to lock or unlock doors. The name 'The Prancing "
    	+ "Pony' has been engraved on it.\n",70));

    add_prop(OBJ_I_VALUE, 60);
    add_prop(OBJ_I_WEIGHT, 100);
   add_prop(OBJ_I_VOLUME, 100);
}
