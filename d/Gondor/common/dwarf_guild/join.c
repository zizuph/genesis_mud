/*
 * /d/Gondor/common/dwarf_guild/join.c
 *
 * Copyright (C) Stas van der Schaaf - January 9 1994
 *               Mercade @ Genesis
 *
 * This is the holy cave. You can join/leave here.
 */

#pragma no_clone
#pragma no_inherit
#pragma save_binary
#pragma strict_types

inherit "/d/Gondor/common/room";
inherit "/lib/guild_support";

#include <macros.h>
#include <ss_types.h>
#include <std.h>
#include <stdproperties.h>
#include "/d/Gondor/defs.h"
#include "dwarf.h"
#include "titles.h"

#define TABLET_ID      "_dwarven_race_guild_tablet_"
#define TABLET         (DWARVEN_RACE_GUILD_OBJECTS + "tablet")
#define CABINET_ID     "_dwarven_race_guild_cabinet_"
#define CABINET        (DWARVEN_RACE_GUILD_OBJECTS + "cabinet")
#define LOG_SIZE       25000
#define NO_UPDATE      600 /* seconds = 10 minutes */
#define NEW_SKILL_AXE  30
#define NEW_SKILL_CLUB 30

#define WRITE_NAME(o) sprintf("%-11s", CAP((o)->query_real_name()))

/*
 * Global variables
 */
static private string *abandoned_players = ({ });
static private object  cabinet;
       private mapping members;
       private string *memberkillers;
static private int     updated;
static private string *titles = TITLES;
static private string *beards = BEARD_DESCRIPTIONS;

/*
 * Prototypes.
 */
nomask static void test_members();

/*
 * Function name: long_description
 * Description  : Modify the long description of the room and make it
 *                dependant on the race of the player and whether (s)he
 *                is or is not a member.
 * Returns      : string - the description.
 */
nomask public string
long_description()
{
    string str = "The holy cave of the " + DWARVEN_RACE_GUILD_NAME + ". " +
        "This cave breathes tranquility and you feel at ease here. There " +
        "is an altar before which you can pray. Here you may also pledge " +
        "faith to the Dwarven God, " + DWARVEN_RACE_GUILD_GOD;

    if (TP->query_race() != "dwarf")
    {
        str += ".";
    }
    else if (IS_MEMBER(TP))
    {
        str += ", or to leave the guild you may abandon your faith in the " +
            "Dwarven God, " + DWARVEN_RACE_GUILD_GOD + ".";
    }
    else
    {
        str += ", to join the guild. Make sure that you read the runic " +
            "writing on the tablet before you join this guild though.";
    }

    str += " A membership list is placed on the altar. Stairs lead down " +
        "into the central guild hall.";

    return str + "\n";
}

/*
 * Function name: altar_description
 * Description  : We modify the description of the altar based on the
 *                race of the viewer.
 * Returns      : string - the description.
 */
nomask public string
altar_description()
{
    return "It is an altar, dedicated to the Dwarven God, " +
        DWARVEN_RACE_GUILD_GOD + ". It is made of solid rock and it is " +
        "ornamented with mithril. Before the altar you may \"kneel\" or " +
        "\"pray\" to " + DWARVEN_RACE_GUILD_GOD + " in order to establish " +
        "your progression with your stats or to alter your learning " +
        "preferences.\nHere you may also \"list guilds\" to see which " +
        "guilds you are a member of, and who are the guildmaster(s) of " +
        "those guilds. On the altar, a membership list is placed. To " +
        "extract information from it, you may use the command \"members\".\n";
}

/*
 * Function name: check_leaving
 * Description  : When someone wants to leave the room we check whether
 *                they have closed the cabinet. Also, dwarves who abandon
 *                their faith and leave the guild must drop their belt
 *                or else they are punished.
 * Returns      : int 1/0 - true if the player isn't allowed to leave.
 */
