/* File         : /d/Khalakhor/guilds/racial/clans/room/joinroom.c
 * Creator      : Tomas@Genesis
 * Date         : March 2001         
 * Purpose      : Join room for the human and dwarven racial guild:Clans of Khalakhor.
 * Related Files: ../include/guild.h, /d/Khalakhor/sys/defs.h, /d/Khalakhor/std/room
 * Comments     : My thanks to Lucius and Goldberry for helping 
 *                out on the difficult stuff. 
 */
#pragma strict_types

#include "../guild.h"
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>

inherit GUILD_ROOM;
inherit SCROLL;

object npc;

#define LOG_SIZE      25000
#define WRITE_NAME(o)   sprintf("%-11s", capitalize((o)->query_real_name()))

public void
reset_room()
{
    if (!npc)
    {
        reset_euid();
        npc = clone_object(NPC + "joinroom_npc");
        npc->arm_me();
        npc->move(TO);
        tell_room(TO, QCTNAME(npc) + "  arrives from the south.\n");
    }
}



void
create_guild_room()
{
    string plaque;

    set_short("Hall of Records");
    set_long("You have entered Khalakhor's Hall of Records. " +
             "The room is basically bare with the exception of " +
             "a large sign just in front of a " +
             "counter located on the far wall.\n");

    plaque = "Here you can do the following:\n " +
    "<list septs>              =  For a list of acceptable septs.\n " +
    "<choose sept>             =  To join your sept.\n " +
    "<list clans>              =  To list the clans of " + GUILD_NAME + ".\n "+
    "'list <clan name>'        =  To list members of a Clan.\n "+
    "<leave guild>             =  Leave the guild to deny your heritage.\n " +
    "<list>                    =  List current guilds you are affiliated "+
    "<request tartan>          =  Obtain a replacement tartan.\n ";

    add_item("plaque",plaque);
    add_item(("counter"), "A large yet barren dark wood grain counter. " +
             "You notice a bronze plaque with writing nailed securely " +
             "on the side of the counter.\n");


    add_cmd_item("plaque", "read", plaque);

    add_cmd_item("sign", "read",
             "Welcome to the Hall of Records. Within this room " +
             "you may select a Sept name thus joining the racial " +
             "guild: 'Clans of Khalakhor'. Please read the plaque on " +
             "the counter for instructions on how to join the Clans. " +
             "More information regarding the guild may be obtained " +
             "from the local Clansmen chapter located south, east and " +
             "north of here.\n");

    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_NO_ATTACK, 1);
    add_prop(ROOM_I_NO_MAGIC_ATTACK, 1);

    add_exit("/d/Khalakhor/se_speir/port/room/th_2", "north");

    reset_room();
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

    if (file_size(GLOG) > LOG_SIZE)
    {
        rename(GLOG, (GLOG + ".old"));
    }

    write_file(GLOG, text);
}


int
add_the_shadow()
{
    object sh;
    mixed why;

    /* Clone the shadow */
    setuid();
    seteuid(getuid());

    sh = clone_object(SHADOW);

    /* See if this member is acceptable */
    if (stringp(why = sh->acceptable_member(TP)))
    {
        write(why);
    }
    else
    {   /* Try to add the shadow to the player */
        switch (sh->add_race_shadow(TP))
        {
        case 1:
            /* We have successfully shadowed the player, so we're set */
            TP->clear_guild_stat(SS_RACE);
   
          write("You sign your mark on the scroll before you " +
                "thus becoming a member of the "+ GUILD_NAME + "!\n" + 
                "A Manach of the Sean-Rhian wanders in and hands " +
                "you a tartan, shakes your hand then leaves.\n");

            say(QCTNAME(TP) + " picks up the quill and signs the "+
              "scroll becoming a member of the " + GUILD_NAME +"! " +
            "Then rings a small bell\nA Manach of the Sean-Rhian " +
            "wanders in and hands " + HIM+ " a tartan " + 
            "shakes " +HIS+ " hand then promptly leaves.\n");

            if (!present(OBJECT_ID, TP))
            {
                clone_object(OBJECT)->move(TP);
            }

            log_file("members", capitalize(TP->query_real_name()) +
              " joined " + ctime(time()) + "\n");

            return 1;
            break;
        case -4:
            /* The player has a race guild already, or one of his existing
             * guilds has blocked this one.
             */ 
            write("Your other guilds don't want you in this one!\n");
            break;
        default:
            /* Some error in shadowing */
            write("OH NO! now you went and did it! You " +
              "broke the guild! Please mail: khalakhor and report the " +
              "error.\n");
            break;
        }
    }

    /* We couldn't shadow the player, so remove the shadow */
    sh->remove_shadow();
    return 1;
}

