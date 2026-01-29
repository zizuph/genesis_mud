/*
 *  /d/Kalad/common/farmland/farm/npc/noblewoman
 *
 *  A female noble in the farm estates in the
 * farmlands of Kalad. Most of the code is stolen
 * From the noble houses of Kalad made by Sarr.
 *
 *  Created September 2017, by Andreas Bergstrom ( Zignur )
 */
#pragma strict_types
inherit "/std/monster";
inherit "/d/Kalad/lib/assist";
#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>
#include <stdproperties.h>
#include "/d/Kalad/sys/npc_types.h"


/* Prototypes */
public void        arm_me();

/* Global variables */
string *ArrAdj1 = ({ "beautiful","cute","young","petite","old"});
string *ArrAdj2 = ({ "tiny","short","sweet-smelling","attractive" });
string Adj1 = one_of_list(ArrAdj1);
string Adj2 = one_of_list(ArrAdj2); 


void
create_monster()
{
    set_name("noblewoman");
    set_race_name("human");
    add_name(({ "noble", "woman","human" }));
    add_adj(({ Adj1, Adj2 }));

    set_short( Adj1+ " "+ Adj2 +" noblewoman");
    
    set_long("A " +Adj1 + " " + Adj2 + " noblewoman. One of the"
      + " inhabitants of the farm estates, she looks at you"
      + " clearly regarding you below her rank. Judging by her" 
      + " regal manners and expensive clothes she is clearly"
      + " part of the family that owns this estate.\n");

        
    set_gender(1);
    set_stats(({70,70,70,70,70,70}));
    set_skill(SS_DEFENCE,30);
    set_alignment(600);
    
    // Assist all kabal citizens and some other type of npcs
    add_friend(LIVE_I_KABAL_NPC_TYPE, KABAL_CITIZEN);
    add_prop(LIVE_I_KABAL_NPC_TYPE, KABAL_CITIZEN);

    set_act_time(5);
    add_act("emote dances the waltz.");
    add_act("giggle");
    add_act("say Oh my!");
    add_act("emote fixes her hair.");
    add_act("laugh merr");
    add_act("wiggle cute");

    set_cact_time(3);
    add_cact("shout Help ! Help !");
    add_cact("say What did I ever do to you!");
    add_cact("scream");
    add_cact("cower");
    add_prop(LIVE_I_NEVERKNOWN,1);
}

/*
 * Function name:        arm_me
 * Description  :        set up the npc with any gear it needs
 */
public void
arm_me()
{
    object  arm;
    /* Add some earrings to the noble*/
    arm = clone_object("/d/Kalad/common/noble/arm/pair_rings");
    arm->set_ring_metal("gold");
    arm->set_ring_metal("emerald", 1);
    arm->set_ring_value(2872);
    arm->move(this_object());
    
    /* Add the rest of the equipment for the noble */
    equip( ({ "/d/Kalad/common/noble/arm/silk_skirt",
              "/d/Kalad/common/noble/arm/silk_tunic",
              "/d/Kalad/common/noble/arm/high-heels",
              "/d/Kalad/common/noble/arm/pearl_necklace",
              "/d/Kalad/common/noble/arm/pierce3"  }));
    
    command("wear all");       
    command("insert rings in both ears");   
    command("wear all");
  
} /* arm_me */


void
attacked_by(object enemy)
{
    ::attacked_by(enemy);
    command("shout Guards! Help! Help!");
   
    /* Make sure the guards help */    
    string env = file_name(environment(this_object()));
    object npc;
    object *guards = env->query_cloned_here(); 
     
    for (int i=0; i<sizeof(guards); i++) {
        npc = guards[i];
        string name = npc->query_name();
        if(name == "Guard") {
            npc->command("kill "+lower_case(enemy->query_name()));
        }
    }
    /* Only make the last npc shout to prevent spam */
    npc->command("say Die worm!");
}   
