// spectral boots  /d/Avenir/common/dead/obj/spectral_boots
// creator(s):      Lilith, Aug 2021 w/ help from Zizuph
// purpose:         Gear for Spectral Guardian
// notes:
//         Effects: 
//       Drawbacks:  
//    Requirements: 
//    Assoc. Files: /d/Avenir/common/dead/mon/spectral_guardian
// updates:
// to-do:    ZIZ:   leave no trace/footprints/so wearer cant be tracked(?)
//                    or something useful for monks? acro or unarmed aid?
//                  have AC reflect bonus based on charge?

inherit "/std/armour";
#include "/d/Avenir/common/holm/holm.h"
#include <wa_types.h>
#include <formulas.h>

int charged = 4;

string my_long()
{
	string gem;
    switch (charged)
    {
	    case 0: gem ="faint";
		  break;
		case 1: gem ="flickering";
	      break;
		case 2: gem ="steady";		
	      break;
		case 3: gem ="bright";
		  break;
		case 4: gem ="pulsing";
		  break;
		default:
		 gem = "faintest";
	}	 
		
	return "If a being was summoned from another plane of existance and "
	    +"happened to be wearing a pair of boots, they would probably "
        +"look something like these. It is difficult to call them boots "
        +"because they don't seem to have a hard edge or outline--rather "
        +"they look mostly like an afterimage of a pair of boots, glowing "
        +"with spectral green energy that flows and eddies around a " 
        +"large crystal resting atop the instep of each boot.\n "
		+"Right now, the crystal has a "+ gem +" glow to it.\n";
		
}

void
create_armour()
{
    set_name("spectral boots");
    add_name(({"_Avenir_spectral_boots", ""}));
    set_short("");
    add_adj(({"opaque", "translucent", "spectral"}));
    set_long (".\n");
    set_at(A_FEET);
    set_ac(38 +(charged)); // AC improves with charged status
    
}

