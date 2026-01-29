/*
* /d/Kalad/common/guilds/new_thanar/npc/std_priest.c
*
* Moderate priest who acts as just a grinding NPC.
* Coded by Mirandus, January 17th, 2018
*
* This is the basic priest who will make up some of the main
* level. Stronger and more worth targeting, but more dangerous.
*
* TODO - Add a response when a non-human enters the environment.
*
* Update Log - Set race name based on gender. Priest/Priestess - Mirandus
*/

#include "../local.h"
#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>
#include <filter_funs.h>
inherit "/d/Kalad/std/active_monster_base.c";
inherit "/d/Genesis/specials/npc/stat_based_specials.c";
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

object shirt,pants,necklace,robe,club;

int x = 0;
string hishers = "";
string heshe = "";
string himher = "";
string hself = "";
string CAPheshe = "";
string CAPhisher = "";
string gender_race = "";

// Prototypes
string help_response();
string thanar_response();
public void create_thanar_living();


/*
 * Function name: determine_sex()
 * Description  : Randomly selects the sex of the NPC and sets pronouns.
 */
void determine_sex()
{
    switch(random(2))
        {
                case 0:  set_gender(G_MALE);
                         hishers = "his";
                         heshe = "he";
                         himher = "him";
                         hself  = "himself";
                         CAPheshe = "He";
                         CAPhisher = "His";
                         gender_race = "priest";
                         x = 0;
                         break;
                case 1:  set_gender(G_FEMALE);
                         hishers = "her";
                         heshe = "she";
                         himher = "her";
                         hself = "herself";
                         CAPheshe = "She";
                         CAPhisher = "Her";
                         gender_race = "priestess";
                         x = 1;
                         break;
                default: set_gender(G_NEUTER);
                         break;
        }
} /* determine_sex */


/*
 * Function name: create_active_monster
 * Description  : Constructor. Creates the monster.
 */
nomask void create_active_monster()
{
    /* Redefine this function to customize the npcs */
    create_thanar_living();         
} /* create_active_monster */

/*
 * Function name: create_thanar_living
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
    add_name(npc_name);
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
    
} /* create_thanar_living */

/*
 * Function name: help_response
 * Description  : Gives a response 
 * Returns      : a string with the response
 */
string
help_response()
{
    if(TP->query_race_name() != "human" && TP->query_race_name() != "half-elf")
    {
        command("say You stand within the Cathedral of the great and "
        +"omnipotent Thanar. You are welcome to gaze upon the glory of "
        +"this place, but do sully it. You poor soul, born to an inferior "
        +"race.\n");
        command("emote frowns sympathetically");
        command("comfort " + OB_NAME(TP));
        return "\n";
    }
    if(TP->query_race_name() == "half-elf")
    {
        command("say You foul beast. How do you come to be here. "
        +"You and your kind are not fit to be in this holy chamber built "
        +"in honour of the human race.\n"
        +"BEGONE ABOMINATION! You sully this holy chamber!\n");
        command("kill " + OB_NAME(TP));
        return "\n";
    }
    //To add a response for a Thanar guild member.
    return "say I do not have time for you!\n";
} /* help_response */

/*
 * Function name: thanar_response
 * Description  : Gives a response 
 * Returns      : a string with the response
 */
string
thanar_response()
{
    if(TP->query_race_name() != "human" && TP->query_race_name() != "half-elf")
    {
        command("say You stand within the Cathedral of the great and "
        +"omnipotent Thanar. You are welcome to gaze upon the glory of "
        +"this place, but do sully it. You poor soul, born to an inferior "
        +"race.\n");
        command("emote frowns sympathetically");
        command("comfort " + OB_NAME(TP));
        return "\n";
    }
    if(TP->query_race_name() == "half-elf")
    {
        command("say You foul beast. How do you come to be here. "
        +"You and your kind are not fit to be in this holy chamber built "
        +"in honour of the human race.\n"
        +"BEGONE ABOMINATION! You sully this holy chamber!\n");
        command("kill " + OB_NAME(TP));
        return "\n";
    }
    //To add a response for a Thanar guild member.
    return "say The Thanarian order is dedicated to the worship of his Lord "
    +"Thanar, the patron saint of humanity. We stand to show that the Human "
    +"race is the superior race. Above all others we stand. You, a human, "
    +"should join us in our cause!\n";
} /* thanar_response */



/*
 * Function name: arm_me()
 * Description  : Arms the NPC
 */
void
arm_me()
{ 
   seteuid(getuid(this_object()));
   equip( ({  ROBE,
              SHIRT,
              PANTS,
              NECK,
              CLUB,  }));
   
 
} /* arm_me */
/*
 * Function name: attacked_by()
 * String       : the object attacking (ob)
 * Description  : Determines who is attacking and gives a response.
 *                
 */
void
attacked_by(object ob)
{
    object *arr;
    int i;

    ::attacked_by(ob);

    command("say Heretic! Thanar shall grant me the power to destroy you!");

    arr = (object *)query_team_others();
    for (i = 0; i < sizeof(arr); i++)
    arr[i]->notify_ob_attacked_me(this_object(), ob);  

} /* attacked_by */

/* Function:         do_die()
 * What's it do:     Ordinarily initiates death in slain monster.
 * What's it do now: Destroys some to all gold and armaments with a higher
 *                   chance the bigger the player. */
void
do_die(object killer)
{
    command("say Thanar grant me peace and smite my foe.");
    command("emote attempts to pray through gurgling blood.");
	
	if (killer->query_race_name() != "human")
	{
		this_object()->set_alignment(0);
	}
    ::do_die(killer);
} /* do_die */