
/* Black orbs, the "eyes" of raging avengers. 
   Can be sold for a nice price!

   Coded by Maniac, 18/12/95

   Updated into jewel for Smiths items, Maniac, 23/8/96
*/

inherit "/std/object";

#include <macros.h>
#include <stdproperties.h>

void
create_object()
{
    set_name("orb");
    set_adj("purple");
    set_long("A purple orb, seemingly made of a rock with unearthly origins. " +
        "It is dense yet clear, with a raging fire burning at its " +
        "core.\n"); 
    add_prop(OBJ_I_WEIGHT, 450);
    add_prop(OBJ_I_VOLUME, 450);
    add_prop(OBJ_I_VALUE, 1100);
}

string
query_smiths_item() {
   return "gondor_gem";
}

