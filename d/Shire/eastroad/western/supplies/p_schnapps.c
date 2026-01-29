/* personalized Schnapps.--Raymundo, dec 2018
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
        add_name("schnapps");
        add_name("glass of schnapps");
        set_pname("glasss of schnapps");
      
        
        set_short("glass of " + name() + "'s schnapps");
        set_pshort("glasss of " + name() +"'s schnapps");
        set_adj(adj());
        set_long("This is a straight sided glass, sometimes called a rocks "
            + "glass. You smell aromas of peach coming from the " + name() 
            + "'s schnapps. The schnapps seems to "
            + "shimmer and sparkle in the light. "
            + "It comes in a rocks glass with a picture of a " + adj() + " on it.\n");
            
       
            
        
        set_soft_amount(50);
        set_alco_amount(80);
        add_prop(OBJ_I_VALUE,500);
}
