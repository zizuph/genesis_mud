/*
 * Phlan city guard, female
 * Tharizdun, 2021
 */

#include <ss_types.h>
#include <macros.h>
#include <stdproperties.h> 
#include <wa_types.h>
#include <filter_funs.h>
#include <defs.h>

inherit "std/monster.c";

#define WEAPON ({"sword"})
#define BOD_ARM ({"chainmail")}
#define GREAVES ({"leggings"})
#define BRACERS (("bracers"))
#define HELM (("coif"))
#define SHIELD (("shield"))


void arm_me(); 

void create_monster()


{
    string type, phys;
    int i;

    seteuid(getuid());
 
    set_living_name("emiridy");
    set_name("emiridy");
    add_name("guard");     
    set_title("city guard");    
    set_race_name("human");
    set_adj( ({"willowy", "hawk-faced"}) );         
    set_gender(G_FEMALE);    

    set_short("willowy hawk-faced female human"); 
    set_long("This is one of the city guards of Phlan. She looks like" +
        " she is quite competent in her job.\n"); 

/*
*   size and skills
*/        

    default_config_npc(90 + random(10));

    set_alignment(300 + random(50));

    set_skill(SS_WEP_SWORD,70);
    set_skill(SS_DEFENCE,50);
    set_skill(SS_PARRY, 50);
    set_skill(SS_AWARENESS, 60);  
    set_skill(SS_BLIND_COMBAT, 60); 

    add_prop(CONT_I_WEIGHT, 54432);
    add_prop(CONT_I_HEIGHT, 162);    
 
/* 
*   Actions 
*/

    set_chat_time(30);
    add_chat("I heard there is something strange going on at Kuto's Well.");
    add_chat("Phlan has a great armour shop.");

    set_act_time(25);
    add_act("emote watches you intently for a moment then looks away.");
    
    set_cchat_time(10);
    add_cchat("You should reconsider your violent actions.");  

    set_cact_time(10);
    add_cact("emote deftly avoids your attack.");   
    
    arm_me();
/*    
 *   set_pick_up_team(({"_phlan_city_guard_leader"}));
 */
 
}

void

/*
*   adding gear
*/

arm_me()

{
    object arm, wep;

    wep = clone_object(WEP_DIR + "longsword");
    wep -> move(this_object());
    arm = clone_object(ARM_DIR + "phlan_chainmail");
    arm -> move(this_object());
    arm = clone_object(ARM_DIR + "phlan_bracers");
    arm -> move(this_object()); 
    arm = clone_object(ARM_DIR + "phlan_coif");
    arm -> move(this_object());  
    arm = clone_object(ARM_DIR + "phlan_leggings");
    arm -> move(this_object());    
    arm = clone_object(ARM_DIR + "phlan_light_steel_shield");
    arm -> move(this_object());     

    command("wield weapon");
    command("wear all");

}

/*
*   Teaming
*
*
*   void
*   init_living()
*   {
*       ::init_living();
*       init_team_pickup();
*   }
*/
