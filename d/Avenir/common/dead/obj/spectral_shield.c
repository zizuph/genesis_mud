// spectral shield  /d/Avenir/common/dead/obj/spectral shield
// creator(s):      Lilith & Zizuph Aug 2021
// purpose:         Magical Gear for Spectral Guardian
// last update:
// note:            This shield is powered by spectral
//                  energy radiating from the crystal.
//                  Shield will need to recharge every few hours.
//                  It has 30 SS_ACROBAT, and magic resistance.
//                  This is an acrobatic/unarmed aid.
//                  Trying to help Ckrik and the DO with the
//                  new direction unarmed is being taken in.
// bug(s):
// to-do:     Get Zizuph to help with the discharged/recharged aspect.


inherit "/std/armour";
inherit "/lib/keep";
#include "../dead.h"
#include "/d/Avenir/include/basic.h"
#include "/d/Avenir/include/relation.h"
#include <wa_types.h>
#include <ss_types.h>
#include <formulas.h>

#define SPECTRAL_PROP "_Avenir_i_wear_spectral_shield"

int charged = 4;  // starts charged. will want a countdown for how long
                  // it lasts, maybe it loses charge after it takes x hits?
				  // is there a counter for that somewhere already in
				  // the armour like with the wear and tear counter?
				  // then it will need a period of time to recharge...

string crystal_state()
{
	string str;
	if (charged)
	    str = "This crystal glows with a bright greenish spectral energy.\n";
	else
		str = "The crystal has a very faint greenish glow to it.\n";
    return str;
}	
		
string my_short()
{
	string str;
	if (charged)
        str = "glowing spectral shield";
   	else	
		str ="crystal-embedded leather strap";
    return str;
}	

string my_long()
{
	string str;
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
	   set_ac(40);

	}
	else
	{
        set_adj(({"glowing", "spectral"}));
        set_ac(40 + (charged * 2));  // max 48
	}
}	
	
void
create_armour()
{
    set_name("shield");
    add_name(({"_Avenir_spectral_shield", "strap"}));
	set_short(my_short);
    set_long(my_long);
    add_adj(({"crystal-embedded", "leather"}));
    add_item(({"strap", "leather strap"}),
	    "It is a thick strap made of leather, with a large crystal "
		+"embedded into it.\n");
	add_item(({"crystal", "spectral crystal"}), "@@crystal_state");
    set_af(this_object());
    set_keep(1);
	add_prop(OBJ_I_AIDS_ACROBATIC, 100);
	add_prop(OBJ_I_IS_MAGIC_ARMOUR, 1);
	add_prop(OBJ_S_WIZINFO, "The spectral shield is worn by the spectral "
	    +"guardians in the catacombs of Sybarus:\n"+
		+"/d/Avenir/common/dead/mon/spectral_guardian\n"	
        +"in /d/Avenir/common/dead/catacombs/* \n"		
		+"The shield is almost entirely spectral energy."
		+"It confers resistance to death and life magic (30) "
		+"to those who wear it. "
		+"Its spectral energy becomes exhausted periodically and requires "
		+"recharge time.\n"
		+"Additionally, the shield has OBJ_I_AIDS_ACROBATIC 100 and "
		+"boosts SS_ACROBAT by 30. This is to help get acrobatic "
		+"aids into the game and may be removed or reduced as the "
		+"number of aids available increases.\n");
//	add_prop(MAGIC_AM_ID_INFO, ({ /*Will fill this in when it is finalized */}));
	add_prop(MAGIC_AM_MAGIC, ({"death", 90}));
	// spectral guardians and their gear are highly resistant to cast magic.
	add_prop(MAGIC_I_RES_MAGIC, 75); 
	set_at(A_SHIELD);
    config_shield();    
}

varargs mixed
query_magic_protection(string prop, object protectee = previous_object())
{
	if (!charged)
		return 0;
	
	// spectral guardians and their gear are highly resistant to magic.
	// lets pass some of that resistance on to players wearing this.
    if (protectee == query_worn())
    {  // Yes they resist all magic.
        if (prop == MAGIC_I_RES_FIRE)
			return ({ -30, 1 });
        if (prop == MAGIC_I_RES_LIFE)
            return ({ 40, 1 });
    }
    else
      return ::query_magic_protection(prop, protectee);
}

public mixed
wear(object ob)
{
	//make sure the props and adjs are updated.
	config_shield();
	
	if (!charged)
		return "It cannot be worn right now. Perhaps try wearing the "
	        +short()+ " again later.\n";
			
    object tp = this_player();

    /* I'm an infidel/enemy of Sybarus, I can't wear the
	 *  spectral guardian's armor.
	 */
    if (IS_INFIDEL(tp))
    {
        return "The Gods of Sybarus to not allow their enemies to wear "
		       +"gifts like the "+ short() +".\n";
    }

    if(!tp->query_prop(SPECTRAL_PROP))
	{
        tp->add_prop(SPECTRAL_PROP, 1);
		ALTER_SKILL(tp, SS_ACROBAT, 30);
	}
	
    tp->add_magic_effect(this_object());
    return 0;
}

public int
remove(object ob)
{
    object tp = query_worn();
	// make sure the props and adjs are updated.
	config_shield();
	if (tp->query_prop(SPECTRAL_PROP))
    {
        tp->remove_prop(SPECTRAL_PROP);
        ALTER_SKILL(wearer, SS_ACROBAT, -30);
    }

    tp->remove_magic_effect(this_object());
    return 0;
}
