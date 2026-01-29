// spectral helm    /d/Avenir/common/dead/obj/spectral_helm.c
// creator(s):      Lilith  Aug 2021
// purpose:         Gear for Spectral Guardian
// note:            This gleams with spectral energy. 
//                  give magic protection, vulnerable to fire magic
//         Effects: Resists cold, death, electricity, life (+20), wearer is unscryable
//       Drawbacks: vulnerable to fire magic (-40)
//    Requirements: 
//    Assoc. Files: /d/Avenir/common/dead/mon/spectral_guardian

inherit "/std/armour";
#include "/d/Avenir/common/holm/holm.h"
#include <wa_types.h>
#include <formulas.h>

int charged;


string crystal_state()
{
	string str;
	switch (charged)
	{
	   case 0: 
	        str = "The helm's crystals have a very faint glow. ";
			return str;
		    break;   
	   case 1: 
	        str = "The green energy of helm's crystals seem to be "
			    +"flickering, as if it will soon fade. ";
	        return str;
			break;
	   case 2:
	        str = "The crystals on the helm glow steadily with greenish "
			    +"spectral energy. ";
			return str;
			break;
	  case 3:
	        str = "The crystals on the helm seem to pulse with intense "
 			    +"dark energy. ";
		    return str;
			break;
	  case 4:
	        str = "The crystals on the helm are a very dark green. They ";
                +"seem to pulse and thrum with spectral energy. ";
            break;
	}
    // Shouldn't get here, but just in case.	
    return "Crystals in the helm glow faintly.\n";
}

void
create_armour()
{
    set_name("helm");
    add_name(({"helmet", "_Avenir_spectral_helm"}));
    set_short("spectral dark helm");
    add_adj(({}));
    set_long ("");
    set_at(A_HEAD);
    set_ac(38 + charged);
	
	

//     add_prop(LIVE_M_NO_SCRY, "Eerie green spectral energy blinds you.\n");
    
}

varargs mixed 
query_magic_protection(string prop, object what)
{
    if (what == this_object())
    {
	    switch(prop)
        {   /* Mostly resistant to magic spells except fire  */
			case MAGIC_I_RES_FIRE:	// Fire is its vulnerability
			    return ({ -40, 1 }); 
            case MAGIC_I_RES_COLD:
			case MAGIC_I_RES_ELECTRICITY:
			case MAGIC_I_RES_LIFE:
            case MAGIC_I_RES_DEATH:
                return ({ 20, 1 });; 
            default:
              break;
        }
    }
    return ::query_magic_protection(prop, what);
}
