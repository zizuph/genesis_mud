/*
 * Phlan city guard
 * Tharizdun, 2021
 */

#include <ss_types.h>
#include <macros.h>
#include <stdproperties.h> 
#include <wa_types.h>
#include <filter_funs.h>
#include <defs.h>

inherit "std/monster.c";

#define WEAPON ({"mace"})
#define BOD_ARM ({"chainmail")}
#define GREAVES ({"leggings"})
#define SHIELD (("shield"))
#define BRACERS (("bracers"))
#define HELM (("coif"))


void arm_me(); 

void create_monster()


{
    string type, phys;
    int i;

    seteuid(getuid());
 
    set_living_name("aaron");
    set_name("aaron"); 
    add_name("guard");    
    set_title("city guard");    
    set_race_name("human");
    set_adj( ({"stern", "husky"}) );         
    set_gender(G_MALE);    

    set_short("stern husky male human"); 
    set_long("This is one of the city guards of Phlan. He looks like" +
        " he is quite competent in his job.\n"); 

/*
*   size and skills
*/        

    default_config_npc(90 + random(10));

    set_alignment(300 + random(50));

    set_skill(SS_WEP_CLUB,70);
    set_skill(SS_DEFENCE,50);
    set_skill(SS_PARRY, 50);
    set_skill(SS_AWARENESS, 60);  
    set_skill(SS_BLIND_COMBAT, 60); 

    add_prop(CONT_I_WEIGHT, 81648);
    add_prop(CONT_I_HEIGHT, 175);    
 
/* 
*   Actions 
*/

    set_chat_time(30);
    add_chat("This is a great job.");
    add_chat("Be sure to visit the city hall.");

    set_act_time(25);
    add_act("emote inspects his armours.");
    
    set_cchat_time(10);
    add_cchat("Stop this fighting at once!");   

    set_cact_time(10);
    add_cact("shout To arms! To arms! We are under attack!");    
    
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

    wep = clone_object(WEP_DIR + "horsemans_mace");
    wep -> move(this_object());
    arm = clone_object(ARM_DIR + "phlan_chainmail");
    arm -> move(this_object());
    arm = clone_object(ARM_DIR + "phlan_bracers");
    arm -> move(this_object());
    arm = clone_object(ARM_DIR + "phlan_light_steel_shield");
    arm -> move(this_object()); 
    arm = clone_object(ARM_DIR + "phlan_coif");
    arm -> move(this_object());  
    arm = clone_object(ARM_DIR + "phlan_leggings");
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
