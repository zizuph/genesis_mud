/*
 *  /d/Sparkle/area/city/rooms/inside/sparkle_pub_parlor.c
 *
 *  This is a more quiet and intimate parlor of the main hall of the
 *  Boar's Head Tavern in Sparkle.
 *
 *  Created August 2018, by Cooper Sherry (Gorboth)
 *
 *  TODO:
 *    - implement no fighting
 *    - implement no stealing
 *    - implement no spitting?
 */
#pragma strict_types

#include "../../defs.h"

inherit SPARKLE_ROOM_BASE;
inherit "/d/Emerald/blackwall/delrimmon/legacy/room_chairs";
inherit "/d/Genesis/ateam/aod/captcha/captcha_module";

#include <composite.h>
#include <language.h>
#include <macros.h>
#include <stdproperties.h>
#include <time.h>
#include "/d/Sparkle/area/city/sys/session.h"
#include "/d/Emerald/blackwall/delrimmon/legacy/room_chairs.h"


/* definitions */
#define TP                    this_player()
#define TO                    this_object()
#define BLOCK_NAME            "cushions"
#define CAPTCHA_DISTORTION    "_smoke_captcha_distortion"
#define SOLO_ANTE             "solo_ante_contest"


/* Global Variables */
public mixed      *Competitors = ({});
public int         Ante = 10;
public int         Pot = 0;
public int         Challenge_Underway = 0;


/* Prototypes */
public void        create_sparkle();
public string      describe();
public int         do_sit(string arg);
public void        do_sit_msgs(object pl, string prep, string name);
public void        do_stand_msgs(object pl, string name);
public string      look_tables();
public void        leave_inv(object ob, object dest);
public string      show_subloc(string subloc, object pl, object for_obj);
public string      sitting_on_chair(string name, object for_obj, int namesonly, int definite = 1);
public int         check_exit();
public int         do_ante(string arg);
public void        solo_ante(object who);
public void        all_ante(object who);
public int         complete_payment(object who, int needed,
                                    string action_txt);
public string      contest_status();

public mixed       query_competitors() { return Competitors; }
public int         query_ante()        { return Ante;        }
public int         query_pot()         { return Pot;         }


/*
 * Function name:        create_sparkle
 * Description  :        set up the room
 */