nomask public int
check_leaving()
{
    if ((TP == (object)cabinet->query_last_manip()) &&
        (!(cabinet->query_prop(CONT_I_CLOSED))))
    {
        write("You shall have to close the cabinet first.\n");

        return 1;
    }

    if ((member_array(TP->query_real_name(), abandoned_players) != -1) &&
        (present(DWARVEN_RACE_GUILD_BELT_ID, ({ TP }) + deep_inventory(TP))))
    {
        write("You have abandoned your faith in " + DWARVEN_RACE_GUILD_GOD +
            ". You were told to drop your belt and you failed to do so. " +
            "You will be punished by divine powers.\n");
        write("A flash of light fills the room, beaming at you. Once " +
            "you are struck by this lightning, you feel hurt, very hurt.\n");

        /*
         * Punish the player if he leaves the room without removing and
         * dropping the belt.
         */
        TP->set_fatigue(1);
        TP->heal_hp(-1 - (TP->query_max_hp() / 2));

        say("A flash of light fills the room, beaming at " + QTNAME(TP) +
            " for " + PRONOUN(TP) + " disobeyed the Dwarven God and is " +
            "punished for it.\n");

        if (TP->query_hp() <= 0)
        {
            TP->do_die(TO);
        }

        return 1;
    }

    return 0;
}

/*
 * Function name: create_room
 * Description  : Called when the room is first loaded into memory.
 */
nomask public void
create_room()
{
    set_short("the holy cave of the " + DWARVEN_RACE_GUILD_NAME);
    set_long(long_description);

#include "cavedesc.h"

    add_item( ({ "stairs", "stais"}),
        "The stairs lead down into the central guild hall.\n");

    add_item( ({ "altar" }), altar_description);
    add_item( ({ "ornament", "ornaments", "mithril" }),
        "The altar is beautifully ornamented with mithril.\n");
    add_item( ({ "list", "membership list" }),
        "You examine the membership list and come to the conclusion " +
        "that you should use the command <members> to get information " +
        "on the members of the " + DWARVEN_RACE_GUILD_NAME + ".\n");
    add_cmd_item( ({ "list", "membership list" }), ({ "read" }),
        "You read the membership list and notice that the command " +
        "<members> will yield information about the members of the " +
        DWARVEN_RACE_GUILD_NAME + ".\n");

    set_noshow_obvious(1);
    add_exit(DWARF_DIR + "guild", "down", check_leaving);

    add_prop(ROOM_I_INSIDE,          1);
    add_prop(ROOM_I_NO_CLEANUP,      1);
    add_prop(ROOM_I_NO_ATTACK,       1);
    add_prop(ROOM_I_NO_MAGIC_ATTACK, 1);

    FIX_EUID;

    clone_object(TABLET)->move(TO);
    cabinet = clone_object(CABINET);
    cabinet->move(TO);

    restore_object(DWARVEN_RACE_GUILD_SAVE);
    if (!mappingp(members))
    {
        members = ([ ]);
    }
    if (!pointerp(memberkillers))
    {
        memberkillers = ({ });
    }

    /* Test the validity of the members only at the first day of the month.
     */
    if (atoi(ctime(time())[8..9]) == 1)
    {
        set_alarm(12.0, 0.0, test_members);
    }
}

/*
 * Function name: log_guild
 * Description  : This function logs some actions of members of the guild.
 *                It uses a larger cycle than basically coded.
 * Arguments    : string text - the message to log.
 */
nomask private void
log_guild(string text)
{
    FIX_EUID;

    if (file_size(DWARVEN_RACE_GUILD_LOG) > LOG_SIZE)
    {
        rename(DWARVEN_RACE_GUILD_LOG, (DWARVEN_RACE_GUILD_LOG + ".old"));
    }

    write_file(DWARVEN_RACE_GUILD_LOG, text);
}

/*
 * Function name: do_pledge
 * Description  : When a dwarf wants to pledge his/her faith to the
 *                Dwarven God, this function makes him/her a member.
 * Arguments    : string str - the command line argument.
 * Returns      : int    1/0 - success/failure.
 */
