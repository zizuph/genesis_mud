/*
 *  /d/Sparkle/area/orc_temple/npc/jailer.c
 *
 *  These is the jailer (who has keys) for the jail cells in the Orc
 *  Dungeons beneath the temple in Sparkle.
 *
 *  Created October 2010, by Cooper Sherry (Gorboth)
 */
#pragma strict_types
#include "../defs.h"

inherit NPC_DIR + "temple_npc";
inherit "/d/Sparkle/area/city/npc/sparkle_npc";

#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>


/* Global Variables */
public int         Key_Anger = 0;

/* Prototypes */
public void        create_sparkle_npc();
public void        introduce(object who);
void               react_intro(object tp);
public string      default_answer();
public void        arm_me();
public void        assist();
public void        ask_for_assistance();
public void        attacked_by(object ob);
public void        cell_walk(string direction, string arrival, string departure);
private void       walk_prestep(string direction, string room);
public void        alert_hour_change_hook(int hour);
public void        walk_destination_reached_hook();
public int         walk_precondition_hook(string direction, string roomfile);
public int         is_valid_room(string str);
public void        cell_arrival();


/*
 * Function name:        create_sparkle_npc
 * Description  :        The constructor for the monster
 */
public void
create_sparkle_npc()
{
    set_living_name("blukkmak");
    set_name("blukkmak");
    set_race_name("orc");
    add_name( ({ "goblin", "jailer", ORC_TEMPLE_NPC }) );
    add_adj( ({ "orcish" }) );

    set_title("the Cruel, Jailer of the Temple Dungeons");

    set_short("orcish jailer");
    set_long("This extremely fat orc looks like he thinks he owns the"
      + " place. The smug look on his face matches his posture, which"
      + " is that of a strutting (and stinking, and fat) peacock. Keys"
      + " jingle from his belt as he walks around.\n");

    set_stats( ({ 30 + (random(10)),
                  25 + (random(10)),
                  40 + (random(10)),
                  20 + (random(10)),
                  17  + (random(7)),
                  15  + (random(10)) }) );
                  
    set_skill(SS_WEP_SWORD,    20);
    set_skill(SS_WEP_AXE,      20);
    set_skill(SS_WEP_CLUB,     20);
    set_skill(SS_WEP_POLEARM,  20);
    set_skill(SS_WEP_KNIFE,    20);
    set_skill(SS_AWARENESS,    60);
    set_skill(SS_DEFENCE,      15);
    set_skill(SS_PARRY,        10);

    remove_prop(LIVE_I_NEVERKNOWN);
    set_default_answer(VBFC_ME("default_answer"));

    set_act_time(10 + random(7));
    add_act("burp");
    add_act("say I catch one more runt in pantry, I cook him!");
    add_act("say Stupid warriors. They not back-talk"
      + " me again, or me feed THEM to demon!");
    add_act("say These prisoners make me want puke!");
    add_act("say Little girl we had in here not stink as"
      + " bad as others, but sure squeal louder!");
    add_act("say Who say it no fun be in jail? Me love it!");
    add_act("emote counts the keys on his keyring and grunts.");
    add_act("say Priests think they so special. Huh!");

    add_cact("emote slaps you in the face with his keyring!");
    add_cact("emote bellows angrily!");
    add_cact("shout Runts, warriors, GET IN HERE!!");

    set_dungeon_response( ({
        "Dungeons where give scum what they deserve!",
        "Doing big stuff here. You find out soon! Haha!",
        "Me keep order down here, that all you"
      + " need know." }) );
    set_demon_response( ({
        "What? Not talk about stuff you can't handle, idiot!",
        "If priest know you talk about"
      + " that, they cut out tongue!",
        "Shut up! They throw you in pit for that!" }) );
    set_prisoner_response( ({
        "Ha! Me love prisoners!",
        "It MY job think about prisoners, not you!",
        "Maybe lock you up with them!" }) );
    set_runt_response( ({ "Runt need work harder!" }) );
    set_warrior_response( ({ "Warriors get mouthy"
      + " too many time. Maybe report to priests, but then priest"
      + " think Jailer not tough enough. JAILER TOUGH ENOUGH!" }) );
    set_priest_response(
        ({ "Priest put me in charge, so you not get any ideas." }) );
    set_jailer_response("That me, fool!");
    set_hp_response("High Priest not even know or care about us."
      + " He too busy with demon!");
    set_give_response("You keep stuff, idiot!");
    add_dungeon_asks();

    add_ask( ({ "food", "eat" }), "say Me eat whatever feel like"
      + " and runts and warriors can just shut up!", 1);
    add_ask( ({ "pit" }), "say Heh. That where prisoners go!", 1);
    add_ask( ({ "haunted", "ghost", "ghosts" }),
        "say Not talk about ghosts! Bad enough they here at all.", 1);

    remove_prop(LIVE_M_NO_ACCEPT_GIVE);

    setuid();
    seteuid(getuid());
} /* create_sparkle_npc */


