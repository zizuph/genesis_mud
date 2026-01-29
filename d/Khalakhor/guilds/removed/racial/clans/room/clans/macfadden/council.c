/* Clans of Khalakhor Join a Clan room
 * Tomas
 */
#pragma strict_types

#include "defs.h"
#include <filter_funs.h>
#include <macros.h>
#include <stdproperties.h>

inherit GUILD_ROOM;
inherit SCROLL;

#define WRITE_NAME(o)  sprintf("%-11s", capitalize((o)->query_real_name()))
#define LOG_SIZE 4000

/* Used to store petitioner info. */
static mapping petition = ([]);


nomask private void
log_exile(string text)
{
    setuid();
    seteuid(getuid());

    if (file_size(EXILE_LOG) > LOG_SIZE)
    {
        rename(EXILE_LOG, (EXILE_LOG + ".old"));
    }

    write_file(EXILE_LOG, text);
}


nomask private void
log_forgive(string text)
{
    setuid();
    seteuid(getuid());

    if (file_size(FORGIVE_LOG) > LOG_SIZE)
    {
        rename(FORGIVE_LOG, (FORGIVE_LOG + ".old"));
    }

    write_file(FORGIVE_LOG, text);
}


/*
 * The room itself.
 */
public void
create_guild_room()
{
    setuid(); seteuid(getuid());

    set_short("Clan Chief Chambers");
    set_long("Clan " +CLANHOME+" Clan Chief personal " +
             "chambers.\n");

  add_cmd_item("plaque", "read", "<list clans>    "+
    "=  To list the clans of Khalakhor.\n"+
    "'list '            = To list members of your clan.\n"+
    "'exile <player>'   = Remove someone from the clan.\n" +
    "'forgive <player>' = Forgive player thus removing Kinslayer.\n");


  add_prop(ROOM_I_INSIDE, 1);
  add_prop(ROOM_I_NO_ATTACK, 1);
  add_prop(ROOM_I_NO_MAGIC_ATTACK, 1);  

  add_exit("joinhouse", "down");
}


public int
list(string str)
{
    if (!strlen(str))
    {
        mixed tmp = ([]) + SERVER->query_clan(CLANHOME);
        tmp = m_indexes(tmp) - ({ CLAN_CLRS });

        tmp = sort_array(map(tmp, capitalize));
        return print_scroll(tmp, "The following members of the " + GUILD_NAME +
            " belong to the Clan " + CLANHOME);
        return 1;
    }
}




public int
do_exile(string str)
{
    string clan, 
           LEADER = this_player()->query_real_name();
    object ob;

    /* Not even in a clan, get lost schmuck */
    if (!IS_CLANCHIEF(TP))
    {

        write("Only the Chief may Exile someone! How'd you get " +
           "in here anyways!\n");
        return 1;
    }

    /* Additional typed characters are necessary */
    if (!strlen(str))
    {
        notify_fail("Exile whom?\n");
        return 0;
    }
    /* Check to see if the person is in the clan or not. */
    if (SERVER->query_clan(str) != CLANHOME)
    {
        write(str + " does not belong to your clan.\n");
        return 1;
    }


    /* Ooops, no can exile, need squash buggie */
    if (!SERVER->remove_from_clan(str, LEADER))
    {
        write("An error has prevented your exile proceedings.\n"+
            "Please make a bug report.\n");
        return 1;
    }

    if (objectp(ob = find_player(str)))
    {
        /* Reset the members tartan to contain clan colours. */
        present(OBJECT_ID, ob)->init();
        tell_object(ob, "You have been banished from the Clan.\n");
    }

    log_exile(WRITE_NAME(TP)+ " exiled " +capitalize(str)+ " on " + ctime(time()) + "\n");
    /* Print messages */
    write("You banish " + capitalize(str) + " from the Clan.\n");
    return 1;
}


// remove_kinslayer(string who, string by, int all)
// query_kinslayer(string who)

public int
do_forgive(string str)
{
    string clan, 
           LEADER = this_player()->query_real_name();
    object ob;

    /* Not even in a clan, get lost schmuck */
    if (!IS_CLANCHIEF(TP))
    {

        write("Only the Chief may forgive someone! How'd you get " +
           "in here anyways!\n");
        return 1;
    }

    /* Additional typed characters are necessary */
    if (!strlen(str))
    {
        notify_fail("Forgive whom?\n");
        return 0;
    }
    /* Check to see if the person is in the clan or not. */
    if (SERVER->query_clan(str) != CLANHOME)
    {
        write(str + " does not belong to your clan.\n");
        return 1;
    }

    if (!SERVER->query_kinslayer(str))
    {
       write(str + " has not been deemed a Kinslayer and is presumed " +
                   "innocent.\n");
       return 1;
    }

    /* Ooops, no can forgive, need squash buggie */
    if (!SERVER->remove_kinslayer(str, LEADER))
    {
        write("An error has prevented your exile proceedings.\n"+
            "Please make a bug report.\n");
        return 1;
    }

    if (objectp(ob = find_player(str)))
    {
        /* Reset the members tartan to contain clan colours. */
        present(OBJECT_ID, ob)->init();
        tell_object(ob, "You have been forgiven for your past agressions against " +
                      "your Clan.\n");
    }

    log_forgive(WRITE_NAME(TP)+ " forgave Kinslayer " +capitalize(str)+ " on " + ctime(time()) + "\n");
    /* Print messages */
    write("You forgive Kinslayer " + capitalize(str) + ".\n");
    return 1;
}



public int
study(string str)
{

    if (!strlen(str))
    {
        notify_fail("Study which scroll? " +
                  "<petition>, " +
                  "<accept>, " +
                  "<exile>, " +
                  "<leave>.\n");
        return 0;
    }

    if(!(IS_CLANCHIEF(TP)))
    {
        TP->catch_msg("Only the Clan Chief may read these scrolls\n");
        return 1;
    }

    switch(str)
    {
        case "petition":
            seteuid(getuid());
            clone_object(MORE_OBJ)->more(PETITION_LOG, 1);
            return 1;
            break;
        case "accept":
            seteuid(getuid());
            clone_object(MORE_OBJ)->more(ACCEPT_LOG, 1);
            return 1;
            break;
        case "leave":
            seteuid(getuid());
            clone_object(MORE_OBJ)->more(QUIT_LOG, 1);
            return 1;
            break;
        case "exile":
            seteuid(getuid());
            clone_object(MORE_OBJ)->more(EXILE_LOG, 1);
            return 1;
            break;
        default: 
            write("Study which scroll? <petition>, <accept> or <leave>.\n");
            return 1;
            break;
     }
     return 1;
}




/*
 * Give us some commands.
 */
public void
init()
{
    ::init();
    add_action(list, "list");
    add_action(do_exile, "exile");
    add_action(do_forgive, "forgive");
    add_action(study, "study");

}
