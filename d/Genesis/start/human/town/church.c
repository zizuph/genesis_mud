/*
 * Human Starting Location
 * Styles 910618
 *
 * Revision history:
 * "Start here" functionality added by /Mercade on 28 April 1994
 * 'Pray' command updated to ghost routines current on Dec 9/96
 *     by Khail.
 *
 * Changed query_race_name in the check for racestart to query_race
 * so that variants of humans can start here.
 *
 * Added newbie poster
 * TAPAKAH, 25/05/2005
 *
 * June 8, 2009 - Changed exits and included ROOM_S_MAP_FILE for inclusion
 *                into New Sparkle (Gorboth)
 * May 18, 2010 - Total style revision and general update, plus added
 *                a fatigue restoration through <rest> and a free
 *                startup weapon with <pray> and <request.> (Gorboth)
 *
 * November 3, 2017  - Made the Church a place of silence. It had become  
 *                     too much a place where people came to chat OOC, which 
 *                     is not what we want as a first experience of players 
 *                     coming from Tutori to the main game (Arman).
 *
 * September 5, 2020 - Changed the rest command so it only works for players
 *                     below veteran level. I think it's supposed to help our 
 *                     newbies, not be part of our larger players grinding 
 *                     scripts.
 */

#pragma save_binary
#pragma strict_types

inherit "/std/room";

#include "/d/Genesis/login/login.h"

#include <macros.h>
#include <stdproperties.h>
#include <time.h>
#include <state_desc.h>

#include "../defs.h"

/* Defenitions */
#define WELCOME_PROP    "_sparkle_church_got_welcomed"
#define REQUEST_PROP    "_sparkle_church_weapon_request"
#define SILENCE_SHADOW  "/d/Genesis/start/human/obj/church_silence_shadow"
#define SILENCE_OBJECT  "/d/Genesis/start/human/obj/church_silence_object"
#define BELLSOUND     "^G^G ^G^G"
#define TELL_STY(x)   find_living("styles")->catch_tell( \
                        ctime(time()) + BELLSOUND + x + "\n")

/* Prototypes */
public void        create_room();
public int         check_exit();
public string      curious();
public int         start(string str);
public void        enter_inv(object ob, object from);
public void        church_welcome(object who);
public int         pray(string str);
public int         rest(string str);
public string      wizinfo();
public int         do_request(string arg);
public void        init();

/*
 * Function name:        create_room
 * Description  :        constructor for the room object
 */
public void
create_room()
{
    set_short("Sparkle church");

    set_long("You are in the local village church. A large black stone"
      + " covers the center of the floor. The air is vaguely fogged by"
      + " burning incense and a feeling of tranquility comes over you."
      + " You feel at ease, as if this place offers you sanctuary from"
      + " all the cares of the world.\n");

    add_exit("/d/Sparkle/area/city/rooms/streets/center_f", "south",
        check_exit, 1, 0);

    add_item( ({ "stone", "large stone", "black stone",
                 "large black stone" }),
        "It feels smooth and somewhat warm to your touch. Its deep black"
      + " colour seems to play tricks with your vision. For a second your"
      + " eyes fail to focus and you feel like falling into a great void."
      + " Blinking at the sparks before your eyes, you shake your head"
      + " and compose yourself.\n");

    add_item( ({ "ceiling", "roof" }),
        "It is very high up and seems to be glittering with millions of"
      + " tiny stars. It is indeed very beautiful.\n");
    add_item( ({ "floor", "ground", "down" }),
        "The floor is made of large rectangular stone slabs. They are"
      + " well fitted and laid with skillful precision. One of the"
      + " slabs near the black stone seems to have an inscription of"
      + " some kind.\n");
    add_item( ({ "inscription", "slab" }),
        "It is carved into the stone floor and says:\n\n"
      + "            SPARKLE.\n"
      + "         LPmud Vers 3.0.\n"
      + "    Human starting location.\n"
      + "         Styles  910618\n"
      + "@@curious");
    add_item( ({ "here", "area", "church", "room" }),
        "Looking around the interior of the church you realize that"
      + " whoever built this place truly knew their craft.\n");

    add_prop(ROOM_M_NO_STEAL, "The black stone pulses, and prevents"
      + " your actions!\n");
    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_TYPE, ROOM_NORMAL);
    add_prop(ROOM_I_NO_ATTACK, 1);
    add_prop(OBJ_S_WIZINFO, "@@wizinfo");
    add_prop(ROOM_S_MAP_FILE, "sparkle_city_genesis.txt");
    add_prop(ROOM_I_LIGHT, ALWAYS_LIGHT);

    /* With the tutorial and new pre-creation sequence in place, we can
     * finally do away with Styles' excellent FAQ book. It served us
     * faithfully for nearly 20 years, but is finally rendered obsolete.
     *    - Gorboth, June 2011
    room_add_object("/d/Genesis/start/FAQ/faq_book");
     */
    room_add_object("/d/Genesis/start/newbie/poster");

    setuid();
    seteuid(getuid());
} /* create_room */


