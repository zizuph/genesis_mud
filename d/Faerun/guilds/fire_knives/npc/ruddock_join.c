/* /d/Faerun/guilds/fire_knives/npc/ruddock_join/
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
    add_name("ruddock");
    add_name("richard");

    add_adj("bald");
    add_adj("muscular");

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
    
    set_short("bald muscular male human");
    
    set_long("This is Richard D. Ruddock, Master Assassin of the "
    +"Fire Knives. He is a bald muscular male human of medium "
    +"stature. Broad shoulders form like mountains descending "
    +"from fibrous trapezius out of which his thick neck holds "
    +"a face sculpted in an eternal smirk. Bulging veins run "
    +"down from his forehead down between his muscles and are "
    +"lost within his extensive chest. Despite his bulk, his "
    +"movements have a feline quality that defies your "
    +"understanding of anatomy. One of the many secrets "
    +"kept behind the intense gaze of his pure white eyes "
    +"that could be seeing everything or nothing at all.\n");

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
}