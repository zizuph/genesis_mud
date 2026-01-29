/* Bracers for Jane the Mercenary, Gwyneth, June 1999 */

inherit "/std/armour";
inherit "/lib/keep";

#include <wa_types.h>
#include <stdproperties.h>

void
create_armour()
{
    set_name("bracers");
    set_adj("silvery");
    set_short("pair of silvery bracers");
    set_pshort("pairs of silvery bracers");
    set_long("These plate bracers are of excellent make, perhaps elvish. " + 
        "The metal is a high quality steel, and has a silvery gleam to it. " + 
        "They are polished to a bright shine, as if it were someone's most " + 
        "prized possession.\n");
    set_ac(40);
    set_at(A_ARMS);

    add_prop(OBJ_I_VOLUME, 700);
}
