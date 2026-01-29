/* By Sarr 
 *  
 * Cotillion 2018-09-18
 * - Increased weight from 3kg. It's crystal and a full plate. 
 *   Shouldn't float!
 */
inherit "/std/armour";
#include "/d/Raumdor/defs.h"

void
create_armour()
{
    ::create_armour();
    set_name("fullplate");
    set_short("shimmering crystalline fullplate");
    add_name("plate");
    set_adj("shimmering");
    add_adj("crystalline");
    set_long("A very beautiful fullplate armour. It's interlocking " +
            "plates provide very good protection, while also providing light.\n");
    set_ac(40);
    set_at(A_TORSO | A_HEAD | A_LEGS | A_ARMS);
    add_prop(OBJ_I_VALUE, 2850);
    add_prop(OBJ_I_VOLUME, 9500);
    add_prop(OBJ_I_WEIGHT, 21000);

    add_prop(OBJ_I_LIGHT, 1);
    add_prop(OBJ_I_IS_MAGIC_ARMOUR, 1);
}
