/* /d/Faerun/guilds/fire_knives/npc/kyri/
 * 
 *
 * Nerull 2019
 */
 
inherit "std/monster.c";
inherit "/std/combat/unarmed";   /* Get standard unarmed routines */
inherit "/d/Genesis/lib/intro";

#include "/d/Faerun/defs.h"
#include <ss_types.h>
#include <macros.h>
#include <stdproperties.h> 
#include <wa_types.h>
#include <filter_funs.h>
#include "../guild.h";


/*
 * Function name: give_tokens()
 * Description  : Deliver the tokens and receive quest reward
 */
int
give_tokens(string str)
{
    setuid();
    seteuid(getuid());
    
    object token;
    object quest_item1;
    object quest_item2;
    object quest_item3;
    object quest_item4;
    object quest_item5;
    
    object quest_item_reward;
    
    if (str == "evidence")
    {
        if (objectp(token = present("_quest_token", 
        this_player())) 
        && objectp(quest_item1 = present("_quest_item1", 
        this_player()))
        && objectp(quest_item2 = present("_quest_item2", 
        this_player()))
        && objectp(quest_item3 = present("_quest_item3", 
        this_player()))
        && objectp(quest_item4 = present("_quest_item4", 
        this_player()))
        && objectp(quest_item5 = present("_quest_item5", 
        this_player())))
        {
            // If the player has done this quest.
            if(this_player()->test_bit(DOMAIN, SIGNET_RING_QUEST_GROUP, 
            SIGNET_RING_QUEST_BIT))
            {
                write("You give the silver hand, soft crimson handkerchief, "
                +"massive golden belt, broad brimmed hat, "
                +"fur trimmed mantle and the platinum signet ring to "
                +"the slim stern-eyed female human.\n");
                
                command("emote snorts as she looks at you "
                +"and says: Stop wasting my time, you already got "
                +"my approval.\n");
                    
                token->remove_object();
                quest_item1->remove_object();
                quest_item2->remove_object();
                quest_item3->remove_object();
                quest_item4->remove_object();
                quest_item5->remove_object();
                
                this_player()->remove_prop(FIREKNIVES_ON_GURUQUEST);
                
                return 1;
            }
            
            write("You give the silver hand, soft crimson handkerchief, "
            +"massive golden belt, broad brimmed hat, "
            +"fur trimmed mantle and the platinum signet ring to "
            +"the slim stern-eyed female human.\n");
                
            command("emote inspects each of the items with "
            +"a scrutinizing gaze before looking up and "
            +"giving you a lopsided smile.\n");
            
            command("emote says: Excellent! You found the "
            +"items I requested.\n");
                
            command("emote looks thoughtfully at the "
            +"platinum signet ring.\n");
            
            command("emote says: You pass my test. Go see "
            +"Master Assassin Ruddock and maybe he will "
            +"teach you a thing or two..\n");
            
            command("emote says: I think the Grandfather "
            +"himself would want you to keep this ring.\n");
            
            command("emote gives you the "
            +"platinum signet ring.\n");
            
            quest_item_reward = clone_object(FIREKNIVES_GUILD_DIR 
            + "obj/fk_quest_ring");
   
            quest_item_reward->move(this_player(), 1);
            
            command("emote looks at you with a searching gaze.\n");
            
            command("emote says: Well what are you waiting for, an invitation?\n");
            
            command("emote nods her head westwards.\n");
            
            token->remove_object();
            quest_item1->remove_object();
            quest_item2->remove_object();
            quest_item3->remove_object();
            quest_item4->remove_object();
            quest_item5->remove_object();
            
            this_player()->set_bit(SIGNET_RING_QUEST_GROUP, SIGNET_RING_QUEST_BIT);
          
            QUEST_LOG_FILE(SIGNET_RING_QUEST_LNG, SIGNET_RING_QUEST_EXP);
            
            this_player()->remove_prop(FIREKNIVES_ON_GURUQUEST);
            
            return 1;
        }
        
        write(" ... Hmm, no. You still believe you need to collect more "
        +"evidence.\n");
         
        return 1;
    } 
    
    return 0;
}


string
guru_quest_response()
{
    if(this_player()->test_bit(DOMAIN, SIGNET_RING_QUEST_GROUP, 
    SIGNET_RING_QUEST_BIT))
    {
        return "The slim stern-eyed female human says: You've "
        +"already earned your place among us, and proved your " 
        +"worth to train to the full of your capacity. The rest is " 
        +"up to your own initiative.\n";
    }
        
    if (this_player()->query_stat(SS_OCCUP) > 99)
    {
        if (this_player()->query_prop(FIREKNIVES_ON_GURUQUEST))
        {
            return "The slim stern-eyed female human rolls her "
            +"eyes in exasperation and says: I thought I had been "
            +"clear enough? Six items as evidence of the demise of Johan "
            +"Dermont, Sand Dan Glokta, Orban Savrian, Kruppe, "
            +"Havelock Vetinari and Arnt Mittet! When you have "
            +"collected the items, please <show evidence>. "
            +"Now, make haste!\n";
        }
        
        this_player()->add_prop(FIREKNIVES_ON_GURUQUEST, 1);
        
        return "The slim stern-eyed female human says: The nobles "
        +"and some of their associates of Faerun have become too "
        +"comfortable in their positions "
        +"and show themselves freely around now. They impede our "
        +"plans as laid out by our Grandmaster. If you truly believe "
        +"you are to be considered an asset to the Brotherhood, locate "
        +"identify and retire these six named individuals; Johan "
        +"Dermont, Sand Dan Glokta, Orban Savrian, Kruppe, "
        +"Havelock Vetinari and Arnt Mittet. Bring a token from each "
        +"of them and <show evidence> that they dreams have "
        +"permanently ended.\n";        
    }
       
    return "The slim stern-eyed female human says: I have "
    +"no use for you...yet.\n";
}


