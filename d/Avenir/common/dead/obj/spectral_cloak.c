// gossamer cape    /d/Avenir/common/dead/obj/spectral_cloak.c
// creator(s):      Lilith  Aug 2021
// purpose:         Gear for Spectral Guardian in the Catacombs.
// note:            This gleams with spectral energy.
//         Effects: AC and Magic Res are tied to the charge of the
//                  spectral crystals (0-4)
//       Drawbacks: When charge = 0 the cape is unusable for ~30mins
//    Requirements: 10% of mana
//    Assoc. Files: /d/Avenir/common/dead/mon/spectral_guardian

inherit "/std/armour";
#include "/d/Avenir/common/holm/holm.h"
#include <wa_types.h>
#include <formulas.h>

int charged =4;

string crystal_state()
{
	string str;
	switch (charged)
	{
	   case 0: 
	        str = "The clasp's crystals have a very faint glow. ";
			return str;
		    break;   
	   case 1: 
	        str = "The green energy of clasp's crystals seem to be "
			    +"flickering, as if it will soon fade. ";
	        return str;
			break;
	   case 2:
	        str = "The crystals on the clasp glow steadily with greenish "
			    +"spectral energy. ";
			return str;
			break;
	  case 3:
	        str = "The crystals on the clasp seem to glow with intense "
 			    +"dark energy. ";
		    return str;
			break;
	  case 4:
	        str = "The crystals on the clasp are a very dark green. They ";
                +"seem to pulse and thrum with spectral energy. ";
            break;
	}
    // Shouldn't get here, but just in case.	
    return "Crystals in the clasp glow faintly.\n";
}

void
create_armour()
{
    set_name("cape");
    add_name(({"cloak", "_Avenir_spectral_cape"}));
    set_short("gleaming gossamer cape");
    add_adj(({"gossamer", "spectral", "glowing", }));
    set_long ("A filmy gossamer cape that seems to float in the air. "
	    +"It glows a very eerie green colour. "
	    +"The most substantial part of it is the clasp, which "
		+"consists of a short chain with a glowing greenish crystal "
		+"at each end that is attached to the cloak. It feels very cold "
		+"to the touch.\n");
    set_at(A_ROBE);
    set_ac(20 + (charged * 2)); // max 28

}

varargs mixed 
query_magic_protection(string prop, object what)
{
	res = ((charged * 2) + 10);
    if (what == this_object())
    {
	    switch(prop)
        { 
            case MAGIC_I_RES_COLD:
			case MAGIC_I_RES_ELECTRICITY:
			case MAGIC_I_RES_FIRE:
                return ({ res, 1 });; 
            default:
              break;
        }
    }
    return ::query_magic_protection(prop, what);
}