nomask static int
do_pledge(string str)
{
    object shadow;
    int    result;

    str = LOW(str);

    if ((!strlen(str)) ||
        (!parse_command(str, ({ }), "[faith] [to] [the] [dwarven] " +
           "'god' / 'mahal' / 'aule'")))
    {
        notify_fail("To join the " + DWARVEN_RACE_GUILD_NAME + " you will " +
            "have to pledge faith to the Dwarven God.\n");
        return 0;
    }

    if (IS_MEMBER(TP))
    {
        notify_fail("You are already a member of the " +
            DWARVEN_RACE_GUILD_NAME + ". If you have lost your belt, you " +
            "may take a new one from the cabinet and have the smith brand " +
            "your name in it.\n");
        return 0;
    }

    if (TP->query_race() != "dwarf")
    {
        notify_fail("You may pledge faith to the Dwarven God, " +
            DWARVEN_RACE_GUILD_GOD + ", and He appreciates it that you do " +
            "so. However, only dwarves may become a member of the " +
            DWARVEN_RACE_GUILD_NAME + ".\n");
        return 0;
    }

    if (TP->query_guild_member(DWARVEN_RACE_GUILD_TYPE))
    {
        notify_fail("You may pledge faith to the Dwarven God, " +
            DWARVEN_RACE_GUILD_GOD + ", here and He appreciates it that you " +
            "do so. However, you are already a member of another " +
            DWARVEN_RACE_GUILD_TYPE + " guild and you may therefore not " +
            "join the " + DWARVEN_RACE_GUILD_NAME + ".\n");
        return 0;
    }

    shadow = clone_object(DWARVEN_RACE_GUILD_SHADOW);

    if ((result = shadow->shadow_me(TP, DWARVEN_RACE_GUILD_TYPE,
        DWARVEN_RACE_GUILD_STYLE, DWARVEN_RACE_GUILD_NAME)) != 1)
    {
        log_guild(ctime(time()) + " " + WRITE_NAME(TP) +
            " failed to add shadow with result " + result + ".\n");
        shadow->remove_shadow();

        write("Due to a problem beyond your control you cannot join the " +
            DWARVEN_RACE_GUILD_NAME + ". Perhaps " + DWARVEN_RACE_GUILD_GOD +
            " does not trust you. However, this should not have happened. " +
            "Please contact the guildmaster about this for wizards are " +
            "closer to the Gods than you are.\n");

        return 1;
    }

    TP->clear_guild_stat(SS_RACE);
    TP->set_guild_pref(SS_RACE, DWARVEN_RACE_GUILD_TAX);
    TP->add_subloc(DWARVEN_RACE_GUILD_NAME, shadow);
 
    write("You pledge faith to " + DWARVEN_RACE_GUILD_GOD + ", the Dwarven " +
        "God. He hears your prayer and grants you the right to join the " +
        DWARVEN_RACE_GUILD_NAME + ".\n");
    write("Welcome to the " + DWARVEN_RACE_GUILD_NAME + " you may now open " +
        "the cabinet and get a belt you like from it. Then you should go " +
        "to the blacksmith and get him to brand your name in it. Only then " +
        "you will be a member of this guild. The command \"help rockfriend\" " +
        "will learn you more about the commands once you wear the belt with " +
        "your name on it.\n");
    say(QCTNAME(TP) + " pledges faith to the Dwarven god and is granted " +
        "the right to join the " + DWARVEN_RACE_GUILD_NAME + ".\n");

    log_guild(ctime(time()) + " " + WRITE_NAME(TP) + " joined the " +
        DWARVEN_RACE_GUILD_NAME + ".\n");

    /* At the new member to the list. */
    members[TP->query_real_name()] = 0;

    save_object(DWARVEN_RACE_GUILD_SAVE);

    return 1;
}

/*
 * Function name: remove_membership_rights
 * Description  : When a member leaves the guild or is kicked out due
 *                to a change of race, this function punishes him/her,
 *                removes the soul, shadow, etcetera.
 * Arguments    : object player - the object leaving.
 */
