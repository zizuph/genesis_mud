/* handaxe  */

inherit "/std/weapon";
#include <wa_types.h>
#include <formulas.h>
#include <stdproperties.h>
#include <macros.h>
#include "/d/Gondor/defs.h"

void
create_weapon() 
{
    set_name("axe");
    set_adj("huge");
    set_short("huge axe");
    set_pshort("axes");
    set_long("This axe is a huge axe, not the axe of a fighter more "+
	"like of the woods man, or the working dwarf, though this "+
	"axe looks like the work of man.\n");

    set_default_weapon(13,17,W_AXE,W_SLASH,W_BOTH,0);
    add_prop(OBJ_I_WEIGHT,7000);
    add_prop(OBJ_I_VOLUME,3400);
    add_prop(OBJ_I_VALUE,F_VALUE_WEAPON(13,17)+random(200)-100);
}
