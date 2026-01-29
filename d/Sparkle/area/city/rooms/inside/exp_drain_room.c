/*
 *  /d/Sparkle/area/city/rooms/inside/exp_drain_room.c
 *
 *  We're experimenting with turning off the death experience penalty
 *  for players right now, which means we need a way for players to be
 *  able to voluntarily reduce their amount of accumulated experience
 *  if they so desire. This room makes that possible.
 *
 *  Created November 2013, by Gorboth (Cooper Sherry)
 */
#pragma strict_types

inherit "/std/room";

#include <macros.h>
#include <time.h>
#include "../../defs.h"


/* Prototypes */
public void        create_room();
public int         climb_stairs(string arg);
public void        init();
public void        do_meditate(string arg);
public int         do_offer(string arg);
public void        pay_death(int exp_cost, object who);
public int         check_warning(int exp_cost, object who);

/* Definitions */
#define            WARNING_PROP  "_exp_drain_warning_prop"
#define            SCYTHE_LOG    (LOG_DIR + "exp_drain_log")


/*
 * Function name:        create_room
 * Description  :        the room constructor
 */
public void
create_room()
{
    set_short("in a dim, murky attic of the Adventurer's Guild");
    set_long("You stand in the dim and murky confines of an attic"
      + " which does not appear to get many visitors. Light from"
      + " outside slants in through a small crack where some shingles"
      + " must have been blown off in a recent storm. The light falls"
      + " on a rather grim-looking circular carpet that rests on"
      + " the dusty floor in the center of the room. A set of"
      + " creaky stairs lead back down to the Adventurer's Guild.\n\n");

    add_item( ({ "here", "room", "area" }),
        "You are in the attic above the Adventurer's Guild in"
      + " Sparkle.\n");
    add_item( ({ "attic" }),
        "This attic looks like the sort of place that most people"
      + " either have forgotten about or avoid altogether.\n");
    add_item( ({ "murky attic", "murky confines" }),
        "And dim ...\n");
    add_item( ({ "dim attic", "dim confines" }),
        "And murky ...\n");
    add_item( ({ "dim murky attic", "murky dim attic",
                 "dim, murky attic", "dim and murky confines",
                 "murky and dim confines",
                 "dim murky confines", "murky dim confines"  }),
        "You said it. This place is just plain dismal.\n");
    add_item( ({ "dismal attic", "dismal place" }),
        "The place needs a woman's touch. Actually, it needs anyone's"
      + " touch. Okay, maybe not an Ogre.\n");
    add_item( ({ "confines", "confines of an attic" }),
        "Things are rather cramped up here, to be sure.\n");
    add_item( ({ "light", "light from outside" }),
        "The light is illuminating an area of the floor where a round"
      + " tattered carpet has been placed.\n");
    add_item( ({ "outside", "sky", "outside sky", "sky outside" }),
        "You can't see much from in here, only a glimpse of the lighter"
      + " outside sky that peeks between the crack in the roof.\n");
    add_item( ({ "crack", "small crack", "crack in the roof" }),
        "It isn't much bigger than two or three of your fingers.\n");
    add_item( ({ "shingles", "shingle" }),
        "Shingles are on the outside of a roof, not the inside. You're"
      + " in no position to examine them here.\n");
    add_item( ({ "storm", "recent storm" }),
        "Sparkle does get its share of storms, positioned here so close"
      + " to the sea.\n");
    add_item( ({ "sparkle" }),
        "Yep. You're in Sparkle.\n");
    add_item( ({ "visitor", "visitors" }),
        "Well, you're here, so I guess there's at least one today.\n");
    add_item( ({ "sea" }),
        "The Pen Sea is just east of here, bordering Sparkle's"
      + " harbour.\n");
    add_item( ({ "harbour", "harbor", "sparkle harbor", "sparkle harbour",
                 "sparkle's harbour", "sparkle's harbor" }),
        "If you'd like to see that, just leave the building and walk"
      + " east for a while.\n");
    add_item( ({ "pen sea" }),
        "They say the Pen Sea is named after Lars himself, whose last"
      + " name needed some sort of play on words.\n");
    add_item( ({ "floor", "down", "ground" }),
        "The floor of the attic is covered with dust. It is also"
      + " covered in part by a circular carpet.\n");
    add_item( ({ "dust" }),
        "Oh you know how it is in an attic - a regular dust gala.\n");
    add_item( ({ "gala", "dust gala" }),
        "Sorry, invitation only.\n");
    add_item( ({ "ceiling", "roof", "up" }),
        "The insides of the roof are stark and rough, slanting down"
      + " to frame the upper reaches of the attic.\n");
    add_item( ({ "upper reaches", "reaches", "upper reach",
                 "upper reaches of the attic" }),
        "Probably lots of spiders there.\n");
    add_item( ({ "spider", "spiders" }),
        "I said probably! No need to investigate. Oh, wait, are you"
      + " one of those oddballs who likes spiders? Shame on you!\n");
    add_item( ({ "stair", "stairs", "stairway", "set of stairs",
                 "creaky stair", "creaky stairs", "creaky stairway",
                 "set of creaky stairs" }),
        "The stairs lead back down to the main floor of the Adventurer's"
      + " Guild.\n");
    add_item( ({ "adventurer guild", "guild", "adventurers guild",
                 "adventurer's guild", "Adventurer's Guild",
                 "building", "main floor" }),
        "The main floor is just below, down those creaky stairs.\n");
    add_item( ({ "wall", "walls" }),
        "The walls here are actually the slanting innards of the roof.\n");
    add_item( ({ "innards", "innard", "innards of the roof",
                 "slanting innards", "slanting innards of the roof" }),
        "The room wouldn't make a good dance, hall, that's for sure.\n");
    add_item( ({ "dance hall" }),
        "Grab your partner, spin her round, do-si-do and OOOF!\n");
    add_item( ({ "carpet", "tattered carpet", "circular carpet",
                 "grim carpet", "grim-looking carpet",
                 "grim circular carpet", "grim-looking curcular carpet",
                 "grim tattered carpet" }),
        "The carpet is circular and black, woven thickly of some coarse"
      + " fabric. The image of a scythe and a grinning skull glow dully"
      + " from the surface, and the longer you stare, the more ill-at-"
      + "ease you feel about being here. A voice in your head whispers,"
      + "\"... yes ... you may <meditate> here also ... if you wish to"
      + " finally pay your dues ...\"\n");
    add_item( ({ "fabric", "coarse fabric" }),
        "It is black, and looks to be goat hair.\n");
    add_item( ({ "goat hair", "hair" }),
        "Very unlovely stuff, this.\n");
    add_item( ({ "scythe" }),
        "Wait, isn't that the favored tool of Death himself?\n");
    add_item( ({ "skull", "grinning skull" }),
        "Yeeesh ... \n");

    add_prop(ROOM_I_INSIDE, 1);

    add_exit("/d/Genesis/start/human/town/adv_guild", "down");

    setuid();
    seteuid(getuid());
} /* create_room */


