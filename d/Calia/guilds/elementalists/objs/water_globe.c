
/* 
 *  Water Globe for the Elemental Clerics
 *  February, 2017
 */


inherit "/std/container";

#include <stdproperties.h>
#include <macros.h>
#include <cmdparse.h>
#include <formulas.h>
#include <composite.h>

#include "defs.h"

public string
long_descrip()
{
	if (TP->is_elemental_cleric())
	{
		return "This is a small water globe. You can put items inside of it and "+
        "have them delivered to someone with the kinisi prayer. If you no "+
        "longer want it, you can <squish globe> to get rid of it. NOTE: It "+
        "must be empty to squish it.\n";
    }
    else
    {
    	return "This is a small water globe. It can contain small items "+
    	"inside of it and was delivered to you by an Elemental Cleric. "+
    	"If you no longer want it, you can <squish globe> to get rid of "+
    	"it. NOTE: It must be empty to squish it.\n";
    }
}

void
create_container()
{
    set_name("globe");
    add_name("_cleric_water_globe");
    set_adj("water");
    add_adj("small");
    set_short("small water globe");
    set_long("@@long_descrip@@"); 

    add_prop(CONT_I_MAX_WEIGHT, 75000);
    add_prop(CONT_I_MAX_VOLUME, 75000);
    add_prop(CONT_I_WEIGHT, 2500);
    add_prop(CONT_I_VOLUME, 2500);
    add_prop(OBJ_M_NO_DROP, "You cannot drop the water globe.\n");
    add_prop(OBJ_M_NO_GIVE, "You cannot give the water globe away.\n");
    add_prop(OBJ_M_NO_STEAL, 1);
}

public int
do_squish(string str)
{
	if (!str || str != "globe")
	{
		notify_fail("Squish what?\n");
		return 0;
	}
	
	if (sizeof(all_inventory(this_object())))
	{
		write("You must empty the globe before squishing it.\n");
		return 1;
	}
	
	write("You squish the water globe between your hands and it vanishes!\n");
	this_object()->remove_object();
	return 1;
}

void
init()
{
	::init();
	add_action(do_squish,"squish");
}