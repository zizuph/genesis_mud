/*
 * Phlan city guard, male
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
#define BRACERS (("bracers"))
#define HELM (("coif"))


void arm_me(); 

void create_monster()


{
    string type, phys;
    int i;

    seteuid(getuid());
 
    set_living_name("darryn");
    set_name("darryn"); 
    add_name("guard");     
    set_title("city guard");    
    set_race_name("human");
    set_adj( ({"long-armed", "brown-eyed"}) );         
    set_gender(G_MALE);    

    set_short("long-armed brown-eyed male human"); 
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

    add_prop(CONT_I_WEIGHT, 68040);
    add_prop(CONT_I_HEIGHT, 172);    
 
/* 
*   Actions 
*/

    set_chat_time(30);
    add_chat("I love this town.");
    add_chat("Bishop Tulloch is so helpful.");

    set_act_time(25);
    add_act("emote takes a moment to pray silently.");
    
    set_cchat_time(10);
    add_cchat("Tyr will judge your soul!");  

    set_cact_time(10);
    add_cact("emote attacks you with holy vigor.");   
    
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

    wep = clone_object(WEP_DIR + "footmans_mace");
    wep -> move(this_object());
    arm = clone_object(ARM_DIR + "phlan_chainmail");
    arm -> move(this_object());
    arm = clone_object(ARM_DIR + "phlan_bracers");
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
