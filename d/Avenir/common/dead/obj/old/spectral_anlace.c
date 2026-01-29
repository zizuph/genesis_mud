// spectral anlace       /d/Avenir/common/holm/dead/obj/spectral_anlace.c
// creator(s):           Lilith, July 2021
// purpose:              Gear for Spectral Guardians
// last update:          
//                        
// note: 
// bug(s):
// to-do:

inherit "/std/weapon";
inherit "/lib/keep";
#include "../dead.h"
#include "/d/Avenir/include/basic.h"
#include "/d/Avenir/include/relation.h"
#include <wa_types.h>
#include <ss_types.h>
#include <formulas.h>

#define SPECTRAL_PROP "_Avenir_i_wear_spectral_anlace"

int charged = 4;  // starts charged. will want a countdown for how long
                  // it lasts, maybe it loses charge after it is 
				  // worn for a period of time or takes x hits?
				  // is there a counter for that somewhere already in
				  // like with the wear and tear counter?
				  // then it will need a period of time to recharge...


string crystal_state()
{
	string str;
	if (charged)
	    str = "The crystal in the hilt of the anlace glows with a "
	          +"bright greenish spectral energy.\n";
	else
		str = "The crystal in the hilt has a very faint greenish glow to it.\n";
    return str;
}
	
string my_short()
{
	string str;
	if (charged)
        str = "spectral green anelas";
   	else	
		str ="spectral anelas";
    return str;
}	

string my_long()
{
	string str;
	
	string str;
	if (charged)
		str = "Once the possession of a spectral guardian, the blade "
            +"of this anelas is comprised entirely of spectral energy " 
            +"whose source is a large crystal glowing in the cupped "
            +"end of the bone hilt. The greenish glow is channeled "
			+"down through the center of the bone, flat and wide, and "
			+"tapers to an infinitessimal point. Obviously magical "
			+"in nature, it is doubtful that anything this blade " 
			+"encounters will be able to resist its power. " 
		    +".\n";
	
    return str;
	
	
	
	
	
	
	
	if (charged)
		str = "Behold this rare and wondrous shield, once worn by "
	    +"a spectral guardian. The shield glows brightly with "
		+"spectral energy that radiates from a large crystal at "
		+"the center. Being purely energy, there is very little "
		+"structure to it other than the crystal and a large "
		+"leather strap used to wear it on your arm.\n";
	else
		str = "This is a leather strap with a large crystal embedded "
	    +"into it. It looks like the kind of strap used to wear a"
        +"shield on your arm.\n";		
	
    return str;
	
}

void config_shield()
{
	if (!charged)
	{	   
	   remove_adj(({"glowing", "spectral"}));
	   set_ac(6);

	}
	else
	{
        set_adj(({"glowing", "spectral"}));
        set_ac(50 + random (5));
	}
}	
	

void create_weapon()
{
    set_name("anlace");    
    add_name("blade", "knife", "dagger", "_Avenir_spectral_anlace");
    set_hit(37);
    set_pen(39);
    set_wt(W_KNIFE);
    set_dt(W_SLASH | W_IMPALE);
    set_hands(W_ANYH);

    configure_it();
}

string exa_pommel()
{
    string str;
    
    if (query_sigil())
    {
        str = "It is the sigil of a Sybarite House: "+ 
              query_sigil() +".\n";
    }   
    else
        str = "It appears to have been broken recently, and you "+
              "can no longer discern what it was.\n";

    return "There is a silver and enamel symbol on the pommel.\n"+ str;
}

string query_recover()
{
    return MASTER + ":" + query_wep_recover() 
                  + "#ADA#"+ad1+"#ADA#"+ad2+"#SIG#"+sigil+"#";
}

void 
init_recover(string arg)
{
    string   foo;

    init_wep_recover(arg);
    sscanf(arg, "%s#ADA#%s#ADD#%s#SIG#%s#", foo, ad1, ad2, sigil);

    configure_it();
}

