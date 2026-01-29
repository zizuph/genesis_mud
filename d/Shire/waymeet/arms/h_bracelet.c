/*
 * A bracelet.
 * Raymundo, Feb 2020
 */

#include "/d/Shire/sys/defs.h"
#include <formulas.h>
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <wa_types.h>
#include <const.h>

inherit "/std/armour";
inherit "/lib/keep";

#define AC  1
#define ADJ1 	"decorative"
#define ADJ2	"bronze"
#define NAME	"bracelet"

create_armour() 
{
	
    set_name(NAME);
    add_adj(ADJ1);
    add_adj(ADJ2);
    add_name("jewelry");
    
    set_short(ADJ1 + " " + ADJ2 + " " + NAME);
   
    set_long("This " + query_short() + " is made of bronze. "
		+ "It has been etched with runes, that are both functional "
		+ "and decorative. It looks quite large, as if it were made "
		+ "for a man's wrist.\n");
    set_default_armour(AC,A_ANY_WRIST,({0,0,0}),0);
    add_item( ({"rune", "runes"}), "@@read_runes@@");
    add_cmd_item( ({"rune", "runes"}), "read", "@@read_runes@@");
    
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
	if(!TP->query_gender() == G_MALE)
	{
		return("This " + query_short() + " was clearly made "
			+ "for a man's wrist. As much as you'd like to "
			+ "wear it, it would just fall off.\n");
		
	}
		write("You wear the " + query_short() + " on your "
			+ "manly wrist.\n");
		say(QCTNAME(TP) + " looks a little more manly as he "
			+ "wears the " + query_short() + " on his "
			+ "wrist.\n");
    return 1;
}

string
read_runes()
{
    return("The runes read:\nTo my beloved husband.\n\nLove,\n"
		+"Your faithful wife.\n");
}
		