/*
 * Function name:        check_exit
 * Description  :        check to see if the player has been praying
 *                       before they leave.
 * Returns      :        0 - always
 */
public int
check_exit()
{
    if (this_player()->query_prop(REQUEST_PROP))
    {
        write("As you leave, the haze above the large black stone"
          + " dissipates and is gone.\n");

        this_player()->remove_prop(REQUEST_PROP);
    }

    return 0;
} /* check_exit */


/*
 * Just curious if someone ever look for nested add_items. If not then
 * quest clues should be placed with caution. -Styles
 */
public string
curious()
{
        TELL_STY(" ##  "+ TP->query_real_name() +" examined the church"
          + " slab.\n\n");
        return "";
} /* curious */


/*
 * Function name:        start
 * Description  :        allow players to start here
 * Arguments    :        string str - what was typed after the verb
 * Returns      :        int 1 - success, 0 - failure
 */
public int
start(string str)
{
    if (str != "here")
    {
        notify_fail("Start where? Here?\n");
        return 0;
    }

    if (RACESTART[this_player()->query_race()] != MASTER)
    {
        notify_fail("This is not your racial starting location.\n");
        return 0;
    }

    if (this_player()->set_default_start_location(MASTER))
    {
        write("Next time you enter the game, you will start here.\n");
    }
    else
    {
        write("Somehow it is not possible for you to start " +
              "here. The room apparently has not been approved of by the " +
              "archwizards of Genesis. Please mail the archwizard of " +
              "player affairs to get it allowed.\n");
    }

    return 1;
} /* start */


/*
 * Function name: enter_inv
 * Description:   Called when objects enter this container or when an
 *                object has just changed its weight/volume/light status.
 * Arguments:     ob: The object that just entered this inventory
 *                from: The object from which it came.
 *
 * Used to move new players to the correct area.
 */     
public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if (interactive(ob))
    {
        setuid();
        seteuid(getuid());
        clone_object(SILENCE_SHADOW)->shadow_me(ob);
        clone_object(SILENCE_OBJECT)->move(ob, 1);

        set_alarm(1.0, 0.0, &church_welcome(ob));
    }

    if (!interactive(ob) || from)
        return;

    if (ob->query_prop("just_created") == 1)
        ob->move(TOWN_DIR + "newcomer");

    return;
} /* enter_inv */

public void
leave_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    object s_obj;

    ob->remove_church_silence_shadow();

    if(s_obj = present("sparkle_church_no_talk_obj", ob))
      s_obj->remove_church_silence_object();

} /* leave_inv */


/*
 * Function name:        church_welcome
 * Description  :        Welcome players to the church, and give them
 *                       some guidance.
 */
public void
church_welcome(object who)
{
    int     welcomed = who->query_prop(WELCOME_PROP);

    /* To prevent horrible spam, we will only show the welcome prop
     * every 5th time the player enters the church after the first.
     */
    if (welcomed)
    {
        if (welcomed > 3)
        {
            who->remove_prop(WELCOME_PROP);
        }
        else
        {
            who->add_prop(WELCOME_PROP, welcomed + 1);
        }

        return;
    }
        
    who->catch_msg("\nA soothing voice whispers inside your"
      + " head: Welcome! While here you may <rest> if you are tired and"
      + " <pray> if you need a weapon or have lost your body.\n");

    who->add_prop(WELCOME_PROP, 1);

    return;
} /* church_welcome */