public void
create_sparkle()
{
    set_short("in a small intimate parlor");
    set_long("@@describe@@");

    add_chair(BLOCK_NAME, "[down] [at] [in] [on] [among] [one] [some]"
                        + " [a] [few] [of] [the] [cozy] [soft] [inviting]"
                        + " 'cushion' / 'cushions' / 'pillow' / 'pillows'",
                          10, "on", 0);

    add_item( ({ "here", "area", "room", "parlor", "parlour",
                 "small parlor", "small parlour", "intimate parlor",
                 "intimate parlour", "small intimate parlor",
                 "small intimate parlour" }),
        "This room offers a very different experence from that of the"
      + " main hall to the east, where things feel rowdy and crowded"
      + " in typical pub fashion. Here, there is a chance for more"
      + " intimate experiences and conversation.\n");
    add_item( ({ "experience", "different experience",
                 "very different experience" }),
        "Are you experienced?\n");
    add_item( ({ "hall", "main hall", "east", "main bar" }),
        "Things to the east are quite a bit more noisy and chaotic than"
      + " what you find here, typically.\n");
    add_item( ({ "pub", "tavern", "bar", "boars head tavern",
                 "boar's head tavern" }),
        "This is but a small part of the pub. The main hall of the tavern"
      + " is east of here, where most of the patrons tend to gather.\n");
    add_item( ({ "patron", "patrons" }),
        "You are one such yourself, are you not?\n");
    add_item( ({ "session", "drinking", "drinking session",
                 "session of drinking" }),
        "It is possible to enjoy a drinking session here, but one"
      + " would need to start it east at the main bar.\n");
    add_item( ({ "companion", "companionship" }),
        "On the lookout, are we? Maybe you'll find just what you are"
      + " in the mood for here.\n");
    add_item( ({ "care", "cares", "cares of the world" }),
        "They are many, but they tend to disappear with a good"
      + " drinking session. Speaking of which ...\n");
    add_item( ({ "decor", "curtain", "curtains" }),
        "The walls are draped with a few curtains which help cut down"
      + " on the sound, and provide a bit of warmth to the atmosphere.\n");
    add_item( ({ "atmosphere" }),
        "Not too bad, thanks to the curtains.\n");
    add_item( ({ "noise", "noises" }),
        "People don't tend to make too much in here. Most of the noise"
      + " is coming from the east, in the main hall of the tavern.\n");
    add_item( ({ "ceiling", "up", "roof" }),
        "Not much to see, really. A roof like most any you've experienced"
      + " is overhead.\n");
    add_item( ({ "cushion", "cushions", "cozy cushion", "cozy cushions",
                 "pillow", "cozy pillow", "pillows", "cozy pillows",
                 "soft cushions", "soft cushion", "many soft cushions",
                 "inviting cushion", "inviting cushions",
                 "inviting pillow", "inviting pillows" }),
        look_tables);
    add_item( ({ "floor", "ground", "down" }),
        "The ground is covered with many soft cushions here. You could"
      + " <sit> if you wished to make yourself more comfortable. A few"
      + " low tables provide space for those seated to set their"
      + " drinks down.\n");
    add_item( ({ "drink", "drinks" }),
        "Bars are always filled with them.\n");
    add_item( ({ "table", "tables", "low table", "low tables" }),
        "These are among the shortest you have ever seen, perfect for"
      + " people who are sitting on the ground to use for perching their"
      + " favorite drink.\n");
    add_item( ({ "favorite drink" }),
        "I bet you have one in mind, don't you?\n");

    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_M_NO_ATTACK, "You sense the dread presence of the"
      + " hellcat lurking just outside the room, and dare not!\n");
    add_prop(ROOM_M_NO_STEAL, "You sense the dread presence of the"
      + " hellcat lurking just outside the room, and dare not!\n");

    add_exit("sparkle_pub", "east", check_sitting, 1, 0);

    set_no_exit_msg( ({ "northeast", "southeast", "southwest",
                        "northwest" }),
        "You poke around the corner of the room, but find nothing.\n");
    set_no_exit_msg( ({ "north", "west", "south" }),
        "There is a wall in that direction.\n");

    setuid();
    seteuid(getuid());

    reset_room();
} /* create_sparkle */


/*
 * Function name:        describe
 * Description  :        provide a state-dependant description of the
 *                       parlor.
 * Returns      :        string - the description
 */
public string
describe()
{
    string  posture = ((this_player()->query_prop(
                            LIVE_S_SITTING) == BLOCK_NAME)
                      ? "lounging comfortably among"
                      : "standing over");

    return "You are in a small, intimate parlor " + posture + " many"
      + " soft cushions that are piled up around the floor. Here, one"
      + " can sit and enjoy a session of drinking, some companionship,"
      + " or just a bit of time away from the cares of the world. The"
      + " decor here is sparse, but elegant, with a few curtains"
      + " providing a bit of a sound damper from the noises coming from"
      + " the main hall to the east.\n";
} /* describe */


/*
 * Function name: init
 * Description:   set up the commands
 */
void
init()
{
//  add_action("do_ante", "ante");

    ::init();
    init_room_chairs();
} /* init */


/*
 * Function name:       do_sit
 * Description  :       mask parent to block "sit" and "sit down"
 * Arguments    :       string arg -- whatever the player typed
 * Returns      :       1 on success, 0 on failure
 */
public int
do_sit(string arg)
{
    if (!arg ||
        arg == "down")
    {
        notify_fail("Sit where?\n");
        return 0;
    }
    return ::do_sit(arg);
} /* do_sit */


/*
 * Function name:       do_sit_msgs
 * Description  :       mask parent so the block msgs look right
 * Arguments    :       object pl -- the person who's sitting
 *                      string prep -- the preposition
 *                      string name -- the name of the chair
 */
