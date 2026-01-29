/* File         : /d/Khalakhor/racial/clans/room/clans/greathall.c
 * Creator      : Tomas@Genesis
 * Copyright:   : Bryan Dees
 * Date         : March 2001         
 * Purpose      : Default inherit GreatHall for the Clans of Khalakhor.
 * Related Files: 
 * Comments     : members may choose to join the clan here
 * Modifications:
 */
#pragma strict_types

#include <filter_funs.h>
#include <macros.h>
#include <stdproperties.h>

#include "defs.h"

inherit GUILD_ROOM;
inherit SCROLL;

#define WRITE_NAME(o)  sprintf("%-11s", capitalize((o)->query_real_name()))
#define LOG_SIZE 4000

/* Used to store petitioner info. */
static mapping petition = ([]);


nomask private void
log_fail(string text)
{
    setuid();
    seteuid(getuid());

    if (file_size(FAIL_LOG) > LOG_SIZE)
    {
        rename(FAIL_LOG, (FAIL_LOG + ".old"));
    }

    write_file(FAIL_LOG, text);
}


nomask private void
log_accept(string text)
{
    setuid();
    seteuid(getuid());

    if (file_size(ACCEPT_LOG) > LOG_SIZE)
    {
        rename(ACCEPT_LOG, (ACCEPT_LOG + ".old"));
    }

    write_file(ACCEPT_LOG, text);
}

nomask private void
log_quit(string text)
{
    setuid();
    seteuid(getuid());

    if (file_size(QUIT_LOG) > LOG_SIZE)
    {
        rename(QUIT_LOG, (QUIT_LOG + ".old"));
    }

    write_file(QUIT_LOG, text);
}

nomask private void
log_petition(string text)
{
    setuid();
    seteuid(getuid());

    if (file_size(PETITION_LOG) > LOG_SIZE)
    {
        rename(PETITION_LOG, (PETITION_LOG + ".old"));
    }

    write_file(PETITION_LOG, text);
}
/*
 * The room itself.
 */
public void
create_guild_room()
{
    setuid(); seteuid(getuid());

    set_short("Clan " + CLANHOME + " Great Hall");
    set_long("You stand beneath the tall arches within the " +
             "Great Hall of the Clan " + CLANHOME + ". There is a " +
             "podium with a gold plaque hanging from it.\n");
  add_item(({"plaque", "gold plaque", "golden plaque"}),
    "The plaque is made of gold and engraved with these words.\n"+
    "'petition <Clan>'  = Petition to join the selected Clan.\n"+
    "'accept <player>'  =  To accept someone in a Clan.\n"+
    "<leave Clan> = Leave the Clan.\n"+
    "<list>        =  List current guilds you are affiliated with.\n");
  add_cmd_item("plaque", "read", 
    "'choose <clan>'  = To join a Clan.\n"+
    "'accept <player>'  =  To accept someone in a Clan.\n"+
    "<leave Clan> = To leave your present Clan.\n"+
    "<list>        =  List current guilds you are affiliated with.\n");


  add_prop(ROOM_I_INSIDE, 1);
  add_prop(ROOM_I_NO_ATTACK, 1);
  add_prop(ROOM_I_NO_MAGIC_ATTACK, 1);  

  add_exit("joinroom", "down");
}


int
do_list(string str)
{
    int name;
    name = (SERVER->query_council_member() == CLANHOME);

    if (!strlen(str))
    {
        if (str = this_player()->list_major_guilds())
            write("You are a member of the following guilds.\n" + str);
        else
            write("You are not a member of any important guilds.\n");
        return 1;
    }

    setuid();
    seteuid(getuid());

    if (!sizeof(name = SERVER->query_council_members()))
    {
        write("There are no members of the council right now.\n");
        return 1;
    }

    write("The Chief of Clan "+ CLANHOME+" is: " +name+".\n");
    return 1;
}



/*
 * Naughty member lost their tartan...
 */
public int
request(string str)
{
    object tartan;

    if (str != "tartan")
    {
        NF("Request what? A tartan maybe?\n");
        return 0;
    }

    if (!IS_MEMBER(TP))
    {
        write("The " + GUILD_NAME + " do not grant requests to " +
          "non-members.\n");
        return 1;
    }

    if (objectp(tartan = present(OBJECT_ID, TP)) &&
      (!tartan->query_prop(OBJ_I_BROKEN)))
    {
        write("You don't need another tartan.\n");
        return 1;
    }

    if (tartan)
        tartan->remove_object();

    clone_object(OBJECT)->move(TP, 1);
    write("A servant to the Clan's wanders in and hands you a replacement " +
      "tartan then leaves.\n");
    say ("A servant wanders in and hands " + QCTNAME(TP) + 
         " a replacement tartan then leaves.\n");
    return 1;
}




/*
 * For members to petition a Clan for membership.
 */