/*
 * Function name:        pray
 * Description  :        Allow players who are (for some reason) in ghost
 *                       form to get a new body.
 * Arguments    :        string str - whatever was typed after the verb
 * Returns      :        int 1 - always (?)
 */
public int
pray(string str)
{
    write("You kneel at the black stone and pray.\n\n"+
          "The texture of the stone makes it hard to focus your vision. "+
          "As your mind clears, you are overcome by a sensation of ease.\n");
    if (!TP->query_invis())
        say( ({METNAME +" kneels at the stone.\n",
                   ART_NONMETNAME +" kneels at the stone.\n"}) );


  /*
   * First we see if the player has a ghost_player.c object.
   * If this is the fact, we'll make sure they've got a ghost
   * var set so the death mark will function, and then give
   * a new death mark to try to repeat the death sequence.
   */
    if (MASTER_OB(TP) == LOGIN_NEW_PLAYER)
    {
      /*
       * Player is a physical ghost. Make sure the ghost
       * var is 33 (GP_DEAD | GP_BODY) and send them to
       * the bodies room.
       */
        TP->set_ghost(GP_DEAD | GP_BODY);
        write("A brilliant light shines above you from out " +
            "of nowhere. You feel yourself drawn upwards " +
            "into the light, to another place.\n");
        say(QCTNAME(TP) + " suddenly looks upwards, as " +
            "a brilliant beam of white light descends through "+
            "the ceiling and falls upon " + TP->query_possessive() +
            " shoulders. Before you realize it, " + 
            TP->query_pronoun() + " has vanished.\n");       
//        TP->move_living("M", "/d/Genesis/login/bodies", 1, 0);
        TP->move_living("M", "/d/Genesis/login/creation", 1, 0);
        say(QCTNAME(TP) + " arrives in a flash of light.\n");
        return 1;
    }

  /*
   * Ok, the player isn't using a ghost_player.c object, but we
   * have to make sure it's not a normal player with a ghost
   * var set running around. That's an easy repair by just
   * removing the ghost variable.
   */
    else if (TP->query_ghost())
    {
        write("Suddenly you feel more solid.\n");
        say(QCTNAME(TP) + " suddenly shimmers into view in " +
            "a more solid form.\n");
        TP->set_ghost(0);
        return 1;
    }

    if (this_player()->query_prop(REQUEST_PROP))
    {
        write("The haze above the slab thickens somewhat, awaiting"
          + " your <request> ...\n");

        return 1;
    }

    write("\nA strange haze materializes above the stone slab. It hangs"
      + " in the air for a moment, and then descends toward the sparkling"
      + " black surface of the stone where it begins to coalesce into"
      + " a dense form of some kind. You aren't sure how you know this, but"
      + " you realize that if you were to <request> a specific weapon"
      + " type, this haze would become the tool you desire.\n");

    this_player()->add_prop(REQUEST_PROP, 1);

    return 1;
} /* pray */


/*
 * Function name:        rest
 * Description  :        Allow small players to recover fatigue fully here
 * Arguments    :        string str - whatever was typed after the verb
 * Returns      :        int 1 - always
 */
public int
rest(string str)
{
    if (this_player()->query_average() > SD_AV_NEWBIE)
    {
        write("Expecting to feel refreshed and envigorated, you're"
          + " quite disappointed when absolutely nothing happens."
          + " Perhaps you're simply too strong to notice any effect?\n");
          return 1;
    }

    write("You rest a while, allowing the serenity of the church to wash"
      + " over you. Soon, you feel quite refreshed, and envigorated.\n");

    this_player()->set_fatigue(this_player()->query_max_fatigue());

    write("Ah, wasn't that nice.\n");

    log_file("fatigue_healed",
        TIME2FORMAT(time(), "mm/dd/yyyy") + " ("
      + ctime(time())[11..18] + ") "
      + capitalize(this_player()->query_real_name()) 
      + " healed fatigue at the Sparkle Church.\n");

    return 1;      

} /* rest */