public void
do_sit_msgs(object pl, string prep, string name)
{
    write("You find a place among the cushions in the parlor, and"
      + " take a seat.\n");
    say(QCTNAME(pl) + " finds a place among the cusions and"
      + " takes a seat.\n");
} /* do_sit_msgs */


/*
 * Function name:       do_stand_msgs
 * Description  :       mask parent so the block msgs look right
 * Arguments    :       object pl -- the person who's standing
 *                      string name -- the name of the chair
 */
public void
do_stand_msgs(object pl, string name)
{
    write("You stand up from the cushions.\n");
    say(QCTNAME(pl) + " stands up from the cushions.\n");
} /* do_stand_msgs */


/*
 * Function name:        look_tables
 * Description  :        VBFC for block; include occupants
 * Returns      :        string -- the desc
 */
public string
look_tables()
{
    return "Inviting cushions are placed around the corners of this"
      + " dark and rather intimate parlor, inviting you to find a"
      + " nice cozy place to <sit> if you wished.\n"
         + sitting_on_chair(BLOCK_NAME, this_player(), 0, 0);
} /* look_block */


/*
 * Function name:       leave_inv
 * Description  :       mask parent to be sure that departing players
 *                      are removed from table occupants
 * Arguments    :       object ob -- the departing object
 *                      object dest -- its destination
 *
 * If they leave via a normal exit, they've already been made to stand.
 * However, if they leave by quitting, going netdead, teleporting, etc
 * and we don't call leave_inv_room_chairs(), then they'll still look
 * as if they're here.
 */
public void
leave_inv(object ob, object dest)
{
    ::leave_inv(ob, dest);
    leave_inv_room_chairs(ob, dest);
} /* leave_inv */


/*
 * Function name:       show_subloc
 * Description  :       generate "foo is sitting ..." msg
 *                      for living's desc.
 * Arguments    :       string subloc -- the subloc
 *                      object pl -- the player
 *                      object for_obj -- who's doing the looking
 * Returns      :       string -- the "is sitting" msg
 *
 * This is a mask from the room_chairs.c code, because I don't want to
 * have it be someone sitting at "the" anything ... I want my own
 * verbage here.
 */
public string
show_subloc(string subloc, object pl, object for_obj)
{
    string      name;
    mixed       *chairptr;

    if (this_player()->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS))
    {
        return "";
    }

    if (subloc != SITTING_S_SUBLOC)
    {
        return pl->show_subloc(subloc, pl, for_obj);
    }

    if (strlen(name = pl->query_prop(LIVE_S_SITTING)) &&
        pointerp(chairptr = query_room_chairs()[name]))
    {
        if (for_obj != pl)
        {
            return capitalize(pl->query_pronoun()) + " is sitting cozily "
              + chairptr[3] + " a few of the " + name + ".\n";
        }
        return "You are sitting cozily " + chairptr[3] + " a few of the"
          + " cushions.\n";
    }
    return "";
} /* show_subloc */


/*
 * Function name:       sitting_on_chair
 * Description  :       describe who's on the chair.
 * Arguments    :       string name -- the chair name
 *                      object for_obj -- who's doing the looking
 *                      int namesonly -- if true, returns only
 *                              the names of occupants, suitably
 *                              formatted, + " is" or " are"
 *                      int definite -- if true, we use a
 *                                     definite article when
 *                                     we modify the ledge name
 * Returns      :       string -- the desc of the occupants
 *
 * N.B. if namesonly is false, the returned string will have an ending
 * newline. if namesonly is true, it will not. it follows that if you
 * want to embed info about who's sitting on what in the middle of 
 * other text, you set namesonly to true and append your own location
 * string (e.g., " at the desk.").
 *
 * Ugh. I had to mask this one from the parent, too. I just didn't like
 * having the prepositions locked into "a" or "the". I needed "one"
 * or "various." (Gorboth)
 */
