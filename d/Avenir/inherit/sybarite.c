#pragma strict_types
/* -*-C++-*-
 * file name:     /d/Avenir/inherit/sybarite.c
 * creator(s):    Lilith    9/17/97
 * purpose:       Inheritable component for Sybarites. 
 *                This file will add the cmdsoul below:
 *                   /d/Avenir/common/obj/npc_soul.c
 *
 * note:          To provide attacks and combat abilities common
 *                to humanoid Sybarites. For use with the
 *                special_attack() function.
 *
 *                See below for list of functions/abilities
 *                and instructions for usage.
 * last update:             11/26/97
 * bug(s):
 * to-do:
 *
 *      Available combat specials: 
 *  Function   Effect
 *  ===================================================================
 *  cdisarm    Disarms (non-damaging attack).
 *  punch      Damaging unarmed attack.
 *  neck       Damaging weapon attack, targets neck.
 *  pluck      Damaging weapon attack.
 *  pommel     Damaging weapon attack, targets face.
 *  skick      Damage&stun unarmed attack, targets legs.
 *
 *      Non-combat special abilities:
 *  Function   Effect
 *  ===================================================================
 *  cure       Cures npc of poisons.
 *  heal       40% chance of healing w/ random messages.
 *
 *
 * --------------------------------------------------------------------
 *
 *  To use the special attack functions, add the following function to
 *  your npc:
 *
 *   int
 *   special_attack(object target)
 *   {
 *       switch (random(6))
 *       {
 *           case 1: command("punch"); 
 *              return 1;    // We are done with this round.
 *           case 2: command("heal me");
 *              return 0;    // Allow another attack in this round.
 *           default: 
 *       }
 *       return 0;
 *   }
 */

inherit  "/d/Avenir/inherit/monster";
#include "/d/Avenir/include/relation.h"

public void
create_sybarite(void)
{
    setuid();
    seteuid(getuid());

    /* Lets make it sybarite */
    add_name("sybarite");
    MAKE_SYBARITE;

    /* Lets add the command soul */
    add_cmdsoul("/d/Avenir/common/obj/npc_soul");
    update_hooks();
}

public void
create_monster(void)
{
    create_sybarite();
}

public string 
query_exp_title(void)
{
    return "sybarite "+ ::query_exp_title();
}

private static string ave_sound = one_of_list(({ "lilting", "sybarite" }));

public string 
race_sound(void)
{           
    return "speaks with a "+ ave_sound +" accent";   
}

/*
 *  Function:   
 *  Description:
 *  Requirements:
 *  Damaging:  
 */
