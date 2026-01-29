/*
 * /d/calia/kcirderf/baby_antwerp.c
 *
 * This is a baby version of the antwerp. When you hit the adult with enough
 * impale or slashing damage it will "pop" into several of these. 
 * Warning: This is an extremely silly monster.  
 * 
 * HISTORY: [98-11-22] Created by Kcirderf 
 *
 * Copyright (C): Kcirderf 1998
 *
 */ 

inherit "/std/creature"; 
inherit "/std/combat/unarmed"; 
inherit "/std/act/action";

#include <stdproperties.h> 
#include <wa_types.h> 
#include <ss_types.h> 
#include <const.h>
#include <macros.h>
#include <tasks.h> 

#define H_BODY 0 
#define H_FACE 1
 
string *bounce_normal = ({"aimlessly" , "cluelessly" , "foolishly", "goofily",
    "gratuitously", "inanely", "judiciously", "merrily", "mysteriously", 
    "obnoxiously", "playfully", "randomly", "rediculously", "stupidly", 
    "unceasingly", "wildly" }); 

string normal_bounce(); 

object visible_to; 

/*
 * Function name:   normal_bounce
 * Description:     Makes the antwerp bounce in a random way 
 * Arguments:       none
 * Returns:         string
 */
string 
normal_bounce()
{
    return "bounce " + bounce_normal[random(sizeof(bounce_normal))]; 
}

int 
check_visible()
{
    int visibility = 1;
    object player = this_player();

    if (player->query_name() == visible_to->query_name()) 
    {
        visibility = 0;
    }

    return visibility; 
}

void
set_visible(object player)
{
    visible_to = player; 
}

create_creature()
{
    set_name("antwerp"); 
    set_race_name("antwerp"); 
    set_adj(({"bouncy", "blue", "baby"})); 
    set_short("bouncy blue baby antwerp"); 
    set_gender(G_NEUTER); 
    set_long("By golly, it's a baby Antwerp! This cute little fellow is a " + 
        "smaller version of the adult. A blue egg-shaped blob of rubbery " + 
        "flesh, with four red eyes, a snout, and a pair of horns. Unlike " + 
        "it's 'parent', it's bouncing quickly all over the place.\n"); 
    
    set_stats(({25 + random(10), 25 + random(10), 25 + random(25), 
        5, 5, 15 + random(10)})); 

    set_skill(SS_DEFENCE, 30); 
    set_skill(SS_UNARM_COMBAT, 40); 

    set_hitloc_unarmed(H_BODY, ({ 15, 25, 50,}), 95, "body");   
    set_hitloc_unarmed(H_FACE, ({ 15, 25, 50,}), 5, "face");

    add_prop(LIVE_I_NEVERKNOWN, 1); 
    add_prop(LIVE_I_NO_CORPSE, 1); 
    add_prop(NPC_I_NO_LOOKS, 1);    
    add_prop(LIVE_I_QUICKNESS, 125); 
    add_prop(OBJ_M_NO_ATTACK, "The baby antwerp is too cute to attack. " + 
        "Besides, it's too quick to catch.\n"); 

    add_prop(OBJ_I_INVIS, check_visible); 

    set_act_time(1); 
    add_act("@@normal_bounce@@"); 

}


