/* Torqual limited production 2007
 * Human base soldier for camp south of the road
 * they need to be killable by rising hero so
 * no fancy stunts
 */

// global include
#include <ss_types.h>
#include <money.h>
#include <stdproperties.h>
#include <living_desc.h>
#include <const.h>
#include <macros.h>
#include <login.h>

// include of nameserver

// project includes
#include "/d/Khalakhor/sys/defs.h"
#include "/d/Khalakhor/sys/paths.h"

#include "../../daenbraigh.h" 
#include "../foraois_deanach.h"


inherit "/d/Khalakhor/common/npc/human";

// preloads
void equip_me(int level);

void
create_human(int level)
{
    int r;
    mixed *categories;
    string *list, cat;
	
    if(! IS_CLONE)
       return;
  
    set_scar(random(2048)); //random scare here and there
    set_appearance(random(99)+1); //how do I look?

//    add_prop(LIVE_I_NEVERKNOWN, 1); //no we will not know the name
//    add_prop(NPC_I_NO_LOOKS,0); //the idea is that they look like players
    
}

void
equip_me(int level)
{
    int i; //counter
    string *wep, *arm;

    FIX_EUID; //ok we fix rights before we start cloning
  
    if (level < FD_KING)
    {
        //possible weapons for leader and below
	wep = (({ FD_WEP + "h_claymore.c",
                  FD_WEP + "h_falcata.c",
	          FD_WEP + "h_shortsword.c",
                  FD_WEP + "h_basket_broadsword.c",
		  FD_WEP + "h_barbed_spear.c",
                  FD_WEP + "h_leaf_spear.c" }));
       // corresponding armours  for leader and below
        arm = (({ FD_ARM + "h_bracers.c", FD_ARM + "h_targa.c",
                  FD_ARM + "h_shield.c" , FD_ARM + "h_targa.c",
        	  FD_ARM + "h_bracers.c", FD_ARM + "h_bracers.c" }));
    }
    else
    {
	    wep = ({ (FD_WEP + "h_claymore_steel.c") });
	    arm = ({ (FD_ARM + "h_bracers_steel.c") });
    }

    i = random(sizeof(wep)-1); // number of elements we choose from

    // we decide if the warrior will or will not have helm
    if (i <= 1)
    {
	clone_object( FD_ARM + "h_helm.c")->move(this_object(), 1);
    } 
    // ok we give them shirt and trousers
    clone_object( COMMON + "arm/breeches.c")->move(this_object(), 1);
    clone_object( FD_ARM + "h_shirt.c")->move(this_object(), 1);
	
    //we clone weapon and corresponding armour so it will
    clone_object(wep[i])->move(this_object(),1);
    clone_object(arm[i])->move(this_object(),1);
	
    command("wield all");
    command("wear all");
}
