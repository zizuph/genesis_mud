// One of the powders found in the toolshed.
// It is a red-herring, and can foil attempts to
// make thermite for the cottage chest quest.

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
        " [the] [pinch] [of] [black] 'powder' / 'gunpowder'", str))
	{
        notify_fail(capitalize(query_verb()) +" what?\n");
        return 0;
    }		
	
    TP->catch_msg("You light the "+ short() +", causing a small "+
        "explosion! Ouch!\n");
	say(QCTNAME(TP) + " sets off a chemical reaction that causes "+
          "a small explosion!\n");	   
    TP->heal_hp(-(TP->query_hp() / 7)); // hurts, but not too much
    set_alarm(1.0, 0.0, &remove_object());	
    return 1;
}

void
create_object()
{
     set_name("powder");
     add_name(({"gunpowder", "safe_gunpowder", "pinch"}));
     set_short("pinch of black powder");
	 set_pshort("pinches of black powder");
     set_long("A strange black powder that smells slightly sulphurous. "+
         "It looks like it is a mixture of charcoal and saltpeter. "+
		 "You've heard a rumor that black powders like this can "+
		 "cause explosions, so be careful.\n");

     add_adj("black");
     add_prop(OBJ_I_WEIGHT, 10);
     add_prop(OBJ_I_VOLUME, 2);

}
     
	 
void
init()
{
	 ::init();
     add_action("do_splode",    "burn");
	 add_action("do_splode",    "ignite");
	 
}