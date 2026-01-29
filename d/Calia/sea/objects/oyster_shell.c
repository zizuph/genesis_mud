/*
*
    Empty oyster shell
*/

inherit "/std/object";
#include <stdproperties.h>
#include <macros.h>

void
create_object()
{
    set_name(({"shell", "oyster shell", "empty shell"}));
    set_adj(({"empty", "oyster"}));
    set_short("oyster shell");
    set_pshort("oyster shells");
    set_long("This is just an empty grey oyster shell.\n");
    add_prop(OBJ_I_VALUE, 0);
    add_prop(OBJ_I_WEIGHT, 15);
    add_prop(OBJ_I_VOLUME, 25);
}
