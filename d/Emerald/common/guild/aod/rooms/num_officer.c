/*
 *  /d/Emerald/common/guild/aod/rooms/num_officer.c
 *
 *  This is the Officers Quarters for the guild member who has collected
 *  the highest total number of skulls. (The Headhunter General)
 *
 *  Special notes: This room is a private chamber for whoever has
 *  earned the right to be called an officer of the Army. It is
 *  their private quarters to do with what they like. Perhaps they
 *  will use it for a droproom. But having such a luxury is no fun
 *  if you can't show it off. So, I've allowed the invitation of
 *  a single guest into these quarters. For fun, I've made it possible
 *  for them to be non-guild members. As the command 'ogrelove'
 *  suggests, this is something I imagine might be interesting to
 *  those who want to roleplay a bit of romance. If this is indeed
 *  the case, I've provided anyone in this room with free emotes.
 *  Personally, I am made uncomfortable by mud-sex or other such
 *  nonsense. However, there are those who enjoy such things, and so
 *  I'll give them the option here. (Options are good!)
 *
 *  Created January 2007, by Cooper Sherry (Gorboth)
 */
#pragma strict_types
#include "../defs.h"
#include <macros.h>
#include <std.h>
#include <stdproperties.h>
#include <time.h>
#include "/d/Gondor/open/room_chairs/room_chairs.h"

inherit AOD_ROOM_DIR + "cave_room";
inherit AOD_LIB_DIR + "add_spike";
inherit AOD_LIB_DIR + "bed_code";

/* global variables */
public string      Officer = NUM_OFFICER;
public string      Officer_Short = NUM_OFFICER_SHORT;
public string      Ogre_Guest;

/* prototypes */
public void        create_cave_room();
public void        set_up_officer_room();
public string      exa_pile();
public void        init();
public void        do_stand_msgs(object pl, string name);
public void        do_sit_msgs(object pl, string prep, string name);
public int         ogre_guest(string arg);

public void        set_officer(string s) { Officer = s; }
public void        set_officer_short(string s) { Officer_Short = s; }

/* definitions */
#define    CHAIR_NAME      "bone pile"


/*
 * Function name:        create_cave_room
 * Description  :        set up the room
 */
public void
create_cave_room()
{
    add_chair(CHAIR_NAME, "[down] [on] [the] [cozy]"
      + " [looking] [bone] [love] 'pile' / 'nest' / 'bed'", 2);

    set_up_officer_room();
    add_spike("num_officer");
    add_exit("magma", "west", check_sitting, 1, 0);

    setuid();
    seteuid(getuid());
} /* create_cave_room */


/*
 * Function name:    set_up_officer_room
 * Description  :    configure the room properly
 */