/*
 * Function name:        wizinfo
 * Description  :        Provide some information for wizards on this
 *                       room.
 */
string
wizinfo()
{
    return ("This is the starting location for all players of the human"
      + " race. Dwarves, Elves, Gnomes and Hobbits will all have their"
      + " own separate starting locations but as of 910721 these are"
      + " not ready yet. This village is named Sparkle after the"
      + " mysterious black stone that has been the source of new human"
      + " life for as long as anyone care to remember. The village of"
      + " Sparkle is situated on the east coast of a large continent."
      + " It lies about 63 kilometers south of Larstown.\n\n"

    + "Okay, so this isn't really true anymore. However, this is such a"
    + " fascinating bit of history, I didn't want to remove it. Actually,"
    + " Sparkle is now the start location for all races, and there is no"
    + " such place as Larstown!\n\n");
} /* wizinfo */


/*
 * Function name:        do_request
 * Description  :        Allow players to request a weapon here in
 *                       the church.
 * Arguments    :        string arg - whatever was typed after the verb
 * Returns      :        int 1 - success, 0 - failure
 */
public int
do_request(string arg)
{
    object  wep;
    string *wep_types = ({ "sword", "axe", "polearm", "knife", "club" });

    if (query_verb() != "request")
    {
        notify_fail("You must <request " + query_verb() + ">.\n");
        return 0;
    }

    if (!this_player()->query_prop(REQUEST_PROP))
    {
        notify_fail("You should probably <pray> first, shouldn't you?"
          + " One can't expect blessings without a bit of piety!\n");
        return 0;
    }

    if (present("_sparkle_church_mistform_weapon", this_player()))
    {
        notify_fail("You already possess a mistform weapon. Let's not"
          + " be greedy with our blessings!\n");
        return 0;
    }

    if (!strlen(arg))
    {
        notify_fail("What type of weapon do you request? A sword,"
          + " axe, polearm, club, or knife?\n");
        return 0;
    }
    
    if (!IN_ARRAY(arg, wep_types))
    {
        notify_fail("You must choose a weapon type to request. For"
          + " example, if you want a sword, you must <request sword>."
          + " You could also choose an axe, polearm, knife, or club,"
          + " however.\n");
        return 0;
    }

    wep = clone_object("/d/Sparkle/area/city/wep/church_"
        + lower_case(arg));

    write("As you reach out toward the haze, the mist solidifies"
      + " completely, forming a dangerous-looking " + arg
      + " which you lift from the stone slab.\n");
    tell_room(this_object(), QCTNAME(this_player()) + " reaches out"
      + " toward the stone slab, and lifts something from its"
      + " surface.\n", this_player());

    if (wep->move(this_player()))
    {
        write("Oops! You're too overloaded, and drop it!\n");
        tell_room(this_object(), "Oops! "
          + capitalize(this_player()->query_pronoun())
          + " dropped it!\n", this_player());

        wep->move(this_object());
    }

    this_player()->remove_prop(REQUEST_PROP);

    log_file("free_weapons",
        TIME2FORMAT(time(), "mm/dd/yyyy") + " ("
      + ctime(time())[11..18] + ") "
      + capitalize(this_player()->query_real_name()) 
      + " got a mistform " + arg + " at the Sparkle Church.\n");

    return 1;
} /* do_request */


/*
 * Function name:        init
 * Description  :        add some actions to the player
 */
public void
init()
{
    add_action(start, "start");
    add_action(pray, "pray");
    add_action(pray, "regenerate");
    add_action(rest, "rest");
    add_action(do_request, "request");
    add_action(do_request, "knife");
    add_action(do_request, "sword");
    add_action(do_request, "club");
    add_action(do_request, "polearm");
    add_action(do_request, "axe");

    ::init();
} /* init */
