/*
 *  /d/Emerald/blackwall/delrimmon/obj/tablet.c
 *
 *  This is the base file which is inherited by the two broken fragments
 *  which the player is awarded for deciphering the emblem puzzles.
 *
 *  Copyright (c) 1995 - March 2001, by Cooper Sherry (Gorboth)
 *
 *  Updated pattern drawing routines in accordance with changes made to
 *  the quest manager. -Shiva, Oct 13 2003
 */
#pragma strict_types
inherit "/std/object";

#include <macros.h>
#include <stdproperties.h>
#include <math.h>
#include "/d/Emerald/blackwall/delrimmon/defs.h"

/* prototypes */
public void        create_tablet();
public void        create_object();
public string      describe();
public string      exa_pattern();
public string      draw_pattern(string pattern);


/*
 * Function name:        create_tablet
 * Description  :        dummy routine for inheriting files
 */
public void
create_tablet()
{
    ::create_object();
} /* create_tablet */


/*
 * Function name:        create_object
 * Description  :        set up the object
 */
public void
create_object()
{
    create_tablet();
    set_short("engraved stone fragment");
    set_long(describe);

    add_item( ({ "back", "back side", "back of tablet",
                 "back of tablets", "back of the tablets",
                 "back side of the tablets",
                 "back of fragment", "back of the fragment",
                 "back of the tablet", "back of the fragments",
                 "back side of tablet", "back side of the tablet",
                 "back side of the fragment", "back side of fragment",
                 "pattern", "marking", "markings" }), exa_pattern);

    add_prop(OBJ_M_NO_INS, "A strange magical force prevents the"
      + " fragment from fitting there.\n");
    add_prop(OBJ_M_NO_GIVE, "A bizarre selfish feeling comes over you,"
      + " and you find yourself unable to give it away.\n");
    add_prop(OBJ_M_NO_STEAL, "Just as your fingers touch the fragment,"
      + " a strange feeling comes over you, and you reconsider your"
      + " action.\n");
    add_prop(OBJ_I_WEIGHT, 20);
    add_prop(OBJ_I_VOLUME, 50);

    FIX_EUID
} /* create_object */


/*
 * Function name:        describe
 * Description  :        draw the depiction of what the player sees
 *                       when examining either or both of the tablet
 *                       fragments
 * Returns      :        string - the description
 */
public string
describe()
{
    string  tab;

    if (present("_del_rimmon_tablet_left", TP) &&
        present("_del_rimmon_tablet_right", TP))
    {
        tab = "You place the pieces together, and gaze at the intricate"
            + " letters engraved upon them.\n\n"

    +"\t     _______________________________   ______________\n"
    +"\t    '                               `v'              `\n"
    +"\t   |                                 |                |\n"
    +"\t   |  Ever vigilant are they who watc| over Telberin  |\n"
    +"\t   |    For they are gifted with the/ inner sight     |\n"
    +"\t   |   Their eyes as travellers thr|ughout Emerald    |\n"
    +"\t   |   And the Torque shall be thei| true vision      |\n"
    +"\t   |                              /                   | \n"
    +"\t   |    It will be with all who f|llow the signs      |\n"
    +"\t   |   Keeping faith with the wat|rs of Del Rimmon    |\n"
    +"\t   |            Trusting eye, ear|and hand            |\n"
    +"\t   |            Following the wr/tten rock            |\n"
    +"\t   |                         _/                       |\n"
    +"\t   |        Finding the w__/to the secret Tower       |\n"
    +"\t   |            By path/ which walk unseen            |\n"
    +"\t   |       Though writ|en map may give no aid         |\n"
    +"\t   |        Ael Ranna/h shall point the way           |\n"
    +"\t   |                |                                 |\n"
    +"\t   |                |                                 |\n"
    +"\t    `._____________,^._______________________________/\n";

        MANAGER->set_read_tablet(environment(this_object()), "Yes");
    }

    else if (present("_del_rimmon_tablet_left", TP))
    {
        tab = "It seems to be a broken fragment of a stone tablet:\n\n"

    +"\t     _______________________________  \n"
    +"\t    '                               `.\n"
    +"\t   |                                 |\n"
    +"\t   |  Ever vigilant are they who watc|\n"
    +"\t   |    For they are gifted with the/\n"
    +"\t   |   Their eyes as travellers thr|\n"
    +"\t   |   And the Torque shall be thei|\n"
    +"\t   |                              / \n"
    +"\t   |    It will be with all who f| \n"
    +"\t   |   Keeping faith with the wat|\n"
    +"\t   |            Trusting eye, ear|\n"
    +"\t   |            Following the wr/\n"
    +"\t   |                        __/\n"
    +"\t   |        Finding the w__/\n"
    +"\t   |            By path/\n"
    +"\t   |       Though writ|\n"
    +"\t   |        Ael Ranna/\n"
    +"\t   |                |\n"
    +"\t   |                |\n"
    +"\t    `._____________,'\n";
    }

    else
    {
    tab = "It seems to be a broken fragment of a stone tablet:\n\n"

    +"\t                      ______________\n"
    +"\t                     /              `\n"
    +"\t                    |                |\n"
    +"\t                    | over Telberin  |\n"
    +"\t                   / inner sight     |\n"
    +"\t                  |ughout Emerald    |\n"
    +"\t                  | true vision      | \n"
    +"\t                 /                   | \n"
    +"\t                |llow the signs      | \n"
    +"\t                |rs of Del Rimmon    |\n"
    +"\t                |and hand            |\n"
    +"\t              _/tten rock            |\n"
    +"\t           __/                       |\n"
    +"\t       ___/to the secret Tower       |\n"
    +"\t      / which walk unseen            |\n"
    +"\t     |en map may give no aid         |\n"
    +"\t    /h shall point the way           |\n"
    +"\t   |                                 |\n"
    +"\t   |                                 |\n"
    +"\t    `.______________________________/\n";
    }

    return tab + "\nThere appear to be some markings on the back"
               + " side of the tablet as well.\n";
} /* describe */


