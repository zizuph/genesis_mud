/*
* /d/Kalad/common/guilds/new_thanar/npc/mpriest.c
*
* Moderate priest who acts as just a grinding NPC.
* Coded by Mirandus, January 17th, 2018
*
* This is the basic priest who will make up some of the main
* level. Stronger and more worth targeting, but more dangerous.
*
* Added a melee special attack.
*
* TODO - Add a response when a non-human enters the environment.
*/

#include "../local.h"
#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>
#include <filter_funs.h>
inherit "/d/Kalad/common/guilds/new_thanar/npc/std_priest";

/* Global variables */
#define ROBE  ARM + "probe"
#define SHIRT ARM + "pmail"
#define PANTS ARM + "pleggings"
#define NECK  ARM + "pnecklace"
#define CLUB  WEP + "pclub"

#define TYPE ({"plain","dour", "friendly", "grim",\
"stoic", "contemplative", "menacing", "intelligent", "refined", "pious", \
"distraught"})
#define PHYS ({"big-eared", "round-eyed", "button-nosed", "towering",\
"barrel-cheasted", "musclebound", "lithe", "languid", "athletic", "weathered"})
#define EYES ({"blue", "green", "brown", "hazel", "grey"})
#define SKIN ({"dark", "light", "pale", "tanned", "sun-burned", "ebony"})
#define HAIR ({"blonde", "dirty-blonde", "red", "black", "auburn", \
"white", "grey"})

// Prototypes

public void create_thanar_living();

/*
 * Function name: create_thanar_living()
 * Description  : Sets all the basic properties for the npc.
 */
public
void create_thanar_living()
{
        determine_sex();
        string type, phys, eyes,skin, hair;
        int i;

        seteuid(getuid());
        type = one_of_list(TYPE);
        phys = one_of_list(PHYS);
        eyes = one_of_list(EYES);
        skin = one_of_list(SKIN);
        hair = one_of_list(HAIR);

        string npc_name = "human";

        add_adj(type);
        add_adj(phys);
        add_prop(LIVE_I_NEVERKNOWN, 1);

        set_race_name(gender_race);
        set_short(type +" "+ phys + " " + gender_race);
        add_name(npc_name);
        add_name("warrior");
        add_name("_thanar_priest");
        
        set_long("Standing tall and proud in his faith, this "+type
        +" "+phys+" "+gender_race+" is intent on ensuring the spread and "
        +"following of "+hishers+" faith. "+CAPheshe+" tends to aspects "
        +"of the church answering questions of practitioners, cleaning "
        +"when need be and ensuring things are organized. Occasionally, "
        +heshe+" mutters something under "+hishers+" breath, "+hishers+" "
        +eyes+" eyes constantly monitoring the situation. You can tell by "
        +"the way "+heshe+" moves that "+heshe+" has spent "+hishers+" life "
        +"dedicated to the art of combat.\n");


        add_prop(CONT_I_WEIGHT, 110000);
        add_prop(CONT_I_HEIGHT, 180);

        for(i = 0; i < 6; i++)
                set_base_stat(i, 120 + random(40));

        set_hitloc_unarmed(A_HEAD, 20, 15, "head");
        set_hitloc_unarmed(A_R_ARM, 20, 10, "right arm");
        set_hitloc_unarmed(A_L_ARM, 20, 10, "left arm");
        set_hitloc_unarmed(A_BODY, 20, 45, "body");
        set_hitloc_unarmed(A_LEGS, 20, 20, "legs");

        set_skill(SS_UNARM_COMBAT,70);
        set_skill(SS_WEP_CLUB, 70);
        set_skill(SS_PARRY, 70);
        set_skill(SS_DEFENCE,70);
        set_skill(SS_AWARENESS,90);
        set_prospective_cluster(({"_thanar_priest"}));

        set_act_time(random(400));
        add_act("say Humanity is the superior race.");
        add_act("say Thanar grants us clarity and wisdom.");
        add_act("say Demi-humans are an abomination.");
        add_act("emote lowers his head in prayer.");
        add_act("emote turns his head to the sky in prayer.");
        add_act("say I am but a conduit for Thanar's power.");
        add_ask(({"about quest","quest", "quests", "task", 
        "tasks", "help"}), help_response,1);
        add_ask(({"about thanar", "thanar", "religion",
        "order"}), thanar_response,1);

      
        set_alarm(1.0,0.0,"arm_me");
}

/*
 * Function name: arm_me()
 * Description  : Arms the NPC
 */
void
arm_me()
{
    seteuid(getuid(this_object()));
    equip(({
        ROBE,
        SHIRT,
        PANTS,
        NECK,
        CLUB,
    }));   

}

/*
 * Function name: special_attack()
 * Description  : Randomly triggers the special attack
 * Arguments    : Enemy = the enemy of the object
 */
int
special_attack(object enemy)
{
    if(random(3))
        return 0;
    if(!random(3))
	set_alarm(6.0,0.0,"charge",enemy);
    return 1;
}

/*
 * Function name: charge()
 * Description  : A straight forward special attack for this NPC
 * Arugments    : en = the enemy of the object.
 */
void
charge(object en)
{
	if (environment(en) != environment(TO)) return;
    tell_object(en,"The "+TO->query_short()+" grasps "+hishers+" medallion "
    +"muttering under "+hishers+" breath to Thanar. Launching "+hself+" at "
    +"you, striking you hard in the chest.\nYou feel bones "
    +"giving away under the onslaught.\n");
    tell_room(environment(en),"The "+TO->query_short()+" grasps "+hishers+
    " medallion muttering under "+hishers+" breath to Thanar. "+CAPheshe+
    "launches "+hself+ " at "+QTNAME(en)+", striking "+en->query_objective()
    +" hard in the chest.\nThere is a crunching sound.\n",en);
    en->hit_me(200 + random(150));
    TO->heal_hp(75 + random(75));
    tell_object(en,"The "+TO->query_short()+" smirks at you as you feel "
    +"him drain your vitality into "+hself+".\n");
    tell_room(environment(en),"The "+TO->query_short()+" smirks at "
    +QTNAME(en)+". You notice The "+TO->query_short()+
    " seems healthier.\n",en);
}


/* Function:         do_die()
 * What's it do:     Initiates death in slain monster.
*/
 
void
do_die(object killer)
{
    command("say Thanar grant me peace and smite my foe.");
    command("emote attempts to pray through gurgling blood.");   
    ::do_die(killer);
}