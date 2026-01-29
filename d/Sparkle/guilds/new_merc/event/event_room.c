/*
 *  /d/Sparkle/guilds/new_merc/event/event_room.c
 *
 *  This room controls the event to launch the Free Mercenary Guild. Only
 *  Gorboth should use it.
 *
 *  Created August 2009, by Cooper Sherry (Gorboth)
 */
#pragma strict_types
#include "../merc_defs.h"

inherit ROOM_DIR + "merc_room";

#include <files.h>
#include <language.h>
#include <macros.h>
#include <ss_types.h>

/* Prototypes */
public void        create_merc_room();
public string      event_commands();
public void        init();
public int         is_gorboth(object me);
public void        march_troops(string troop_type, string room);
public int         send_troops(string arg);
public int         gsummon(string arg);
public int         gsummon_non_merc(string arg);
public int         list_adapt(string arg);
public void        adapt_display(object who, string name);
public void        print_columns(string *skill_names, object who, mapping enhance_map);
public void        print_columns2(string *skill_names, object who);
public int         tell_game(string arg);


/*
 * Function name:        create_merc_room
 * Description  :        set up the room
 */
public void
create_merc_room()
{
    set_short("Mercenary Event Room");
    set_long("In this room, Gorboth runs events for the Mercenary Guild."
      + " if you are not him, then you oughtn't fiddle around. If you are,"
      + " then the commands are as follows:\n\n" + event_commands());

    setuid();
    seteuid(getuid());

} /* create_merc_room */


/*
 * Function name:        event_commands
 * Description  :        print a list of event commands
 * Returns      :        The string to print
 */
public string
event_commands()
{
    return "\t<alist [playername> - List the adapted skills for a merc\n"
         + "\t<gsend [troopname] [room a-g or market]>\n"
         + "\t<gbring [playername]> - Summon a non-Merc to Sparkle\n"
         + "\t<gmessage [playername]> - Morgan summons a player\n"
         + "\t<gametell [message] - Message to all players.\n\n";
} /* event_commands */


/*
 * Function name:        init
 * Description  :        add some actions to the room
 */
public void
init()
{
    ::init();

    add_action(gsummon, "gmessage");
    add_action(send_troops, "gsend");
    add_action(gsummon_non_merc, "gbring");
    add_action(list_adapt, "alist");
    add_action(tell_game, "gametell");
} /* init */


/*
 * Function name:        is_gorboth
 * Description  :        see if the user is me. If not ... no!
 * Arguments    :        object me - the user
 * Returns      :        int 1 - is gorboth
 *                           0 - not gorboth (go away!)
 */
public int
is_gorboth(object me)
{
    return (me->query_real_name() == "gorboth");
} /* is_gorboth */


/*
 * Function name:        march_troops
 * Description  :        Show the troops actually travelling from the
 *                       goblin fortress to Sparkle.
 * Arguments    :        string troop_type - what sort of troops are
 *                                           we marching?
 *                       string march_room - what is the room we land in?
 */
