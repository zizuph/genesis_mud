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

// project includes
#include "/d/Khalakhor/sys/defs.h"
#include "/d/Khalakhor/sys/paths.h"

#include "../../daenbraigh.h" 
#include "../foraois_deanach.h"


inherit "/d/Khalakhor/std/monster";

// preloads
void equip_me(int level);
void create_foraois_monster( int level);

// create random adjs and names here because we do not wish to have it changed
void
create_khalakhor_monster()
{
    int r;
    mixed *categories;
    string *list, cat;
	
    if(! IS_CLONE)
       return;
    ::create_khalakhor_monster(); // we better call master object in case something
						   // will be there
    set_race_name("human");
  
    // random adjectives
    if (!sizeof(query_adjs()))
    {
        categories = get_dir(ATTRIBS);
        for(r=0; r<2; r++)
        {
            cat = categories[random(sizeof(categories))];
            list = explode(read_file(ATTRIBS + cat), "\n");
            add_adj(list[random(sizeof(list))]);
            categories -= ({ cat });
        }
    }

    set_scar(random(2048)); //random scare here and there
    set_appearance(random(99)+1); //how do I look?
    set_gender(G_MALE);

    add_prop(LIVE_I_NEVERKNOWN, 1); //no we will not know the name
    add_prop(NPC_I_NO_LOOKS,0); //the idea is that they look like players
    
    // stats are not level dependant
    set_base_stat(SS_STR, FD_H_STR, 10);
    set_base_stat(SS_DEX, FD_H_CON, 10);
    set_base_stat(SS_CON, FD_H_DEX, 10);
    set_base_stat(SS_INT, FD_H_INT, 10);
    set_base_stat(SS_WIS, FD_H_WIS, 10);
    set_base_stat(SS_DIS, FD_H_DIS, 10);

    //now we call for rest of creation with default level
    create_foraois_monster(FD_SOLDIER);

}

void create_foraois_monster( int level)
{

    // skill are level dependant
    set_skill(SS_WEP_SWORD,FD_H_LEVEL_SWORD(level));
    set_skill(SS_DEFENSE,FD_H_LEVEL_DEF(level));
    set_skill(SS_PARRY,FD_H_LEVEL_PARRY(level));

    set_alarm(0.5,0.0,&equip_me(level));
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
