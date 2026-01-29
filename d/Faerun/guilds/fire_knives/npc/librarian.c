/* /d/Faerun/guilds/fire_knives/npc/librarian/
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
    add_name("jon");

    set_adj("sharp-eyed");
    add_adj("old");

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
    
    set_short("sharp-eyed old male human");
    
    set_long("Dressed in comfortable robes, this retired assassin "
    +"continues serving the brotherhood as a record keeper and "
    +"maintainer of all documents belonging to it. Although his "
    +"time in the field came to an end, his skills did not, and "
    +"both his physique and keen eyes speak volumes of his "
    +"capacities and eagerness to slip a knife as a last "
    +"resort.\n");

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
    add_act("ponder");
    add_act("emote reads a few scrolls.");
	add_act("emote pens a scroll and stores it in one of the many shelves.");
	add_act("emote brushes some dust from some books.");
	add_act("emote mutters about something else while reading a recent "
	+"submitted scroll.");
	add_act("emote pokes a tiny spider hanging from a thread of cobweb.");
	add_act("emote coughs violently due to all the present dust in the air.");
	add_act("emote stores something in a bookshelf.");
	add_act("emote throws a book at some bypassing mouse while "
	+"cursing violently.");
    add_act("emote searches for his monocle, but fails to find it.");
    add_act("emote drinks a cup of herbal tea.");
	
	set_default_answer("The sharp-eyed old male human "
	+"says: Shh! To break the silence with such nonsense - the nerve!\n");
	
	add_ask( ({ "robes" }),
    "say A uniform, a weapon, a mind... All are tools. Pick the "
	+"right one for your job.", 1); 

    add_ask( ({ "book", "books", "scroll", "scrolls" }),
    "say Train your mind as well as your body. Instruct and prepare "
	+"yourself for your tasks.", 1); 

    add_ask( ({ "dust" }),
    "say It's no easy task to keep such things tidy, nor "
	+"is it a priority.", 1);

    add_ask( ({ "brotherhood" }),
    "say The Brotherhood has a rich and ancient history. You "
	+"should read up on it.", 1); 

    add_ask( ({ "assassin", "assassins" }),
    "say Such a word! We don't merely 'kill'. We remove "
	+"obstacles, make way for progress.", 1); 

    add_ask( ({ "progress" }),
    "say Too many men chew on last year's tobacco even "
	+"after it has lost all its flavor.", 1);

    add_ask( ({ "mouse", "mice" }),
    "say Dreadful creatures, I tell you. Pests worse "
	+"than the dust.", 1); 

    add_ask( ({ "topic", "topics" }),
    "say Feel free to browse through them. There are "
	+"plenty of tomes on each one.", 1);

    add_ask( ({ "writing" }),
    "say You can compose a scroll and submit it for my "
	+"review. We will see if it's worthy of publication.", 1);   			
       
	add_ask( ({ "quest", "task", "help" }),
    "say Thanks for asking, but I need no help for the moment.", 1);   
}