public void
march_troops(string troop_type, string march_room)
{
    object *travel_rooms = ({
                        "/d/Genesis/start/human/wild2/orcfort/temple",
                        "/d/Genesis/start/human/wild2/orcfort/r2",
                        "/d/Genesis/start/human/wild2/orc_fort",
                        "/d/Genesis/start/human/wild2/orc_sett",
                        "/d/Genesis/start/human/wild2/orc_vall1",
                        "/d/Genesis/start/human/wild2/slope",
                        "/d/Genesis/start/human/wild2/forest1",
                        "/d/Genesis/start/human/wild2/orc_road3",
                        "/d/Genesis/start/human/wild2/orc_road2f",
                        "/d/Genesis/start/human/wild2/orc_road2e",
                        "/d/Genesis/start/human/wild2/orc_road2d",
                        "/d/Genesis/start/human/wild2/orc_road2c",
                        "/d/Genesis/start/human/wild2/orc_road2b",
                        "/d/Genesis/start/human/wild2/orc_road2a",
                        "/d/Genesis/start/human/wild2/orc_road2",
                        "/d/Genesis/start/human/wild2/orc_road1",
                        "/d/Genesis/start/human/wild2/crossroad",
                        "/d/Genesis/start/human/wild2/hump",
                        "/d/Genesis/start/human/town/vill_gate",
                           });
    string *travel_dirs = ({  "south",
                              "south",
                              "south",
                              "south",
                              "east",
                              "east",
                              "south",
                              "east",
                              "east",
                              "east",
                              "east",
                              "east",
                              "east",
                              "east",
                              "east",
                              "east",
                              "east",
                              "east",
                              "east",
                              "east",
                            });
    int     i = 0;
    object  room;
    object *npcs;
    string  destination_room = "/d/Sparkle/area/city/rooms/streets/"
                             + ( (march_room == "market_square")
                             ? "" : "center_") + march_room;

    /* First, we take the goblins from the fortress to the gates of
     * the city.
     */
    foreach(object travel_room: travel_rooms)
    {
        room = safely_load_master_file(travel_room);

        if (!i)
        {
            tell_room(room, "With a tearing of magic energy, a group of"
              + " creatures lead by a goblin " + troop_type
              + " materialize out of thin air and swarm south out"
              + " of the temple.\n");
        }
        else
        {
            tell_room(room, "A group of creatures lead by a"
              + " goblin "  + troop_type + " swarms"
              + " suddenly into the room and rushes past, heading "
              + travel_dirs[i] + " until they are out of sight.\n");
        }

        i++;
    }

    TELL_G("destination_room = " + destination_room);

    /* Now, we redefine the rooms and directions depending on which
     * city room we want them to land in.
     */
    switch (march_room)
    {
        case "a":
            travel_rooms = ({
                "/d/Sparkle/area/city/rooms/streets/center_c",
                "/d/Sparkle/area/city/rooms/streets/center_b" });
            travel_dirs = ({ "north", "east" });
            break;
        case "b":
            travel_rooms = ({
                "/d/Sparkle/area/city/rooms/streets/center_c" });
            travel_dirs = ({ "north" });
            break;
        case "d":
            travel_rooms = ({
                "/d/Sparkle/area/city/rooms/streets/center_c" });
            travel_dirs = ({ "south" });
            break;
        case "e":
            travel_rooms = ({
                "/d/Sparkle/area/city/rooms/streets/center_c",
                "/d/Sparkle/area/city/rooms/streets/center_d" });
            travel_dirs = ({ "south", "south" });
            break;
        case "f":
            travel_rooms = ({
                "/d/Sparkle/area/city/rooms/streets/center_c",
                "/d/Sparkle/area/city/rooms/streets/center_d",
                "/d/Sparkle/area/city/rooms/streets/center_e" });
            travel_dirs = ({ "south", "south", "east" });
            break;
        case "g":
            travel_rooms = ({
                "/d/Sparkle/area/city/rooms/streets/center_c",
                "/d/Sparkle/area/city/rooms/streets/center_d",
                "/d/Sparkle/area/city/rooms/streets/center_e",
                "/d/Sparkle/area/city/rooms/streets/center_f" });
            travel_dirs = ({ "south", "south", "east", "east" });
            break;
        case "market":
            travel_rooms = ({
                "/d/Sparkle/area/city/rooms/streets/center_c",
                "/d/Sparkle/area/city/rooms/streets/center_d",
                "/d/Sparkle/area/city/rooms/streets/center_e",
                "/d/Sparkle/area/city/rooms/streets/center_f",
                "/d/Sparkle/area/city/rooms/streets/center_g" });
            travel_dirs = ({ "south", "south", "east", "east", "east" });
            break;
        default:
            travel_rooms = ({});
            travel_dirs = ({});
            break;
    }

    dump_array(travel_rooms);
    dump_array(travel_dirs);

    i = 0;

    /* Now, we march them through the city to the room they want to
     * be in.
     */
    foreach(object travel_room: travel_rooms)
    {
        room = safely_load_master_file(travel_room);

        if (!i)
        {
            tell_room(room, "A group of creatures lead by a goblin "
              + troop_type + " burst through the city gates and"
              + " swarm down the street to the " + travel_dirs[i] + "!\n");
        }
        else
        {
            tell_room(room, "A group of creatures lead by a"
              + " goblin "  + troop_type + " swarms"
              + " suddenly into the room and rushes past, heading "
              + travel_dirs[i] + " down the street!\n");
        }

        i++;
    }

    switch (troop_type)
    {
        case "runt":
            npcs = ({
                clone_object(EVENT_DIR + "goblin_runt"),
                clone_object(EVENT_DIR + "goblin_runt"),
                clone_object(EVENT_DIR + "goblin_runt") });
            break;
        case "shaman":
            npcs = ({
                clone_object(EVENT_DIR + "goblin_shaman") });
            break;
        case "warrior":
            npcs = ({
                clone_object(EVENT_DIR + "goblin_warrior"),
                clone_object(EVENT_DIR + "goblin_warrior") });
            break;
        case "bloater":
            npcs = ({
                clone_object(EVENT_DIR + "goblin_bloater") });
            break;
        case "giant":
            npcs = ({
                clone_object(EVENT_DIR + "goblin_giant") });
            break;
        default:
            npcs = ({});
            break;
    }

    foreach(object npc: npcs)
    {
        npc->arm_me();
        npc->move(destination_room);
        tell_room(destination_room, QCNAME(npc)
          + " charges into the room!\n");
    }

} /* march_troops */