public void
set_up_officer_room()
{
    set_short("a warm, secluded chamber");
    set_em_long("These are the private quarters of the " + Officer
      + " of the Army of Darkness. Perhaps once a small"
      + " magma chamber, it is now a warm, secluded place where"
      + " the " + Officer_Short + " and perhaps a guest can enjoy"
      + " time alone. A cozy looking pile of bones rests in the"
      + " center of the room.\n");

    add_item( ({ "quarter", "quarters", "private quarter",
                 "private quarters" }),
        "The magic of the Darklings affords total privacy in this"
      + " place to all but the " + Officer + " and their"
      + " chosen guest.\n");
    add_item( ({ "magic", "darkling magic",
                 "magic of the darklings" }),
        "There is a strange purple energy floating around the"
      + " lava tube which acts as an entrance to this chamber."
      + " It seems to keep out anyone that is not supposed to"
      + " be here.\n");
    add_item( ({ "energy" }),
        "Yes ... purple energy!\n");
    add_item( ({ "purple energy" }),
        "Yes ... STRANGE purple energy!\n");
    add_item( ({ "strange energy" }),
        "Yes ... strange PURPLE energy!\n");
    add_item( ({ "strange purple energy" }),
        "Definitely the strangest purple energy you have ever seen."
      + " Well, except for all that other strange purple energy"
      + " the Darklings seem to have floating around the guild. That"
      + " stuff is just as strange and just as purple.\n");
    add_item( ({ "lava" }),
        "These chambers seem to be made of it.\n");
    add_item( ({ "chamber", "room", "place", "chambers", "here",
                 "area", "secluded chamber", "warm chamber",
                 "warm secluded chamber", "secluded place" }),
        "This place is warm and cozy. The walls pulse with a dull"
      + " red glow where the heat from magma which churns behind"
      + " the dried crust sends warmth through to soothe your"
      + " weary bones.\n");
    add_item( ({ "wall", "walls", "chamber wall", "chamber walls",
                 "crust", "wall of the chamber",
                 "walls of the chamber", "dried crust" }),
        "The dried crust pulses with a dull red glow."
      + " Ahh ... warmth.\n");
    add_item( ({ "pulse", "glow", "red glow", "dull glow",
                 "dull red glow" }),
        "Though the reality of the situation is somewhat lethal," 
      + " this room is still extremely cozy.\n");
    add_item( ({ "magma" }),
        "Good thing there are no holes in the crust.\n");
    add_item( ({ "warmth", "heat" }),
        "Ahhhh ... its like a warm bath in here.\n");
    add_item( ({ "bath", "warm bath" }),
        "You need to be slapped.\n");
    add_item( ({ "magma chamber", "small magma chamber",
                 "small chamber" }),
        "Long ago it is likely this was a pocket of magma that"
      + " has since seeped to the surface.\n");
    add_item( ({ "dome", "lava dome", "magma dome" }),
        "You are deep within it.\n");
    add_item( ({ "volcano" }),
        "You cannot view the volcano from here, though you are most"
      + " certainly deep within it.\n");
    add_item( ({ "sky" }),
        "The sky is not visible from here.\n");
    add_item( ({ "ceiling", "up", "roof" }),
        "The ceiling is made up of the same crust that forms the"
      + " walls of the chamber.\n");
    add_item( ({ "floor", "down", "ground" }),
        "The floor is made up of the same crust that forms the"
      + " walls. At the center of the floor is a cozy looking"
      + " pile of bones.\n");
    add_item( ({ "nest", "love nest", "personal love nest",
                 "ogre love nest" }),
        "Ah, love ... *sigh* ... wait, this is Ogre love ..."
      + " er ... *gulp*\n");
    add_item ( ({ "cloth", "pieces of cloth", "refuse",
                  "bones", "bone", "pile", "bone pile", 
                  "pile of bones", "cozy pile", "cozy looking pile",
                  "cozy pile of bones", "cozy bone pile",
                  "cozy looking pile of bones",
                  "cozy looking bone pile", "bed" }), exa_pile);
} /* set_up_officer_room */


/*
 * Function name:        exa_pile
 * Description  :        return the description of the bone pile. It
 *                       will be different depending on who examines
 *                       it.
 * Returns      :        string - the pile description
 */
public string
exa_pile()
{
    string  ptxt = "A pile of bones has been padded with various"
                 + " pieces of cloth and other refuse. It looks"
                 + " positively cozy. ";
    string      chairname = this_player()->query_prop(LIVE_S_SITTING);

    if (AOD_GENERAL(this_player()) ||
        AOD_CORPORAL(this_player()))
    {
        ptxt += "In fact, this appears as if it could become your"
          + " personal love nest. If you wish, you may allow a"
          + " single special person in here for private Ogre"
          + " fun. Use the command <ogrelove> to do so.\n";
    }
    else
    {
        ptxt += "You feel as if you have been welcomed into this"
          + " cozy Ogre love nest. ";

        if (!strlen(chairname))
        {
            ptxt += "Make yourself at home!\n";
        }

    }

    return ptxt + sitting_on_chair(CHAIR_NAME, this_player(), 0, 1);
} /* exa_pile */


/*
 * Function name:        do_emote
 * Description  :        We want this to be a free emote room. I'm
 *                       not a personal fan of mud-sex, but I suppose
 *                       I'll allow those who do like it their fun.
 * Arguments    :        string str - what the emote text should be.
 * Returns      :        1 - always
 */
public int
do_emote(string str)
{
    if (!strlen(str))
    {
        write("Emote what?\n");
        return 1;
    }

    write("You emote: "+ capitalize(this_player()->query_name())
      + " " + str + "\n");
    say(QCTNAME(this_player())+ " " + str + "\n");

    write_file(AOD_LOG_DIR + "chamber_log",
        TIME2FORMAT(time(), "mm/dd/yyyy") + " (" + ctime(time())[11..18]
      + ") " + capitalize(this_player()->query_name()) + " emotes: "
      + str + "\n");

    return 1;
} /* do_emote */


/*
 * Function name:        init
 * Description  :        init the room chairs
 */
public void
init()
{
    ::init();

    add_action(do_emote, "emote");
    add_action(ogre_guest, "ogrelove");

    init_room_chairs();
} /* init */


