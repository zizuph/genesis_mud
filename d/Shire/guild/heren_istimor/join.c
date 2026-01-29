/*
 * /d/Shire/guild/heren_istimor/join.c
 *
 */

#pragma save_binary
#pragma strict_types

inherit "/d/Shire/std/room";
inherit "/lib/guild_support";

#include <composite.h>
#include <macros.h>
#include <ss_types.h>
#include <std.h>
#include <stdproperties.h>
#include "/d/Shire/sys/defs.h"
#include "/d/Shire/guild/heren_istimor/heren_istimor.h"
#include "/d/Shire/bits.h"

#define START          (HEREN_ISTIMOR_DIR + "start")
#define LOG_SIZE       25000


#define WRITE_NAME(o)  sprintf("%-11s", capitalize((o)->query_real_name()))


/*
 * Function name: create_room
 * Description : Called when the room is first loaded into memory.
 */
nomask public void
create_shire_room()
{
    set_short("The initiation room of Heren Istimor.");
    set_long("The initiation room of Heren Istimor.\n");


    add_prop(ROOM_I_INSIDE, 0);
    add_prop(ROOM_I_NO_CLEANUP, 1);
    add_prop(ROOM_I_NO_CLEANUP, 1);
    add_prop(ROOM_I_NO_ATTACK, 1);
    add_prop(ROOM_I_NO_MAGIC_ATTACK, 1);

    create_guild_support();
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
    setuid();
    seteuid(getuid());

    if (file_size(HEREN_ISTIMOR_GUILD_LOG) > LOG_SIZE)
    {
    rename(HEREN_ISTIMOR_GUILD_LOG, (HEREN_ISTIMOR_GUILD_LOG + ".old"));
    }

    write_file(HEREN_ISTIMOR_GUILD_LOG, text);
}

/*
 * Function name: do_serve
 * Description  : When a Noldor wants to join the guild, this function
 *                makes him/her a member.
 * Arguments    : string str - the command line argument.
 * Returns      : int    1/0 - success/failure.
 */
nomask static int
do_serve(string str)
{
    object tp = this_player();
    object shadow;
    string family;
    int    result;

    string buffoon;

    buffoon = tp->query_race_name();
    if (!strlen(str))
    {
    notify_fail(capitalize(query_verb()) + " whom?\n");
    return 0;
    }

    if (str != "the sindar")
    {
    write("Serve whom?\n");
    return 1;
    }

    write(buffoon + "\n");
    if (buffoon != "grey-elf")
    {
        write("Only the Sindar may serve.\n");
        return 1;
    }

    if (tp->query_guild_name_race() == "Drow race guild")
    {
        write("Only the creations of Eru Illuvatar may serve the Valar.\n");
        return 1;
    }

    if((tp->query_alignment() < 1100))
    {
        write("Only those who are clearly devoted to the Song of Illuvatar are "+
        "welcome here.\n");
        return 1;
    }

    if (IS_MEMBER(tp))
    {
        write("You are already a member.\n");
        return 1;
    }

    if (tp->query_guild_member(HEREN_ISTIMOR_GUILD_TYPE))
    {
        write("You still belong to another occupational guild.\n");
        return 1;
    }

    write(HEREN_ISTIMOR_GUILD_SHADOW + "\n");
    shadow = clone_object(HEREN_ISTIMOR_GUILD_SHADOW);

    if ((result = shadow->shadow_me(tp, HEREN_ISTIMOR_GUILD_TYPE,
        HEREN_ISTIMOR_GUILD_STYLE, HEREN_ISTIMOR_GUILD_NAME)) != 1)
    {
        log_guild(ctime(time()) + " " + WRITE_NAME(tp) +
        " failed to add shadow with result " + result + ".\n");
        shadow->remove_shadow();

        write("There was an error, you are not able to join at this "+
        "time, please leave a bug report.\n");

        return 1;
    }
    //shadow->init_lay_shadow();

    write("You are One.\n");
    say(QCTNAME(tp) + " is One.\n");
    log_guild(ctime(time()) + " " + WRITE_NAME(tp) + " joined the " +
      HEREN_ISTIMOR_GUILD_NAME + ".\n");

    tp->clear_guild_stat(SS_OCCUP);
    tp->set_guild_pref(SS_OCCUP, HEREN_ISTIMOR_GUILD_TAX);
    tp->set_bit(FOURTH_GROUP,HEREN_ISTIMOR_BIT);
    return 1;
}

