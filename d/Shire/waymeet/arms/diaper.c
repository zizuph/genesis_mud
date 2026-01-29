/*
 * A diaper for hobbit children.
 * Raymundo, Feb 2020
 */

#include "/d/Shire/sys/defs.h"
#include <formulas.h>
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <wa_types.h>

inherit "/std/armour";
inherit "/lib/keep";

#define AC  1
#define DIAPER_SUBLOC 	"_diaper_subloc_"
create_armour() 
{
    add_name(({"diaper"}));
    
    add_adj(({"white","cloth"}));
    set_short("white cloth diaper");
   
    set_long("This diaper is the kind of thing parents wrap around "
		+ "their childrens' waists so the kids don't make a mess all "
		+ "over the floor. It's made out of soft cloth so as not to "
		+ "irritate the childrens' soft skin.\n");
    set_default_armour(AC,A_WAIST,({0,0,0}),0);
    
    set_ac(AC);
	set_af(TO);
    add_prop(OBJ_I_WEIGHT,250);
    add_prop(OBJ_I_VOLUME,1000);
    add_prop(OBJ_I_VALUE,100);
    set_keep(0);
}


string query_recover()
{
    return MASTER + ":" + query_arm_recover();
}


void init_recover(string arg)
{
    init_arm_recover(arg);
}

public mixed
wear(object obj)
{
	if(wearer!=environment(TO))
	{
		return 0;
	}
	write("You wrap the " + query_short() + " around your waist.\n");
	say(QCTNAME(TP) + " wraps the " + query_short() + " around "
		+ HIS_HER(TP) +  " waist.\n");
	TP->add_subloc(DIAPER_SUBLOC, TO);
	return 1;
}

public mixed
remove(object obj)
{
	if(wearer!=environment(TO))
	{
		return 0;
	}
	wearer->catch_msg("You unwrap the " + query_short() 
		+ " from around your waist.\n");
	tell_room(environment(wearer), QCTNAME(wearer) + " unwraps the "
		+ query_short() + " from around " + HIS_HER(wearer) 
		+ " waist.\n", wearer);
	TP->remove_subloc(DIAPER_SUBLOC, TO);
	return 1;
}

public string
show_subloc(string subloc, object on, object for_obj)
{
	string data;
	if((on->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS)) || (subloc != DIAPER_SUBLOC))
	{
		return TP->show_subloc(subloc, on, for_obj);
	}
	if (for_obj == on) 
	{
		data = ("You look like a baby in your " 
			+ query_short() + ".\n");
	}
	else
	{
		data =  (CAP(HE_SHE(on)) + " looks like a baby in " +
			HIS_HER(on) + " " + query_short()
			+ ".\n");
	}
	return data;

}

public void
leave_env(object from, object to)
{
    TP->remove_subloc(DIAPER_SUBLOC, TO);
    ::leave_env(from, to);
}		


