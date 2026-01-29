/*
 *  /d/Sparkle/guilds/new_merc/npc/cook.c
 *
 *  This is Harold, the cook who works the kitchens of the Mercenary
 *  Guild. 
 *
 *  Created September 2009, by Cooper Sherry (Gorboth)
 */
#pragma strict_types

inherit "/d/Sparkle/area/city/npc/sparkle_npc";
inherit "/d/Genesis/lib/intro";

#include <filter_funs.h>
#include <formulas.h>
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <time.h>

#include "../merc_defs.h"

/* Definitions */
#define            CAFETERIA  (ROOM_DIR + "mess_hall")
#define            KITCHEN    "_merc_guild_kitchen"

/* Global Variables */
public string     *Indoor_Acts = ({
                       "emote mutters something about taking a nap.",
                       "emote shuffles slowly over to the water bucket and"
                     + " starts rinsing out a pot.",
                       "emote heats up a griddle and cracks an egg on it.",
                       "emote winces as a loud shouted command for more"
                     + " food echoes from the dining hall.",
                       "shout We're ... um ... a bit backed up in here,"
                     + " Darling. It won't be but a minute more!",
                       "emote starts chopping a piece of meat with a"
                     + " dirty-looking cleaver.", });
public string      Cook_Errand = "";

/* Prototypes */
public void        create_sparkle_npc();
public mixed       attack_cook();
public void        introduce(object who);
public void        react_intro(object tp);
public string      default_answer();
public void        notify_death(object killer);
public void        run_away();
public int         notify_you_killed_me(object player);
public void        attacked_by(object attacker);
public void        arm_me();
public void        do_errand();
public void        shoo_player();
public void        pre_shoo();
public void        wake_me();

public string      query_errand() { return Cook_Errand; }


/* 
 * Function name:       create_sparkle_npc
 * Description  :       This function overrides the one in the base class
 * Arguments    :       none
 * Returns      :       void/nothing
 */
public void
create_sparkle_npc()
{
    set_living_name("harold");
    set_name("harold");
    add_name( ({ "husband", "cook", "chef", "man",
                 "_merc_guild_cook" }) );
    set_race_name("human");
    add_adj( ({ "waitresses", "waitress's", "slow", "glassy-eyed",
                "glassy", "eyed" }) );

    set_title("Black, Cook for the Mercenary Guild");

    set_short("slow glassy-eyed cook");
    set_long("Shuffling about at what appears to be half speed, this"
      + " haggard individual looks ready to take a nap. Were it not"
      + " for the constant nagging of his wife (the waitress) he would"
      + " probably get three orders at most filled in a whole hour. But"
      + " the Mercenary Guild has many hungry mouths to feed, and so"
      + " he is kept much busier than that.\n");

    set_stats( ({ 70, 50, 50, 100, 60, 80 }) ); /* No hero, this. */
    set_alignment(400); /* A good-natured fellow. */

    set_act_time(10);
    add_act("emote mutters something about taking a nap.");
    add_act("emote shuffles slowly over to the water bucket and starts"
      + " rinsing out a pot.");
    add_act("emote heats up a griddle and cracks an egg on it.");
    add_act("emote winces as a loud shouted command for more food"
      + " echoes from the dining hall.");
    add_act("shout We're ... um ... a bit backed up in hear, Darling."
      + " It won't be but a minute more!");
    add_act("emote starts chopping a piece of meat with a dirty-looking"
      + " cleaver.");

    set_cact_time(4);
    add_cact("shout Pearl ... Darling!! Someone is holding up the"
      + " cooking in here!!");
    add_cact("emote tries to hide behind the oven.");
    add_cact("say No ... no ... stop this!");

    set_default_answer(VBFC_ME("default_answer"));

    remove_prop(LIVE_I_NEVERKNOWN);
    add_prop(OBJ_M_NO_ATTACK, attack_cook);
    add_prop(LIVE_I_NO_CORPSE, 1); /* He runs away instead of dying. */

    set_skill(SS_UNARM_COMBAT, 20); /* Just a bit here ...           */
    set_skill(SS_HERBALISM, 100);   /* A cook knows his herbs!       */
    set_skill(SS_AWARENESS, 75);    /* Though sleepy, he's watchful. */

    setuid();
    seteuid(getuid());
} /* create_sparkle_npc */   


/*
 * Function name:        attack_cook
 * Description  :        The chef cannot be attacked if Pearl is in
 *                       her normal place working the cafeteria.
 * Returns      :        string - if Pearl is around (can't attack him)
 *                       int 0  - if not (can attack him) 
 */
