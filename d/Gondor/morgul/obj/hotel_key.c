/* An wooden key for a hotel room in the Red Eye Inn. Olorin 930801 */
inherit "/std/key";

#include <stdproperties.h>

create_key()
{
    ::create_key();

    set_name("key");
    add_name("_the_key_to_the_red_eye_inn_");
    set_pname("keys");
    set_short("wooden key");
    set_pshort("wooden keys");
    set_adj(({"wooden", "small"}));
    set_long(break_string("It's a small wooden key. It doesn't look as if one "
    	+ "could use it to lock or unlock doors. The name 'RED EYE INN' "
    	+ "has been engraved on it.\n",75));

    add_prop(OBJ_I_VALUE, 0);
    add_prop(OBJ_I_WEIGHT, 250);
    add_prop(OBJ_I_VOLUME, 50);
    add_prop(OBJ_I_NO_DROP, "The innkeeper told you to keep the key! You cannot drop it!\n");
}