/*
 * Function name:        hook_gorboth_fail
 * Description  :        The fail message if you aren't gorboth
 * Returns      :        string - the fail message
 */
public string
hook_gorboth_fail()
{
    return "You are not Gorboth, and have no authorization.\n";
} /* hook_gorboth_fail */


/*
 * Function name:        send_troops
 * Description  :        send some goblins to a particular room in
 *                       Sparkle
 * Arguments    :        string arg - what was typed after the command
 * Returns      :        int 1 - success,
 *                           0 - failure
 */
public int
send_troops(string arg)
{
    string    room,
              trooptype,
             *valid_troops,
             *valid_rooms;

    valid_troops = ({ "runt", "shaman", "warrior", "bloater", "giant" });
    valid_rooms = ({ "a", "b", "c", "d", "e", "f", "g", "market" });

    if (!is_gorboth(this_player()))
    {
        notify_fail(hook_gorboth_fail());
        return 0;
    }

    if (!strlen(arg) ||
        !parse_command(arg, ({}), "%w %w", trooptype, room))
    {
        notify_fail("Usage: <gsend [trooptype] [room a-g or market]>\n");
        return 0;
    }

    if (member_array(trooptype, valid_troops) == -1)
    {
        notify_fail("Invalid troop type.\n");
        return 0;
    }

    if (member_array(room, valid_rooms) == -1)
    {
        notify_fail("Invalid destination room.\n");
        return 0;
    }

    march_troops(trooptype, room);
    write("Troops sent!\n");
    return 1;
} /* send_troops */


/*
 * Function name:        gsummon
 * Description  :        Have the Morgan npc send a letter to one
 *                       of the players we want to involve
 * Arguments    :        string arg - what was typed after the verb
 * Returns      :        int 1 - success, 0 - failure
 */
public int
gsummon(string arg)
{
    object  player;
    object  letter;

    if (!is_gorboth(this_player()))
    {
        notify_fail(hook_gorboth_fail());
        return 0;
    }

    if (!strlen(arg))
    {
        notify_fail("You must <gmessage [playername]>.\n");
        return 0;
    }

    player = find_living(arg);

    if (!player)
    {
        notify_fail("That is not a valid player.\n");
        return 0;
    }

    player->catch_msg("\nA sleek black hunting dog bounds into the room"
      + " and gives you a letter from Eldon!\n\nThe dog dashes away.\n\n");
    tell_room(environment(player), "\nA sleek black hunting dog bounds"
      + " into the room and gives " + QTNAME(player) + " a letter!\n"
      + "The dog dashes away.\n\n",
        player);
    letter = clone_object(EVENT_DIR + "letter");
    letter->move(player);

    return 1;
} /* gsummon */


/*
 * Function name:        gsummon_non_merc
 * Description  :        Have the Morgan npc send a letter to one
 *                       of the players we want to involve
 * Arguments    :        string arg - what was typed after the verb
 * Returns      :        int 1 - success, 0 - failure
 */
public int
gsummon_non_merc(string arg)
{
    object  player;
    object  letter;

    if (!is_gorboth(this_player()))
    {
        notify_fail(hook_gorboth_fail());
        return 0;
    }

    if (!strlen(arg))
    {
        notify_fail("You must <gmessage [playername]>.\n");
        return 0;
    }

    player = find_living(arg);

    if (!player)
    {
        notify_fail("That is not a valid player.\n");
        return 0;
    }

    player->catch_msg(one_of_list( ({
        "\n\nYou feel a sudden inexplicable urge to travel AT ONCE to"
      + " Sparkle!\n\n",
        "\n\nSparkle is in need! You aren't sure how you know ... but"
      + " you somehow sense it! You feel you should travel there"
      + " immediately!\n\n",
        "\n\nSparkle ... Sparkle ... you feel a strange sense in your"
      + " head. Something is happening in Sparkle ... you've never been"
      + " more sure of anything in your life!\n\n" }) ));

    return 1;
} /* gsummon_non_merc */


