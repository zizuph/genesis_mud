/*
 * Common leather tuniuc
 * - Finwe, November 2006
 */
inherit "/std/armour";

#include "/d/Faerun/defs.h"
#include "defs.h"
#include <macros.h>
#include <stdproperties.h>
#include <formulas.h>
#include <wa_types.h>

void
create_armour()
{
    set_name("tunic");
    set_pname("tunics");
    set_adj("plain");
    set_adj("cotton");
    set_short("plain cotton tunic");
    set_long("This is a plain cotton tunic worn by commoners. It is " +
        "sleeveless and extends down to the knees. The tunic is woven from " +
        "thick threads and looks dirty.\n");
    	       
    set_at(A_BODY);
    set_ac(8);
    set_am(({ 0,0,0}));
    
    add_prop(OBJ_I_VALUE, 200);
    add_prop(OBJ_I_VOLUME, 4000);
    add_prop(OBJ_I_WEIGHT, 2000);
    
}
