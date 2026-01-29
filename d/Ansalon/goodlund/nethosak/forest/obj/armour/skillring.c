/* Skill ring by Elmore, inspired by black-gem ring
   of Flotsam Forest.

   When worn, the ring gives a few levels of extra skill levels, however it drains
   a bit of fatigue when worn.

*/

inherit "/std/armour";
inherit "/lib/keep";
#include <stdproperties.h>
#include <wa_types.h>
#include <formulas.h>
#include <macros.h>
#include "/d/Ansalon/common/defs.h"

string *gemType = ({"diamond-encrusted",      // defence
                    "ruby-encrusted",         // axe
                    "sapphire-encrusted",     // club
                    "emerald-encrusted",      // sword
                    "topaz-encrusted",        // knife
                    "tourmaline-encrusted",   // polearm
                    "alexandrite-encrusted",  // parry
                    "moonstone-encrusted"});  // spellcraft

#ifndef ONE_OF
#define ONE_OF(x)   (x[random(sizeof(x))])
#endif
				
string adj1 = ONE_OF(gemType);
				
void
create_armour()
{
    set_name("band");
	add_name("ring");
    set_adj(adj1);
    add_adj("platinum");
    set_short(adj1 + " platinum band");
    set_long("This is a thin ring of gold, @@ornament@@. The " +
        "ring feels warm to the touch.\n");
    add_prop(OBJ_I_IS_MAGIC_ARMOUR, 1);
    add_prop(MAGIC_AM_ID_INFO,
        ({ "The ring is enchanted with some magical powers.\n", 5,
           "When worn, improve certain skills of the wearer.\n",20 }));
    add_prop(MAGIC_AM_MAGIC,({20,"enchantment"}));
    add_prop(OBJ_S_WIZINFO,
        "The ring gives the wearer +5 in a skill, depending on the gem type.\n");
   
    set_at(A_ANY_FINGER);
    set_af(TO);
   
    add_prop(OBJ_I_WEIGHT, 120);
    add_prop(OBJ_I_VOLUME, 70);
    add_prop(OBJ_I_VALUE, 1000);
}

mixed
wear(object what)
{
    object p;
    p = E(TO);
    
    p->add_fatigue((p->query_max_fatigue()/2)*-1);
	
	switch (adj1)
	{
		case "diamond-encrusted":
			p->set_skill_extra(SS_DEFENCE,5);
			break;
        case "ruby-encrusted":
			p->set_skill_extra(SS_WEP_AXE,5);
			break;
        case "sapphire-encrusted":
			p->set_skill_extra(SS_WEP_CLUB,5);
			break;
		case "emerald-encrusted":
			p->set_skill_extra(SS_WEP_SWORD,5);
			break;
		case "topaz-encrusted":
			p->set_skill_extra(SS_WEP_KNIFE,5);
			break;
		case "tourmaline-encrusted":
			p->set_skill_extra(SS_WEP_POLEARM,5);
			break;
		case "alexandrite-encrusted":
			p->set_skill_extra(SS_PARRY,5);
			break;
		case "moonstone-encrusted":
			p->set_skill_extra(SS_SPELLCRAFT,5);
			break;
		default:
			break;	
	}
	
    p->catch_msg("As you slip the ring on a finger, you feel slightly dizzy and confused.\n");
    return 0;
}

mixed
remove(object what)
{
	object p;
    p = E(TO);
	
	switch (adj1)
	{
		case "diamond-encrusted":
			p->set_skill_extra(SS_DEFENCE,0);
			break;
        case "ruby-encrusted":
			p->set_skill_extra(SS_WEP_AXE,0);
			break;
        case "sapphire-encrusted":
			p->set_skill_extra(SS_WEP_CLUB,0);
			break;
		case "emerald-encrusted":
			p->set_skill_extra(SS_WEP_SWORD,0);
			break;
		case "topaz-encrusted":
			p->set_skill_extra(SS_WEP_KNIFE,0);
			break;
		case "tourmaline-encrusted":
			p->set_skill_extra(SS_WEP_POLEARM,0);
			break;
		case "alexandrite-encrusted":
			p->set_skill_extra(SS_PARRY,0);
			break;
		case "moonstone-encrusted":
			p->set_skill_extra(SS_SPELLCRAFT,0);
			break;
		default:
			break;
	}

    return 0;	
}
