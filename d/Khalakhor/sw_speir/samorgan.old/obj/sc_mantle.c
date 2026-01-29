/* This mantle is to resemble
 * the Eil-Galaith guild item -for npcs
 * Damaris 02/2001
 */
 

#pragma strict_types

inherit "/std/object";
inherit "/lib/wearable_item";

#include <language.h>
#include <macros.h>
#include <wa_types.h>

public void
create_object()
{
    set_name( ({"mantle","tunic","shirt","clothing"}) );
    add_adj("wool");
    set_short("saffron and cerulean mantle");
    set_long("This soft woolen mantle is commonly worn by members " +
      "of the Eil-Galaith. The frills and shoulders of the mantle " +
      "have been dyed saffron and cerulean and the torso has been coloured " +
      "saffron and cerulean as well.\n");

    set_layers(1);
    set_looseness(10);
    set_wf(this_object());
    set_slots(A_BODY | A_ARMS);

    add_prop(OBJ_M_NO_SELL, "The shopkeeper finds it uninteresting.\n");
    add_prop(OBJ_M_NO_STEAL, 1);
    add_prop(OBJ_I_WEIGHT, 400);
    add_prop(OBJ_I_VOLUME, 1200);
    add_prop(OBJ_I_VALUE, 100);
}