/*
 * Function name:        list_adapt
 * Description  :        Display the adaptation list for a given
 *                       Mercenary
 * Arguments    :        What was typed after the verb
 * Returns      :        1 - success, 0 - failure
 */
public int
list_adapt(string arg)
{
    if (!strlen(arg))
    {
        notify_fail("List the skills for which Mercenary?\n");
        return 0;
    }

    adapt_display(this_player(), arg);
    return 1;
} /* list_adapt */


/*
 * Function name:        adapt_display
 * Description  :        Print a nifty list for the player describing
 *                       which skills they have learned to adapt, and
 *                       to what levels they are currently allocating
 *                       adaptation points.
 * Arguments    :        object who - the person to see the list
 *                       string name - the name of the player we want to
 *                                     see info on.
 */
public void
adapt_display(object who, string name)
{
    int     *v_skills = MERC_MASTER->query_skillnum_index(),
             ap_available,
             ap_spent,
             ap_remaining;
    mapping  enhance_map;
    string  *skill_names = ({});
    object   player = SECURITY->finger_player(name);

    /* Lets make sure that a formatted datafile exists for this
     * player.
     */
    MERC_MASTER->check_enhance_map(player);

    /* Lets populate an array with all of the skill numbers that this
     * player has already adapted.
     */
    enhance_map = MERC_MASTER->get_info(player, "skill_enhance");

    /* Now, lets populate an array with the names of the skills that
     * the player has actually trained for adaptation so far.
     */
    foreach (int skillnum: v_skills)
    {
        if (member_array(skillnum, m_indices(enhance_map)) > -1)
        {
            skill_names += ({ SS_SKILL_DESC[skillnum][0] });
        }
    }

    ap_available = player->query_skill(SS_MERC_ADAPT_SKILL);
    ap_spent = MERC_MASTER->skill_extra_total(player);
    ap_remaining = ap_available - ap_spent;

    /* Print the list header. */
    who->catch_tell(
        sprintf("%|80s",
        ".--------------------------------------------------------.\n")
      + sprintf("%|80s",
        "|             -**- Adapted Skill Levels -**-               |\n")
      + sprintf("%|80s",
        "|      (Current allocations displayed in parenthesis)      |\n")
      + sprintf("%|80s",
        sprintf("|  Adaptability Points: "
          + "%-3d Allocated: %-3d Remaining: %-3d  ",
             ap_available, ap_spent, ap_remaining)
      + "|\n")
      + sprintf("%|80s",
        "| ======================================================== |\n")
      + sprintf("%|80s",
        "|                                                          |\n"));

    /* Now, lets print the names of the skills in columns that the
     * player has adapted so far.
     */
    print_columns(skill_names, who, enhance_map);
    skill_names = ({}); /* re-initialize the array */

    /* Now, lets recreate the array, this time listing those skills
     * that the player has yet to adapt with a specialized trainer.
     */
    foreach (int skillnum: v_skills)
    {
        if (member_array(skillnum, m_indices(enhance_map)) == -1)
        {
            skill_names += ({ SS_SKILL_DESC[skillnum][0] });
        }
    }

    /* Print a divider. */
    who->catch_tell(
        sprintf("%|80s",
        "|                                                          |\n")
      + sprintf("%|80s",
        "| ======================================================== |\n")
      + sprintf("%|80s",
        "|    Skills that have yet to be trained for adaptation     |\n")
      + sprintf("%|80s",
        "| ======================================================== |\n")
      + sprintf("%|80s",
        "|                                                          |\n"));

    /* Now, we print the names of the unadapted skills in columns. */
    print_columns(skill_names, who, enhance_map);

    /* Print the list footer. */
    who->catch_tell(
        sprintf("%|80s",
        "|                                                          |\n")
      + sprintf("%|80s",
        "| ======================================================== |\n")
      + sprintf("%|80s",
        "| You may <adapt skillname> to attempt to adapt any skill. |\n")
      + sprintf("%|80s",
        "`--------------------------------------------------------'\n"));

    player->remove_object();
} /* adapt_display */


