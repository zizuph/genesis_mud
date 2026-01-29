/* Boots for Maen, Gwyneth, June 1999 */

inherit "/std/armour";
#include <wa_types.h>
#include <stdproperties.h>

void
create_armour()
{
    set_name("boots");
    set_pname("pairs of boots");
    add_name("pair of boots");
    set_adj("leather");
    add_adj("soft");
    set_short("soft leather boots");
    set_long("These boots are made of soft deerskin. They are perfect " + 
        "for wearing in a city, but would soon fall apart with serious " + 
        "travel.\n");
    set_ac(1);
    set_at(A_FEET);
    add_prop(OBJ_I_VOLUME, 100);
}
