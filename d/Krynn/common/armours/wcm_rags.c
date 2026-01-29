/* Wandering Cleric of Morgion's Rags/Cloak
 * by Teth, Feb 21 1997
 */


inherit "/std/armour";
#include "/d/Krynn/common/defs.h"
#include <wa_types.h>
#include <formulas.h>
#include <macros.h>

void
create_armour()
{
    set_name("cloak");
    set_pname("cloaks");
    set_short("ragged cloak");
    set_pshort("ragged cloaks");
    set_adj("ragged");
    add_adj("cloth");
    add_name(({"armour","robe"}));
    add_pname(({"armours","robes"}));
    set_ac(2);
    set_at(A_ROBE);
    set_long("This ragged cloak is made of aged and decaying cloth. " +
       "It is poor protection, but better than nothing. The smell of " +
       "disease rests upon it.\n");
    add_item("disease","It would be difficult to see a disease.\n");
    add_cmd_item(({"cloak","disease"}),"smell",
       "The smell of the disease on the cloak makes you ill.\n");

    add_prop(OBJ_I_VOLUME, 3300);
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_ARMOUR(2, A_ROBE));
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(2));
}

