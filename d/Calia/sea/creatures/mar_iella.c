
/* 
 * This is Mar-Iella, the shopkeeper in the fish market of the 
 * fishing village on the west coast of Calia.  
 * 
 * Coded by Maniac 13/9/96
 */  

#include <stdproperties.h> 
#include <macros.h>
#include <ss_types.h>
#include <const.h>

#include "defs.h"
inherit "/std/monster"; 


#include HAUNT



void
arm_me()
{
     object knife; 

     knife = clone_object(SEA_WEAPONS+"gutting_knife"); 
     knife->move(this_object()); 
     command("wield " + OB_NAME(knife)); 
}


string
random_fish()
{
    return ({ "sardines", "herring", "tuna", 
              "mackerel", "squid", "shark meat",  
              "turtle meat", "crab meat", "oysters" })[random(9)]; 
}


string
random_barrel()
{
    return (({"small", "medium", "large", "huge"})[random(4)] + " barrel"); 
}


string
gut_fish()
{
    return ("emote skillfully cleans and carves up some " + 
            random_fish() + "."); 
}


string
sell_fish()
{
    return ("emote sells " + LANG_ADDART(random_barrel()) + " of " + 
            random_fish() + ".");  
}

void
create_monster()
{
    set_name("mar-Iella"); 
    add_name("mar-iella"); 
    add_name("shopkeeper"); 
    
    set_adj(({"petite", "blue-eyed"}));  

    set_race_name("human"); 

    set_gender(G_FEMALE); 

    set_long("Mar-Iella is a busy clever woman who runs the fish market. " +
             "She is probably the nearest thing to an entrepreneur in " +
             "village, but as with the other villagers she usually " +
             "works unselfishly and for long term gain. Her hands and " +
             "limbs show signs of constant hard work.\n"); 

    default_config_npc(50); 

    add_prop(NPC_I_NO_RUN_AWAY, 1); 
    add_prop(CONT_I_WEIGHT, 45000); 
    add_prop(CONT_I_VOLUME, 45000); 

    set_skill(SS_WEP_KNIFE, 50);  
    set_skill(SS_DEFENCE, 50); 
    set_skill(SS_PARRY, 50); 

    set_act_time(10); 
    add_act(VBFC_ME("gut_fish"));
    add_act(VBFC_ME("sell_fish")); 
    add_act("emote takes a deep breath."); 
    add_act("emote cleans the floor with a mop."); 
    add_act("smile wearily"); 
}


void
add_introduced(string str)
{
    set_alarm(2.0, 0.0, &command("introduce me")); 
}


