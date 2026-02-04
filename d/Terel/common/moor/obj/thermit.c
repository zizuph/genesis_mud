// made by Sorgum in 1994
// Lilith, Jan 2022: getting the cottage chest/safe cracking quest done.
// Purpose:  This is part of the Cottage Chest quest. To break the lock  
//           on the chest the player needs thermite in the flower pot.          
//           Thermite is 3 parts iron oxide and one part aluminum.

inherit "/std/object";
#include <stdproperties.h>
#include "/d/Terel/include/Terel.h"

int
do_splode(string str)
{
    if (!strlen(str))
    {
        notify_fail(capitalize(query_verb()) +" what?\n");
        return 0;
    }		
	
    if (!parse_command(str, ({ }),
        " [the] [fine] [dark] 'powder' / 'compound' / 'thermite'", str))
	{
        notify_fail(capitalize(query_verb()) +" what?\n");
        return 0;
    }		
	
    TP->catch_msg("You light the "+ short() +", causing an "+
        "explosion! Ouch!\n");
	say(QCTNAME(TP) + " sets off a chemical reaction that causes "+
          "an explosion!\n");	   
    TP->heal_hp(-(TP->query_hp() / 3)); // hurts, but won't kill.
    set_alarm(1.0, 0.0, &remove_object());	
    return 1;
}


void
create_object()
{
     set_name("thermite");
     add_name(({"compound", "powder"}));
     set_short("thermite");
     add_name(({"_cottage_thermite"}));
     set_long("This is thermite, a fine, dark powder that "+
         "burns VERY hot when it is properly ignited.\n");
     set_adj(({"fine", "dark"}));
     add_prop(OBJ_I_WEIGHT, 10);
     add_prop(OBJ_I_VOLUME, 2);
     add_prop(OBJ_M_NO_DROP, 0);

}
     
void
init()
{
	 ::init();
     add_action("do_splode",    "burn");
	 add_action("do_splode",    "ignite");	 
}	 
