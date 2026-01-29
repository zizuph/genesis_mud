/* /d/Faerun/guilds/fire_knives/npc/shady_man/
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
    set_name("_otrollo");
    add_name("man");
    add_name("shady man");
    add_name("vigilant man");
    add_name("shady vigilant man");

    add_adj("shady");
    add_adj("vigilant");

    set_gender(G_MALE);

    add_prop(LIVE_I_NEVERKNOWN, 1);
    add_prop(NPC_I_NO_FEAR, 1);
    add_prop(NPC_I_NO_RUN_AWAY, 1);
    add_prop(NPC_M_NO_ACCEPT_GIVE, 1);
    
    set_short("shady vigilant man");
    
    set_long("This shady individual is a retired member of the "
    +"outfit. He is rather bald and old, but his eyes sport "
    +"a shine of interest and curiousity. Clad in a dark leather "
    +"coat with many pockets, his appearance somewhat blends "
    +"with the environment. He is serving as a black market "
    +"liaison and may have some rare and special items for "
    +"trade. <check display table> will reveal what he has "
    +"in store.\n");

    add_prop(CONT_I_WEIGHT, 50000);
    add_prop(CONT_I_HEIGHT, 160);

    set_stats(({ 135, 134, 150,
                 110, 120, 100 }));

    set_hitloc_unarmed(A_HEAD, 25, 15, "head");
    set_hitloc_unarmed(A_R_ARM, 25, 10, "right arm");
    set_hitloc_unarmed(A_L_ARM, 25, 10, "left arm");
    set_hitloc_unarmed(A_BODY, 25, 45, "body");
    set_hitloc_unarmed(A_LEGS, 25, 20, "legs");

    set_attack_unarmed(W_LEFT,  15, 15, W_BLUDGEON,
    50, "left fist");

    set_attack_unarmed(W_RIGHT,  15, 15, W_BLUDGEON,
    50, "right fist");
    
    set_attack_unarmed(W_FOOTR, 15, 15, W_BLUDGEON,
    0, "left foot");

    set_attack_unarmed(W_FOOTL, 15, 15, W_BLUDGEON,
    0, "right foot");

    set_skill(SS_UNARM_COMBAT,50);
    set_skill(SS_DEFENCE,55);
    set_skill(SS_AWARENESS,50);
	
	set_act_time(5);
    set_cact_time(5);
    add_act("smile myst");
    add_act("emote cleans the area with a fine broom.");
	add_act("emote adjusts the heavy velvet drapes.");
	add_act("emote polishes the display table.");
	add_act("emote dusts some shelves.");
	add_act("emote eats some exotic flavored food.");
	add_act("emote moves some of the souvernirs around.");
	add_act("emote swats a bypassing fly with his fine broom.");
	add_act("emote opens a jar of cookies and eats the content.");
    add_act("emote counts a few of his many platinum coins.");
    add_act("emote drinks a cup of exotic herbal tea.");
	
	set_default_answer("The shady vigilant man "
	+"says: Hmm, I'm not familiar with that, but I will ask around.\n");
	
	add_ask( ({ "black market" }),
    "say A truly libertarian market without any "
	+"third party intereference, where the best items are found.", 1);  

    add_ask( ({ "symbol", "symbols" }),
    "say The symbols represent various things in the manifold "
	+"worldly cultures. All a matter of perspective, same as price.", 1); 

    add_ask( ({ "travel", "travels" }),
    "say It's important to travel far and wide, and often, to learn "
	+"of the best routes for items and meet connoisseurs.", 1);

    add_ask( ({ "culture", "cultures" }),
    "say Cultures around the world are superficially diverse. "
	+"In all of their cores, though, they're the same.", 1);

    add_ask( ({ "souvenirs", "souvernir" }),
    "say Some of these items haven't a practical use and are "
	+"mere mementos of cultural and personal value.", 1); 

    add_ask( ({ "liaison" }),
    "say A connection between a network and another is "
	+"important to have to tap into the world's vast potential.", 1);

    add_ask( ({ "display", "display table", "table" }),
    "say Feel free to peruse the currently available items. They "
	+"are displayed on the table.", 1); 

    add_ask( ({ "item", "items" }),
    "say All of these items have a corresponding price attached "
	+"to them. They're yours if you can meet it.", 1); 

    add_ask( ({ "uniform", "uniforms" }),
    "say I do not sell those, nor should you. Some things "
	+"are earned.", 1);   	
       
	add_ask( ({ "quest", "task", "help" }),
    "say Thanks for asking, but I need no help for the moment.", 1);   
}