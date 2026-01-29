inherit "/std/weapon";
#include "/d/Shire/common/defs.h"
#include <macros.h>
#include <stdproperties.h>
#include <formulas.h>
#include <wa_types.h>


create_weapon()
{
    int randy;
    
    set_name(({"axe","waraxe"}));
    set_pname(({"axes","waraxes"}));
    set_short("sharp axe");
    set_pshort("sharp axes");
    set_adj(({"sharp", ""}));
    add_adj("metal");  /* added by Gorboth, July 2007 */
    set_long("This is a sharp axe, often used by dwarves. Since they are so strong "
    	    +"they can use heavy weapons. This axe is quite sharp but heavy. It has "
    	    +"sharp edges and looks like a very fine weapon for dwarves.\n");
    	    
    randy = random(5);
    set_hit(17);
    set_pen(20);
    set_wt(W_AXE);
    set_dt(W_BLUDGEON | W_SLASH);
    set_hands(W_BOTH);
    
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(20,17));
   add_prop(OBJ_I_WEIGHT, 500);
    add_prop(OBJ_I_VOLUME, 300);
    
}
