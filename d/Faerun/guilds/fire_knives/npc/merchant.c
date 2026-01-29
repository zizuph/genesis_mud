/* /d/Faerun/guilds/fire_knives/npc/merchant/
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
    add_name("oddleif");

    set_adj("well-travelled");
    add_adj("sinewy");

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
    
    set_short("well-travelled sinewy male human");
    
    set_long("This trader of the brotherhood specialized in traveling "
    +"during his training years and decided to serve as a dedicated "
    +"tradesman for the brotherhood. A trained assassin like every "
    +"other, his eloquence and charisma allow him to be of more use "
    +"acquiring and selling diverse goods brought from his many "
    +"travels.\n");

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
    add_act("mutter");
    add_act("emote checks the store inventory.");
	add_act("emote counts a few gold coins.");
	add_act("emote puts some iron sword back in the store room.");
	add_act("emote eats some dried salty meat.");
	add_act("emote ponders about the weather.");
	add_act("emote opens a box of candy and eats the content.");
	add_act("emote cleans the floor with a broom.");
	add_act("emote writes a message to someone and sends it "
	+"away with a black crow.");
    add_act("emote smiles greedily.");
    add_act("emote drinks a cup of mushroom tea. The odor from it "
	+"smells outright horrible.");
	
	set_default_answer("The well-travelled sinewy male human "
	+"says: Hmm, no, I don't think I have that in store.\n");
	
	add_ask( ({ "item", "items" }),
    "say I carry various items of interest. Take a look.", 1); 

    add_ask( ({ "counter" }),
    "say Beautiful, isn't it? I try and keep it clean.", 1);

    add_ask( ({ "inventory" }),
    "say You can list it and see what I have for sale.", 1);

    add_ask( ({ "rarity" }),
    "say The rarity of an item increases the price. It "
	+"all depends on the market.", 1);

    add_ask( ({ "buy" }),
    "say Feel free to do so!", 1);

    add_ask( ({ "sell" }),
    "say I may be interested in an item you have to sell, indeed.", 1);

    add_ask( ({ "trading" }),
    "say A very useful and taxing profession which involves a lot "
	+"of travel.", 1);

    add_ask( ({ "price" }),
    "say The price of an item depends on its rarity.", 1);

    add_ask( ({ "value" }),
    "say Ah, good question. A price is economics, but the "
	+"value of an item depends on your circumstances.", 1); 	 		
       
	add_ask( ({ "quest", "task", "help" }),
    "say Thanks for asking, but I need no help for the moment.", 1);   
}