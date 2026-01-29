/* personalized vodka.--Raymundo, dec 2018 */

#include <stdproperties.h>
#include "/d/Shire/eastroad/western/local.h"
#include "/d/Shire/sys/defs.h"

inherit "/std/drink";
inherit EAST_R_DIR + "supplies/p_drink_base.c"; 
 
string
name()
{
    return(this_player()->query_name());
}
 
string 
adj()
{
    return(this_player()->query_nonmet_name());
}
void
create_p_drink()
{
        set_name(name());
        add_name("vodka");
        add_name("shot of vodka");
        set_pname("shots of vodka");
      
        
        set_short("glass of " + name() + "'s vodka");
        set_pshort("glasses of " + name() +"'s vodka");
        set_adj(adj());
        set_long("This is very small, narrow glass, sometimes called "
            + "a shot glass. Through the opening at the top of the glass "
            + "you can smell almost nothing, except just a hint of alcohol "
            + "from the " + name() 
            + "'s vodka. It's completely clear and seems to "
            + "shimmer and sparkle in the light. "
            + "It comes in shot glass with a picture of a " + adj()
            + " on it.\n");
            
       
            
        
        set_soft_amount(50);
        set_alco_amount(80);
        add_prop(OBJ_I_VALUE,500);
}
