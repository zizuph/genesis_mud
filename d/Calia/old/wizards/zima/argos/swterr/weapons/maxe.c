/* Axe of the Minotaur, Guardian of the Temple of Dephonia */
inherit "std/weapon";
#include <stdproperties.h>
#include <wa_types.h>
#include <macros.h>
 
void
create_weapon()
{
    set_name(({"minotaur axe","axe"}));
    set_adj("raven crested");
    set_short("minotaur axe");
    set_long(break_string(
             "A large silver axe with a twisted handle, it has a " +
             "crested raven etched on its wide blade.\n",70));
    set_hit(40);
    set_hands(W_NONE);
    set_pen(40);
 
    set_wt(W_AXE);
    set_dt(W_SLASH);
 
    add_prop(OBJ_I_WEIGHT, 3000);
    add_prop(OBJ_I_VOLUME, 3000);
}
