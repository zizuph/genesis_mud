/*
 * Phlan city guard leader
 * Tharizdun, 2021
 */

#include <ss_types.h>
#include <macros.h>
#include <stdproperties.h> 
#include <wa_types.h>
#include <filter_funs.h>
#include <defs.h>

inherit "std/monster.c";
inherit "/d/Genesis/lib/intro";

#define WEAPON ({"sword"})
#define BOD_ARM ({"platemail")}
#define GREAVES ({"leggings"})
#define BRACERS (("bracers"))
#define HELM (("helm"))
#define SHIELD (("shield"))


void arm_me(); 

void create_monster()


{
    string type, phys;
    int i;

    seteuid(getuid());
 
    set_living_name("garret");
    set_name("garret"); 
    add_name("guard");     
    set_title("city guard leader");    
    set_race_name("human");
    set_adj( ({"thick-armed", "brooding"}) );         
    set_gender(G_MALE);    

    set_short("thick-armed brooding male human"); 
    set_long("This is one of the leaders of the city guards of Phlan. He looks like" +
        " he is quite competent in his job.\n"); 

/*
*   size and skills
*/        

    default_config_npc(100 + random(10));

    set_alignment(350 + random(50));

    set_skill(SS_WEP_SWORD,80);
    set_skill(SS_DEFENCE,60);
    set_skill(SS_PARRY, 60);
    set_skill(SS_AWARENESS, 60);  
    set_skill(SS_ACROBAT, 70); 

    add_prop(CONT_I_WEIGHT, 86184);
    add_prop(CONT_I_HEIGHT, 180);    
 
/* 
*   Actions 
*/

    set_chat_time(30);
    add_chat("I am proud of the work my guards do.");
    add_chat("Councilman Cadorna's family history worries me.");

    set_act_time(25);
    add_act("emote polishes his sword.");
    
    set_cchat_time(10);
    add_cchat("Surrender and we will spare your life!");   

    set_cact_time(10);
    add_cact("emote slams you with his shield.");    
    
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

    wep = clone_object(WEP_DIR + "broadsword");
    wep -> move(this_object());
    arm = clone_object(ARM_DIR + "phlan_platemail");
    arm -> move(this_object());
    arm = clone_object(ARM_DIR + "phlan_bracers");
    arm -> move(this_object());
    arm = clone_object(ARM_DIR + "phlan_heavy_steel_shield");
    arm -> move(this_object()); 
    arm = clone_object(ARM_DIR + "phlan_plate_helm");
    arm -> move(this_object());  
    arm = clone_object(ARM_DIR + "phlan_leggings");
    arm -> move(this_object());    

    command("wield weapon");
    command("wear all");

}

/*
 * This is called if the person has already been introduced before.
 */

void
greet(object who)
{
    command("bow respectfully " + OB_NAME(who));
}

/*
 * This is called if the person has not been introduced before.
 */

void
introduce(object who)
{
    command("introduce me to " + this_player()->query_real_name() + "");
}

/*
*   React to introduction. String name is person being introduced.
*/

void
react_to_introduction(string name)
{
    object who = find_player(name);
    if (!who || !present(who, environment(this_object())))
    {
        return;
    }
    if (this_object()->query_prop(LIVE_I_NEVERKNOWN) ||
        who->query_met(this_object()))
        {
            greet(who);
        }
        else
        {
            introduce(who);
        }
}

/*
*   react_intro 
*   Function name: add_introduced
*   Description  : Called automatically from the mudlib whenever a person
*                introduces himself to this NPC.
*   Arguments    : string name - the name of the person being introduced.
*
*/

public void
add_introduced(string name)
{
    if (intro_delay)
    {
        set_alarm(itof(intro_delay), 0.0, &react_to_introduction(name));
    }
    else
    {
        react_to_introduction(name);
    }
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
