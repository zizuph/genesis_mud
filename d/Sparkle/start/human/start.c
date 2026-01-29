/*
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
 */

#pragma save_binary
#pragma strict_types

inherit "/std/room";

#include "/d/Genesis/login/login.h"

#include <stdproperties.h>
#include <macros.h>

#include "defs.h"
#include S_DOMAIN_SYS_LINKS

void
create_room()
{
    set_short("Sparkle church");

    set_long("\n"+
             "You are in the local village church.\n"+
             "A large black stone covers the center of the floor.\n"+
             "The air is vaguely fogged by burning incense and a feeling of\n"+
             "tranquility comes over you. You feel at ease. Lost souls come\n"+
             "here to pray and reincarnate while tired people come here to rest.\n"+
             "");

    add_exit(S_LOCAL_ROOM_DIR + "road4", "south");

    add_item(({"stone" }),"It feels smooth and somewhat warm to your touch. Its deep black\n"+
    "colour seems to play tricks with your vision. For a second your eyes\n"+
    "fail to focus and you feel like falling into a great void. Blinking\n"+
    "at the sparks before your eyes, you shake your head and compose yourself.\n"+
    "");
    add_item(({"ceiling" }),"It is very high up and seems to be glittering with\n"+
    "millions of tiny stars. It is indeed very beautiful.\n"+
    "");
    add_item(({"floor" }),"The floor is made of large rectangular stone slabs.\n"+
    "They are well fitted and laid with skillful precision.\n"+
    "One of the slabs near the black stone seems to have an\n"+
    "inscription of some kind.\n"+
    "");
    add_item(({"inscription","slab" }),"It is carved into the stone floor and says,\n"+
    "       LPmud Vers 3.0\n"+
    "    Human starting location.\n"+
    "       Styles  910618\n"+
    "");
    add_item(({"room" }),"Looking around the interior of the church you realize\n"+
    "that whoever built this place truly knew their craft.\n"+
    "");

    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_TYPE, ROOM_NORMAL);
    add_prop(ROOM_I_NO_ATTACK, 1);
    add_prop(OBJ_S_WIZINFO, "@@wizinfo");

    room_add_object(S_COMMON_OBJ_DIR + "faq_book");
    room_add_object(S_COMMON_OBJ_DIR + "newbie_poster");
}

int
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
}

int query_no_snoop() { return 1; }

void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if (!interactive(ob) || from)
        return;

    if (ob->query_prop("just_created") == 1)
        ob->move(S_COMMON_ROOM_DIR + "newcomer");

    return;
}

int
pray(string str)
{
    write("You kneel at the black stone and pray.\n"+
          "The texture of the stone makes it hard to focus your vision.\n"+
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
        TP->move_living("M", S_LINK_LOGIN_BODIES, 1, 0);
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

    write("Nothing else happens.\n");
    return 1;
}

int
rest(string str)
{
    write("Ah, wasn't that nice.\n");
    return 1;
}

string
wizinfo()
{
    return ("This is the starting location for all players of the human race.\n"+
            "Dwarves, Elves, Gnomes and Hobbits will all have their own\n"+
            "separate starting locations but as of 910721 these are not\n"+
            "ready yet. This village is named Sparkle after the mysterious\n"+
            "black stone that has been the source of new human life for as\n"+
            "long as anyone care to remember. The village of Sparkle is\n"+
            "situated on the east coast of a large continent. It lies about\n"+
            "63 kilometers south of Larstown.\n");
}

int
do_start(string str)
{
    if (str == "here" && this_player()->query_race() == "human")
    {
        this_player()->set_default_start_location(S_DOMAIN_START_DIR + "human/start");
        write("Ok.\n");
        return 1;
    }
    return 0;
}

void
init()
{
    add_action(start, "start");
    add_action(pray, "pray");
    add_action(pray, "regenerate");
    add_action(rest, "rest");

    ::init();
}