public string
sitting_on_chair(string name, object for_obj, int namesonly, int definite = 1)
{
    mixed       *chairptr;
    object      *occupants,
                *others;
    int         i,
                s;
    string      *names,
                 desc,
                 my_art,
                 some = " a few of the ";

    my_art = (definite ? " the " : " a ");

    if (!strlen(name) ||
        !pointerp(chairptr = query_room_chairs()[name]) ||
        !(s = sizeof(occupants = chairptr[2])))
    {
        return "";
    }

    if (!objectp(for_obj))
    {
        for_obj = this_player();
    }

    if (s == 1)
    {
        if (occupants[0] != for_obj) 
        {
            desc =  occupants[0]->query_Art_name(for_obj) + " is";
        }
        else
        {
            desc = "You are";
        }
    }
    else
    {
        some = " a few of the ";
        if ((i = member_array(for_obj, occupants)) < 0)
        {
            names = occupants->query_art_name(for_obj);
        }
        else
        {
            others = exclude_array(occupants, i, i);
            names = others->query_art_name(for_obj)  +  ({ "you" });
        }
        desc =  capitalize(COMPOSITE_WORDS(names)) + " are";
    }

    if (!namesonly)
        desc += " sitting cozily " + chairptr[3] + some + name + ".\n";
    return desc;
} /* sitting_on_chair */


/*
 * Function name:    check_exit
 * Description  :    players will stand up before leaving if sitting
 * Returns      :    1 - cannot leave, 0 - can leave
 */
public int
check_exit()
{
    return check_sitting();
} /* check_exit */


/*
 * Function name:        pre_image_hook
 * Description  :        Redefine this to create unique text that will
 *                       preceed the display of the captcha test.
 * Returns      :        string - the text to display
 */
public string
pre_image_hook()
{
    return "\n\n\nBlowing smoke into the air, the old woman holds"
      + " up a card with a letter on it.\n\n";
} /* pre_image_hook */


/*
 * Function name:        test_prompt_hook
 * Description  :        Redefine this to create unique text that will
 *                       follow the test image, prompting the player
 *                       for a response.
 * Returns      :        string - the text to display
 */
public string
test_prompt_hook()
{
    return "\n\nThe old woman will know your mind.\n\n"
      + "Which letter do you see? Answer: ";
} /* test_prompt_hook */


/*
 * Function name:        incorrect_answer_hook
 * Description  :        Redefine this to create unique text that will
 *                       indicate the player has failed the test
 * Returns      :        string - the text to display
 */
public string
incorrect_answer_hook()
{
    return "\nAlas! The old woman smiles at your wrong answer.\n";
} /* incorrect_answer_hook */


/*
 * Function name:        correct_answer_hook
 * Description  :        Redefine this to create unique text that will
 *                       indicate the player has passed
 * Returns      :        string - the text to display
 */
public string
correct_answer_hook()
{
    return "\nThe old woman's eyebrows raise. You were right!\n";
} /* correct_answer_hook */


/*
 * Function name:        do_ante
 * Description  :        Allow a player to begin a contest either
 *                       against the old woman, or against others.
 * Arguments    :        string arg - what was typed after the verb
 * Returns      :        1 - success, 0 - failure
 */
public int
do_ante(string arg)
{
    object   who = this_player();

    if (Challenge_Underway)
    {
        if (IN_ARRAY(who, Competitors))
        {
            notify_fail("Your current challenge is not yet"
              + " complete. Be patient!\n");
        }
        else
        {
            notify_fail("A challenge is being decided at this"
              + " very moment. You must wait for the conclusion"
              + " before you may do that.\n");
        }

        return 0;
    }

    if (arg != "solo" && arg != "all")
    {
        notify_fail("You can either <ante solo> to do a solo"
          + " challenge, or <ante all> to challenge other people"
          + " in the room.\n");

        return 0;
    }

    if (IN_ARRAY(who, Competitors))
    {
        notify_fail("You have already anteed up.\n");
        return 0;
    }

    if (sizeof(Competitors))
    {
        if (sizeof(Competitors) > 1 && Competitors[1] == SOLO_ANTE)
        {
            write(capitalize(Competitors[0]->query_The_name(who))
              + " is already involved in a solo contest with the"
              + " old woman. You'll need to wait until their"
              + " game is complete.\n");
            return 1;
        }
        else if (arg == "solo")
        {
            notify_fail(contest_status()
              + "A challenge has been issued by "
              + Competitors[0]->query_the_name(who) + ". If you"
              + " wished to compete for the pot, you could"
              + " <ante all> to take part.\n");
            return 0;
        }
    }

    if (arg == "solo")
    {
        solo_ante(who);
        return 1;
    }

    all_ante(who);
    return 1;
} /* do_ante */


