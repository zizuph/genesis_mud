/*
 *  /d/Kalad/common/farmland/farm/npc/nobleman
 *
 * A male noble in the farm estates in the
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
string *ArrAdj1 = ({ "handsome","rich","young","drunk","old"});
string *ArrAdj2 = ({ "tiny","short","tall","attractive" });
string Adj1 = one_of_list(ArrAdj1);
string Adj2 = one_of_list(ArrAdj2); 


void
create_monster()
{
    set_name("nobleman");
    set_race_name("human");
    add_name(({ "noble", "man","human" }));
    add_adj(({ Adj1, Adj2 }));

    set_short( Adj1+ " "+ Adj2 +" nobleman");
    
    set_long("A " +Adj1 + " " + Adj2 + " nobleman. One of the"
      + " inhabitants of the farm estates, he looks at you"
      + " clearly regarding you below his rank. Judging by his" 
      + " regal manners and expensive clothes he is clearly"
      + " part of the family that owns this estate.\n");

    set_gender(0);
    set_stats(({70,70,70,70,70,70}));
    set_skill(SS_DEFENCE,30);
    set_alignment(600);
    // Assist all kabal citizens and some other type of npcs
    add_friend(LIVE_I_KABAL_NPC_TYPE, KABAL_CITIZEN);
    add_prop(LIVE_I_KABAL_NPC_TYPE, KABAL_CITIZEN);

    set_act_time(5);
    add_act("emote dances the waltz.");
    add_act("emote downs another class of champagne.");
    add_act("emote steals a swift kiss from the girl next to him.");
    add_act("laugh merr");
    add_act("emote cracks a joke about dwarves.");
    add_act("emote cracks a joke about hobbits.");
    add_act("emote cracks a joke about goblins.");
    add_act("wiggle");
    add_act("emote whines about petty things.");
    add_act("emote plays with his ring.");

    set_cact_time(3);
    add_cact("shout Help ! Help !");
    add_cact("say What did I ever do to you!");
    add_cact("say Leave me alone! Why are you doing this!!");
    add_cact("cower");}

/*
 * Function name:        arm_me
 * Description  :        set up the npc with any gear it needs
 */
public void
arm_me()
{
    object  arm;
    /* Add a ring to the noble */  
    arm = clone_object("/d/Kalad/common/noble/arm/single_ring");
    arm->set_ring_metal("gold");
    arm->set_ring_metal("onyx", 1);
    arm->set_ring_value(1872);
    arm->move(this_object());

    /* Add the rest of the equipment for the noble */
    equip( ({ "/d/Kalad/common/noble/arm/e_leather_pants",
              "/d/Kalad/common/noble/arm/silk_tunic",
              "/d/Kalad/common/noble/arm/leather_shoes",
              "/d/Kalad/common/noble/arm/silver_pendant",
              "/d/Kalad/common/noble/wep/jeweled_dagger"  }));
    
    command("wear all");
    command("wield all");
    
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
           // npc->command("say Die worm!");
            npc->command("kill "+lower_case(enemy->query_name()));
        }
    }
    /* Only make the last npc shout to prevent spam */
    npc->command("say Die worm!");
}   