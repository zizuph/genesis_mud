/* Boots found in Kendermore, Gwyneth, July 1999 */

inherit "/std/armour";
#include <wa_types.h>
#include <stdproperties.h>

void
create_armour()
{
    set_name("boots");
    set_pname("pairs of boots");
    add_name("pair of boots");
    set_adj("night-blue");
    add_adj("gold-trimmed");
    set_short("pair of night-blue gold-trimmed boots");
    set_pshort("pairs of night-blue gold-trimmed boots");
    set_long("These are a pair of night-blue boots with gold trim. The " + 
        "material is a thin metallic cloth. They don't provide very " + 
        "much protection, but the effect of the metallic blue against " + 
        "the gold is very striking.\n");
    set_ac(8);
    set_at(A_FEET);
    add_prop(OBJ_I_VOLUME, 300);
}