nomask private void
remove_membership_rights(object player)
{
    int skill = (int)player->query_skill(SS_WEP_AXE);

    player->set_guild_pref(SS_RACE, 0);
    player->clear_guild_stat(SS_RACE);
    player->remove_cmdlist(DWARVEN_RACE_GUILD_SOUL);
    player->update_hooks();

    /* If the player starts in the guild by default, set this to
     * the default starting location for all players.
     */
    if (player->query_default_start_location() == (DWARF_DIR + "start"))
    {
        if (player->set_default_start_location(player->query_def_start()))
        {
            tell_object(player, "Your default starting location has " +
                "been changed from the caves of the " +
                DWARVEN_RACE_GUILD_NAME + " to the default starting " +
                "location of your race.\n");
        }
    }

/*
 * Since skill-decay has been implemented, we do not cut the skill of leaving
 * Rockfriend any longer. The skills will decay if they are not trainable
 * anywhere else for the player.
 */
#define ROCKFRIEND_NO_SKILL_DECAY
#ifndef ROCKFRIEND_NO_SKILL_DECAY

    if (skill > NEW_SKILL_AXE)
    {
        player->set_skill(SS_WEP_AXE, NEW_SKILL_AXE);

        tell_object(player, "The Dwarven God, " + DWARVEN_RACE_GUILD_GOD +
            ", despises you for abandoning faith in Him. Due to his divine " +
            "intervention you feel that your hands become less nimble with " +
            "axes.\n");

        log_guild(ctime(time()) + " " + WRITE_NAME(player) + " Axe skill " +
            "from " + skill + " to " + NEW_SKILL_AXE + ".\n");
    }
    else
    {
        tell_object(player, "Even though the Dwarven God, " +
            DWARVEN_RACE_GUILD_GOD + ", despises you for abandining faith " +
            "in Him, He does not punish you any further for you already " +
            "have a worthless skill with axes.\n");

        log_guild(ctime(time()) + " " + WRITE_NAME(player) +
            " Axe skill unchanged: " + skill + ".\n");
    }

    if (skill > NEW_SKILL_CLUB)
    {
        player->set_skill(SS_WEP_CLUB, NEW_SKILL_CLUB);

        tell_object(player, "The Dwarven God, " + DWARVEN_RACE_GUILD_GOD +
            ", despises you for abandoning faith in Him. Due to his divine " +
            "intervention you feel that your hands become less nimble with " +
            "clubs.\n");

        log_guild(ctime(time()) + " " + WRITE_NAME(player) + " Club skill " +
            "from " + skill + " to " + NEW_SKILL_CLUB + ".\n");
    }
    else
    {
        tell_object(player, "Even though the Dwarven God, " +
            DWARVEN_RACE_GUILD_GOD + ", despises you for abandining faith " +
            "in Him, He does not punish you any further for you already " +
            "have a worthless skill with clubs.\n");

        log_guild(ctime(time()) + " " + WRITE_NAME(player) +
            " Club skill unchanged: " + skill + ".\n");
    }

#endif ROCKFRIEND_NO_SKILL_DECAY

    /* Remove him/her from the list of members. */
    members = m_delete(members, player->query_real_name());
    memberkillers -= ({ player->query_real_name() });

    save_object(DWARVEN_RACE_GUILD_SAVE);
}

/*
 * Function name: do_abandon
 * Description  : This is a waste of memory since no-one would ever
 *                consider leaving a guild like this, or would they?
 *                Just for the completeness, this function takes care
 *                of a voluntary leave.
 * Arguments    : string str - the command line argument
 * Returns      : int    1/0 - success/failure.
 */