int
add_me(string str)
{
    string *arr;
    int race;

    if (!strlen(str))
    {
        notify_fail(capitalize(query_verb()) + " what?\n");
        return 0;
    }

    if (((TP->query_race() != "human") && (TP->query_race() != "dwarf")))
    {
        write("You are not of the correct race for joining.\n");
        return 1;
    }

    if (TP->query_guild_member("race"))
    {
        write("You still belong to another racial guild.\n");
        return 1;
    }

    if (TP->query_prop(LIVE_I_UNDEAD))

    {
        write("The " + GUILD_NAME + " appreciate life, not death.\n " +
          "Corpses need not apply.\n");
        return 1;
    }

    arr = explode(str, " ");
    str = TP->query_real_name();

    if (SERVER->query_member(str))
    {
        write("You are already a member, find something" +
          "more productive to do.\n");
        return 1;
    }

    if (member_array(arr[0], SURNAMES) == -1) 
    { 
        write("That is not a valid sept choice, please try again.\n");
        return 1;
    }

    if (SERVER->add_member(str, arr[0], race))
    {
        add_the_shadow();
        write("Welcome home.\n"+
          "For assistance type: <clhelp>\n");
    }
    else
    {
        write("You were not able to join, please make a bug " +
          "report.\n");
    }
    return 1;
}


int
leave(string str)
{
    if (str != "guild" &&  str != "the guild")
    {
        NF("Leave what? The guild??\n");
        return 0;
    }

    str = TP->query_real_name();

    if (!SERVER->query_member(str))
    {
        write("You are not a member, how do you propose to leave?\n");
        return 1;
    }

   if (IS_CLANCHIEF(TP))
    {
      if (!SERVER->remove_council_member(SERVER->query_clan(str)))
      {
        write("An error occured attempting to remove you as " +
              "Clan leader. Please make a bug report.\n");
        return 1;
      }
    }   

    if (!TP->leave_guild_race())
    {
        write("There has been an error, please contact the Liege " +
          "or an aop member.\n");
    }
    else
    {
        say(QCTNAME(TP) + " leaves the " + GUILD_NAME + ".\n");
        log_file("members", capitalize(TP->query_real_name()) +
            " left " + ctime(time()) + "\n");

    }
    return 1;
}



public int
list(string str)
{
    if (!strlen(str))
    {
        if (str = this_player()->list_major_guilds())
            write("You are a member of the following guilds.\n" + str);
        else
            write("You are not a member of any important guilds.\n");
        return 1;
    }

    if (strlen(str))
    {
        if (str == "septs")
        {
            return print_scroll(sort_array(SURNAMES),
                "These are the Sept names of the " + GUILD_NAME);
        }

      if (CAP(str) == "Clans")
      {
           return print_scroll(sort_array(m_indexes(CLANS)),
               "These are the available clans of the " + GUILD_NAME);
      }

       if (member_array(str, m_indexes(CLANS)) == -1)
       {
           write("That is not a clan of the " + GUILD_NAME + ".\n");
           return 1;
       }
      else
       {
           mixed tmp = ([]) + SERVER->query_clan(str);
           tmp = m_indexes(tmp) - ({ CLAN_CLRS });

           if (!sizeof(tmp))
           {
               write("The clan " + str + " is currently empty and in " +
                     "need of a claimant.\n");
               return 1;
           }

           tmp = sort_array(map(tmp, capitalize));
           return print_scroll(tmp, "The following members " +
               "belong to the Clan " + str);
       }
       return 0;
    }
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


void
init()
{
    ::init();
    add_action(list, "list");
    add_action(add_me, "choose");
    add_action(leave, "leave");
    add_action(request, "request");
}