public mixed
attack_cook()
{
    object    waitress = present("_merc_guild_waiter",
                             find_object(CAFETERIA));

    if (!environment(this_object())->id(KITCHEN))
    {
        return 0;
    }

    if (waitress)
    {
        tell_room(CAFETERIA, "A yell for help comes from the kitchen!\n");
        waitress->command("$grumble");
        waitress->command("say What now?!");
        waitress->command("emote storms into the kitchen and returns a"
          + " minute later looking positively menacing.");

        tell_room(environment(this_object()), "As "
          + QCTNAME(this_player()) + " approaches the cook to"
          + " attack, he yells for help! A gruff irritable waitress"
          + " storms into the room, and gives a very clear and"
          + " withering death stare to the would-be assailant,"
          + " who quails under her gaze. Satisfied, she leaves again.\n",
          this_player());

        return "As you approach, the cook yells for help! A gruff"
          + " irritable waitress storms into the room, takes one look"
          + " at you, and cackles with a dreadful voice! You suddenly"
          + " lose your nerve to attack. Nodding at you with a look of"
          + " death in her eyes, the waitress leaves the kitchen"
          + " again.\n";
    }

    return 0;
} /* attack_cook */


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
        command("say Where'd they go now?");
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
    command("emote blinks sleepily.");
    command("say Uh .... er ......... um .... sorry, I'm not sure I"
      + " ... ");
    return "";
} /* default_answer */


/*
 * Function name: notify_death
 * Description:   Notify onlookers of my death,
 * Arguments:     object killer - the object that killed me
 */
public void
notify_death(object killer)
{
    tell_room(environment(this_object()), 
        QCTNAME(this_object()) + " squeals like a piggy and runs,"
      + " arms flailing, from the kitchen!\n");

    if (living(killer))
    {
        tell_object(killer, 
            "You've beaten the cook and taken charge of the kitchen!\n");
        tell_room(environment(this_object()),  QCTNAME(killer) + 
            " has beaten the cook!\n",
           ({ this_object(), killer }));
    }

    write_file(LOG_DIR + "cook", killer->query_name() + " ("
      + killer->query_average_stat() + ") defeated Harold!\n");
} /* notify_death */


/*
 * Function name:        run_away
 * Description  :        we mask the fun from /std/living/combat.c to
 *                       keep him from ever leaving the ledge.
 */
public void
run_away()
{
    command("tremble");
    command("say If I leave my post, my wife will turn me into a"
      + " catfish!!");

    return;
} /* run_away */


/*
 * Function name:        notify_you_killed_me
 * Description  :        Called when this npc kills something. We want
 *                       to see who he ends up killing.
 * Arguments    :        object player: the one who was killed
 * Returns      :        1
 */
public int
notify_you_killed_me(object player)
{
    write_file(LOG_DIR + "harold",
        TIME2FORMAT(time(), "mm/dd/yyyy") + " (" + ctime(time())[11..18]
      + ") " + capitalize(player->query_name()) + " was killed by "
      + capitalize(query_real_name()) + "!\n");

    return 1;
} /* notify_you_killed_me */


/*
 * Function name:        attacked_by
 * Description  :        Lets keep track of who attacks us for now
 * Arguments    :        object attacker - who is attacking us?
 */
public void
attacked_by(object attacker)
{
    string roomfile;
    
    roomfile = MASTER_OB(environment(this_object()));

    ::attacked_by(attacker);

    if (roomfile == ROOM_DIR + "neutral_start" &&
        this_object()->query_prop("_bunk_prop"))
    {
        command("emote wakes with a start!");
        command("emote yells and falls out of bed!");
        command("emote tries to stand up but trips and falls onto the"
          + " bunk again!");
        command("rise");
    }

    this_player()->catch_tell(this_object()->query_The_name(attacker)
      + " turns slowly to face you with a frightened look in his eyes.\n");
    tell_room(environment(this_object()), QCTNAME(this_object())
      + " turns slowly to face " + QTNAME(attacker) + " with a frightened look"
      + " in his eyes.\n", attacker);
    tell_room(environment(this_object()), QCTNAME(this_object())
      + " shout: Pearl! Help!! Some fool is after my job!\n");

    write_file(LOG_DIR + "harold", 
        TIME2FORMAT(time(), "mm/dd/yyyy") + " (" + ctime(time())[11..18]
      + ") " + capitalize(attacker->query_name()) + " attacked"
      + " Harold.\n");
} /* attacked_by */