nomask static int
do_abandon(string str)
{
    int result;

    str = LOW(str);

    if ((!strlen(str)) ||
        (!parse_command(str, ({ }),
            "[the] [dwarven] 'god' / 'mahal' / 'aule'")))
    {
        notify_fail("To leave the " + DWARVEN_RACE_GUILD_NAME +
            " you will have to abandon the Dwarven God.\n");
        return 0;
    }

    if (!IS_MEMBER(TP))
    {
        notify_fail("Since you are not a member of the " +
            DWARVEN_RACE_GUILD_NAME + ", you cannot leave the guild. " +
            "However, we regret it that you abandon the Dwarven God, " +
            DWARVEN_RACE_GUILD_GOD + ".\n");
        return 0;
    }

    if ((result = TP->remove_rockfriend_guild()) != 1)
    {
        log_guild(ctime(time()) + " " + WRITE_NAME(TP) +
            " failed to remove shadow with result " + result + ".\n");

        write("The Dwarven God, " + DWARVEN_RACE_GUILD_GOD + " apparently " +
            "does not approve of you breaking your faith in Him. His divine " +
            "intervention does not allow you to leave. However, this should " +
            "not happen. Please contact the guildmaster about it. Wizards " +
            "are closer to the gods and maybe they can help you.\n");

        return 1;
    }

    say(QCTNAME(TP) + " breaks faith in the Dwarven God and leaves the " +
        DWARVEN_RACE_GUILD_NAME + ".\n");
    write("You break faith the Dwarven God, " + DWARVEN_RACE_GUILD_GOD +
        " and leave the " + DWARVEN_RACE_GUILD_NAME + ". Breaking faith " +
        "with a God is not something you to do every day and He might " +
        "become sad with you. Beware of his wrath. Begin by removing your " +
        "belt and drop it on the floor before you leave this cavern. Fail " +
        "to do so and you shall be severely punished by divine powers.\n");

    abandoned_players += ({ (string)TP->query_real_name() });
    remove_membership_rights(TP);

    log_guild(ctime(time()) + " " + WRITE_NAME(TP) + " left the " +
        DWARVEN_RACE_GUILD_NAME + ".\n");

    return 1;
}

/*
 * Function name: remove_player_changed_race
 * Description  : Whenever a member changes his/her race (s)he is
 *                mercilessly kicked out the guild by this function.
 * Arguments    : object player - the object to kick out.
 */
nomask public void
remove_player_changed_race(object player)
{
    int    result;
    object belt;

    if (!objectp(player))
    {
        return;
    }

    tell_object(player, "\nYou are no longer a dwarf. Therefore you do " +
        "not belong in the " + DWARVEN_RACE_GUILD_NAME + " any more. You " +
        "are expelled from the guild. Your belt is removed.\n");

    /* This is also true if people carry the belt in a box. */
    while(objectp(belt = present(DWARVEN_RACE_GUILD_BELT_ID,
        ({ player }) + deep_inventory(player))))
    {
        belt->remove_object();
    }

    remove_membership_rights(player);

    log_guild(ctime(time()) + " " + WRITE_NAME(player) + " (" +
        player->query_race() + ") was kicked out.\n");
}

/*
 * Function name: remove_player_killed_dwarf
 * Description  : Whenever a member kills one of the NPC's in this guild, he
 *                or she is mercilessly kicked out the guild by this function.
 * Arguments    : object player - the object to kick out.
 */
nomask public void
remove_player_killed_dwarf(object player)
{
    int    result;
    object belt;

    if (!objectp(player))
    {
        return;
    }

    tell_object(player, "\nYou have slain one of the inexhaustible members " +
        "that take care of this fine guild and its members. Therefore you " +
        "do not belong in the " + DWARVEN_RACE_GUILD_NAME + " any more. You " +
        "are expelled from the guild. Your belt is removed.\n");

    /* This is also true if people carry the belt in a box. */
    while(objectp(belt = present(DWARVEN_RACE_GUILD_BELT_ID,
        ({ player }) + deep_inventory(player))))
    {
        belt->remove_object();
    }

    remove_membership_rights(player);

    log_guild(ctime(time()) + " " + WRITE_NAME(player) +
        " was kicked out (killed RF NPC).\n");
}

/*
 * Function name: leave_inv
 * Description  : Called to remove the guild support if it is stuck.
 * Arguments    : object obj - the leaving object.
 *                object to  - the new destination of the object.
 */
nomask public void
leave_inv(object obj, object to)
{
    ::leave_inv(obj, to);

    gs_leave_inv(obj, to);
}

/*
 * Function name: remove_dropped_belt
 * Description  : When a belt is dropped in this room, a dwarf will pick
 *                it up and dispose of it in a while.
 * Arguments    : object belt - the belt to remove.
 */