/*
 * Function name:        print_columns
 * Description  :        Print a double-column alphabetized list of
 *                       a given array
 * Arguments    :        string *skill_names - the array of strings
 *                                             to print
 *                       object who - who to print it to
 *                       mapping enhance_map - mapping of the adaptation
 *                                             list from the player's
 *                                             merc data file
 */
public void
print_columns(string *skill_names, object who, mapping enhance_map)
{
    string  column1;
    string  column2;
    int     i,
            n,
            odd_true,
            half,
            c1_val,
            c2_val;

    /* Lets alphabetize the array of skill names. */
    skill_names = sort_array(skill_names, MERC_MASTER->sort_name());
    n = sizeof(skill_names);
    half = n / 2;
    odd_true = (n % 2 == 1);

    if (n)
    {
        for (i = 0; i < half + odd_true; i++)
        {
            column1 = capitalize(skill_names[i]);
            column2 = "";
            c1_val = enhance_map[MERC_MASTER->skill_num(skill_names[i])];

            /* If the player has currently allotted adaptation points
             * to this skill, we display how many in () alongside.
             */
            if (c1_val)
            {
                /* For formatting purposes, we need to know if the
                 * amount of adapted skill exceeds 9.
                 */
                column1 = ( (c1_val > 9) ? "(" : " (")
                        + c1_val + ") " + column1;
            }
            else
            {
                column1 = "     " + column1;
            }

            if (half > i)
            {
                /* This is a bit tricky. We have to know if the size
                 * of the list is odd. Since we are printing two columns,
                 * we want to begin the second column just past the
                 * halfway point (for alphabetical purposes). If it
                 * is odd in length, though, we want to go one more
                 * place past that.
                 */
                column2 = capitalize(
                              skill_names[i + half + odd_true]);
                c2_val = enhance_map[MERC_MASTER->skill_num(
                              skill_names[i + half + odd_true])];

                if (c2_val)
                {
                    column2 = ( (c2_val > 9) ? "(" : " (")
                            + c2_val + ") " + column2;
                }
                else
                {
                    column2 = "     " + column2;
                }
            }

            /* All set. So lets print out this line! */
            who->catch_tell(sprintf("%|80s",
                "|" + sprintf(" %-26s    %-26s %2s",
                column1, column2, "|\n")));
        }
    }
    else /* Nothing to list. */
    {
        who->catch_tell(sprintf("%|80s",
        "|                          (none)                          |\n"));
    }
} /* print_columns */


/*
 * Function name:        print_columns2
 * Description  :        Print a double-column alphabetized list of
 *                       a given array
 * Arguments    :        string *skill_names - the array of strings
 *                                             to print
 *                       object who - who to print it to
 */
public void
print_columns2(string *skill_names, object who)
{
    string  column1;
    string  column2;
    int     i,
            n,
            odd_true,
            half,
            c1_val,
            c2_val;

    /* Lets alphabetize the array of skill names. */
    skill_names = sort_array(skill_names, MERC_MASTER->sort_name());
    n = sizeof(skill_names);
    half = n / 2;
    odd_true = (n % 2 == 1);

    if (n)
    {
        for (i = 0; i < half + odd_true; i++)
        {
            column1 = capitalize(skill_names[i]);
            column2 = "";

            if (half > i)
            {
                /* This is a bit tricky. We have to know if the size
                 * of the list is odd. Since we are printing two columns,
                 * we want to begin the second column just past the
                 * halfway point (for alphabetical purposes). If it
                 * is odd in length, though, we want to go one more
                 * place past that.
                 */
                column2 = capitalize(
                              skill_names[i + half + odd_true]);
            }

            /* All set. So lets print out this line! */
            who->catch_tell(sprintf("%|80s",
                sprintf(" %-36s    %-36s",
                column1, column2, "\n")));
        }
    }
    else /* Nothing to list. */
    {
        who->catch_tell(sprintf("%|80s",
        "|                          (none)                          |\n"));
    }
} /* print_columns2 */


/*
 * Function name:        tell_game
 * Description  :        Send a tell to all players who are logged on
 * Arguments    :        string arg: the text to send them
 * Returns      :        1 - success always
 */
public int
tell_game(string arg)
{
    object  *players;
    int      i;

    if (!is_gorboth(this_player()))
    {
        notify_fail(hook_gorboth_fail());
        return 0;
    }

    players = filter(users(), not @ &->query_wiz_level());

    for (i = 0; i < sizeof(players); i++)
    {
        players[i]->catch_tell(arg + "\n");
    }

    return 1;
} /* tell_game */
