/* Personalized White Lightning--Raymundo, dec 2018
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
        add_name("white lightning");
        add_name("lightning");
        set_pname("glasses of white lightning");

        
        set_short("glass of " + name() + "'s white lightning");
        set_pshort("glasses of " + name() +"'s white lightning");
        set_adj(adj());
        set_long("This is white lightning, unaged whiskey. Made primarily "
            + "of fermented corn mash, this stuff could take the paint off "
            + "a barn. Drink this " + name() 
            + "'s white lightning quickly, and try not to notice the taste. "
            + "It's crystal clear in colour and seems to "
            + "shimmer and sparkle in the light. "
            + "It comes in a cheap shot glass "
            + "with a picture of a " + adj() + " on it.\n");
            
            
        
        set_soft_amount(50);
        set_alco_amount(80);
        add_prop(OBJ_I_VALUE,500);
}
