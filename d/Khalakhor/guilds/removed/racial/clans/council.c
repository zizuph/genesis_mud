/* Clans of Khalakhor Join a Clan room
 * Tomas
 */
#pragma strict_types

#include "guild.h"
#include <filter_funs.h>
#include <macros.h>
#include <stdproperties.h>

inherit GUILD_ROOM;
inherit SCROLL;

/* Used to store petitioner info. */
static mapping petition = ([]);

/*
 * The room itself.
 */
public void
create_guild_room()
{
    setuid(); seteuid(getuid());

    set_short("Council Room");
    set_long("Clan Council Test room.\n");

  add_cmd_item("plaque", "read", "<list clans>    "+
    "=  To list the clans of Khalakhor.\n"+
    "'list <clan name>' = To list members of a clan.\n"+
    "'accept <player>'  =  To accept someone in a clan.\n"+
    "'exile <player>'   = Remove someone from the clan.\n" +
    "'forgive <player>' = Forgive player thus removing Kinslayer.\n");


  add_prop(ROOM_I_INSIDE, 1);
  add_prop(ROOM_I_NO_ATTACK, 1);
  add_prop(ROOM_I_NO_MAGIC_ATTACK, 1);  

  add_exit("joinhouse", "down");
}


/*
 * Accept a petitioner into your Household.
 */
public int
accept_member(string str)
{
    string clan, name = this_player()->query_real_name();
    object ob;

    /* Not even in a clan, get lost schmuck */
    if ((IS_LEADER(LEADER) != "MacVay"))
    {
       write("Only the Chief may accept new members into the tribe.\n");
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
        write("Nobody is petitioning your Clan.\n");
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


    /* Ooops, no can join, need squash buggie */
    if (!SERVER->add_to_clan(str, clan, name))
    {
        write("An error has prevented your accepting petitioners.\n"+
            "Please make a bug report.\n");
        return 1;
    }

    /* Reset the members tartan to contain clan colours. */
    (OBJECT_ID, ob)->init();

    /* Print messages */
    write("you accept " +ob+ " into the Clan.\n");
    return 1;
}



public int
do_exile(string str)
{
    string clan, 
           LEADER = this_player()->query_real_name();
    object ob;

    /* Not even in a clan, get lost schmuck */
    if ((IS_LEADER(LEADER) != "MacVay"))
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
    if (SERVER->query_clan(str) != "MacVay")
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

    /* Print messages */
    write("You banish " + capitalize(str) + " from the Clan.\n");
    return 1;
}





/*
 * Give us some commands.
 */
public void
init()
{
    ::init();

    add_action(do_exile, "exile");
    add_action(accept_member, "accept");

}