/*
 * Function name:        introduce
 * Description  :        create a delay between intro and reaction
 * Arguments    :        object who - the player
 */
public void
introduce(object who)
{
    set_alarm(itof(2 + random(5)), 0.0, &react_intro(who));
} /* introduce */


/*
 * Function name:        react_intro
 * Description  :        the npc introduces himself
 * Arguments    :        tp - the player
 */
void
react_intro(object tp)
{
    if (!present(tp, environment(this_object())))
    {
        command("say Where'd that punk go?");
        return;
    }

    command("introduce me");
} /* react_intro */


/* 
 * Function name:       default_answer
 * Description  :       give the default response to questions
 */
public string
default_answer()
{
    command("emote growls stupidly.");
    command("say Ask someone else! Me too busy to waste time on you.");
    return "";
} /* default_answer */


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
                                  "axe", }) );

    arm = clone_object(WEP_DIR + "warrior_" + wep);
    arm->move(this_object());

    arm = clone_object(ARM_DIR + "warrior_helm");
    arm->move(this_object());

    arm = clone_object(ARM_DIR + "crude_shield");
    arm->move(this_object());

    arm = clone_object(ARM_DIR + "warrior_plate");
    arm->move(this_object());

    arm = clone_object(DOORS_DIR + "2_cell_key");
    arm->move(this_object());

    command("wear all");
    command("wield all");
} /* arm_me */


/*
 * Function name:        assist
 * Description  :        When assisting other goblins that get attacked,
 *                       we display what is happening.
 */
public void
assist()
{
    command(one_of_list( ({
        "shout Heh! You deal with me now!",
        "emote roars and charges at you!",
        "shout Time to feed YOU to demon!!",
        "shout Me have this one, boys!" }) ) );
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
        "emote shouts: Runts! Warriors! You get fool off me!",
        "shout Get in here, stupid guards!",
        "emote laughs slowly.",
        "shout Good! I not have breakfast yet. You do just fine!" }) ) );
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
 * Function name:        cell_walk
 * Description  :        Actions the jailer should perform when just
 *                       outside a cell door
 * Arguments    :        string direction = The direction the npc will go
 *                       string arrival   = the direction the jailer is
 *                                          walking if they are arriving
 *                                          to enter the cell
 *                       string departure = the direction the jailer is
 *                                          walking if they are leaving
 *                                          the cell
 */
public void
cell_walk(string direction, string arrival, string departure)
{
    if (direction == arrival || direction == arrival[0..0])
    {
        command("$unlock door with key");
        command("$open door");
        command(direction);
    }

    if (direction == departure || direction == departure[0..0])
    {
        command("$close door");
        command("$lock door with key");
    }
} /* cell_walk */


/*
 * Function name:       walk_prestep
 * Description  :       Override this method to have the npc perform
 *                      any commands before performing the walk action
 * Arguments    :       direction - direction that npc will go
 *                      room - the current room file
 * Returns      :       nothing
 */
