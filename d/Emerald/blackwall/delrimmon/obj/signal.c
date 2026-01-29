/*
 *  /d/Emerald/blackwall/delrimmon/obj/signal.c
 *
 *  The signal horn which was used by Formandil's men to sound various
 *  messages throughout the lake area. Different combinations were used
 *  for different purposes. It was enchanted by Maeltar to be used
 *  in the quest for the Toruqe.
 *
 *  Copyright (c) March 2001, by Cooper Sherry (Gorboth)
 *
 *  Routines only handled 15 horn blasts, but as many as 20 could be
 *  required to complete the signal. 30 blasts are now processed, and
 *  more will be ignored. -Shiva, Oct 13 2003
 */
#pragma strict_types

inherit "/std/object";
inherit "/d/Emerald/blackwall/delrimmon/legacy/tell_funcs";

#include <macros.h>
#include <stdproperties.h>
#include "/d/Emerald/quest_handler/quest_handler.h"
#include "/d/Emerald/blackwall/delrimmon/defs.h"

/* global variables */
public int         Glow = 0;
public int         Glow_Alarm = 0;
public int         Notes_Played = 0; /* Number of notes played */
public mixed       Last_Note = 0;  /* what type of note was played? */
public int         Ignore_Blast = 0;
public int         Pattern_Number = 0; /* binary pattern representation */
public mixed       Player = 0; /* last person who played a note */

/* prototypes */
public void        create_object();
public int         do_blow(string arg);
public void        init();
public void        glow_decay();
public void        glow_message();
public void        begin_glow(mixed actor);
public void        trigger_beacon();
public void        complete_quest(object player);


/*
 * Function name:        create_object
 * Description  :        set up the object
 */
public void
create_object()
{
    set_name("signal");
    add_name("del_rimmon_signal");
    add_name( ({ "horn", "trumpet" }) );
    add_adj( ({ "large", "mounted", "brass" }) );

    set_short("large mounted horn");
    set_long("A great brass horn stands out in the open air here,"
           + " mounted on a sturdy pillar of iron which is deeply"
           + " embedded in the rock of the cliffs. Though obviously"
           + " much neglected, and stained by centuries of exposure"
           + " to the elements, it looks fully functional and ready"
           + " to send forth a mighty call at need.\n");

    add_item( ({ "pillar", "pillar of iron", "iron" }),
        "The pillar upon which the large horn is mounted stands"
      + " erect, rising from the rock of the cliffs into which it"
      + " has been deeply embedded. Two tiny figures have been carved"
      + " into its surface, just beneath the base of the horn.\n");
    add_item( ({ "figure", "figures", "two figures", "tiny figure",
                 "tiny figures", "two tiny figures", "eye", "ear",
                 "carving", "carvings" }),
        "Beneath the horn, two tiny figures have been carved into the"
      + " pillar of iron. One is of an ear, and one is of an eye.\n");

    add_cmd_item( ({ "horn", "signal", "large horn", "mounted horn",
                     "large mounted horn" }),
                  ({ "search" }),
        "You noticed that something has been carved into the iron"
      + " pillar upon which the horn is mounted.\n");
    add_cmd_item( ({ "ear", "eye", "figure", "figures",
                     "ear figure", "eye figure",
                     "figure of an ear", "figure of an eye" }),
                  ({ "push", "press", "touch" }),
        "You press lightly on the figures, but nothing happens.\n");

    add_prop(OBJ_I_WEIGHT, 100000);
    add_prop(OBJ_I_VOLUME, 15000);
    add_prop(OBJ_M_NO_GET,
        "The horn is fixed in place atop a sturdy mount. You cannot"
      + " move it.\n");

    add_prop(OBJ_S_WIZINFO, "Wizards and juniors should avoid using the " +
        "horn while players are in Del Rimmon: triggering the beacon may " +
        "reveal quest information to players in the area.\n");

    FIX_EUID
} /* create_object */


/*
 * Function name:        do_blow
 * Description  :        allow the player to sound the horn
 * Arguments    :        string arg - what the player typed
 * Returns      :        int 1: success, 0: failure
 */
