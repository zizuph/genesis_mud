
/* Black orbs, the "eyes" of furious avengers. 
   Can be sold for a nice price!

   Coded by Maniac, 18/12/95

   Made as jewels for smiths, Maniac, 23/8/96 
*/

inherit "/std/object";

#include <macros.h>
#include <stdproperties.h>

void
create_object()
{
    set_name("orb");
    set_adj("red");
    set_long("A red orb, seemingly made of a rock with unearthly origins. " +
        "It is dense yet clear, with a furious fire burning at its " +
        "core.\n"); 
    add_prop(OBJ_I_WEIGHT, 400);
    add_prop(OBJ_I_VOLUME, 400);
    add_prop(OBJ_I_VALUE, 900);
}


string
query_smiths_item() 
{
   return "gondor_gem";
}