private void
walk_prestep(string direction, string room)
{
    if (room == (ROOMS_DIR + "2_hall1"))
    {
        cell_walk(direction, "west", "north");
    }
    else if (room == (ROOMS_DIR + "2_hall2"))
    {
        cell_walk(direction, "west", "north");
    }
    else if (room == (ROOMS_DIR + "2_hall3"))
    {
        cell_walk(direction, "west", "north");
    }
    else if (room == (ROOMS_DIR + "2_hall4"))
    {
        cell_walk(direction, "west", "east");
    }
    else if (room == (ROOMS_DIR + "2_hall5"))
    {
        cell_walk(direction, "east", "south");
    }
    else if (room == (ROOMS_DIR + "2_hall6"))
    {
        cell_walk(direction, "east", "south");
    }
    else if (room == (ROOMS_DIR + "2_hall7"))
    {
        cell_walk(direction, "east", "south");
    }
    else if (room == (ROOMS_DIR + "2_hall8"))
    {
        cell_walk(direction, "east", "west");
    }
} /* walk_prestep */


/*
 * Function name:       alert_hour_change_hook
 * Description  :       This function gets called whenever the hour
 *                      hour changes in the City of Sparkle
 *                      NPCs can use this to act upon the hour,
 *                      to provide the semblance of a daily routine.
 * Arguments    :       hour - current hour in Sparkle time
 * Returns      :       nothing
 */
public void
alert_hour_change_hook(int hour)
{
    string  roomfile;
    string *time_acts = ({ "scratch ear",
                           "chuckle cruel",
                           "emote looks over his artifacts.",
                           "peer proud",
                        });
    string *no_key_acts = ({ "Who took keys?!",
                             "Where my keys go!?",
                             "When find who did this, he dead!",
                             "Come back with keys, thief!",
                          });
    string *cell_acts = ({ "On to next rothole.",
                           "We through here.",
                           "Moving on ...",
                           "Me see enough here.",
                           "Me check back here tomorrow."
                        });
    object  heart_attack;
    
    roomfile = MASTER_OB(environment(this_object()));

    if (is_busy())
    {
        // Don't participate in daily routines when interacting.
        return;
    }

    if (!present(JAILERS_KEYS, this_object()))
    {
        if (present(JAILERS_KEYS, environment(this_object())))
        {
            command("say What the ... ?");
            command("get keys");

            Key_Anger = 0;
        }
        else
        {
            command("shout " + one_of_list(no_key_acts));
            Key_Anger++;

            if (Key_Anger > 5)
            {
                heart_attack = clone_object("/std/object");
                heart_attack->set_name("heart attack");
                heart_attack->set_short("shock to his heart");
                set_alarm(1.0, 0.0, &heart_attack->remove_object());

                command("choke");
                command("emote grabs his chest, looking stricken!");
                command("shout AAAAAARRRRRRGH!!!");
                command("emote appears to suffer a lethal heart attack.");
                heal_hp(-10000000);
                do_die(heart_attack);
            }

            return;
        }
    }
    
    switch (hour)
    {
    case 0..1:
    case 10..11:
    case 20..23:
        if (roomfile != ROOMS_DIR + "2_jailer")
        {
            command("say Blast, me tired! Time to relax.");
            walk_to_room(ROOMS_DIR + "2_jailer");
            break;
        }

        command(one_of_list(time_acts));
        break;
    case 2:
    case 12:
        if (walk_to_room(ROOMS_DIR + "2_cell5"))
        {
            command("grumble");
            command("say Time to make rounds again.");
        }
        break;
    case 3:
    case 13:
        if (walk_to_room(ROOMS_DIR + "2_cell6"))
        {
            command("kick prisoner");
            command("say " + one_of_list(cell_acts));
            command("unlock door with key");
            command("open door");
        }
        break;
    case 4:
    case 14:
        if (walk_to_room(ROOMS_DIR + "2_cell7"))
        {
            command("kick prisoner");
            command("say " + one_of_list(cell_acts));
            command("unlock door with key");
            command("open door");
        }
        break;
    case 5:
    case 15:
        if (walk_to_room(ROOMS_DIR + "2_cell8"))
        {
            command("kick prisoner");
            command("say " + one_of_list(cell_acts));
            command("unlock door with key");
            command("open door");
        }
        break;
    case 6:
    case 16:
        if (walk_to_room(ROOMS_DIR + "2_cell1"))
        {
            command("kick prisoner");
            command("say " + one_of_list(cell_acts));
            command("unlock door with key");
            command("open door");
        }
        break;
    case 7:
    case 17:
        if (walk_to_room(ROOMS_DIR + "2_cell2"))
        {
            command("kick prisoner");
            command("say " + one_of_list(cell_acts));
            command("unlock door with key");
            command("open door");
        }
        break;
    case 8:
    case 18:
        if (walk_to_room(ROOMS_DIR + "2_cell3"))
        {
            command("kick prisoner");
            command("say " + one_of_list(cell_acts));
            command("unlock door with key");
            command("open door");
        }
        break;
    case 9:
    case 19:
        if (walk_to_room(ROOMS_DIR + "2_cell4"))
        {
            command("kick prisoner");
            command("say " + one_of_list(cell_acts));
            command("unlock door with key");
            command("open door");
        }
        break;
    }
} /* alert_hour_change_hook */


