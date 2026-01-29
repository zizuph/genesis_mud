/* RANGERS_OBJ + "bowstring.c"
 * Tigerlily, Jan. 1, 2005
 *     made for the ranger stores
 *
 */

inherit "/std/bowstring";

#include <stdproperties.h>
#include <macros.h>

void
create_bowstring()
{
    set_name("bowstring");
    set_adj("golden");
    set_short("golden bowstring");
    set_pshort("golden bowstrings");
    set_pname("bowstrings");
    set_long("This is a long bowstring made from a " +
        "single golden strand of elven hair. It is " +
        "very fine and strong.\n");
    add_prop(OBJ_I_VOLUME, 50);
    add_prop(OBJ_I_WEIGHT, 10);
}