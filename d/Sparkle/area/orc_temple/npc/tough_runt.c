/*
 *  /d/Sparkle/guilds/new_merc/event/tough_runt.c
 *
 *  A slightly toughter version of the runt. This particular fellow is
 *  stationed outside the doors on the first level and has keys to the
 *  locks.
 *
 *  Created August 2009, by Cooper Sherry (Gorboth)
 */
#pragma strict_types
#include "../defs.h"

inherit NPC_DIR + "temple_npc";

#include <filepath.h>
#include <filter_funs.h>
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <time.h>


/* Definitions */
#define            GOBLIN_RUNT     "_orc_temple_goblin_runt"
#define            ORIGIN_ROOM     "_orc_temple_runt_origin"

/* Global Variables */
public int         Currently_Attacking = 0; /* true if the npc is currently
                                             * participating in a special,
                                             * and thus may not enact a
                                             * new one.
                                             */
public string      Goblin_Type = "runt";

/* Prototypes */
public void        create_temple_npc();
public void        arm_me();
public void        add_key();
public int         special_attack(object enemy);
public string      default_answer();
public void        intro_responses(object tp);
public int         not_here_func();
public void        my_actions();
public void        return_to_post();

public void        set_currently_attacking() { Currently_Attacking = 1; }


/*
 * Function name:        create_temple_npc
 * Description  :        The constructor for the monster
 */
public void
create_temple_npc()
{
    set_name("orc");
    add_name("guard");
    set_race_name("orc");
    add_name( ({ "runt", GOBLIN_RUNT, ORC_TEMPLE_NPC, "goblin" }) );
    add_adj( ({ "tough" }) );

    set_short("tough runt");
    set_long("This runt looks a bit tougher than the others in the"
      + " area. He still isn't very big, though. The look in his"
      + " eye means business, that is for sure! Perhaps he is"
      + " here to guard something?\n");

    set_stats( ({ NPC_RUNT_STR + 1,
                  NPC_RUNT_DEX + 1,
                  NPC_RUNT_CON + 1,
                  NPC_RUNT_INT,
                  NPC_RUNT_WIS,
                  NPC_RUNT_DIS + 1,
               }) );
                  
    set_skill(SS_WEP_SWORD,   10);
    set_skill(SS_WEP_AXE,     10);
    set_skill(SS_WEP_CLUB,    10);
    set_skill(SS_WEP_POLEARM, 10);
    set_skill(SS_WEP_KNIFE,   10);
    set_skill(SS_AWARENESS,   50);
    set_skill(SS_DEFENCE,     10);
    set_skill(SS_PARRY,       10);

    add_cact("emote yells in alarm!");
    add_cact("emote runs around, trying not to get hurt.");
    add_cact("shout Kill! Kill!!!");

    set_job_response("Job? Runt protect dungeon from sneaky ones!");
    set_dungeon_response( ({
        "Dungeons good for runts! Runts like smells here!",
        "You come to dungeons? You prisoner maybe? Soon will be!",
        "Grunt like dungeons, but want more food!" }) );
    set_demon_response( ({
        "Eeeek! Demon too scary for runt! Not talk about demon!",
        "Priest say demon hungry. Maybe demon eat all food!",
        "Not talk about demon! Priest get angry!" }) );
    set_prisoner_response( ({
        "Hee hee! Prisoners so fun to find. Bring to dungeon and make cry!",
        "Runt so hungry, maybe eat prisoner or two!",
        "Every day, find more prisoners. Runt have so much fun!" }) );
    set_runt_response( ({ "Runt? That me!" }) );
    set_warrior_response( ({ "Warriors tough, but too bossy!" }) );
    set_priest_response(
        ({ "Priest? They smart. Runt scared of priest!" }) );
    set_jailer_response("Jailer think he big time. He not so big!");
    set_hp_response("High Priest? He big time. Runt shut up when"
      + " he come.");
    set_give_response("Not want! You keep!");
    add_dungeon_asks();

    add_ask( ({ "food", "eat" }), "say Runt hungy! Dungeon not have"
      + " enough food!", 1);

    set_default_answer(VBFC_ME("default_answer"));

    add_prop(LIVE_I_NEVERKNOWN, 1);
    remove_prop(LIVE_M_NO_ACCEPT_GIVE);

    set_alarm(20.0, 0.0, my_actions);

    setuid();
    seteuid(getuid());
} /* create_temple_npc */


/*
 * Function name:        arm_me
 * Description  :        set up the npc with any gear it needs
 */
public void
arm_me()
{
    object  arm;
    string  wep = one_of_list( ({ "sword",
                                  "mace",
                                  "axe",
                                  "dagger",
                                  "spear" }) );

    arm = clone_object(WEP_DIR + "crude_" + wep);
    arm->move(this_object());

    arm = clone_object(ARM_DIR + "crude_leather");
    arm->move(this_object());

    arm = clone_object(ARM_DIR + "crude_shield");
    arm->move(this_object());

    set_alarm(0.0, 0.0, add_key);

    command("wear all");
    command("wield all");
} /* arm_me */


/*
 * Function name:        add_key
 * Description  :        add a key to this runt if it is in the correct
 *                       room
 */