/*
 * Function name:       walk_destination_reached_hook
 * Description  :       Override this to do something when the 
 *                      npc arrives at his destination.
 * Arguments    :       none
 * Returns      :       nothing
 */
public void
walk_destination_reached_hook()
{
    string roomfile;
    
    roomfile = MASTER_OB(environment(this_object()));

    if (roomfile->id(DUNGEON_CELL))
    {
        command("$close door");
        set_alarm(3.0, 0.0, &cell_arrival());
        return;
    }

    if (roomfile == ROOMS_DIR + "2_jailer")
    {
        set_alarm(3.0, 0.0, &command("say Home sweet home ..."));
    }
} /* walk_destination_reached_hook */


/*
 * Function name:       walk_precondition_hook
 * Description  :       Override this to define something that the npc
 *                      will check before moving onto the next step.
 * Arguments    :       direction - direction the next move is
 *                      roomfile  - current room location
 * Returns      :       0/1 - allow walk step or not
 */
public int
walk_precondition_hook(string direction, string roomfile)
{
    return !is_busy();
} /* walk_precondition_hook */


/*
 * Function name: is_valid_room
 * Arguments  : str - the path of the room
 * Returns   : 1 = can be used in the pathfinding, 0 if not
 */
public int
is_valid_room(string str)
{
    if (wildmatch(ROOMS_DIR + "*", str))
    {
        return 1;
    }
    
    return 0;
} /* is_valid_room */


/*
 * Function name:        cell_arrival
 * Description  :        This is the script for the jailer's behavior
 *                       when he arrives at a jail cell.
 */
public void
cell_arrival()
{
    object  prisoner = present("prisoner", environment(this_object()));
    object  ghost = present("ghost", environment(this_object()));
    string  exit_dir = environment(this_object())->query_door_direction();

    if (ghost)
    {
        command("gasp");
        command("point ghost");
        command("say What the hell that thing?!?");
        command("tremble");
        command("scream");
        command("unlock door with key");
        command("open door");
        command(exit_dir);
        return;
    }

    if (prisoner)
    {
        command("shout You feel better today?");
        command("spit prisoner");
        command("shout Not anymore!");
        command("knee prisoner");
        command("laugh merciless");
        return;
    }

    command("sniff deep");
    command("say Look like this one not live through night.");
    command("say Good. Runts get lazy - need more work.");
    command("say Give them new fetching job.");
} /* cell_arrival */



/*
 * Function name:       add_sparkle_asks
 * Description  :       These are standard asks to be inherited by
 *                      other Sparkle npc's, allowing us more varied
 *                      responses without inconsistancy.
 */
public void
add_sparkle_asks()
{
    /* We don't want these defined from the city npcs. */
    add_ask( ({ "job", "occupation", "work", "career" }),
        "say Me in charge! You not notice?", 1);
} /* add_sparkle_asks */


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
        "shout This one all mine! Me give to High Priest!",
        "shout Me show stupid warriors how it done!",
        "shout Brothers, you watch! See how it done!" }) ) );
} /* not_ask_for_assistance */


/*
 * Function name:        not_assist
 * Description  :        What goblins do when the refuse to assist
 */
public void
not_assist()
{
    command(one_of_list( ({
        "shout Brothers! You kill this one! Me too busy!",
        "emote backs up, clearly too afraid to help.",
        "shout Me not have time for this!",
        "shout Bah! This warrior job, not mine!" }) ) );
} /* not_assist */
