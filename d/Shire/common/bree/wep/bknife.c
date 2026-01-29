inherit "/std/weapon";
inherit "/lib/keep";
#include "/d/Shire/sys/defs.h"
#include <macros.h>
#include <stdproperties.h>
#include <formulas.h>
#include <wa_types.h>


create_weapon()
{
    int randy;
    
    set_name(({"long-knife","knife"}));
    set_pname(({"long-knives","knives"}));
    set_short("shimmering long-knife");
    set_pshort("shimmering long-knives");
    set_adj(({"shimmering", "long"}));
    add_adj("metal");  /* added by Gorboth, July 2007 */
    set_long("This is a long knife, often used by hobbits. Since they are so small "
    +"they do not use swords. This knife is more like a short sword. It has "
    	    +"sharp edges and looks like a very fine weapon for hobbits.\n");
    	    
    randy = random(5);
    set_hit(17);
    set_pen(16);
    set_wt(W_KNIFE);
    set_dt(W_IMPALE | W_SLASH);
    set_hands(W_ANYH);
    
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(16,17));
    set_keep();
    
}