/*
 * Function name:        climb_stairs
 * Description  :        Let players climb the stairs
 * Arguments    :        What the player typed after the verb
 * Returns      :        int 1 - success, 0 - failure
 */
public int
climb_stairs(string arg)
{
    if (!strlen(arg))
    {
        notify_fail("Climb where?\n");
        return 0;
    }

    if (!parse_command(arg, ({}),
        "[down] [the] [creaky] 'stair' / 'stairs' / 'stairway'"
      + " / 'staircase' [case]"))
    {
        notify_fail("Do you want to climb down the stairs perhaps?\n");
        return 0;
    }

    if (this_player()->query_wiz_level())
    {
        notify_fail("Normally, we would move the player 'down' here using"
          + " command(). Since you're a wizard, that won't work. You can"
          + " simply type <down> manually to use the stairs.\n");
        return 0;
    }

    this_player()->command("$d");
    return 1;
} /* climb_stairs */


/*
 * Function name:        init
 * Description  :        add some actions to the player 
 */
public void
init()
{
    ::init();

    add_action(climb_stairs, "climb");
    add_action(do_meditate, "meditate");
    add_action(do_offer, "offer");
} /* init */


/*
 * Function name:        do_meditate
 * Description  :        Allow players to meditate here
 * Arguments    :        string arg - what was typed after the verb
 * Returns      :        1 - always
 */
