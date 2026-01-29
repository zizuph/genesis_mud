/* /d/Faerun/guilds/fire_knives/npc/herbalist/
 * 
 *
 * Nerull 2019
 */
 
inherit "std/monster.c";
inherit "/std/combat/unarmed";   /* Get standard unarmed routines */

#include <ss_types.h>
#include <macros.h>
#include <stdproperties.h> 
#include <wa_types.h>
#include <filter_funs.h>
#include "../guild.h";


/*
* Function name: create_monster()
* Description  : Constructor. Edit this to change monster.
*/
nomask void create_monster()
{
    seteuid(getuid());

    set_race_name("human");
    add_name("tyrell");

    set_adj("adolescent");
    add_adj("attentive");

    set_gender(G_MALE);

    add_prop(LIVE_I_NEVERKNOWN, 1);
    add_prop(LIVE_I_SEE_DARK, 100);
    add_prop(LIVE_I_SEE_INVIS, 99);
    add_prop(NPC_I_NO_FEAR, 1);
    add_prop(NPC_I_NO_RUN_AWAY, 1);
    add_prop(LIVE_I_NO_STUN, 1);
    add_prop(NPC_M_NO_ACCEPT_GIVE, 1);
    add_prop(OBJ_I_RES_MAGIC, 100);
    add_prop(OBJ_I_NO_ATTACK, 1);
    add_prop(OBJ_I_NO_MAGIC_ATTACK, 1);
    
    set_short("adolescent attentive male human");
    
    set_long("This learning assassin was recruited from "
    +"his clan as a young boy where he was employed tending the "
    +"flora and fauna of his village. Eager to learn and sporting "
    +"a great desire to earn a living by virtue of his abilities, he "
    +"now serves storing, buying, caring for, and selling the herbs "
    +"brought in by all members of the brotherhood until his "
    +"training begins.\n");

    add_prop(CONT_I_WEIGHT, 1400000);
    add_prop(CONT_I_HEIGHT, 170);

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
    add_act("peer");
    add_act("emote stashes away some dried herbs.");
	add_act("emote opens a jar containing herbs and count the "
	+"content of it.");
	add_act("emote hungrily eats a red-spotted leaf.");
	add_act("emote brushes away a passing spider with his hand.");
	add_act("emote eats a black mushroom.");
	add_act("emote cleans the place with a broom.");
	add_act("emote tends to a few growing herbs in some pots.");
	add_act("emote waters a flower.");
    add_act("emote counts a few seeds before storing them away in "
	+"a jar.");
    add_act("emote drinks a cup of herbal tea.");
	
	set_default_answer("The adolescent attentive male human "
	+"says: I have yet to find such a herb. Where does it grow?\n");
       
	add_ask( ({ "quest", "task", "help" }),
    "say Thanks for asking, but I need no help for the moment.", 1); 
	
	add_ask( ({ "herb", "herbs" }),
    "say Herbs are very important and grow throughout the "
	+"realms. Knowledge of them is of vital importance.", 1); 
	
	add_ask( ({ "herblore" }),
    "say The way to acquire it is to investigate where "
	+"what grows, study its growth, and take notes.", 1); 
	
	add_ask( ({ "counter" }),
    "say Beautiful, isn't it? I try to keep it as clean "
	+"as possible.", 1); 
	
	add_ask( ({ "tome", "catalogue" }),
    "say I catalogue all the herbs we have in store for "
	+"both purchase and information.", 1); 
	
	add_ask( ({ "smell", "aroma" }),
    "say A fantastic aroma, isn't it? The smell of life "
	+"itself... And death.", 1); 
	
	add_ask( ({ "plant" }),
    "say If you were so inclined, you could learn to "
	+"plant herbs of your liking. It is a fine skill to learn.", 1); 
	
	add_ask( ({ "garden" }),
    "say If you had access to a garden, you could plant "
	+"some herbs in it.", 1);

    add_ask( ({ "flowers", "flower" }),
    "say Caring for plants require finesse and attention "
	+"to detail. Vital skills.", 1);

    add_ask( ({ "access" }),
    "say We don't have access to one in the castle, but "
	+"perhaps we will one day.", 1); 	 	
}