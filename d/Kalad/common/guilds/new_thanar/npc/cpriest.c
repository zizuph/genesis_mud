/*
* /d/Kalad/common/guilds/new_thanar/npc/cpriest.c
*
* Common priest who acts as just a simplistic NPC. Nothing special.
* Coded by Mirandus, January 16th, 2018
*
* This is the basic priest who will make up the majority of the main
* level. This is not a grinding NPC.
*
* TODO - Add a response when a non-human enters the environment.
*
*
*   20210717 Meton typo changed from barrel-cheasted to -chested
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

#define TYPE ({"plain","dour", "friendly", "grim",\
"stoic", "contemplative", "menacing", "intelligent", "refined", "pious", \
"distraught"})
#define PHYS ({"big-eared", "round-eyed", "button-nosed", "towering",\
"barrel-chested", "musclebound", "lithe", "languid", "athletic", "weathered"})
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

        set_race_name(npc_name);
        set_name(gender_race);    
        add_name("_thanar_priest");
        
        set_long("Standing tall and proud in his faith, this "+type
        +" "+phys+" "+gender_race+" is intent on ensuring the spread and "
        +"following of "+hishers+" faith. "+CAPheshe+" tends to aspects "
        +"of the church answering questions of practitioners, cleaning "
        +"when need be and ensuring things are organized. Occasionally, "
        +heshe+" mutters something under "+hishers+" breath, "+hishers+" "
        +eyes+" eyes constantly monitoring the situation.\n");

        add_prop(CONT_I_WEIGHT, 110000);
        add_prop(CONT_I_HEIGHT, 180);

        for(i = 0; i < 6; i++)
                set_base_stat(i, 20 + random(20));

        set_hitloc_unarmed(A_HEAD, 20, 15, "head");
        set_hitloc_unarmed(A_R_ARM, 20, 10, "right arm");
        set_hitloc_unarmed(A_L_ARM, 20, 10, "left arm");
        set_hitloc_unarmed(A_BODY, 20, 45, "body");
        set_hitloc_unarmed(A_LEGS, 20, 20, "legs");

        set_skill(SS_UNARM_COMBAT,70);
        set_skill(SS_DEFENCE,70);
        set_skill(SS_AWARENESS,90);
        set_prospective_cluster(({"_thanar_priest_"}));
		
		set_alignment(-400);

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
    }));   

}
