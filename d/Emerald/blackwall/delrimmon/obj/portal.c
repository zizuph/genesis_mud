/*
 *  /d/Emerald/blackwall/delrimmon/obj/portal.c
 *
 *  This item is placed in the rooms which are potentially identified
 *  by the Finger of Maeltar. It is invisible unless the player has
 *  activated the enchantment.
 *
 *  Copyrignt (c) March 2001, by Cooper Sherry (Gorboth)
 *
 *  Changed the password checking routine to give a message when an incorrect
 *  suffix is used. Previously, the player would simply see "What?", and we
 *  would occasionally get bug reports from confused players who thought the
 *  quest was bugged. The player would already receive a message when
 *  incanting the password without any suffix at all, so this change shouldn't
 *  make the portal any easier to find simply by running around incanting in
 *  every room. -Shiva, Oct 14 2003
 */
#pragma strict_types

inherit "/std/object";

#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include "/d/Emerald/quest_handler/quest_handler.h"
#include "/d/Emerald/blackwall/delrimmon/defs.h"

/* global variables */
public mixed       Standing = 0;  /* who is standing in the depression? */

/* prototypes */
public void        create_object();
public string      do_test();
public string      exa_this();
public int         do_stand(string arg);
public int         say_password(string arg);
public void        complete_quest(object player);
public void        corporeal_flux(object who, int what);
public int         do_point(string arg);
public void        init();

public mixed       query_standing() { return Standing; }


/*
 * Function name:        remove_standing
 * Description  :        remove the person standing from the
 *                       depression
 * Arguments    :        int falling - true if the person is leaving
 *                       the room because they have triggered the
 *                       enchantment in the portal. Default = 0.
 */
public void
remove_standing(int falling = 0)
{
    if (Standing)
    {
        if (!falling)
        {
            Standing->catch_msg("You step out of the depression.\n");
        }

        Standing = 0;
    }
} /* remove_standing */


/*
 * Function name:        create_object
 * Description  :        set up the object
 */
public void
create_object()
{
    set_name("portal");
    add_name( ({ "depression", "_del_rimmon_portal" }) );
    add_adj( ({ "circular" }) );

    set_short("circular depression in the ground");
    set_long(exa_this);

    add_prop(OBJ_M_NO_GET, "What?\n");

    FIX_EUID
} /* create_object */


public string
do_test()
{

    return MASTER->query_door_location(this_player()) + "\n";
}


/*
 * Function name: check_seen
 * Description:   True if this object can be seen by a given object
 * Arguments:     for_obj: The object for which visibilty should be checked
 * Returns:       1 if this object can be seen.
 */
public int
check_seen(object for_obj)
{
    string  lname = MANAGER->query_door_location(this_player());

    if (!objectp(for_obj) ||
         obj_no_show ||
        !this_player()->query_prop(SEEN_PROP) ||
        !environment(this_object())->id(lname) ||
         (!for_obj->query_wiz_level() &&
          (for_obj->query_prop(LIVE_I_SEE_INVIS) <
           this_object()->query_prop(OBJ_I_INVIS) ||
           for_obj->query_skill(SS_AWARENESS) <
           this_object()->query_prop(OBJ_I_HIDE))))
    {
        return 0;
    }

    return 1;
} /* check_seen */


/*
 * Function name:        exa_this
 * Description  :        show this to the player if and only if they have
 *                       triggered the enchantment (we know this by the
 *                       prop added to them should they do so.
 * Returns      :        string - the description
 */
public string
exa_this()
{
    string  txt;

    if (!this_player()->query_prop(SEEN_PROP))
    {
        return "You find no depression.\n";
    }

    txt = "A circular depression is visible in the ground here. It"
         + " almost looks to be a thin layer of turf"
         + " covering a large hole like a net. It appears to be roughly"
         + " five feet in diameter. ";

    if (Standing)
    {
        if (Standing == this_player())
        {
            txt += "You are standing upon it.";
        }
        else
        {
            txt += Standing->query_The_name() + " is standing upon it.";
        }
    }

    return txt + "\n";
} /* exa_this */


/*
 * Function name:        do_stand
 * Description  :        allow the player to try to stand on the
 *                       portal.
 * Arguments    :        string arg - what the player typed
 * Returns      :        int 1 - success, 0 - failure
 */
public int
do_stand(string arg)
{
    if (!environment(this_object())->id(
         MANAGER->query_door_location(this_player())))
    {
        return 0;
    }

    if (!strlen(arg))
    {
        NFN0(CAP(QVB) + " where?");
    }

    if (!parse_command(arg, ({}),
        "[on] [into] [in] [to] [inside] [the] [circular] 'depression'") ||
        QVB == "leave" || QVB == "exit")
    {
        if (parse_command(arg, ({}),
            "[off] [out] [of] [the] [circular] 'depression'"))
        {
            if (Standing == this_player())
            {
                remove_standing();
                return 1;
            }

            return 0;
        }
        return 0; /* can't parse the player's syntax */
    }

    if (!this_player()->query_prop(SEEN_PROP))
    {
        return 0;
    }

    if (Standing)
    {
        if (Standing == this_player())
        {
            write("You are already standing on the depression.\n");
            return 1;
        }

        this_player()->catch_msg(QCTNAME(Standing) + " is already"
          + " standing there.\n");
        return 1;
    }

    write("You step into the center of the depression.\n");
    Standing = this_player();

    return 1;
} /* do_stand */


