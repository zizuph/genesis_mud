/* lump - a lump of gold /Ashlar 3 May 97 */

inherit "/std/object";

#include <stdproperties.h>

void
create_object()
{
	set_name("lump");
    set_pname("lumps");
    set_adj("gold");

    set_short("lump of gold");
    set_pshort("lumps of gold");

    set_long("The gold looks pure, so this lump is probably worth " +
        "quite a lot.\n");

    add_prop(OBJ_I_WEIGHT, 220);
    add_prop(OBJ_I_VALUE, 10*12*12);    /* 10 gold coins */
}