static void
remove_dropped_belt(object belt)
{
    tell_room(TO, "A dwarf with a long braided beard enters the room and " +
        "picks up the belt that was sacrificed. Then he leaves again.\n");
    belt->remove_object();
}

/*
 * Function name: enter_inv
 * Description  : When someone sacrifices his/her belt, we do not want
 *                other people to pick it up.
 * Arguments    : object obj  - the entering object.
 *                object from - the source of the object.
 */
nomask public void
enter_inv(object obj, object from)
{
    ::enter_inv(obj, from);

    if (!objectp(from))
    {
        return;
    }

    if ((obj->id(DWARVEN_RACE_GUILD_BELT_ID)) &&
        (member_array(from->query_real_name(), abandoned_players) != -1))
    {
        obj->add_prop(OBJ_M_NO_GET,
            "The belt was sacrificed and cannot be taken.\n");
        set_alarm(4.0, 0.0, &remove_dropped_belt(obj));
    }
}

/*
 * Stuff for meditation.
 */

/*
 * Function name: gs_hook_start_meditate
 * Description  : Gives a nice description when someone starts to meditate.
 */
nomask public void
gs_hook_start_meditate()
{
    write("You kneel down before the altar and start praying to the Gods. " +
        "As you close your eyes, you feel that the deities are propitiated " +
        "and they allow you to ask them about your soul and mind. After " +
        "they have given you an estimate of your different preferences for " +
        "concentration, you may also beg them to <set> them to other " +
        "values. If you are done with your prayers, you can <rise> and " +
        "open your eyes.\n\n");
    say(QCTNAME(TP) + " kneels down before the altar and starts praying to " +
        "the Gods.\n");
}

/*
 * Function name: gs_hook_rise
 * Description  : Gives a nice description when someone is done meditating.
 */
nomask public void
gs_hook_rise()
{
    write("After you have communed with the Gods, you rise again and open " +
        "your eyes. You feel relaxed and tranquillized, able to conquer " +
        "the world.\n");
    say(QCTNAME(TP) + " rises again after " + POSSESSIVE(TP) + " prayers " +
        "are answered by the Gods.\n");
}

/*
 * Function name: gs_hook_already_meditate
 * Description  : Gives a nice message when someone tries to meditate
 *                when (s)he is already mediating.
 */
nomask public int
gs_hook_already_meditate()
{
    write("You are already in conclave with the Gods, you cannot get any " +
        "closer to them. You may beg them to <set> your learning " +
        "preferences for concentration to other values. If you are done " +
        "with your prayers, you can <rise> and open your eyes.\n");
    return 1;
}

/*
 * Function name: gs_hook_catch_error
 * Description  : Gives a friendly error message when someone gives the
 *                wrong command while meditating.
 */
nomask public int
gs_hook_catch_error(string str)
{
    write("You are in conclave with the Gods and you need all your " +
        "concentration while communing with them. You cannot do anything " +
        "else before you <rise> if you are done praying. While praying " +
        "you may beg them to <set> your different preferences for " +
        "concentration to other values.\n");
    return 1;
}

/*
 * This section takes care of the member administration.
 */

/*
 * Function name: query_rockfriend_beard_description
 * Description  : This function will return the beard description of the
 *                player if (s)he is a Rockfriend. Yes, indeed. Even female
 *                dwarves wear a beard.
 * Arguments    : int level - the level of the member in the guild.
 * Returns      : string - the description
 */
nomask public string
query_rockfriend_beard_description(int level)
{
    return beards[level];
}

/*
 * Function name: query_guild_title_race
 * Description  : This function will return the title for the Rockfriends.
 * Arguments    : int level - the level of a member in the guild.
 * Returns      : string - the title.
 */
nomask public string
query_guild_title_race(int level)
{
    return titles[level] + " Rockfriend";
}

/*
 * Function name: test_members
 * Description  : At the first of the month, we test whether all members
 *                listed are still valid. Ie. players who have quit will
 *                be kicked out of the list.
 */