/*
* Function name: create_monster()
* Description  : Constructor. Edit this to change monster.
*/
nomask void create_monster()
{
    seteuid(getuid());

    
    set_name("kyri");
    set_race_name("human");

    add_adj("slim");
    add_adj("stern-eyed");
    
    set_title("the Deadly Assassin");

    set_gender(G_FEMALE);

    //add_prop(LIVE_I_NEVERKNOWN, 1);
    add_prop(LIVE_I_SEE_DARK, 100);
    add_prop(LIVE_I_SEE_INVIS, 99);
    add_prop(NPC_I_NO_FEAR, 1);
    add_prop(NPC_I_NO_RUN_AWAY, 1);
    add_prop(LIVE_I_NO_STUN, 1);
    add_prop(NPC_M_NO_ACCEPT_GIVE, 1);
    add_prop(OBJ_I_RES_MAGIC, 100);
    add_prop(OBJ_I_NO_ATTACK, 1);
    add_prop(OBJ_I_NO_MAGIC_ATTACK, 1);
    
    set_short("slim stern-eyed female human");
    
    set_long("This is Kyri, Deadly Assassin and trainer for "
    +"the prospects of the Outfit. Although apparently young in "
    +"years, her eyes reveal a depth of experience only seen "
    +"in those who have lived beyond them. Lithe, swift, and "
    +"deadly, she is in charge of training members of "
    +"the Brotherhood.\n");

    add_prop(CONT_I_WEIGHT, 70000);
    add_prop(CONT_I_HEIGHT, 190);

    set_stats(({ 310, 310, 320,
                 243, 320, 280 }));

    set_hitloc_unarmed(A_HEAD, 25, 15, "head");
    set_hitloc_unarmed(A_R_ARM, 25, 10, "right arm");
    set_hitloc_unarmed(A_L_ARM, 25, 10, "left arm");
    set_hitloc_unarmed(A_BODY, 25, 45, "body");
    set_hitloc_unarmed(A_LEGS, 25, 20, "legs");

    set_attack_unarmed(W_LEFT,  55, 55, W_BLUDGEON,
    80, "left fist");

    set_attack_unarmed(W_RIGHT,  55, 55, W_BLUDGEON,
    80, "right fist");
    
    set_attack_unarmed(W_FOOTR, 40, 40, W_BLUDGEON,
    0, "left foot");

    set_attack_unarmed(W_FOOTL, 40, 40, W_BLUDGEON,
    0, "right foot");

    set_skill(SS_UNARM_COMBAT,100);
    set_skill(SS_DEFENCE,100);
    set_skill(SS_AWARENESS,100);
    
    set_act_time(5);
    set_cact_time(5);
    add_act("smile discree");
    add_act("emote sharpens one of her blades with a whetstone.");
    add_act("emote pets one of the guard dogs.");
    add_act("emote adjusts one of the training dummies.");
	
	set_default_answer("The slim stern-eyed female human "
	+"says: Self-sufficience is essential "
	+"to success. Do not pester me with simplistic questions.\n");
	
    add_ask( ({ "quest", "task", "help" }),
    VBFC_ME("guru_quest_response"));
	
	add_ask( ({ "skill", "skills" }),
    "say The skills I teach can only be honed by the best "
	+"of assassins.", 1);
	
	add_ask( ({ "train", "training" }),
    "say We may train a particular skill if you wish, and can.", 1);   

    add_ask( ({ "assassin", "assassins" }),
    "say The Brotherhood of Assassins is based on Loyalty, "
	+"Secrecy, and Skill. In that order.", 1); 	
	
	add_ask( ({ "brotherhood", "outfit" }),
    "say The Brotherhood of Assassins is based on Loyalty, "
	+"Secrecy, and Skill. In that order.", 1); 	
	
	add_ask( ({ "dog", "dogs" }),
    "say They represent loyalty and trust, and impose "
	+"these qualities upon all who cross them.", 1); 

    add_ask( ({ "member", "members" }),
    "say Members of the Brotherhood are encouraged "
	+"to train daily.", 1); 

    add_ask( ({ "sharpen" }),
    "say Keep your blades sharp as well as your "
	+"mind, and you will succeed in your missions.", 1); 	

    add_ask( ({ "pet" }),
    "say They do not like to be petted by just "
	+"anyone, only the chosen to do so.", 1);

    add_ask( ({ "name" }),
    "say My name is Kyri. That is all you need to know.", 1); 			
}


/*
 * Function name:        react_intro
 * Description  :        the npc introduces himself
 * Arguments    :        tp - the player
 */
void
react_intro(object tp)
{
    if (!present(tp, environment(this_object())))
    {
        command("emote narrows his eyes and goes back to his studies.");
        return;
    }

    command("introduce me");
} /* react_intro */


/*
 * Function name:        introduce
 * Description  :        create a delay between intro and reaction
 * Arguments    :        object who - the player
 */
public void
introduce(object who)
{
    set_alarm(itof(2 + random(5)), 0.0, &react_intro(who));
} /* introduce */


void
init_living()
{
    ::init_living();
    
	// GURU quest. 
    add_action(give_tokens, "show");
}