/*
 * Function name:        say_password
 * Description  :        catch it if the player happens to speak the
 *                       password which he has been assigned for the
 *                       portal
 * Arguments    :        string arg - what the player typed after 'say'
 * Returns      :        1 - success, 0 - failure
 */
public int
say_password(string arg)
{
    string  txt = LOW(arg);
    string  ptxt;
    string  correct = MANAGER->query_password(this_player())
                    + MANAGER->query_suffix(this_player());
    string  close = MANAGER->query_password(this_player());

    if (!environment(this_object())->id(
        MANAGER->query_door_location(this_player())))
    {
        return 0; /* don't want to give this out so easily */
    }

    if (txt == correct ||
        txt == correct + "." ||
        txt == correct + "!")
    {
        if (!environment(this_object())->id(
            MANAGER->query_door_location(this_player())))
        {
            /* right command word, wrong room! */
            return 0;
        }

        write("You incant: " + CAP(correct) + "!\n");

        if (this_player() == Standing)
        {
            set_alarm(1.0, 0.0, &corporeal_flux(this_player(), 1));
            return 1;
        }

        if (!this_player()->query_prop(SEEN_PROP))
        {
            set_alarm(1.0, 0.0, &corporeal_flux(this_player(), 2));
            return 1;
        }
        else
        {
            set_alarm(1.0, 0.0, &corporeal_flux(this_player(), 3));
        }

        return 1;
    }

#if 0
    if (txt == close ||
        txt == close + "." ||
        txt == close + "!")
#else
    if (strlen(txt) &&
        (txt[strlen(txt) - 1] == '.' ||
        txt[strlen(txt) - 1] == '!' ||
        txt[strlen(txt) - 1] == '?'))
    {
        txt = txt[..-2];
    }
 
    if (wildmatch(close + "*", txt))
#endif
    {
        write("You incant: " + CAP(txt) + "!\n");
        write("Nothing seems to happen.\n");

        return 1;
    }


    return 0; /* let the mudlib take it from here */
} /* say_password */


/*
 * Function name:        complete_quest
 * Description  :        reward the player for their progress
 * Arguments    :        object player - the player object
 */
public void
complete_quest(object player)
{
    if (QH_QUEST_COMPLETED(player, "torque_portal"))
    {
        player->catch_tell("As you gaze on these strange new"
          + " surroundings, you feel as if your hard work has"
          + " been worth the effort.\n"
          + "You feel more experienced!\n");
    }
    return;
} /* complete_quest */


/*
 * Function name:        corporeal_flux
 * Description  :        the player has triggered the enchantment.
 *                       here we determine what will happen based on
 *                       whether the player has seen it yet, or
 *                       whether they are standing in it
 * Arguments    :        int what 1: seen it, in it
 *                                  2: not seen it, not in it
 *                                  3: seen it, not in it
 *                       object who - the player
 */
public void
corporeal_flux(object who, int what)
{
    switch(what)
    {
        case 1:
            who->catch_msg("The ground beneath you pulses with a"
              + " bright blue light, and you feel yourself falling!"
              + " All goes black.\n\n");
            who->move_living("M",
                DELRIMMON_DIR + "lakeside/caves/fallroom", 1, 1);
            MANAGER->set_found_tower(this_player(), "Yes");
            set_alarm(20.0, 0.0, &complete_quest(this_player()));
            break;
        case 2:
            who->catch_msg("A circular section of the ground pulses"
                 + " briefly with a bright blue light. As it fades, you"
                 + " notice that the ground has sunk considerably"
                 + " where the light shone, leaving a visible"
                 + " depression.\n");
            who->add_prop(SEEN_PROP, 1);
            break;
        case 3:
            who->catch_msg("The depression pulses briefly with a bright"
                 + " blue light which soon fades and disappears.\n");
            break;
    }

    return;
} /* corporeal_flux */


/*
 * Function name:        do_point
 * Description  :        we don't want players to be able to point
 *                       this out to people who can't see it, so we
 *                       need to mask the emote and create our
 *                       own
 * Arguments    :        string arg - what the player typed
 * Returns      :        int 1 - success, 0 - failure
 */
public int
do_point(string arg)
{
    if (!strlen(arg))
    {
        return 0;
    }

    if (!parse_command(arg, ({}),
        "[at] [the] [circular] 'depression' / 'portal' [in] [the]"
      + " [ground]"))
    {
        return 0; /* let the mudlib take it */
    }

    write("You point at the circular depression in the ground.\n");
    tell_room(environment(this_player()),
        QCTNAME(this_player()) + " points at the ground.\n",
        this_player());

    return 1;
} /* do_point */


/*
 * Function name:        init
 * Description  :        add some actions to the player
 */
public void
init()
{
    ::init();

    add_action(do_point, "point");
    add_action(do_stand, "get");
    add_action(do_stand, "stand");
    add_action(do_stand, "enter");
    add_action(do_stand, "move");
    add_action(do_stand, "step");
    add_action(do_stand, "walk");
    add_action(do_stand, "leave");
    add_action(do_stand, "exit");
    add_action(say_password, "incant");
    add_action(do_test, "test");
} /* init */