/*
 * Function name: enter_env
 * Description  : This function is called each time this object enters a
 *                new environment. If you mask it, be sure that you
 *                _always_ call the ::enter_env(dest, old) function.
 * Arguments    : object dest - the destination we are entering.
 *                object old  - the location we came from. This can be 0.
 *
 * We mask this object so that the emotes the cook can do only occur
 * if he is in the kitchen.
 */
public void
enter_env(object dest, object old)
{
    ::enter_env(dest, old);

    clear_act();

    if (!dest->id(KITCHEN))
    {
        return;
    }

    foreach (string cook_act: Indoor_Acts)
    {
        add_act(cook_act);
    }

    pre_shoo();
} /* enter_env */



/*
 * Function name:        arm_me
 * Description  :        set up the npc with any gear it needs
 */
public void
arm_me()
{
    object  arm;

    arm = clone_object(OBJ_DIR + "cook_hat");
    arm->move(this_object());
    arm = clone_object(OBJ_DIR + "cook_apron");
    arm->move(this_object());

    command("wear all");
    command("wield all");
} /* arm_me */


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
    if (room == (ROOM_DIR + "kitchen")
        && (direction == "north" || direction == "n"))
    {
        command("$open door");
    }
    else if (room == (ROOM_DIR + "wep_train")
             && (direction == "south" || direction == "s"))
    {
        command("$open door");
    }
    else if (room == (ROOM_DIR + "entry_hall")
             && (direction == "south" || direction == "s"))
    {
        command("$open door");
    }
    else if (room == (ROOM_DIR + "neutral_bunk")
        && (direction == "north" || direction == "n"))
    {
        command("$open door");
    }
    else if (room == (ROOM_DIR + "mess_hall")
             && (direction == "south" || direction == "s"))
    {
        if (!present("_merc_guild_waiter", environment(this_object())))
        {
            command("peer");
            command("say I wonder where Pearl is ...");
            command("shrug");
        }
        else
        {
            command("say I'm going to bed now, Darling.");
            command("kiss pearl gently");
        }
    }
    else if (room == (ROOM_DIR + "mess_hall")
             && (direction == "east" || direction == "e"))
    {
        if (!present("_merc_guild_waiter", environment(this_object())))
        {
            command("peer");
            command("say Pearl? Darling? I wonder where she's gone ...");
            command("shrug");
        }
        else
        {
            command("yawn");
            command("say Good morning, Darling.");
            command("kiss pearl gently");
        }
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
    string roomfile;
    
    roomfile = MASTER_OB(environment(this_object()));
    Cook_Errand = one_of_list( ({
                         "woodpile",
                         "herbs",
                         "water",
                         "rubbish",
                     }) );

    if (is_busy())
    {
        // Don't participate in daily routines when interacting.
        return;
    }
    
    switch (hour)
    {
    case 0..5:
        if (roomfile != ROOM_DIR + "neutral_start")
        {
            command("say Oh heaven's why aren't I in bed?");
            walk_to_room(ROOM_DIR + "neutral_start");
            break;
        }

        command("lie bunk");
        command(one_of_list( ({
            "emote snores loudly.",
            "emote rolls over in his sleep.",
            "emote mumbles something in his sleep.",
            "emote stirs restlessly in his bunk.",
            "emote twitches suddenly!", }) ));
        break;
    case 6..7:
        if (walk_to_room(ROOM_DIR + "kitchen"))
        {
            command("$rise");
            command("$stretch");
            command("$wear all");
            clear_act();
        }
        break;
    case 8..22:
        if (hour % 2)
        {
            if (roomfile != ROOM_DIR + "kitchen")
            {
                command("$say What the deuce am I doing here? I must"
                  + " get back to the kitchen!");
                walk_to_room(ROOM_DIR + "kitchen");
                break;
            }

            command("emote glances out the window, muttering about"
              + " the time.");
            break;
        }

        if (walk_to_room(ROOM_DIR + "lumber_pile"))
        {
            command("$grumble"); 

            switch (Cook_Errand)
            {
                case "woodpile":
                    command("$emote mutters something about needing"
                      + " an errand boy.");
                    break;
                case "herbs":
                    command("$emote grabs an empty herb jar from a"
                      + " shelf.");
                    break;
                case "water":
                    command("$emote picks up the water bucket and"
                      + " huffs and puffs.");
                    break;
                case "rubbish":
                    command("$emote grabs the rubbish trough and"
                      + " starts heading for the door.");
                    break;
            }
        }
        break;
    case 23:
        if (walk_to_room(ROOM_DIR + "neutral_start"))
        {
            command("$yawn");
            command("$say Time for this cook to hit the sack!");
            clear_act();
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
    switch (roomfile)
    {
    case ROOM_DIR + "neutral_start":
        command("$remove all");
        command("$yawn");
        command("$lie bunk");
        command("$snore");
        break;
    
    case ROOM_DIR + "lumber_pile":
        set_alarm(3.0, 0.0, do_errand);
        break;

    case ROOM_DIR + "kitchen":
        command("$close door");
        switch (Cook_Errand)
        {
            case "woodpile":
                command("$emote opens the stove and shoves in a pile"
                  + " of firewood he had carried in from outside.");
                break;
            case "herbs":
                command("$emote puts a jar full of herbs on the counter"
                  + " and gets back to work.");
                break;
            case "water":
                command("$emote puts a bucket of fresh cleaning water"
                  + " on the floor and resumes his cooking duties.");
                break;
            case "rubbish":
                command("$emote plops an empty rubbish trough in the"
                  + " corner and goes back to cooking.");
            default:
                command("sigh");
                command("emote fires up the stove and starts preparing"
                  + " food.");
                break;
        }

        Cook_Errand = "";
        break;
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
    if (wildmatch(ROOM_DIR + "*", str))
    {
        return 1;
    }
    
    return 0;
} /* is_valid_room */


/*
 * Function name:        do_errand
 * Description  :        The cook has a number of errands he does.
 *                       This is called when he reaches the room he
 *                       heads to for them.
 */
public void
do_errand()
{
    string roomfile;
    
    roomfile = MASTER_OB(environment(this_object()));

    if (roomfile == ROOM_DIR + "lumber_pile")
    {
        switch (Cook_Errand)
        {
            case "woodpile":
                command("$emote grabs some firewood from the lumber"
                  + " pile and turns to head back to the lodge.");
                break;
            case "herbs":
                command("$emote searches around the area, picking"
                  + " various herbs and putting them in a small jar.");
                break;
            case "water":
                command("$emote walks through the trees to the"
                  + " edge of the river. You see him empty a large"
                  + " bucket of dirty water, and then refill it with"
                  + " fresh water from the Copper River.");
                command("$emote walks back toward you on his way"
                  + " to the lodge.");
                break;
            case "rubbish":
                command("$emote walks behind the mill and empties a"
                  + " trough of rubbish.");
                break;
        }
    }

    set_alarm(2.0, 0.0, &walk_to_room(ROOM_DIR + "kitchen"));
} /* do_errand */


/*
 * Function name:        shoo_player
 * Description  :        The cook shoos a player out of the kitchen.
 *                       We need this for the instances where the cook
 *                       will return to the kitchen from some other location
 *                       and find players within.
 */
public void
shoo_player()
{
    int     n;
    mixed  *targets = FILTER_LIVE(all_inventory(environment(
                     this_object())));
    object  herded;

    foreach (object target: targets)
    {
        if (CAN_SEE(this_object(), target) &&
            !target->query_wiz_level() &&
            !target->id("_merc_guild_cook"))
        {
            target->catch_msg("The cook cries: Out! Out!!\n");
            target->catch_msg("The cook brandishes a spatula and"
              + " herds you out of the kitchen!\n");
            command("open door");
            target->command("$north");
            command("close door");
            n++;
            herded = target;
        }
    }

    if (n)
    {
        tell_room(environment(this_object()), "The cook cries: Out!"
          + " Out!!\nThe cook brandishes a spatula and herds "
          + ((n > 1) ? "everyone" : QTNAME(herded)) + " out of"
          + " the kitchen!\n");
    }
} /* shoo_player */


/*
 * Function name:        pre_shoo
 * Description  :        We want a slight delay for the shoo. This
 *                       creates it.
 */
public void
pre_shoo()
{
    set_alarm(2.0, 0.0, "shoo_player");
} /* pre_shoo */


/*
 * Function name:        wake_me
 * Description  :        Called if players try to wake him when he is
 *                       asleep.
 */
public void
wake_me()
{
    command("emote blinks sleepily");
    command("rise");
    command("scowl .");
    command("say What ... what is it?? I'm trying to sleep!");
} /* wake_me */