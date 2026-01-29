/* Personalized Whisky--Raymundo, dec 2018
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
        add_name("whisky");
        add_name("whiskey");
        set_pname("glasses of whisky");

        
        set_short("glass of " + name() + "'s whisky");
        set_pshort("glasses of " + name() +"'s whisky");
        set_adj(adj());
        set_long("This is a tulip shapped glass, designed to help one "
            + "notice every nuance of the fragerance of this " + name() 
            + "'s whisky. It's golden amber in colour and seems to "
            + "shimmer and sparkle in the light. Truly it is the water "
            + "of life. It comes in a tulip-shaped tasting glass "
            + "with a picture of a " + adj() + " on it.\n");
            
            
        
        set_soft_amount(50);
        set_alco_amount(80);
        add_prop(OBJ_I_VALUE,500);
}
