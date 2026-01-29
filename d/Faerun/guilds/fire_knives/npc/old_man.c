/* /d/Faerun/guilds/fire_knives/npc/old_man/
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
    set_name("_olufander");
    add_name("man");
    add_name("old man");
    add_name("decrepit man");
    add_name("old decrepit man");

    add_adj("decrepit");
    add_adj("old");

    set_gender(G_MALE);

    add_prop(LIVE_I_NEVERKNOWN, 1);
    add_prop(NPC_I_NO_FEAR, 1);
    add_prop(NPC_I_NO_RUN_AWAY, 1);
    add_prop(NPC_M_NO_ACCEPT_GIVE, 1);
    
    set_short("old decrepit man");
    
    set_long("A black-clad man past his prime. Once a dashing "
    +"officer destined for great things, now an old decrepit "
    +"human whose once graceful gait has been replaced with a "
    +"painful limp to the rhythmn of his cane on which he heavily "
    +"leans. His bent back rises in a hunch, making him face "
    +"downward and hiding his teethless grimace of pain caused "
    +"by the torture of each one of his steps.\n");

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
}