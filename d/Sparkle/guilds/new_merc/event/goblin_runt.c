/*
 *  /d/Sparkle/guilds/new_merc/event/goblin_runt.c
 *
 *  The lowest-level goblin attacker for the raid on Sparkle that will
 *  lead to the opening of the Free Mercenary Guild.
 *
 *  Created August 2009, by Cooper Sherry (Gorboth)
 */
#pragma strict_types

inherit "/std/monster";
inherit "/d/Emerald/lib/aid_npc";

#include <filepath.h>
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
public string      Goblin_Type = "runt";

/* Prototypes */
public void        create_monster();
public void        arm_me();
public int         special_attack(object enemy);
public void        notify_death(object killer);

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
    add_name( ({ "runt", GOBLIN_RUNT, EVENT_GOBLIN }) );
    add_adj( ({ "goblin" }) );

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

    set_aggressive(1, 60);
} /* create_monster */


/*
 * Function name:        arm_me
 * Description  :        set up the npc with any gear it needs
 */
public void
arm_me()
{
    object  arm;

    arm = clone_object(EVENT_DIR + "crude_sword");
    arm->move(this_object());
    arm = clone_object(EVENT_DIR + "crude_leather");
    arm->move(this_object());

    command("wear all");
    command("wield all");
} /* arm_me */


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
    int     attack_type = random(4); /* 25% chance to do special */
    int     runts = 0; /* How many runts are in the room? */
    mixed  *targets = FILTER_LIVE(all_inventory(environment(
                       this_object())));
    string  bite_loc;
    int     bite_damage;

    /* We'll only let the runts try this once per 10 combat rounds. */
    if (attack_type)
    {
        return 0;
    }

    if (Currently_Attacking)
    {
        Currently_Attacking = 0;

        return 0;
    }

    foreach(object target: targets)
    {
        runts += target->id(GOBLIN_RUNT);
        target->set_currently_attacking();
    }

    if (runts < 3)
    {
        this_object()->command("emote looks desperately around for"
          + " backup, spoiling his combat stance.");
        return 1;
    }

    enemy->catch_msg("The goblin runts in the room suddenly leap"
      + " into a formation of sorts. One jumps on your chest while"
      + " the others circle around behind you, biting ferociously at"
      + " your exposed back with their horrible teeth!\n");
    tell_room(environment(enemy),
        "The goblin runts in the room suddenly leap into a formation of"
      + " sorts. While one jumps onto the chest of " + QTNAME(enemy)
      + ", the others run around behind " + enemy->query_objective()
      + " where they leap onto " + enemy->query_possessive() + " back"
      + " and begin to ravage " + enemy->query_objective() + " with"
      + " their ferocious teeth!\n", enemy);

    runts--;

    while (runts)
    {
        bite_loc = one_of_list( ({ "neck", "left shoulder",
                                   "right shoulder", "back" }) );

        bite_damage = 40 + random(25);

        /* Lets make it a 50% chance that the runts fail to bite. */
        if (random(2))
        {
            enemy->catch_msg("You feel teeth barely missing your "
              + bite_loc + "!\n");
            tell_room(environment(enemy),
                QCTNAME(enemy) + " barely avoids being bitten on the "
              + bite_loc + "!\n", enemy);
        }
        else
        {
            enemy->catch_msg("You are bitten on the " + bite_loc + "!\n");
            tell_room(environment(enemy),
                QCTNAME(enemy) + " is bitten on the " + bite_loc + "!\n",
                enemy);

            enemy->heal_hp(-(bite_damage));

            write_file(LOG_DIR + "bite_log",
               TIME2FORMAT(time(), "mm/dd/yyyy") + " ("
             + ctime(time())[11..18] + ") "
             + capitalize(this_player()->query_real_name()) 
             + " bitten for " + bite_damage + " hp.\n");            


            if (enemy->query_hp() < 1)
            {
                enemy->do_die();

                write_file(LOG_DIR + "bite_log",
                   TIME2FORMAT(time(), "mm/dd/yyyy") + " ("
                 + ctime(time())[11..18] + ") "
                 + capitalize(this_player()->query_real_name()) 
                 + " DIED from the bite!\n");

                /* If the player died, no need to keep biting them. */
                runts = 0;
            } /* if (enemy->query_hp() < 1) */
        } /* else */

        runts--;
    } /* while (runts) */

    return 1;
} /* special_attack */


/*
 * Function name:        assist
 * Description  :        When assisting other goblins that get attacked,
 *                       we display what is happening.
 */
public void
assist()
{
    /* Too spammy otherwise */
    if (random(7))
    {
        return;
    }

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
    /* Too spammy otherwise */
    if (random(7))
    {
        return;
    }

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


/*
 * Function name:        notify_death
 * Description  :        Notify onlookers of my death
 * Arguments    :        object killer - the object that killed me
 *
 * We redefine this so that Gorboth can get notifications of who is
 * dying where and by whom.
 */
public void
notify_death(object killer)
{
    ::notify_death(killer);

    TELL_G(" -*-*-*-* A " + Goblin_Type + " was killed by "
      + capitalize(killer->query_real_name()) + " at "
      + FILE_NAME(MASTER_OB(environment(this_object()))) + "!");
} /* notify_death */