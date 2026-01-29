/* personalized gin.--Raymundo, dec 2018
 */
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
        add_name("gin");
        add_name("glass of gin");
        set_pname("glasses of gin");
      
        
        set_short("glass of " + name() + "'s gin");
        set_pshort("glasses of " + name() +"'s gin");
        set_adj(adj());
        set_long("This is straight sided small glass, sometimes called "
            + "a rocks glass. Through the opening at the top of the glass "
            + "you can smell the fragerance of this " + name() 
            + "'s gin. It's completely clear and seems to "
            + "shimmer and sparkle in the light. "
            + "It comes in a straight sided rocks glass "
            + "with a picture of a " + adj() + " on it.\n");
            
       
            
        
        set_soft_amount(50);
        set_alco_amount(80);
        add_prop(OBJ_I_VALUE,500);
}
