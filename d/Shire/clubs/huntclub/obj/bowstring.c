/*
 * Steel bowstring for bows
 * -- Finwe, June 2004
 */
inherit "/std/bowstring";
#include <stdproperties.h>
#include <macros.h>

void
create_bowstring()
{
    set_name("bowstring");
    add_name("string");
    set_adj("thin");
    set_long("This is a thin steel bowstring. It is made from a length " +
        "of steel that has been twisted and polished until it is smooth " +
        "and long. You may <string bow> or <unstring bow> with this " +
        "bowstring as necessary.\n");
    add_prop(OBJ_I_VALUE, 25);
}