public void
add_key()
{
    object     arm;

    if (environment(this_object())->id("_runt_key_guard"))
    {
        arm = clone_object(DOORS_DIR + "1_weapon_key");
        arm->move(this_object());
    }
} /* add_key */


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
    int     attack_type = random(20); /* 5% chance to do special */
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

    enemy->catch_msg("The orcish runts in the room suddenly leap"
      + " into a formation of sorts. One jumps on your chest while"
      + " the others circle around behind you, biting ferociously at"
      + " your exposed back with their horrible teeth!\n");
    tell_room(environment(enemy),
        "The orcish runts in the room suddenly leap into a formation of"
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

        bite_damage = 3 + random(3);

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

            log_file("runt_bite_log", TIMESTAMP + " "
             + capitalize(this_player()->query_real_name()) 
             + " bitten for " + bite_damage + " hp.\n");            

            if (enemy->query_hp() < 1)
            {
                enemy->do_die();

                log_file("runt_bite_log", TIMESTAMP + " "
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


/* 
 * Function name:       default_answer
 * Description  :       give the default response to questions
 */
public string
default_answer()
{
    string  answer = one_of_list( ({
        "Huh ... ? Why you bother runt?!",
        "Runt not like answer questions.",
        "You ask warrior. Maybe warrior know.",
        }) );

    command("emote cocks his head in confusion.");
    command("say " + answer);
    return "";
} /* default_answer */


/*
 * Function name:        intro_responses
 * Description  :        provide responses to an introduction
 * Arguments    :        object tp - this_player()
 *
 * This should be redefined in inheriting npcs for flavor variation.
 */
public void
intro_responses(object tp)
{
    switch(random(6))
    {
    case 0:
        command("sneer amus "+tp->query_real_name());
        break;
    case 1:
        command("say Why you say funny word? Oh, that name? Ha!");
        break;
    case 2:
        command("say Runt not care about name. Runt hungry!");
        break;
    case 3:
        command("say Name sound silly. You go away.");
        break;
    case 4: 
        command("say You want runt name? Not telling!");
        break;
    case 5:
        command("say That sound like name of cow. You cow?");
        break;
    }
} /* intro_responses */


/*
 * Function name:       not_here_func
 * Description  :       called when player asks question & leaves
 * Returns      :       0 -> don't answer the question
 */
public int
not_here_func()
{
     command("peer");
     command("shout Who ask runt question and sneak away?");
     return 0;
} /* not_here_func */


/*
 * Function name:        not_ask_for_assistance
 * Description  :        When we don't want assistance from other goblins,
 *                       this happens.
 */
public void
not_ask_for_assistance()
{
    command(one_of_list( ({
        "emote closes on you, clearly wanting to take you on alone!",
        "shout This one all mine!",
        "shout You not scare me! Me take you blindfolded!",
        "shout Brothers not help! Me kill this one!" }) ) );
} /* not_ask_for_assistance */


/*
 * Function name:        not_assist
 * Description  :        What goblins do when the refuse to assist
 */
public void
not_assist()
{
    command(one_of_list( ({
        "shout Uh ... no, brother! You take that one!",
        "emote backs up, clearly too afraid to help.",
        "shout You can do it, brother! You not need help!",
        "shout Brother! You tough! You kill him! Me watch!" }) ) );
} /* not_assist */


/*
 * Function name:        my_actions
 * Description  :        have the runt do an action
 */
public void
my_actions()
{
    mixed   door = present("door", environment(this_object()));
    string  room;
    object *players;
    string *msgs = ({
                "grin",
                "say Runt make sure door stay shut!",
                "say You stay away from door!",
                "say Why you here? You keep going, go away!",
                "say Runt ready to kick face of anyone who get close.",
                "say Brother runts so weak. Still, they brothers.",
                "say Door stay closed! You go!",
                "say Brothers! Kill any who open door!",
                    });
    float  action_delay = itof(250 + random(100));

    if (door)
    {
        room = door->query_other_room();

        players = filter(all_inventory(find_object(room)), interactive);

        if (door->query_open())
        {
            if (sizeof(players))
            {
                add_prop(ORIGIN_ROOM, environment(this_object()));
                command("shout Hey! Who that in there?!");
                command(door->query_pass_command()[0]);
                command("kill " + players[0]->query_real_name());

                set_alarm(180.0, 0.0, return_to_post);
                return;
            }

            command("close door");
            command("lock door with key");

            if (!door->query_locked())
            {
                command("lock door with key");
            }

            return;
        }

        if (!door->query_locked() && !sizeof(players))
        {
            command("lock door with key");
            return;
        }
    }

    command(one_of_list(msgs));

    set_alarm(action_delay, 0.0, my_actions);
} /* my_actions */


/*
 * Function name:        return_to_post
 * Description  :        have the guy return to his post if he is in
 *                       the wrong room
 */
public void
return_to_post()
{
    mixed   door = present("door", environment(this_object()));

    if (environment(this_object()) == query_prop(ORIGIN_ROOM))
    {
        return;
    }

    if (door)
    {
        command("unlock door with key");
        command("open door");
        command(door->query_pass_command()[0]);

        return;
    }

    command("say Uhhhh ... why me here?");
} /* return_to_post */
