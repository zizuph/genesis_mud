/* A stiletto  */

inherit "/std/weapon";
#include <stdproperties.h>
#include <wa_types.h>
#include <formulas.h>
#include <macros.h>

void
create_weapon()
{
    set_name("stiletto");
    set_pname("stilettos");
    add_pname("knives");
    add_pname("daggers");
    add_name("knife");
    add_name("dagger");
    set_short("steel shining stiletto");
    set_pshort("steel shining stilettos");
    set_adj("steel");
    add_adj("shining");
    set_long(break_string("The fine blade picks up all the " +
        "light in the room, reflecting it off its well-crafted " +
        "edges and planes. It tapers to a fine point. The handle  " +
        "is bone and obsidian, faceted to sparkle, but also to " +
        "improve the grip.\n",78));

    set_default_weapon(14,16,W_KNIFE,W_SLASH|W_IMPALE,W_LEFT,0);
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(14,16)+random(80)-10);
    add_prop(OBJ_I_WEIGHT, 1200);
}
