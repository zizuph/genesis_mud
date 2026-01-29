/*
 * Coarse bowstring for bows
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
    set_adj("coarse");
    set_long("This is a coarse bowstring. It is woven from some coarse " +
        "yarn and wound tightly. You may <string bow> with this bowstring " +
        "if necessary.\n");
    add_prop(OBJ_I_VALUE, 50);
}
