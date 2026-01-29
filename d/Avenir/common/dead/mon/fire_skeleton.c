
// fire skeleton  /d/Avenir/common/dead/mon/fire_skeleton.c
// creator(s):     Lilith  Sept 2021
// last update:  
// purpose:        This is the skeleton that is cloned when the petal
//                 of the fire rose enters a room. 
//                 Based on the serpent cloned by the serpent staff.
// note:          Benefits:
//                -If the owner/dropper is in combat when the petal
//                 is dropped, the skeleton will attack their enemies.
//                 (I'm not sure how to calculate its combat aid.)
//                Drawbacks:
//                  One skeleton per petal. When the skeleon is 
//                  dead, its gone forever.
// bug(s):
// to-do:
inherit "/std/monster";

#include "../dead.h"
#include <formulas.h>
#include <cmdparse.h>
#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>
#include <stdproperties.h>

string own;

string query_owner()          {    return own;    }
void   set_owner(string str)  {    own = str;     }
void   help_owner(object owner);

void
create_monster()
{
    if (!IS_CLONE)
        return;
    set_name("skeleton");
    add_name("_av_fire_rose_npc");
    set_race_name("skeleton");
    set_gender(G_MALE);
    add_adj(({"flaming", "orange-red"}));
    set_long("This skeleton is a collection of bones that "+
	    "are both sentient and magically aflame.\n");
  
    default_config_creature(50 + random(10));
    set_alignment(0);

    /* They are skeletons, they don't have eyes, but they can still 'see' */	
    add_prop(LIVE_I_NO_CORPSE,1);
    add_prop(LIVE_I_SEE_DARK,20);
    add_prop(LIVE_I_UNDEAD, 1);
    add_prop(LIVE_I_NEVERKNOWN,1);
 	
	// hit 30, pen 30
	set_all_attack_unarmed(30, 30); 

	// avg ac is 30
    set_hitloc_unarmed(A_TORSO,({25,30,35}),25,"sternum");
    set_hitloc_unarmed(A_CHEST,({25,30,35}),25,"ribs");
    set_hitloc_unarmed(A_HEAD,({25,30,35}),10,"skull");
    set_hitloc_unarmed(A_LEGS,({25,30,35}),20,"leg bone");
    set_hitloc_unarmed(A_ARMS,({25,30,35}),20,"leg bone");
  
    set_skill(SS_DEFENCE, 30);
    set_skill(SS_UNARM_COMBAT, 50);
    set_skill(SS_BLIND_COMBAT, 30);

    add_prop(OBJ_I_RES_FIRE, 50);
    add_prop(LIVE_I_NO_CORPSE, 1);
	
    seteuid(getuid());
}

public string cr_attack_desc(int id)
{
    if (id == W_LEFT)
    {
        return "flaming left hand";
    }
    if (id == W_RIGHT)
    {
        return "flaming right hand";
    }
	
    return ::cr_attack_desc(id);
}

/*
 * help_owner is called from the rose petal that clones this.
 * If the 'owner' is in combat, the skeleton will join in.
 */
void
help_owner(object owner)
{
    object *foes, foe;
    int i;
  
    if (!query_owner())
      return;

	TO->team_join(owner);
	TO->set_leader(owner);
	TO->set_follow(owner->query_name());
	
    foes = owner->query_enemy(-1);
    for (i=0; i<sizeof(foes); i++) 
    if (objectp(foe = foes[i]) && environment() == environment(foe)) 
    {
        add_prop(NPC_I_NO_FEAR, 1);
        command("kill " + foe->query_real_name());
    }
}
