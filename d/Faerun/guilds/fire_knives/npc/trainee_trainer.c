/* /d/Faerun/guilds/fire_knives/npc/trainee_trainer/
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
    add_name("william");

    add_adj("eldery");
    add_adj("musclebound");

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
    
    set_short("elderly musclebound male human");
    
    set_long("This is William, an assassin well past his "
	+"prime, his eyes still has the vigor of youth as he "
	+"keenly observes you. Although his face is wrinkled "
	+"and scarred his body still rivals that of those in "
	+"their prime, no doubt his experience more than makes "
	+"up for it. William is responsible for teaching "
	+"the skills used by the Brotherhood Trainees.\n");

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
    add_act("mutter");
    add_act("emote stretches his weary back.");
	add_act("emote picks a tooth with one of his long sharp daggers.");
	add_act("emote does an acrobatic maneuver with both of his "
	+"long sharp daggers.");
	add_act("emote coughs heavily.");
	add_act("emote eats a field ration.");
	add_act("emote ponders about cleaning up the place.");
	add_act("emote sharpens one of his long sharp daggers.");
	add_act("emote glances at you with one of his weary eyes.");
    add_act("emote drinks a cup of cold tea.");
    add_act("emote lacerates a bypassing rat with one of his "
	+"long sharp daggers.");
	
	set_default_answer("The elderly musclebound male human "
	+"says: Youth is wasted on the young, and you're "
	+"wasting yours with such questions.\n");
	
	add_ask( ({ "skill", "skills" }),
    "say Those who wish to one day be recognized as assassins "
	+"must prove their worth to me.", 1); 

    add_ask( ({ "train", "training" }),
    "say We may train according to the rank "
	+"you've earned within the Brotherhood.", 1); 

    add_ask( ({ "dummy", "dummies" }),
    "say If you're not practising every day, you're "
	+"not improving every day.", 1);

    add_ask( ({ "ration", "rations" }),
    "say Keeping your body fit is essential to "
	+"improve. Eat, drink, and sleep.", 1); 

    add_ask( ({ "sack", "sacks" }),
    "say They can take a beating far worse than "
	+"you can dish out. Prove me wrong.", 1);

    add_ask( ({ "mats" }),
    "say It's easier to replace one of those "
	+"than to clean your broken teeth from the floor.", 1);

    add_ask( ({ "old", "age" }),
    "say I was young and eager like you once. You "
	+"need patience and attention to detail.", 1); 

    add_ask( ({ "cough" }),
    "say Concerned with my health? Worry not. I will "
	+"outlive your skills without a sweat.", 1);  

    add_ask( ({ "experience" }),
    "say You earn it twofold: surviving and meeting your quota.", 1);  			
       
	add_ask( ({ "quest", "task", "help" }),
    "say Thanks for asking, but I need no help for the moment.", 1);   
}