public int
do_meditate(string arg)
{
    write("You seat yourself on the circular carpet, and are instantly"
      + " swept into a deep trance. Into your mind comes a voice that"
      + " sounds like two slabs of rough stone slapping against one"
      + " another:\n\n"
      + "SO, HAVE YOU FINALLY COME TO PAY ME MY DUE? PERHAPS YOU ARE"
      + " TIRED OF ALL THIS UNHEALTHY EXPERIENCE YOU'VE GAINED? MAYBE"
      + " YOU'D LIKE TO UNLOAD THAT ON ME, EH? YES ... YES, I CAN HELP"
      + " WITH THAT. AND HERE IS HOW!\n\n"
      + "If you would like to rid yourself of combat and general"
      + " experience you can do so with the following commands here:\n\n"
      + "\t<offer death his due>           - Death will take one fifth\n"
      + "\t<offer death more than his due> - Death will take one half\n"
      + "\t<offer death everything>        - Death will take it all!\n\n"
      + "You rise, shaking slightly, from the carpet and ponder these"
      + " terrible potentials.\n");

    tell_room(this_object(), QCTNAME(this_player())
      + " sits down on the carpet, where "
      + this_player()->query_pronoun() + " slumps into a trance. A few"
      + " brief moments pass, and then " 
      + this_player()->query_pronoun() + " jerks alert once again to"
      + " rise, slightly shaken, from the carpet.\n", this_player());

    return 1;
} /* do_meditate */


/*
 * Function name:        do_offer
 * Description  :        Allow the player to give Death their
 *                       experience.
 * Arguments    :        string arg - what the player typed
 * Returns      :        int 1 - success, 0 - failure
 */
public int
do_offer(string arg)
{
    object  who = this_player();
    mapping exp_cost_map = ([ "death his due"           : 20,
                              "death more than his due" : 50,
                              "death everything"        : 100 ]);
    string *cost_map_indices = m_indices(exp_cost_map);

    notify_fail("You must correctly and exactly specify what you wish"
      + " to offer to Death. You can <meditate> here to learn the"
      + " correct methodology.\n");

    if (!strlen(arg))
    {
        return 0;
    }

    if (IN_ARRAY(arg, cost_map_indices))
    {
        write("You seat yourself on the circular carpet, and are"
          + " instantly swept into a deep trance.\n\n");
        tell_room(this_object(), QCTNAME(who)
          + " sits down on the carpet, where "
          + who->query_pronoun() + " slumps into a trance.\n", who);

        if (!check_warning(exp_cost_map[arg], who))
        {
            write("You blink suddenly, and rise from the carpet"
              + " to consider your choice.\n");
            tell_room(this_object(), QCTNAME(who)
              + " blinks and rises from the carpet again, a look of"
              + " contemplation on " + who->query_possessive()
              + " face.\n", who);

            return 1;
        }

        pay_death(exp_cost_map[arg], who);

        write("You rise, trembling, from the carpet.\n\n");
        tell_room(this_object(), QCTNAME(who)
          + " rises, trembling, from the carpet.\n", who);

        return 1;
    }

    return 0;
} /* do_offer */


/*
 * Function name:        pay_death
 * Description  :        The player is ready, so we pay death and
 *                       remove the warning in case they want to do it
 *                       again.
 * Arguments    :        int    exp_cost - the % of exp they will lose
 *                       object who      - the player
 */
