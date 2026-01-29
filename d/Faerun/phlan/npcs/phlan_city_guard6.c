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

#define WEAPON ({"ranseur"})
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
 
    set_living_name("ferrel");
    set_name("ferrel");
    add_name("guard");     
    set_title("city guard");    
    set_race_name("human");
    set_adj( ({"compact", "muscular"}) );         
    set_gender(G_MALE);    

    set_short("combact muscular male human"); 
    set_long("This is one of the city guards of Phlan. He looks like" +
        " he is quite competent in his job.\n"); 

/*
*   size and skills
*/        

    default_config_npc(90 + random(10));

    set_alignment(300 + random(50));

    set_skill(SS_WEP_POLEARM,70);
    set_skill(SS_DEFENCE,50);
    set_skill(SS_PARRY, 50);
    set_skill(SS_AWARENESS, 60);  
    set_skill(SS_ACROBAT, 60); 

    add_prop(CONT_I_WEIGHT, 81648);
    add_prop(CONT_I_HEIGHT, 165);    
 
/* 
*   Actions 
*/

    set_chat_time(30);
    add_chat("It has been a calm shift so far.");
    add_chat("I wish the gnomes at the bank wrote like normal folks.");

    set_act_time(25);
    add_act("emote leans on his ranseur.");
    
    set_cchat_time(10);
    add_cchat("I'll run you through!");   

    set_cact_time(10);
    add_cact("emote slaps you on the backside with the haft of his ranseur.");    
    
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

    wep = clone_object(WEP_DIR + "ranseur");
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
