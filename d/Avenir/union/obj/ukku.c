/* Ingot of steel 
 * Quest item, making it autoloading.
 */
#pragma strict_types
inherit "/std/object";

#include <macros.h>
#include <stdproperties.h>


public void 
create_object()
{
    set_name("ingot");
    add_name(({"ukku", "steel", "_crucible_component"}));
    set_pname("ingots");
    set_short("ingot of ukku");
    set_pshort("ingots of ukku");
    add_adj(({"ukku", "steel"}));
    set_long("This is one of the most precious substances in "+
      "all of Sybarus. Ukku is an iron alloy which, when "+
      "forged correctly, forms the sharpest and most flexible "+
      "blades known to man: damask steel. It has been cast "+
      "into an ingot and stamped with a trefoil.\n");

    add_item(({"trefoil", "stamp", "mark", "marking"}),
      "It has been stamped with a trefoil, the symbol of Sybarus.\n");

    add_prop(OBJ_I_VALUE,  5000);
    add_prop(OBJ_I_VOLUME, 250);
    add_prop(OBJ_I_WEIGHT, 1000);
    add_prop(OBJ_M_NO_SELL, "Something prevents you from doing so.\n");
}

public string
query_auto_load(void)
{
    return MASTER + ":";
}
