/*
 *  /d/Emerald/common/guild/aod/obj/chaos_gate.c
 *
 *  This is the Chaos Gate - a structure which Val-Shoreil once used
 *  to traverse the land. In that it is of his own chaotic nature, one
 *  can never be sure where it will land you. Use at your own risk!
 *
 *  Created April 2007, by Cooper Sherry (Gorboth)
 */
#pragma strict_types
#include "../defs.h"

inherit "/std/object";

#include <macros.h>
#include <stdproperties.h>
#include <time.h>
#include "../chaos_locations.h"


/* Definitions */
#define        ALARM_INTERVAL  3.0
#define        CHAOS_DESTINATIONS ({ \
                   AOD_ROOM_DIR + "tunnel5", \
                   AOD_ROOM_DIR + "council", \
                                  })

/* Prototypes */
public void        create_object();
public void        init();
public int         touch_gate(string arg);
public int         enter_gate(string arg);
public void        chaos_warp(object who, int count, object vortex);
public void        crashland(object who, int count, object midair);

/*
 * Function name:        create_object
 * Description  :        set up the object
 */
public void
create_object()
{
    set_name("gate");
    set_short("huge swirling vortex");
    add_name( ({ "vortex", "portal", "structure" }) );
    add_adj( ({ "huge", "swirling", "chaos", "orange", "energy",
                "giant", "big", "large", "massive" }) );

    set_long("Before you looms a Chaos Gate. These massive structures"
      + " have existed for centuries in Emerald - remnants from the"
      + " time of Darkness before the conquest of the Elves. The"
      + " gate itself is a swirling vortex of orange energy perhaps"
      + " forty meters high, couched between a huge pillar of black"
      + " stone on either side. Enter it, if you dare!\n");

    add_item( ({ "energy", "swirling energy" }),
        "It swirls hideously fast, and throbs ominously with power.\n");
    add_item( ({ "stone", "black stone", "pillar", "pillars",
                 "pillar of stone", "stone pillar", "huge pillar",
                 "huge pillar of black stone" }),
        "The pillars on either side of the vortex make this already"
      + " frightening structure look positively ominous.\n");

    add_prop(OBJ_I_VOLUME, 10000000);
    add_prop(OBJ_I_WEIGHT, 10000000);
    add_prop(OBJ_M_NO_GET, "Don't be ridiculous.\n");

    setuid();
    seteuid(getuid());
} /* create_object */


/*
 * Function name:        init
 * Description  :        add some actions to the player
 */
public void
init()
{
    ::init();

    add_action(enter_gate, "enter");
    add_action(touch_gate, "touch");
    add_action(touch_gate, "feel");
    add_action(touch_gate, "push");
} /* init */


/*
 * Function name:        touch_gate
 * Description  :        Allow players to mess with the gate
 * Arguments    :        string arg: what the player typed after the verb
 * Returns      :        1: success, 0: failure
 */
public int
touch_gate(string arg)
{
    if (!strlen(arg) || !parse_command(arg, ({}),
        "[on] [the] [huge] [giant] [big] [large] [massive]"
      + " [swirling] [orange] [chaos] 'gate' / 'structure' / 'vortex'"))
    {
        notify_fail(capitalize(query_verb()) + " what?\n");
        return 0;
    }

    write("As you reach out to " + query_verb() + " the Chaos Gate, your"
      + " hands pass into the swirling orange energy, and you feel your"
      + " flesh being scrambled! Instinctively, you jerk your hand back"
      + " and gaze at your unharmed fingers.\n");
    tell_room(environment(this_player()), QCTNAME(this_player())
      + " reaches out to " + query_verb() + " the Chaos Gate. After a"
      + " brief instant of contact with the orange energy, "
      + this_player()->query_pronoun() + " jerks "
      + this_player()->query_possessive() + " hand back in alarm!\n",
        this_player());
    return 1;
} /* touch_gate */


/*
 * Function name:        enter_gate
 * Description  :        allow players to enter the chaos gate, thus
 *                       teleporting them to a random location chosen
 *                       from a large prescribed list of rooms.
 * Arguments    :        string arg: what was typed after the verb
 * Returns      :        1: success, 0: failure
 */