/*
 * Function name:       do_sit_msgs
 * Description  :       do the you-sit and foo-sits msgs
 * Arguments    :       object pl -- the person who's sitting
 *                      string prep -- the preposition
 *                      string name -- the name of the chair
 *
 * this function exists to provide a convenient hook for
 * inheriting rooms to roll their own messages.
 */
public void
do_sit_msgs(object pl, string prep, string name)
{
    write("You lie down on the bone pile, sprawling luxuriously"
      + " on numerous rib cages which crack beneath you. You get"
      + " the feeling that you could <emote> freely in here if"
      + " you felt so inclined.\n");
    say(QCTNAME(this_player()) + " lies down on the bone pile and"
      + " sighs luxuriously.\n");
} /* do_sit_msgs */


/*
 * Function name:       do_stand_msgs
 * Description  :       do the you-stand and foo-stands msgs
 * Arguments    :       object pl -- the person who's standing
 *                      string name -- the name of the chair
 *
 * this function exists to provide a convenient hook for
 * inheriting rooms to roll their own messages.
 */
public void
do_stand_msgs(object pl, string name)
{
    write("You roll to the side of the bone pile and stand up.\n");
    say(QCTNAME(this_player()) + " rolls to the side of the bone"
      + " pile and stands up.\n");
} /* do_stand_msgs */


/*
 * Function name:        ogre_guest
 * Description  :        Here we allow the officers to invite a
 *                       single person in to be their special
 *                       designated guest.
 * Arguments    :        string arg - what the player typed
 * Returns      :        1 - success, 0 - otherwise
 */
public int
ogre_guest(string arg)
{
    Ogre_Guest = CHAMBER_MASTER->get_info("guests", Officer_Short);

    if (!AOD_GENERAL(this_player()) &&
        !AOD_CORPORAL(this_player()))
    {
        notify_fail("Only the Officers of the Army may invite a"
          + " guest to this chamber!\n");
        return 0;
    }

    if (!strlen(arg))
    {
        if (!strlen(Ogre_Guest))
        {
            write("You may invite a special guest to be welcome"
              + " into your private chambers and the guildhall"
              + " with the syntax <ogrelove 'playername'>.\n");
            return 1;
        }

        write("Currently, " + capitalize(Ogre_Guest) + " is the person"
          + " you have invited to be a special guest in your personal"
          + " chambers and the Army of Darkness guild. If you no"
          + " longer wish to make them welcome, you may designate"
          + " 'none' with your <ogrelove> command, or just choose a"
          + " new guest.\n");

        return 1;
    }

    if (lower_case(arg) == "none")
    {
        if (!strlen(Ogre_Guest))
        {
            write("No need to do that since there is no one currently"
              + " designated as a guest.\n");

            return 1;
        }

        write_file(AOD_LOG_DIR + "guest_log",
            TIME2FORMAT(time(), "mm/dd/yyyy") + " ("
          + ctime(time())[11..18] + ") " + capitalize(
            this_player()->query_name()) + " cleared "
          + capitalize(Ogre_Guest) + " (" + Officer_Short + ")\n");

        CHAMBER_INFO(Officer_Short, 0);
        write("Your guest list is now cleared.\n");

        return 1;
    }

    if (!SECURITY->exist_player(arg))
    {
        write("No such person exists in the realms of Genesis.\n");
        return 1;
    }

    if (arg == this_player()->query_real_name())
    {
        write("Congratulations, you are now your own best friend."
          + " Now, perhaps you'd like to actually invite someone"
          + " ELSE in here?\n");

        return 1;
    }

    if (arg == Ogre_Guest)
    {
        write(capitalize(arg) + " is already designated as your"
          + " special guest. No need to reinvite them.\n");

        return 1;
    }

    CHAMBER_INFO(Officer_Short, arg);
    Ogre_Guest = CHAMBER_MASTER->get_info("guests", Officer_Short);

    write("You have invited " + capitalize(Ogre_Guest) + " to be"
      + " welcome into your private chambers and the Army of Darkness"
      + " guild.\n");

    write_file(AOD_LOG_DIR + "guest_log",
        TIME2FORMAT(time(), "mm/dd/yyyy") + " (" + ctime(time())[11..18]
      + ") " + capitalize(this_player()->query_name()) + " invited: "
      + capitalize(arg) + " (" + Officer_Short + ")\n");

    return 1;
} /* ogre_guest */