/*
 * Function name: lower_skill
 * Description  : When a member leaves the guild or is kicked out due
 *                to a change of race, this function punishes him/her,
 *                removes the soul, shadow, etcetera.
 * Arguments    : object tp - the object leaving.
 */
nomask private int
lower_skill(object tp)
{
    int result;
    object ob;

    if (!objectp(tp))
        return 0;
    if ((result = tp->remove_guild_occ()) != 1)
    {
    log_guild(ctime(time()) + " " + WRITE_NAME(tp) +
      " failed to remove shadow with result " + result + ".\n");

    write("We'd like you to reconsider.  In fact, you cannot leave "+
      "the guild at this time due to a bug.  Please leave a report.\n");

    return 0;
    }
    tp->set_guild_pref(SS_OCCUP, 0);
    tp->clear_guild_stat(SS_OCCUP);
    tp->remove_cmdlist(HEREN_ISTIMOR_GUILD_SOUL);
    tp->clear_bit(FOURTH_GROUP,HEREN_ISTIMOR_BIT);
    tp->update_hooks();
    tp->setup_skill_decay();

    /* If the player starts in the guild by default, set this to
     * the default starting location for all players.
     */
    if (tp->query_default_start_location() == START)
    {
    tp->set_default_start_location(tp->query_def_start());
    }

    while (objectp(ob = present("_heren_istimor_robe_", tp)))
    {
    ob->remove_object();
    }
    while (objectp(ob = present("_shire_heren_istimor_prayerbook_", tp)))
    {
    ob->remove_object();
    }
    MEMBER_TRACKER->remove_member(tp);
    return 1;
}

/*
 * Function name: do_betray
 * Description  : This is a waste of memory since no-one would ever
 *                consider leaving a guild like this, or would they?
 *                Just for the completeness, this function takes care
 *                of a voluntary leave.
 * Arguments    : string str - the command line argument
 * Returns      : int    1/0 - success/failure.
 */
nomask static int
do_betray(string str)
{
    object tp = this_player();
    int    result;

    if (str != "sindar")
    {
    notify_fail("abandon whom?\n");
    return 0;
    }

    if (!IS_MEMBER(tp))
    {
    write("You cannot leave a guild when you are not a member!\n");
    return 1;
    }

    if (!lower_skill(tp))
    return 1;

    write("You are not One.\n");
    say(QCTNAME(tp)+ " is not One.\n");


    log_guild(ctime(time()) + " " + WRITE_NAME(tp) + " left the " +
      HEREN_ISTIMOR_GUILD_NAME + ".\n");

    return 1;
}

/*
 * Function name: do_list
 * Description  : This function allows people to list their (major) guilds.
 * Arguments    : string str - the command line argument.
 * Returns      : int 1/0    - success/failure.
 */
nomask static int
do_list(string str)
{
    if (str != "guilds")
    {
    NF("List what? Your guilds?\n");
    return 0;
    }

    str = this_player()->list_major_guilds();

    if (strlen(str))
    {
    write("You are a member of the following major guilds:\n" + str);
    }
    else
    {
    write("You are not a member of any major guild.\n");
    }

    return 1;
}

/*
 * Function name: ask
 * Description  : Members who have lost their objects, may get them back here.
 * Arguments    : string str - the command line argument.
 * Returns      : int 1/0    - success/failure.
 */
