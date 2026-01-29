/* 
*  A sign letting people know that the Sparkle dock goes to 
*  Waterdeep now.
*  
*  Raymundo, 2019
*/
#include "/d/Faerun/defs.h"
#include "defs.h"
#include <macros.h>
#include <stdproperties.h>
#include <formulas.h>
#include <wa_types.h>


inherit "/std/object";
public void
create_object()
{
    setuid();
    seteuid(getuid());
    
    set_name("sign");
    add_name("_waterdeep_sign");
    add_name("pole");
    set_adj("construction");   
    set_adj("under");
    set_adj("large");
    set_short("lare pole with a sign on it");
    set_long("This is a " + query_short() + ". The pole has been sunk into "
        + "the road. It is sturdy as can "
        + "be, resistant to all manner of shaking and whatnot. There is a "
        + "sign attached to it.\n");
        
    add_item("sign", "There is writing you could likely read on the sign.");
    add_item("pole", "The pole is made of one solid piece of wood, probably "
        + "pine. It's about as big around as the last halfling you dated and "
        + "quite sturdy. It seems resistant to shaking and whatnot.\n");
    
    add_prop(OBJ_I_VOLUME, 40000);
    add_prop(OBJ_I_WEIGHT, 10000);
    add_prop(OBJ_M_NO_BUY, 1);
    add_prop(OBJ_I_VALUE, 10000000000);
    add_prop(OBJ_M_NO_GET, 1);
    
}

void
init()
{
    ::init();
    add_action("shake_sign", "shake");
    add_action("shake_sign", "whatnot");
  //  add_action("climb_sign", "climb");
    add_action("read_sign", "read");
}

//players can shake the sign. How fun.
mixed
shake_sign(string str)
{
    if(str == "sign" | str == "pole")
    {
        tell_room(E(TP), QCTNAME(TP) + " tries to shake the " + str + 
            " but it's resistant. Any fool could have seen that just by "
            + "looking at it!\n", TP);
        write("You try to shake the " + str + " but find that it's resistant. "
            + "Don't you feel silly?\n");
        return("");
    }
}


//looks pretty when you read it
mixed
read_sign(string str)
{
    if(str == "sign" | str == "writing" | str == "words")
    {
    write(""+
        "+------------------------------------------------+\n"+
        "|                                                |\n"+
        "|   Greetings, Travelers                         |\n"+             
        "|                                                |\n"+
        "|   Ships' passengers are fickle, always wanting |\n"+
        "|   something more than I am offering. Due to    |\n"+
        "|   intense demand, the Sparkle line will now    |\n"+
        "|   dock in Waterdeep, to the south.             |\n"+
        "|                                                |\n"+
        "|   I apologize for any inconvenience, but       |\n"+
        "|   look forward to accepting your fare in       |\n"+
        "|   Waterdeep!                                   |\n"+
        "|                                                |\n"+
        "|   -- Captain Waillan                           |\n"+
        "|                                                |\n"+
        "+------------------------------------------------+\n");
        return("");
    }
}