nomask static void
test_members()
{
    string *names = m_indices(members);
    int    index = -1;
    int    size = sizeof(names);

    while(++index < size)
    {
        if (!(SECURITY->exist_player(names[index])))
        {
            log_guild(ctime(time()) +
                sprintf(" %-11s is not a player any more. -> removed.\n",
                CAP(names[index])));

            members = m_delete(members, names[index]);
            memberkillers -= ({ names[index] });
        }
    }

    FIX_EUID;
    save_object(DWARVEN_RACE_GUILD_SAVE);
}

/*
 * Function name: update_level
 * Description  : Called from the shadow each time a player logs in.
 *                His/her current level is stored into the membership
 *                list.
 * Arguments    : string name   - the name of the player.
 *                int    level  - the level of the player.
 */
public nomask void
update_level(string name, int level)
{
    members[name] = level;

    FIX_EUID;
    save_object(DWARVEN_RACE_GUILD_SAVE);
}

/*
 * Function name: query_player_killed_dwarf
 * Description  : Called to query whether a person has slain a member of the
 *                Rockfriend Guild.
 * Arguments    : string name - the name of the person to test.
 * Returns      : int 1/0 - if true, the person killed a member.
 */
public nomask int
query_player_killed_dwarf(string name)
{
    return (member_array(name, memberkillers) > -1);
}

/*
 * Function name: set_player_killed_dwarf
 * Description  : Called to indicate that a person has slain a member of the
 *                Rockfriend Guild.
 * Arguments    : string name - the name of the person to test.
 */
public nomask void
set_player_killed_dwarf(string name)
{
    if (!query_player_killed_dwarf(name))
    {
        memberkillers += ({ name });

        FIX_EUID;
        save_object(DWARVEN_RACE_GUILD_SAVE);
    }
}

/*
 * Function name: is_member
 * Description  : Tests whether the dwarf is a member of the guild.
 * Arguments    : object dwarf - the player to test.
 * Returns      : int - 1/0 - true if it is a dwarf.
 */
public nomask int
is_member(object dwarf)
{
    return IS_MEMBER(dwarf);
}

/*
 * Function name: query_restore_belt
 * Description  : Find out whether a player is elegible for a brooch
 *                restoration.
 * Arguments    : object player - the player to test.
 * Returns      : int 1/0 - if true, the player is elegible for restoration.
 */
nomask public int
query_restore_belt(object player)
{
    return (is_member(player) &&
        !present(DWARVEN_RACE_GUILD_BELT_ID, player));
}

/*
 * Function name: restore_belt
 * Description  : Restore the belt to the player (but test elegibility first).
 * Arguments    : object player - the player to give the belt to.
 * Returns      : int 1/0 - if true, the player got the belt.
 */
nomask public int
restore_belt(object player)
{
    if (query_restore_belt(player))
    {
        player->catch_tell("Notice: You still need to get the belt branded by Borin, the smith.\n");
        /* This returns the negation of the result from the move(). */
        return !(clone_object(DWARVEN_RACE_GUILD_BELT)->move(player, 1));
    }
    return 0;
}

/*
 * Function name: update_levels
 * Description  : When someone wants to manipulate or list the members,
 *                we update the levels of all members logged in.
 */
static nomask void
update_levels()
{
    object *dwarves;
    int    index = -1;
    int    size;

    if (updated + NO_UPDATE < time())
    {
        return;
    }

    updated = time();
    dwarves = filter(users(), is_member);
    size    = sizeof(dwarves);

    while(++index < size)
    {
        members[dwarves[index]->query_real_name()] =
            dwarves[index]->query_rockfriend_level();
    }

    FIX_EUID;
    save_object(DWARVEN_RACE_GUILD_SAVE);
}

/*
 * Function name: report_levels
 * Description  : This object generates a list of the Dwarves and their
 *                titles. The indices of the mapping are the titles possible
 *                and the values the number of members with that title.
 * Returns      : mapping - the resulting mapping.
 */
