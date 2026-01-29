/* Leather vest for Maen, Gwyneth, June 1999 */

inherit "/std/armour";
#include <wa_types.h>
#include <stdproperties.h>

void
create_armour()
{
    set_name("vest");
    set_adj("leather");
    set_short("leather vest");
    set_long("This is a vest of soft deer skin. It is more for decoration " + 
        "than for protection.\n");
    set_ac(5);
    set_at(A_BODY);
    add_prop(OBJ_I_VOLUME, 1000);
}