nomask static int
ask(string str)
{
    object tp = this_player();
    object robe;


    if ((str != "new robe") && (str != "new book"))
    {
    notify_fail("Ask for what? A new robe or a new book?\n");
    return 0;
    }

    if (!IS_MEMBER(tp))
    {
    write("The Valar do not grant requests to those who do not serve!\n");
    return 1;
    }


    if(str == "new robe")
    {

    if (objectp(robe = present("_heren_istimor_robe_",tp)) &&
      (!robe->query_prop(OBJ_I_BROKEN)))
    {
        write("You don't need two robes.\n");
        return 1;
    }

    setuid();
    seteuid(getuid());

    robe->remove_object();
    clone_object(HEREN_ISTIMOR_GUILD_OBJ)->move(tp, 1);

    write("A magnificent elf arrives, and hands you a new robe.\n");
    say(QCTNAME(tp)  + " is given a new robe by a magnificent elf.\n");

    return 1;

    }

    if (objectp(present("_heren_istimor_book_", tp)))
    {
    write("You don't need two prayer books.\n");
    return 1;
    }

    setuid();
    seteuid(getuid());

    clone_object(HEREN_ISTIMOR_GUILD_SPELLS)->move(tp, 1);

    write("A magificent elf arrives, and hands you a prayer book.\n");
    say(QCTNAME(tp)  + " is given a new prayer book by a magnificent elf.\n");

    return 1;

}

/*
 * Function name: remove_player_changed_race
 * Description  : Whenever a member changes his/her race (s)he is
 *                mercilessly kicked out the guild by this function.
 * Arguments    : object tp - the object to kick out.
 */
nomask public void
remove_player_changed_race(object tp)
{
    if (!objectp(tp))
        return;
    tp->catch_tell("\nYou have changed races.  Your race is not " +
      "one created or permitted by Eru Illuvatar.  You are being removed " +
      "from the Heren Istimor.\n");
    set_alarm(0.1,0.0,&lower_skill(tp));
    log_guild(ctime(time()) + " " + WRITE_NAME(tp) + " (race " +
      tp->query_race_name() + ") was kicked out.\n");
}

void
do_valid_race_check(object player)
{
    string race_name;

    race_name = player->query_race_name();
    if (race_name != "grey-elf"  && race_name != "elf"
        && race_name != "half-elf")
    remove_player_changed_race(player);
}

void
valid_race_check(object player)
{
    set_alarm(5.0, 0.0, &do_valid_race_check(player));
}

/*
 * Function name: remove_player_low_alignment
 * Description  : Whenever the alignment of a player is too low, the player
 *                is mercilessly kicked out the guild by this function.
 * Arguments    : object tp - the object to kick out.
 */