public void
solo_ante(object who)
{
    if (!complete_payment(who, Ante,
           "sit down in front of the old woman."))
    {
        who->catch_tell("\nIt looks like you'd better find the right"
          + " coins first.\n");
        return;
    }
        
    Competitors = ({ who, SOLO_ANTE });
}


public void
all_ante(object who)
{
    string  fellows = ((sizeof(Competitors))
                    ? "beside " + COMPOSITE_LIVE(Competitors)
                    : "to await other challengers");

    if (!complete_payment(who, Ante,
           "sit down in front of the old woman " + fellows + "."))
    {
        who->catch_tell("\nIt looks like you'd better find the right"
          + " coins first.\n");
        return;
    }

    Competitors += ({ who });
}


/*
 * Function name:        complete_payment
 * Description  :        See if the player has the right number of
 *                       platinum coins for the transaction. If not,
 *                       we let them know.
 * Arguments    :        object who - the player trying to pay
 *                       int needed - the number of plats it will cost
 *                       string action_txt - describes the action
 * Returns      :        int 1 - successful payment made
 *                           0 - not able to pay
 */
public int
complete_payment(object who, int needed, string action_txt)
{
    object  *inv_items = all_inventory(who);
    object  coin;
    object  temp_location;
    string  coin_word = ((needed > 1) ? "coins" : "coin");

    foreach (object inv_item: inv_items)
    {
        if (inv_item->query_coin_type() == "platinum" &&
           (MASTER_OB(inv_item)) == "/std/coins")
        {
            coin = inv_item;
        }
    }

    if (!coin)
    {
        who->catch_tell("The old woman looks at you and shakes her"
          + " head. You do not have even a single platinum coin, and"
          + " you would need " + LANG_NUM2WORD(needed) + " of them to"
          + " take part in this ante.\n");
        return 0;
    }

    if (coin->num_heap() < needed)
    {
        who->catch_tell("The old woman raises one eyebrow at you."
          + " Your " + LANG_NUM2WORD(coin->num_heap())
          + " platinum " + coin_word
          + ((coin->num_heap() == 1) ? " falls" : " fall" )
          + " short of the " + LANG_NUM2WORD(needed) + " that would"
          + " be needed to ante up.\n");
        return 0;
    }

    who->catch_tell("You lay " + needed + " platinum " + coin_word
      + " on the red velvet pillow and " + action_txt + "\n");
    tell_room(environment(who), QCTNAME(who) + " lays some platinum"
      + " in the red velvet pillow and " + action_txt + ".\n", who);

    temp_location = clone_object("/std/room");
    coin->split_heap(needed);
    coin->move(temp_location);
    /* Clean up afterward. */
    temp_location->remove_object();

    //IMBUE_GENERATOR->imbue_log("imbue_payments", 
    //    TIME2FORMAT(time(), "mm/dd/yyyy")
    //  + " (" + ctime(time())[11..18] + ") "
    //  + capitalize(this_player()->query_name())
    //  + " pays " + needed + " platinum coins. (" + reason + ")\n");

    return 1;
} /* complete_payment */


/*
 * Function name:       contest_status
 * Description  :       Print a bit of info on the status of
 *                      the contest - size of ante/pot.
 * Returns      :       string - the text
 */
public string
contest_status()
{
    return "========================\n"
         + "  Current Ante = " + Ante + "plats\n\n"
         + "  Current Pot  = " + Pot + " plats\n"
         + "========================\n\n";
} /* contest_status */