public int
enter_gate(string arg)
{
    object  vortex;

    if (!strlen(arg) || !parse_command(arg, ({}),
        "[in] [to] [into] [the] [huge] [giant] [big] [large] [massive]"
      + " [swirling] [orange] [chaos] 'gate' / 'structure' / 'vortex'"))
    {
        notify_fail(capitalize(query_verb()) + " what?\n");
        return 0;
    }

    vortex = clone_object("/d/Emerald/std/room");
    vortex->set_short("orange energy swirls around you in a torent");
    vortex->set_long("You are spinning around within a swirling torrent"
      + " of orange energy - the funnel of the Chaos Gate! With each"
      + " rotation of your body your mind becomes more disoriented,"
      + " and your sense of balance more confused and dizzy.\n");
    vortex->set_no_exit_msg( ({ "north", "northeast", "east",
                                "southeast", "south", "southwest",
                                "west", "northwest", "up", "down",
                                "in", "out", "exit", "leave" }),
        "You cannot escape the vortex!\n");
    vortex->add_item( ({ "energy", "orange energy" }),
        "The orange energy blinds your senses, swirling around you in"
      + " a wild torrent.\n");
    vortex->add_item( ({ "torrent", "funnel", "swirling torrent" }),
        "The energy has formed a funnel which is spinning you in"
      + " some unknown direction. Round and round and round it goes,"
      + " and where it stops, nobody knows!\n");
    vortex->add_item( ({ "gate", "chaos gate" }),
        "This is chaotic indeed! What is happening here?!\n");
    vortex->add_prop(ROOM_I_INSIDE, 1);

    this_player()->catch_tell("Stepping into the Chaos Gate, you feel"
      + " yourself ripped off the ground and into the funnel of orange"
      + " energy!\n");
    this_player()->move_living("M", vortex, 1, 1);

    tell_room(environment(this_object()), QCTNAME(this_player())
      + " steps into the Chaos Gate. There is a loud ripping sound and "
      + this_player()->query_pronoun() + " is gone.\n");

    set_alarm(ALARM_INTERVAL, 0.0, &chaos_warp(this_player(), 1,
                                               vortex));
    return 1;
} /* enter_gate */


/*
 * Function name:        chaos_warp
 * Desription   :        Give the player a brief stint in the chaos
 *                       vortex and then spit them out whevever fate
 *                       decides.
 * Arguments    :        object who: the player in question
 *                       int  count: the iteration of the warp
 *                       object vortex: the temp room that the player
 *                                      is in.
 */
public void
chaos_warp(object who, int count, object vortex)
{
    object  midair;

    switch (count)
    {
        case 1:
            who->catch_tell("Orange energy swirls around your body,"
              + " spinning you rapidly around.\n");
            break;
        case 2:
            who->catch_tell("You spin faster and faster. Your mind"
              + " begins to throb with pain and confusion.\n");
            break;
        case 3:
            who->catch_tell("Aaaaaarrrrgh! The pain! You are being"
              + " torn apart!\n");
            break;
        case 4:
            who->catch_tell("\n .... rrrrrrrrrrrrrip .... "
              + "BOOOOOOM!!!\n\n");
            break;
        default:
            break;
    }

    if (count < 4)
    {
        count++;
        set_alarm(ALARM_INTERVAL, 0.0, &chaos_warp(who, count, vortex));
        return;
    }

    midair = clone_object("/d/Emerald/std/room");
    midair->set_short("you are falling through mid-air");
    midair->set_long("You are falling through mid-air! Vague shapes,"
      + " too difficult to make out in all the confusion, swirl around"
      + " your senses above and below.\n");
    midair->add_item( ({ "air", "mid air", "midair", "mid-air" }),
        "The air whips past you as you fall.\n");
    midair->add_item( ({ "shapes", "shape", "vague shape",
                         "vague shapes" }),
        "Shapes. Vague. Confusing. Eeks!\n");
    midair->set_no_exit_msg( ({ "north", "northeast", "east",
                                "southeast", "south", "southwest",
                                "west", "northwest", "up", "down",
                                "in", "out", "exit", "leave" }),
        "You are flailing in the air, unable to control direction!\n");

    who->move_living("M", midair, 1, 1);
    vortex->remove_object();

    set_alarm(ALARM_INTERVAL, 0.0, &crashland(who, 1, midair));
} /* chaos_warp */


/*
 * Function name:        crashland
 * Description  :        The player finally lands in whatever location
 *                       they have been transported to.
 * Arguments    :        object who: the player
 *                       int count: the iteration of the fall
 *                       object midair: the temp room to destruct
 */
public void
crashland(object who, int count, object midair)
{
    object   land_room = one_of_list(CHAOS_LOCATIONS);

    switch (count)
    {
        case 1:
            who->catch_tell("You are suddenly falling through"
              + " mid air!\n");
            break;
        case 4:
            who->catch_tell("OOOOOF!! ... You land with a thud!\n");
            break;
        default:
            who->catch_tell("\n");
            break;
    }

    if (count != 4)
    {
        count++;
        set_alarm(ALARM_INTERVAL, 0.0, &crashland(who, count, midair));
        return;
    }

    tell_room(land_room, "BOOOOOM!!!\n"
      + "A hole is suddenly ripped in the air revealing a swirling"
      + " vortex of orange energy! The hole quickly begins to twist"
      + " shut, but just before it disappears, " + QTNAME(who)
      + " falls from its center to land with a heavy thud on the"
      + " ground just a few yards away.\n");
    who->move_living("M", land_room, 1, 1);
    midair->remove_object();

    write_file(AOD_LOG_DIR + "chaos_log",
        TIME2FORMAT(time(), "mm/dd/yyyy") + " (" + ctime(time())[11..18]
      + ") " + " -- " + file_name(environment(who))
      + " (" + who->query_real_name() + ")\n");

    return;
} /* crashland */