nomask public void
remove_player_low_alignment(object tp)
{
    tp->catch_tell("\nYou have gone back on your pledge to serve the "+
      "Light.  The Valar do not reward disfealty.  You are removed from "+
      "The Heren Istimor.\n");

    log_guild(ctime(time()) + " " + WRITE_NAME(tp) + " (alignment " +
      tp->query_alignment() + ") was kicked out.\n");
    lower_skill(tp);
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
 * Stuff for meditation.
 */

/*
 * Function name: gs_hook_start_meditate
 * Description  : Gives a nice description when someone starts to meditate.
 */
nomask public void
gs_hook_start_meditate()
{
    write("Sitting down on the floor, you let the tranquil surroundings have " +
      "their effect on you. You close your eyes and find your mind floating " +
      "away from your body. Finally, you become as relaxed as possible and " +
      "feel yourself able to \"estimate\" your different preferences for " +
      "concentration and \"set\" them to new values if desired. To go back " +
      "to the world outside, all you have to do is \"rise\".\n");
    say(QCTNAME(this_player()) + " sits down in order to meditate.\n");
}

/*
 * Function name: gs_hook_rise
 * Description  : Gives a nice description when someone is done meditating.
 */
nomask public void
gs_hook_rise()
{
    write("Having reached a new peace with yourself, you feel relaxed and " +
      "ready to conquer the world. You open your eyes and stand up.\n");
    say("Looking quite relaxed indeed, " + QTNAME(this_player()) + " opens " +
      this_player()->query_possessive() + " eyes and stands up.\n");
}

/*
 * Function name: gs_hook_already_meditate
 * Description  : Gives a nice message when someone tries to meditate
 *                when (s)he is already mediating.
 */
nomask public int
gs_hook_already_meditate()
{
    write("It is not possible to come to an even higher level of meditation. " +
      "Since you are already meditating, you can now \"estimate\" your " +
      "different preferences for concentration and \"set\" them to new " +
      "values if you please. To relax and get back to the outside world, " +
      "just \"rise\".\n");
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
    write("It is not possible to do that in your current state. Since you are " +
      "meditating, you can only \"estimate\" your different preferences for " +
      "concentration and \"set\" them to new values if you please. To relax " +
      "and get back to the outside world, just \"rise\".\n");
    return 1;
}


/*
 * Function name: cap
 * Description  : Map-function to capitalize strings.
 * Arguments    : string str - the string to capitalize.
 * Returns      : string - the capitalized string.
 */
string
cap(string str)
{
    return capitalize(str);
}

int
do_slide(string str)
{
    if (!str || !strlen(str)) {
       notify_fail("Slide what?\n");
        return 0;
    }

    if ((str == "door") || (str == "bark door"))
    {
       if (!IS_MEMBER(this_player()))
       {
          notify_fail("You are not a member, you are not " +
                      "allowed to enter.\n");
           return 0;
       }

    write("The door slides open easily and you go in.\n");
    say(QCTNAME(TP)+ " slides the bark door open and enters the tree.\n");
    TP->move_living("M",HEREN_ISTIMOR_DIR + "herb",1);
    tell_room((HEREN_ISTIMOR_DIR + "herb"),
      QCTNAME(TP)+" comes crawling into the tree.\n",TP);
    return 1;
    }
    write("Slide what ? A "+str+" ? You must be kidding!\n");
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

    add_action(do_serve,    "serve");
    add_action(do_betray,   "abandon");
    add_action(ask,         "ask");
    add_action(do_list,     "list");
    add_action(do_slide,    "slide");
    add_action(do_slide,    "push");
}

nomask public void
angry_valar(object tp)
{
    tp->catch_tell("\n \nYou have disappointed Manwe Sulimo.\n" +
      "Feel his wrath, and know that you are forsaken!\n");
    lower_skill(tp);
    log_guild(ctime(time()) + " " + WRITE_NAME(tp) + " was removed from "+
      "the guild by the Valar.\n");
    tp->catch_tell("\nA thunderbolt rains down from the sky.\n");
    tp->catch_tell("It smites you in the forehead, and all goes black.\n");
    tp->heal_hp(-tp->query_max_hp());
    tp->do_die(TO);
    return;
}

nomask public int
valar_wrath(object player)
{
    int ran, ran2;

    ran = random(10);
    ran2 = random(10);

    if(ran + ran2 > 15)
    {
    set_alarm(3.0,0.0, &angry_valar(player));
    return 1;
    }

    if(ran2 < 9)
    {
    player->catch_tell("You are stung by the angry gaze of Varda.\n");
    player->heal_hp(-100);
    if (player->query_hp() <= 0)
    {
        player->do_die(this_object());
    }
    log_guild(ctime(time()) + " " + WRITE_NAME(player) + " (race " +
      player->query_race_name() + ") was punished by Varda.\n");

    return 1;
    }

    if(ran > 7)
    {
    player->catch_tell("Ulmo looks upon you from afar and you feel his wrath.\n");
    player->add_fatigue(-100);
    log_guild(ctime(time()) + " " + WRITE_NAME(player) + " (race " +
      player->query_race_name() + ") was punished by Ulmo.\n");

    return 1;
    }

    if((ran < 3) || (ran2 < 3))
    {
    player->catch_tell("You feel an intense gaze coming from the Undying Lands.\n"+
      "You feel very very afraid.\n");
    player->command("drop all");
    player->add_panic(150);
    log_guild(ctime(time()) + " " + WRITE_NAME(player) + " (race " +
      player->query_race_name() + ") was punished by Lorien.\n");

    return 1;
    }
}