public nomask mapping
report_levels()
{
    int     index = -1;
    mapping report = ([ ]);
    string  *names = m_indices(members);
    int     size = sizeof(names);

    update_levels();

    while(++index < size)
    {
        if (SECURITY->query_wiz_level(names[index]))
        {
            report[-1]++;
        }
        else
        {
            report[members[names[index]]]++;
        }
    }

    return report;
}

/*
 * Function name: list_level
 * Description  : It is possible to list all members of a certain level.
 * Arguments    : int level - the level to list.
 */
public nomask string *
list_level(int level)
{
    string *names = m_indices(members);
    int    index = -1;
    int    size = sizeof(names);
    string *result = ({ });

    update_levels();

    while(++index < size)
    {
        if (members[names[index]] == level)
        {
            result += ({ names[index] });
        }
    }

    return result;
}

/*
 * The members-command can be used to print statistics on members of
 * the guild.
 */
nomask static int
do_members(string str)
{
    int    scrw;
    int    index;
    int    level;
    int    size;
    string *names;
    string *in_level;
    int    wizard = 0;

    if (!strlen(str))
    {
        notify_fail("The command <members> can take three forms. Use " +
            "\"members list\" to list the names of all members. \"members " +
            "sort\" will list the number of members bearing a certain title " +
            "and \"members <title>\" can be used to display all members of " +
            "the " + DWARVEN_RACE_GUILD_NAME + " bearing a certain title.\n");
        return 0;
    }

    update_levels();
    if (!m_sizeof(members))
    {
        notify_fail("No members of the " + DWARVEN_RACE_GUILD_NAME +
            " registered.\n");
    }

    scrw = TP->query_prop(PLAYER_I_SCREEN_WIDTH);
    scrw = (scrw ? (scrw - 5) : 75);

    if (str == "list")
    {
        write("The following players are a member of the " +
            DWARVEN_RACE_GUILD_NAME + ".\n");
        write(sprintf("\n%-*#s\n", scrw,
            implode(sort_array(map(m_indices(members), capitalize)), "\n")));
        return 1;
    }

    if (str == "sort")
    {
        mapping list = report_levels();
        names = ({ });
        index = -1;
        while(++index < NUM_TITLES)
        {
            names += ({ sprintf("%-*s %3d", LONGEST_TITLE,
                titles[index], list[index]) });
        }

        write("The following table contains the numbers of people " +
            "decorated with a certain title:\n");
        write(sprintf("\n%-*#s\n", scrw, implode(names, "\n")));

        if (list[-1])
        {
            write(((list[-1] == 1) ? "One wizard is" :
                (CAP(LANG_WNUM(list[-1])) + " wizards are")) +
                " member of the guild.\n");
        }

        return 1;
    }

    level = member_array(CAP(str), titles);
    if (level == -1)
    {
        notify_fail("Not a possible title: \"" + str +
            "\". Use <members> without parameters for the possible syntax.\n");
        return 0;
    }

    names    = m_indices(members);
    index    = -1;
    size     = sizeof(names);
    in_level = ({ });
    while(++index < size)
    {
        if (members[names[index]] == level)
        {
            in_level += ({ capitalize(names[index]) });

            if (SECURITY->query_wiz_rank(names[index]))
            {
                in_level[sizeof(in_level) - 1] += "*";
                wizard = 1;
            }
        }
    }

    if (!sizeof(in_level))
    {
        write("No members of the " + DWARVEN_RACE_GUILD_NAME +
            " with that title.\n");
    }
    else
    {
        write("The following members are decorated with the title \"" +
            CAP(str) + "\":\n");
        write(sprintf("\n%-*#s\n", scrw, implode(in_level, "\n")));

        if (wizard)
        {
            write("   * - member is a wizard.\n");
        }
    }

    return 1;
}

/*
 * Function name: init
 * Description  : When someone enters the room, the commands are linked
 *                to him/her.
 */
nomask public void
init()
{
    ::init();

    init_guild_support();
    add_action(gs_meditate, "kneel");
    add_action(gs_meditate, "pray");

    add_action(do_pledge,   "pledge");
    add_action(do_abandon,  "abandon");
    add_action(do_members,  "members");
}