public void
pay_death(int exp_cost, object who)
{
    int     cxp = who->query_exp_combat();
    int     gxp = who->query_exp_general();
    int     old_ave = who->query_average_stat();
    string  message;
    string  much = "";
    int     worth_it = ((cxp + gxp) > 5000);

    if (!worth_it)
    {
        message = "OH, THANKS A LOT. GET ME ALL EXCITED AND THEN YOU"
          + " DON'T EVEN HAVE ENOUGH EXPERIENCE TO SATISFY A GULLY"
          + " DWARF! KEEP YOUR PATHETIC SOUL AND COME BACK"
          + " IF YOU EVER HAVE A *REAL* OFFER FOR ME!";

        write("Into your mind comes a voice that sounds like two slabs"
          + " of rough stone slapping against one another:\n\n"
          + message + "\n\n");

        write_file(SCYTHE_LOG, 
            TIME2FORMAT(time(), "mm/dd/yyyy") + "--"
          + capitalize(who->query_name()) + "("
          + old_ave + ") offered " + exp_cost
          + "%: REJECTED! " + "(cxp: " + cxp + ", gxp: " + gxp +")\n");

        who->remove_prop(WARNING_PROP);
        return;
    }

    switch (exp_cost)
    {
        case 20:
            cxp = cxp / 5;
            gxp = gxp / 5;
            message = "SO, LARS THOUGHT HE COULD KEEP ME FROM GETTING"
              + " MY DUE, DID HE? HE NEVER THOUGHT OF YOU, THOUGH, I"
              + " GUESS. I ALWAYS GET MY DUE ONE WAY OR ANOTHER!"
              + " AH, JUST LIKE THE GOOD OLD DAYS! HAHAHAHAHAHA!";
            break;
        case 50:
            cxp = cxp / 2;
            gxp = gxp / 2;
            message = "SO, LARS THOUGHT A LUCKY WIN AT CARDS WOULD"
              + " KEEP ME FROM GETTING MY DUE, DID HE? JUST LOOK AT"
              + " THIS, YOU PROVING HIM SO WRONG THAT I'M GETTING"
              + " MORE THAN I USED TO. OH, WAIT TILL I TELL HIM ABOUT"
              + " YOU. I CAN'T WAIT TO SEE THE LOOK ON HIS FACE!"
              + " IT'S EVEN BETTER THAN THE GOOD OLD DAYS! HAHAHAHAHAHA!";
            much = " much";
            break;
        default:
            message = "OH, THIS IS RICH! ONE LUCKY CARD GAME AND LARS"
              + " THINKS HE'S GOT ME ALL DRIED UP FROM GETTING MY DUE,"
              + " BUT THEN YOU COME ALONG AND GIVE UP THE WHOLE FARM!"
              + " LARS WILL CRY HIMSELF TO SLEEP TONIGHT, AND MY"
              + " LAUGHTER WILL BE HIS LULLABYE! HAHAHAHAHAHAHAHAHAHA!";
            much = " MUCH";
            break;
    }

    write("Into your mind comes a voice that sounds like two slabs"
      + " of rough stone slapping against one another:\n\n"
      + message + "\n\n"
      + "The ghostly image of a scythe flies up suddenly out of the"
      + " carpet and slices mercilessly into your soul!\n\n"
      + "You feel" + much + " less experienced!\n\n");
    tell_room(this_object(),
        "\nThe ghostly image of a scythe flies up suddenly out of the"
      + " carpet and slices mercilessly through " + QTNAME(who)
      + "!\n\n", who);

    who->add_exp_combat(-cxp);
    who->add_exp_general(-gxp);
    who->remove_prop(WARNING_PROP);

    write_file(SCYTHE_LOG, 
        TIME2FORMAT(time(), "mm/dd/yyyy") + "--"
      + capitalize(who->query_name()) + "("
      + old_ave + ") paid " + exp_cost
      + "% " + "(cxp: " + cxp + ", gxp: " + gxp + ", ave: "
      + who->query_average_stat() + ")\n");

    return;
} /* pay_death */


/*
 * Function name:        check_warning
 * Description  :        The player gets a warning before they take the
 *                       plunge here. We want to be sure to spell it out
 *                       very clearly what they are about to do.
 * Arguments    :        int    exp_cost - the % of exp they will lose
 *                       object who      - the player
 * Returns      :        int 1 - the have already been warned
 *                       int 0 - they have not yet been warned, and we warn
 *                               them now.
 */
public int
check_warning(int exp_cost, object who)
{
    string  loss_amount;

    if (who->query_prop(WARNING_PROP) == exp_cost)
    {
        return 1;
    }

    switch (exp_cost)
    {
        case 20:
            loss_amount = "one fifth";
            break;
        case 50:
            loss_amount = "one half";
            break;
        case 100:
            loss_amount = "ALL";
            break;
        default:
            who->catch_tell("There seems to have been a catastrophic"
              + " rip in the fabric of reality. Please contact an"
              + " Administrative wizard via mail about this problem"
              + " and file a bug report.\n");
            return 0;
            break;
    }

    who->catch_tell("WARNING: To pay Death his due you will be giving"
              + " up " + loss_amount + " of the combat and general"
              + " experience you have earned. If you are convinced you"
              + " wish to proceed, please type the command a second"
              + " time.\n\n");
    who->add_prop(WARNING_PROP, exp_cost);
    return 0;
} /* check_warning */