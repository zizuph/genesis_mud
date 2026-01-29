/* An wooden key for a hotel room in the Old Guesthouse. Olorin 920929 */
inherit "/std/key";

#include <stdproperties.h>

create_key()
{
    ::create_key();

    set_name("key");
    add_name("_the_key_to_the_old_guesthouse_");
    set_pname("keys");
    set_short("wooden key");
    set_pshort("wooden keys");
    set_adj(({"wooden", "small"}));
    set_long(break_string("It's a small wooden key. It doesn't look as if one "
    	+ "could use it to lock or unlock doors. The name 'The Old "
    	+ "Guesthouse' has been engraved on it.\n",70));

    add_prop(OBJ_I_VALUE, 60);
}