public int
do_blow(string arg)
{
    object *ppl = get_players_in_dir("/d/Emerald/blackwall/delrimmon/*");
    int     n;
    string *names = ({ "long", "short" });
    string  txt;
    string  note;

    if (!strlen(arg))
    {
        NFN0(CAP(QVB) + " what?");
    }

    if (!parse_command(arg, ({}),
        "[on] [the] [large] [mounted] 'horn' / 'signal'"))
    {
        if (!parse_command(arg, ({}),
            "[a] %p 'note' / 'blast' [on] [the] [horn] [signal]", names))
        {
            return 0; /* don't like the syntax */
        }

        switch(names[0])
        {
            case "long":
                txt = " a long, deep-throated blast on the horn.\n";
                Last_Note = "long";
                note = "A long, deep-throated horn call sounds"
                     + " suddenly throughout the area.\n";
                break;
            case "short":
                txt = " a short, crisp blast on the horn.\n";
                Last_Note = "short";
                note = "A short, crisp horn call sounds suddenly"
                     + " througout the area.\n";
                break;
            default:
                txt = "Something wierd happened.\n";
                break;
        }

        write("You blow" + txt);
        tell_room(environment(this_object()),
            QCTNAME(this_player()) + " blows" + txt, this_player());

        for (n = 0; n < sizeof(ppl); n++)
        {
            if (!environment(ppl[n])->query_prop("_signal_room"))
            {
                ppl[n]->catch_tell(note);
            }
        }

        begin_glow(this_player());
        return 1;
    }

    write("You blow a blast on the horn.\n");
    tell_room(environment(this_object()),
        QCTNAME(this_player()) + " blows a blast on the horn.\n",
        this_player());

    for (n = 0; n < sizeof(ppl); n++)
    {
        if (!environment(ppl[n])->query_prop("_signal_room"))
        {
            ppl[n]->catch_tell(
                "A loud horn call sounds suddenly throughout"
              + " the area.\n");
        }
    }

    begin_glow(this_player());

    return 1;
} /* do_blow */


/*
 * Function name:        init
 * Description  :        add some actions to the player
 */
public void
init()
{
    ::init();

    add_action(do_blow, "blow");
    add_action(do_blow, "sound");
    add_action(do_blow, "play");
} /* init */


/*
 * Function name:        glow_decay
 * Description  :        the magic glow of the horn will slowly
 *                       fade unless another note is blown
 */
public void
glow_decay()
{
    if (Glow <= 0)
    {
        remove_alarm(Glow_Alarm);
        tell_room(environment(this_object()),
            "The glow surrounding the horn dies away.\n");

        if (MANAGER->query_signal_pattern(Player) == Pattern_Number)
        {
            set_alarm(2.0, 0.0, trigger_beacon);

            if (!QH_QUERY_QUEST_COMPLETED(Player, "torque_horn"))
            {
                set_alarm(4.0, 0.0, &complete_quest(Player));
            }

            MANAGER->set_triggered_beacon(Player, "Yes");
        }

        Notes_Played = 0;
        Player = 0;
        Last_Note = 0;
        Pattern_Number = 1;
    }

    if (Glow == 5)
    {
        tell_room(environment(this_object()),
            "The glow surrounding the horn begins to fade somewhat.\n");
    }

    Glow--;
    return;
} /* glow_decay */


/*
 * Function name:        glow_message
 * Description  :        send a message to the room that the horn
 *                       begins glowing
 */
public void
glow_message()
{
    tell_room(environment(this_object()), "The horn begins to glow!\n");
    return;
} /* glow_message */


/*
 * Function name:        begin_glow
 * Description  :        the horn glows when it is played. Begin this
 *                       process.
 * Arguments    :        mixed actor - the player object for the person
 *                                     who blew the horn just now
 */
public void
begin_glow(mixed actor)
{
    if (Player)
    {
        if (Player != actor)
        {
            tell_room(environment(this_object()),
                "The glow on the horn subsides for a moment.\n");
            remove_alarm(Glow_Alarm);
            Glow = 0;
            Player = actor;
            Pattern_Number = 1;
            Notes_Played = 0;
            begin_glow(actor);
            return;
        }
    }

    Player = actor;
    Glow = 10;

    if (!Glow_Alarm || !sizeof(get_alarm(Glow_Alarm)))
    {
        Glow_Alarm = set_alarm(1.0, 1.0, glow_decay);
        set_alarm(1.0, 0.0, glow_message);

        Notes_Played = 0;
        Pattern_Number = 1;
    }

    Notes_Played++;

    // To avoid overflow, we only deal with 30 notes. The rest are ignored.
    if (Notes_Played > 30)
    {
        return;
    }

    // Create a bit-encoded value to store the pattern of horn blasts,
    // long = 1 short = 0. Remember that there must be a leading 1 
    // (Pattern_Number should be initialized to 1) so that we can capture
    // short blasts at the beginning.
    Pattern_Number = Pattern_Number << 1 | (Last_Note == "long" ? 1 : 0);
} /* begin_glow */


/*
 * Function name:        trigger_beacon
 * Description  :        this function triggers the beacon to be lit
 *                       in the Del Rimmon area. We use this function
 *                       for aesthetic purposes (the delay created by
 *                       set_alarm)
 */
public void
trigger_beacon()
{
    BEACON->light_beacon();
} /* trigger_beacon */


/*
 * Function name:        complete_quest
 * Description  :        reward the player if they have earned it
 * Arguments    :        object player - the player object
 */
public void
complete_quest(object player)
{
    if (QH_QUEST_COMPLETED(player, "torque_horn"))
    {
        player->catch_tell("You feel more experienced!\n");
    }
    else
    {
        player->catch_tell("You feel no more experienced.\n");
    }

    return;
} /* complete_quest */
