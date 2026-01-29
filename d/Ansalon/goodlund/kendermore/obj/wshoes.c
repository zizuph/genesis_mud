/* Sandals for Sateela, Gwyneth, 06/16/99 */

inherit "/std/armour";
#include <wa_types.h>
#include <stdproperties.h>

void
create_armour()
{
    set_name("sandals");
    set_pname("pairs of sandals");
    add_name("pair of sandals");
    set_adj("leather");
    set_short("pair of leather sandals");
    set_pshort("pairs of leather sandals");
    set_long("This pair of elegant sandals has a hard base, with leather " +
        "straps that tie around the leg up to mid-calf.\n"); 
    set_ac(1);
    set_at(A_FEET);
    add_prop(OBJ_I_VOLUME, 100);
}
