inherit "/std/weapon";

#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>

create_weapon()
{
    set_name("mace");
    set_adj("shiny");
    add_adj("spiked");
    add_adj("metal");  /* added by Gorboth, July 2007 */
    set_short("shiny spiked mace");
    set_long("This spiked mace is a favoured weapon of people who just enjoy using " +
      "their brute strength to bludgeon their enemies down, and by the look of its large shiny " +
      "head, you do not doubt it would really pack a whallop.\n");
    set_default_weapon(25,34,W_CLUB,W_BLUDGEON,W_ANYH);
    add_prop(OBJ_I_VOLUME, 6000);
    add_prop(OBJ_I_WEIGHT, 6000);
}
