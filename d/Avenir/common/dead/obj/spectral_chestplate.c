// spectral chestplate  /d/Avenir/common/dead/obj/spectral_chestplate
// creator(s):          Lilith  01/18/97
// purpose:             Gear for the spectral guardians
// last update:          covers chest only
// note:                
// bug(s):
// to-do:


inherit "/std/armour";
inherit "/lib/keep";
#include "../dead.h"
#include "/d/Avenir/include/basic.h"
#include "/d/Avenir/include/relation.h"
#include <wa_types.h>
#include <ss_types.h>
#include <formulas.h>

#define SPECTRAL_PROP "_Avenir_i_wear_spectral_chest"

int charged = 4;  

string crystal_state()
{
	string str;
	if (charged)
	    str = "This crystal pulses with a bright greenish spectral energy.\n";
	else
		str = "The crystal has a very faint greenish glow to it.\n";
    return str;
}	
		
string my_short()
{
	string str;
	if (charged)
        str = "pulsing spectral chestplate";
   	else	
		str ="crystal-embedded leather harness";
    return str;
}	

string my_long()
{
	string str;
	if (charged)
		str = "that pulses with greenish spectral energy "
		    +"as through in time with a heart.";
	else
		str = "that has a faint glow.";		
	
    return "This is a chestplate that was once worn by "
	    +"a spectral guardian. At its center is a large "
		+"crystal "+ str +" Consisting  "
		+"almost entirely of energy, this armour has very "
		+"little detail or structure to it other than the "
		+"crystal and a leather harness used to hold it "
		+"over your chest.\n";
	
}


void config_harness()
{
	if (!charged)
	{	   
	   remove_adj(({"glowing", "spectral"}));
	   set_ac(35);

	}
	else
	{
        set_adj(({"glowing", "spectral"}));	
	    set_ac(40 + (charged * 2); // max 48
	}
	object wearer = query_worn();
	if (wearer)
	    wearer->update_armour(TO);
}	


void
create_armour()
{
    set_name("chestplate");
    add_name(({"_Avenir_spectral_chestplate", "breastplate", "harness"}));
    set_short(my_short);
    set_long(my_long);
    set_at(A_CHEST);
    config_harness();
}

