inherit "/std/weapon";
#include "/d/Shire/common/defs.h"
#include <macros.h>
#include <stdproperties.h>
#include <formulas.h>
#include <wa_types.h>


void
create_weapon()
{
    set_name(({"longsword","sword"}));
    set_pname(({"longswords","swords"}));
    set_short("sturdy longsword");
    set_pshort("sturdy longswords");
    set_adj(({"sturdy", "long"}));
    add_adj("metal");  /* added by Gorboth, July 2007 */
    set_long("This is a long sword, often used by humans. Since they are so sturdy "
    	    +"they make a nice sword. This sword is old and well used. It has "
    	    +"sharp edges and looks like a very fine weapon for outdoorsmen.\n");
    	    
    set_hit(29);
    set_pen(25);
    set_wt(W_SWORD);
    set_dt(W_SLASH);
    set_hands(W_ANYH);
    
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(29,25));
    
}
