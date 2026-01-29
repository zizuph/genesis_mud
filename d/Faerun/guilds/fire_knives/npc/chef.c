/* /d/Faerun/guilds/fire_knives/npc/chef/
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
    add_name("olaf");

    set_adj("fat");
    add_adj("greasy");

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
    
    set_short("fat greasy male human");
    
    set_long("This is Olaf, Retired Assassin and the chef "
    +"of the outfit. One wonders if Olaf in some point in his "
    +"service grew too close the interest of food and became "
    +"physically unfit for the more agile services assassins "
    +"perform, but atleast his recipes are outstanding.\n");

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
    add_act("smile hungr");
    add_act("emote cleans a couple of stone tables.");
	add_act("emote sneezes.");
	add_act("emote accidently breaks a jar on the floor.");
	add_act("emote stares at a bypassing rat and ignores it.");
	add_act("emote stares at a bypassing mouse and ignores it.");
	add_act("emote opens a bottle of cheap beer and drinks it.");
	add_act("emote smells like a plate of week old fine "
	+"room-tempered seafood.");
	add_act("emote polishes the menu with a greasy rag.");
    add_act("emote leaves for a short moment to the kitchen "
	+"with a few jars and plates before returning to clean "
	+"some more.");
    add_act("emote picks up a broom and swipes the floor, keeping "
	+"it clean and tidy.");
	
	set_default_answer("The fat greasy male human "
	+"says: I don't have that recipe, but if you bring it "
	+"I can cook it .\n");
	
	add_ask( ({ "special" }),
    "say Read the menu to find out more about the special!", 1); 

    add_ask( ({ "fat", "weight" }),
    "say It has never bothered me in accomplishing my tasks.", 1);   

    add_ask( ({ "recipe", "recipes" }),
    "say I have a great knowledge of many recipes but I am "
	+"always eager to learn of more.", 1);

    add_ask( ({ "menu" }),
    "say It's right next to the bar. Feel free to read it.", 1);

    add_ask( ({ "cook" }),
    "say I can cook various dishes. Peruse the menu for "
	+"more information.", 1);

    add_ask( ({ "bar" }),
    "say You can comfortably have a drink at the bar.", 1);

    add_ask( ({ "stool", "stools" }),
    "say The stools are for sitting, though barely "
	+"anyone stays long enough to do so.", 1);

    add_ask( ({ "table", "tables" }),
    "say The tables are for sitting in a group, though "
	+"people are in such a rush these days.", 1);

    add_ask( ({ "kitchen" }),
    "say Ah, my kingdom. The kitchen. If you weren't so "
	+"busy with your training I'd give you a tour of it.", 1); 	 		
       
	add_ask( ({ "quest", "task", "help" }),
    "say Thanks for asking, but I need no help for the moment.", 1);   
}