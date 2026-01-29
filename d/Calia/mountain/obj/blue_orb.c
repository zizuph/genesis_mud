
/* Black orbs, the "eyes" of wrathful avengers. 
   Can be sold for a nice price!

   Coded by Maniac, 18/12/95

   Updated to be usable as Smiths jewels, Maniac, 23/8/96
*/

inherit "/std/object";

#include <macros.h>
#include <stdproperties.h>

void
create_object()
{
    set_name("orb");
    set_adj("blue");
    set_long("A blue orb, seemingly made of a rock with unearthly origins. " +
        "It is dense yet clear, with a wrathful fire burning at its " +
        "core.\n"); 
    add_prop(OBJ_I_WEIGHT, 350);
    add_prop(OBJ_I_VOLUME, 350);
    add_prop(OBJ_I_VALUE, 700);
}

string
query_smiths_item() {
   return "gondor_gem";
}

