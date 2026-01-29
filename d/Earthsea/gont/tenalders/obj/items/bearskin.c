/* the grizzly bear's skin
 * for the Ten Alders grizzly bear 
 * Amelia 6/30/97
*/

#pragma strict_types

inherit "/std/armour";

#include <stdproperties.h>
#include <wa_types.h>

public void
create_armour()
{
    set_name("skin");
    add_name("bearskin");
    set_adj(({ "furry", "brown", "bear" }));
    add_name("skin");
    set_at(A_ROBE);
    set_ac(10);
    set_short("brown furry bearskin");
    set_long("The skin from a grizzly bear. It is " +
        "covered with thick golden-brown fur. Wearing a " +
        "grizzly bearskin is said to increase your " +
        "courage.\n");
    add_prop(OBJ_I_WEIGHT, 1000);
    add_prop(OBJ_I_VOLUME, 1200);
    add_prop(OBJ_I_VALUE, 250);
}
