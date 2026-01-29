/* 
 * Louie 2005
 * Designed by Anahita
 */

inherit "/std/armour";

#include "/d/Krynn/common/defs.h"
#include <wa_types.h>
#include <formulas.h>
#include <macros.h>

public void
create_armour()
{
    set_name("boots");
    set_pname("boots");
    add_name("armour");
    add_pname("armours");

    set_adj(({"skull","kender-hide"}));
    add_name(({"pair of boots","pair of skull boots"}));
    add_pname(({"pairs of boots","pairs of skull boots"}));
    set_short("pair of skull boots");
    set_pshort("pairs of skull boots");
    set_ac(30);
    set_at(A_FEET);
    set_long("Made from the finest kender-hide available, these "+
        "boots have been dyed midnight-blue.  "+
        "Bone fragments and beads form a large skull "+
        "on the side of each boot."+
        "\n");

    add_prop(OBJ_I_VOLUME, 1000);
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_ARMOUR(30, A_HEAD));
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(30));
}
