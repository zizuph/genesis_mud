/*Personalized Brandy.--Raymundo, dec 2018
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
string drink_msg;
void
create_p_drink()
{
        set_name(name());
        add_name("brandy");
        add_name("snifter of brandy");
        set_pname("snifters of brandy");
      
        
        set_short("snifter of " + name() + "'s brandy");
        set_pshort("snifters of " + name() +"'s brandy");

        set_adj(adj());
        set_long("This is snifter, designed to maximize the surface area of "
            + "the brandy to help as much of the fragerance escape at once, "
            + "and then the snifter narrows at the top, directing all that "
            + "fragerance to your nose, so you can really appreciate the "
            + "craftsmanship that goes into creating " + name() 
            + "'s brandy. It's dark gold, almost brown and seems to "
            + "shimmer and sparkle in the light. "
            + "It comes in snifter with a picture of a " + adj() + " on it.\n"
            + "You could probably sniff and sip the brandy.\n");
            
       
   
        
        set_soft_amount(50);
        set_alco_amount(80);
        add_prop(OBJ_I_VALUE,500);
}

void
init()
{
    ::init();
    add_action("sniff_brandy", "sniff");
    add_action("sip_brandy", "sip");
}

int
sniff_brandy(string str)
{
    if(str == "brandy" | str == "snifter" | str == query_short())
    {
    tell_room(environment(TP), QCTNAME(TP) + " lifts the " + query_short() + 
        " to " + HIS_HER(TP) + " nose and inhales the complex aromas of the "
        + "drink.\n" + QCTNAME(TP) + " smiles contentedly, knowing what "
        + "true luxury is.\n", TP);
    write("You lift the " + query_short() + " to your nose and inhale the "
        + "complex aromas of the drink.\nYou smile contentedly, knowing what "
        + "true luxury is.\n");
    return(1);
    }
	else
	{
		return 0;
	}
}

int
sip_brandy(string str)
{
    if(str == "brandy" | str == "snifter" | str == query_short())
    {
       tell_room(environment(TP), QCTNAME(TP) + " sips brandy from the "
            + query_short() + ", enjoying it immensely.\n", TP);
        write("You sip brandy from the " + query_short() + ", "
            + "enjoying it immensely.\n");
        return(1);
    }
    else
	{
		return 0;
	}
}
    
