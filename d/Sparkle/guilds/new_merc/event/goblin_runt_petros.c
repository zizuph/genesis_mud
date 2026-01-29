/*
 *  /d/Sparkle/guilds/new_merc/event/goblin_runt.c
 *
 *  The lowest-level goblin attacker for the raid on Sparkle that will
 *  lead to the opening of the Free Mercenary Guild.
 *
 *  Created August 2009, by Cooper Sherry (Gorboth)
 *
 *  Expected damage currently:
 *     Number of runts per room            Expected damage per minute
 *    ------------------------------------+---------------------------
 *                                      3 | 558
 *                                      4 | 1116
 *                                      5 | 1860
 *                                      6 | 2790
 */
#pragma strict_types

inherit "/std/monster";
inherit "/d/Emerald/lib/aid_npc";

#include <filter_funs.h>
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <time.h>
#include "../merc_defs.h"


/* Global Variables */
public int         Currently_Attacking = 0; /* true if the npc is currently
                                             * participating in a special,
                                             * and thus may not enact a
                                             * new one.
                                             */

/* Prototypes */
public void        create_monster();
public void        arm_me();
public int         special_attack(object enemy);

public void        set_currently_attacking() { Currently_Attacking = 1; }


/*
 * Function name:        create_monster
 * Description  :        The constructor for the monster
 */
public void
create_monster()
{
    set_name("goblin");
    set_race_name("goblin");
    add_name( ({ "runt", GOBLIN_RUNT }) );

    set_short("goblin runt");
    set_long("This goblin looks fairly weak and small. Nonetheless, it"
      + " looks as if he has a great deal of confidence and malevolence"
      + " in his every move.\n");

    set_stats( ({ 30 + (random(30)),
                  25 + (random(25)),
                  30 + (random(30)),
                  10 + (random(10)),
                  7  + (random(7)),
                  40 + (random(40)) }) );
                  
    set_skill(SS_WEP_SWORD,   50);
    set_skill(SS_AWARENESS,   50);
    set_skill(SS_DEFENCE,     50);
    set_skill(SS_PARRY,       50);

    add_act("cackle");
    add_act("say At last! At last! Sparkle will burn!!");
    add_act("say With all my big brothers around, I'm invincible!!");
    add_act("say Will they really let me burn the boats all by myself?");

    add_cact("emote shrieks in fright!");
    add_cact("emote runs around, trying not to get hurt.");
    add_cact("shout Kill! Kill!!!");

    /* We assist other goblins who get attacked. */
    set_give_aid(1);
} /* create_monster */


/*
 * Function name:        arm_me
 * Description  :        set up the npc with any gear it needs
 */
public void
arm_me()
{
    add_weapon(EVENT_DIR + "crude_sword");
    add_armour(EVENT_DIR + "crude_leather");
} /* arm_me */


#define ON_PLAYER_FACE_PROP "_on_player_face"

/*
 * Function name:        special_attack
 * Description  :        every so often we'll do a special attack
 * Arguments    :        object enemy - the person we're attacking
 * Returns      :        int 0 - don't do the special
 *                           1 - do the special attack
 */
public int
special_attack(object enemy)
{
    object * runts;
    
    runts = filter(all_inventory(environment(this_object())), &->id(GOBLIN_RUNT));
    foreach (object runt : runts)
    {
        if (time() - runt->query_prop(ON_PLAYER_FACE_PROP) > 5)
        {
            runt->remove_prop(ON_PLAYER_FACE_PROP);
            continue;            
        }
        
        // If we get here, that means that the current runt is the leader
        // who jumped on the face. We go ahead and do the attack
        // << Insert bite code for this goblin >>        
        return 1;
    }
    
    // If we get here, that means that there are no current runts on
    // the face of the player.
    if (!random(4)) // 25% chance of landing on face
    {
        // << Insert landing on face messages >>
        add_prop(ON_PLAYER_FACE_PROP, time());
        return 1;
    }
    
    return 0; // allow a normal attack
} /* special_attack */


/*
 * Function name:        assist
 * Description  :        When assisting other goblins that get attacked,
 *                       we display what is happening.
 */
public void
assist()
{
    command(one_of_list( ({
        "shout Brother need help!! Runt help brother!!!",
        "emote screams and charges to assist his brother.",
        "shout Brother not fight alone!! Runt help!",
        "shout Quick!! Help brother!!!" }) ) );
} /* assist */


/*
 * Function name:        ask_for_assistance
 * Description  :        When we need assistance from other goblins,
 *                       this happens.
 */
public void
ask_for_assistance()
{
    command(one_of_list( ({
        "emote screams for help from his brothers!",
        "emote bellows loudly, screaming for help!",
        "emote wails in terror and cries out for help!",
        "shout Brothers!!! Come help!!!" }) ) );
} /* ask_for_assistance */


/*
 * Function name:       attacked_by
 * Description:         This routine is called when we are attacked.
 * Arguments:           ob: The attacker
 *
 * Mask to allow for assistance from other goblins.
 */
public void
attacked_by(object ob)
{
    ::attacked_by(ob);
    get_assistance(ob);
} /* attacked_by */