/*
 * Function name:        exa_pattern
 * Description  :        allow the player to see the pattern
 * Returns      :        string - the pattern
 */
public string
exa_pattern()
{
    string txt = "You turn the tablet over and examine the back side."
               + " There appear to be some markings there.\n\n\n";

    if (present("_del_rimmon_tablet_left", TP) &&
        present("_del_rimmon_tablet_right", TP) &&
        this_object()->id("_del_rimmon_tablet_left"))
    {
        return "";
    }

    MANAGER->assign_signal_pattern(this_player());

    txt += draw_pattern(MANAGER->query_first_pattern(this_player()));
    txt += draw_pattern(MANAGER->query_second_pattern(this_player()));
    txt += draw_pattern(MANAGER->query_third_pattern(this_player()));
    txt += draw_pattern(MANAGER->query_fourth_pattern(this_player()));
    txt += draw_pattern(MANAGER->query_fifth_pattern(this_player()));

    txt += "\n\n";

    if (!present("_del_rimmon_tablet_right", TP))
    {
        return txt + "\n";
    }

    return txt + "You notice a tiny figure carved beneath the"
      + " markings.\n";
} /* exa_pattern */


public string
pattern_bit_to_desc(int bit)
{
    // 1 represents a long blast, 0 represents a short blast
    return ((bit == 1) ? "*XXXXXXXXXXXXXXX*" : "*XXXXXX*");
}

/*
 * Function name:        draw_pattern
 * Description  :        draw the different lines of the pattern
 * Arguments    :        pattern - which pattern are we drawing?
 * Returns      :        string - the drawing of the pattern
 */
public string
draw_pattern(int pattern)
{
    string pattern_str;
    int i, *bits;

    // The leftmost bit is just a placeholder, so discard it.
    bits = DEC2BIN(pattern)[1..];

    pattern_str = implode(map(bits, pattern_bit_to_desc), " ");

    // Show the full pattern if both pieces are present. Otherwise, we
    // only show half.
    if (present("_del_rimmon_tablet_left", this_player()))
    {
        if (present("_del_rimmon_tablet_right", this_player()))
        {
            return "\t\t" + pattern_str + "\n\n";
        }

        return "\t\t" + pattern_str[0..strlen(pattern_str) / 2] + "\n\n";
    }
    else if (present("_del_rimmon_tablet_right", this_player()))   
    {
        return sprintf("\t\t%" + strlen(pattern_str) + "s\n\n",
                       pattern_str[strlen(pattern_str) / 2 + 1..]);
    }

    return "";
} /* draw_pattern */


/*
 * Function name:        leave_env
 * Description  :        since this is such a sensitive quest
 *                       item, we break it if it is dropped
 *                       or put in something
 * Arguments    :        object from - where it came from
 *                       object to   - where it went
 */
public void
leave_env(object from, object to)
{
    ::leave_env(from, to);

    if (!objectp(from) || !objectp(to) || !living(from))
        return;

    if (!to->query_prop(ROOM_I_IS))
    {
        return;
    }


    tell_room(to, "The " + TO->short() + " shatters into a million"
      + " tiny pieces as it hits the ground!\n");
    set_alarm(0.0, 0.0, "remove_object");
} /* leave_env */