public int
choose_clan(string str)
{
    string *tmp, name;

    /* Not a member, go away. */
    if (!IS_MEMBER(this_player()))
    {
        return 0;
    }

    /* Input would be helpful. */
    if (!strlen(str))
    {
        notify_fail("Choose what? A Clan maybe?\n");
        return 0;
    }

    /* Member has memory problem as they are already petitioning */
    name = this_player()->query_real_name();
    if (petition[name])
    {
        write("You are already seeking to join a Clan.\n");
        return 1;
    }

    /* Stoopid mortal, your already in a Clan. */
    if (SERVER->query_clan(name))
    {
        write("You already belong to a Clan.\n");
        return 1;
    }

    /* Are we asking to join a real clan? */
    CAP(str); tmp = SERVER->query_clan("all");
    if (member_array(str, tmp) == -1)
    {
        write("No such Clan exists, try again.\n");
        return 1;
    }

    /* Clan is empty, lay your claim and take it over. */
    if (m_sizeof(SERVER->query_clan(str)) < 2)
    {
        /* Rut-roh! An error.. ickyness */
        if (!SERVER->add_to_clan(name, str, name))
        {
            write("An error has prevented you from claiming " +
                "that Clan, please make a bug report.\n");
            return 1;
        }
       
      if (!SERVER->add_council_member(str, name))
      {
          write("An error has prevented you from becoming " +
                "Clan Chief. Please make " +
                "a bug report.\n");
          return 1;
      }

        write("You claim the Clan " + str + " as your own.\n" +
            "A servant of the Clans fetches your new tartan " +
            "and placing it within your hands, taking the old " +
            "one away with him.\n");
        say(QCTNAME(this_player()) + " has claimed the Clan " +
            str + " as their own.\n");

        /* In case we don't have one */
        if (!present(OBJECT_ID, this_player()))
        {
            clone_object(OBJECT)->move(this_player());
        }

        /* This resets the players tartan with Clan colours */
        present(OBJECT_ID, this_player())->init();
    }
    else /* Attempt to petition a Clan. */
    {
        object *obs = FILTER_PLAYERS(all_inventory(this_object()));

        obs -= ({ this_player() });

        /* Nobody here. */
        if (!sizeof(obs))
        {
            write("There is nobody present to accept you into that Clan.\n");
            return 1;
        }

        obs = filter(obs, &operator(==)(str) @ 
            &SERVER->query_clan() @ &->query_real_name());

        /* No one of the petitioned clan here. */
        if (!sizeof(obs))
        {
            write("There is no one available to accept you into that Clan.\n");
            return 1;
        }

        /* Petition away... */
        petition[name] = str;

      log_petition(WRITE_NAME(TP)+ " petitioned " +CLANHOME+ " on " + ctime(time()) + "\n");
        write("You enter a petition to join the Clan " + str + ".\n");
        obs->catch_msg(QCTNAME(this_player()) + " has made a " +
            "petition to join the Clan " + str + ".\n");
    }
    return 1;
}

/*
 * Accept a petitioner into your Clan.
 */
public int
accept_member(string str)
{
    string clan, name = this_player()->query_real_name();
    object ob;
    
    setuid();
    seteuid(getuid());

    if (!IS_CLANCHIEF(TP) || !(clan = SERVER->query_clan(name)))
    {
      log_fail(WRITE_NAME(TP)+ " tried to accept "+str+", but "+
         "they were not a member!\n");
        return 0;
    }

    /* Additional typed characters are necessary */
    if (!strlen(str))
    {
        notify_fail("Accept what?  A petitioner mayhaps?\n");
        return 0;
    }

    /* We have no petitioners. */
    if (member_array(clan, m_values(petition)) == -1)
    {
        write("Nobody is petitioning your clan.\n");
        return 1;
    }

    /* Petitioner doesn't exist. */
    if (!petition[MLC(str)])
    {
        write("There is no such petitioner.\n");
        return 1;
    }

    /* Petitioner isn't seeking our clan. */
    if (petition[str] != clan)
    {
        write(capitalize(str) + " is not petitioning your Clan.\n");
        return 1;
    }

    /* Where did that stoopid member run off too? */
    if (!objectp(ob = present(str, this_object())))
    {
        write(capitalize(str) + " is not present for their petition " +
            "to be heard.\n");
        return 1;
    }

    /* Ooops, no can join, need squash buggie */
    if (!SERVER->add_to_clan(str, clan, name))
    {
        write("An error has prevented your accepting petitioners.\n"+
            "Please make a bug report.\n");
        return 1;
    }

    /* Reset the guild item to contain clan colours. */
    present(OBJECT_ID, ob)->init();

    log_accept(WRITE_NAME(TP)+ " accepted "+
      capitalize(str) + " into Clan " +clan+ " on " + ctime(time()) + ".\n");

    /* Print messages */
    this_player()->catch_msg("You accept " + QTNAME(ob) +
        " into your clan.\n");
    ob->catch_msg(QCTNAME(this_player()) + " accepts you into " +
        "the Clan " + clan + ".\n");
    tell_room(this_object(), QCTNAME(this_player()) + " accepts " +
        QTNAME(ob) + " into the Clan " + clan + ".\n",
        ({ ob, this_player() }));
    return 1;
}

public int
leave_clan(string str)
{
    string clan, name = this_player()->query_real_name();

    if (!IS_MEMBER(this_player()) || !(clan = SERVER->query_clan(name)))
    {
        return 0;
    }

    if ((CAP(str) != "Clan") && (str != clan))
    {
        return notify_fail("Leave what, your clan?");
    }

    if (IS_CLANCHIEF(TP))
    {
      if (!SERVER->remove_council_member(SERVER->query_clan(name)))
      {
        write("An error occured attempting to remove you as " +
              "Clan leader. Please make a bug report.\n");
        return 1;
      }
    }  

    if (!SERVER->remove_from_clan(name, name))
    {
        write("An error occured preventing your leaving.\n" +
            "Please make a bug report.\n");
        return 1;
    }

    write("You leave the " + str + " and turn in your " +
        "tartan for your old one.\n");
    say(QCTNAME(this_player()) + " has left the " + str + ".\n");

    present(OBJECT_ID, this_player())->init();

    log_quit(WRITE_NAME(TP)+ " left " +CLANHOME+ " on " + ctime(time()) + "\n");

    return 1;
}



/*
 * Give us some commands.
 */
public void
init()
{
    ::init();

    add_action(do_list, "list");
    add_action(request, "request");
    add_action(leave_clan, "leave");
    add_action(choose_clan, "choose");
    add_action(accept_member, "accept");
}
