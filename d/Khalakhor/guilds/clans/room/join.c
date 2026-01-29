/**********************************************************************
 * - join.c                                                         - *
 * - Joining room for the Clans of Khalakhor                        - *
 * - Created by Damaris 05/2006                                     - *
 **********************************************************************/
#pragma strict_types

#include "../guild.h"
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>

inherit GUILD_ROOM;
inherit SCROLL;
#include "fireplace.c"

#define LOG_SIZE      25000
#define WRITE_NAME(o)   sprintf("%-11s", capitalize((o)->query_real_name()))

void
create_guild_room()
{
    string scroll;
    set_short("Private Room");
    set_long("   This simple but private room has a long table "+
    "pushed against the eastern wall. The southern wall has a "+
    "large tapestry that takes up most of it. A roaring fire "+
    "bathes the room in dim light along with some sturdy torches.\n");
    
    scroll = "Here you can do the following:\n" +
    /* Misleading..
    "<list surnames>  =  For a list of acceptable surnames.\n"+
    "<choose surname> =  To join the Clan.\n" +
    "<request tunic>  =  To obtain a new tunic.\n"+
    "<leave guild>    =  Leave the Clan.\n" +
    "<list>           =  List current guilds you are affiliated "+
    */
    "list surnames    =  For a list of acceptable surnames.\n"+
    "choose <surname> =  To join the Clan.\n" +
    "request tunic    =  To obtain a new tunic.\n"+
    "leave guild      =  Leave the Clan.\n" +
    "list             =  List current guilds you are affiliated "+
    "with.\n\n"+
    "Please note males will be known as Mac(surname) and females "+
    "Nic(Surname).\n"+
    "Examples: MacAlasdair, NicAlasdair\n"+
    "Or if lower case <a> Mac a' Ghobhainn, Nic a' Ghobhainn.\n\n"+
    "Only humans may claim their celtic heritage.\n";
    
    add_item("scroll",scroll);
    add_cmd_item("scroll", "read", scroll);
    add_item(({"room", "area"}), query_long);
    add_item(({"table"}),
    "The table is long with a scroll placed upon it.\n");    
    add_item(({"tapestry"}),
    "This tapestry is filled with many different celtic symbols, "+
    "which represents all the clans of Khalakhor.\n");
    add_item(({"symbols", "symbol"}),
    "There are many different celtic symbols sewn into the "+
    "tapestry.\n");
    
    add_item(({"fireplace"}),
    "The fireplace is quite large and set in the west wall.\n");
    add_item(({"fire"}),
    "The fire dances and bathes the room in dim light.\n");
    add_item(({"north"}),
    "An archway leads back to the hall.\n");
    add_item(({"south", "east", "southeast", "southwest", "northeast", "northwest"}),
    "A wall is in that direction.\n");
    add_item(({"west", "west wall"}),
    "A large fireplace is in that direction\n");
    add_item(({"east wall"}),
    "A large tapestry and table are against this wall.\n");
    add_item(({"south wall"}),
    "It is bare except for a couple of torches\n");
    add_item(({"north wall"}),
    "It has an archway in it.\n");
        
    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_LIGHT, 1);
    add_exit("entrance", "north");
    add_fail("west", "You walk right into the fireplace and get "+
    "burned!\n\nOuch! That hurts!\n");
    add_fail(({"north", "east", "southeast", "southwest", "northeast", "northwest"}),
    "A wall stops you.\n");    
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
    {
        /* Try to add the shadow to the player */
        switch (sh->add_race_shadow(TP))
        {
            case 1:
            /* We have successfully shadowed the player, 
             * so we're set */
            TP->clear_guild_stat(SS_RACE);
            write("You announce your lineage by picking "+
            "up the quill and placing your mark on the "+
            "scroll.\nA young lad enters handing you a "+
            "tunic then departs.\n");
            say(QCTNAME(TP) + " picks up the quill and "+
            "signs "+ HIS(TP) +" mark upon the scroll.\n"+
            "A young lad hands "+HIM(TP) +" a tunic then "+
            "departs.\n");
            if (!present(OBJECT_ID, TP))
            {
                clone_object(OBJECT)->move(TP);
            }
            write_file(LOG + "members",
            ctime(time()) + " " +
            capitalize(this_player()->query_real_name()) +
            " (age = " + (this_player()->query_age() / 43200) +
            ", avg = " + this_player()->query_average_stat() + 
            ") joined\n");
            return 1;
            break;
            case -4:
            /* The player has a race guild already, or one of
              * his existing guilds has blocked this one.
              */
             write("Your other guilds don't want you in "+
             "this one!\n");
             break;
             default:
             /* Some error in shadowing */
             write("OH NO! now you went and did it! You "+
             "broke the guild! Please mail: khalakhor and "+
             "report the error.\n");
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
    // Hmm...
    //string *name;
    string name, surname;
    int race;
    if (!strlen(str))
    {
        notify_fail(capitalize(query_verb()) + " what?\n");
        return 0;
    }
    if (TP->query_race_name() != "human")
    {
        write("You are not of the correct race for joining.\n");
        return 1;
    }
    // If this happens here, the next check will never work.
    /*if (TP->query_guild_member("race"))
    {
        write("You still belong to another racial guild.\n");
        return 1;
    }*/
    name = TP->query_real_name();
    // Wrong. Should check for member name
    //if (SERVER->query_member(str))
    if (SERVER->query_member(name))
    {
        write("You are already a member, find something "+
        "more productive to do.\n");
        return 1;
    }
    if (TP->query_guild_member("race"))
    {
        write("You still belong to another racial guild.\n");
        return 1;
    }
    // WRONG        Lavellan, 2011/02/25
    //if (!member_array(str, SURNAMES))
    foreach (string sn : SURNAMES)
    {
        if (lower_case(sn) == lower_case(str))
        {
            surname = sn;
            break;
        }
    }
    if (!surname)
    {
        write("That is not a valid surname choice, please try "+
        "again.\n");
        return 1;
    }
    //if (SERVER->add_member(name, str, race))
    if (SERVER->add_member(name, surname, race))
    {
        add_the_shadow();
        write("Welcome home.\n"+
        "For assistance type: <clhelp>\n");
    }
    else
    {
        write("You were not able to join, please make a bug "+
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
        write("You are not a member, how do you propose to "+
        "leave?\n");
        return 1;
    }
    if (!TP->leave_guild_race())
    {
        write("There has been an error, please contact "+
        "an aop member.\n");
    }
    else
    {
        say(QCTNAME(TP) + " leaves the " + GUILD_NAME + ".\n");
        write_file(LOG + "members",
        ctime(time()) + " " +
        capitalize(this_player()->query_real_name()) +
        " (age = " + (this_player()->query_age() / 43200) +
        ", avg = " + this_player()->query_average_stat() + 
        ") left\n");
    }
    return 1;
}

int
list(string str)
{
    if (strlen(str))
    {
        if (str == "surnames")
        {
            // Don't want "" in there!
            //return print_scroll(sort_array(SURNAMES),
            return print_scroll(sort_array(SURNAMES - ({ "" })),
            "These are the Celtic surnames within the " + GUILD_NAME);
        }
        return 0;
    }
    str = TP->list_major_guilds();
    
    if (str)
    write("You are a member of the following guilds.\n" + str);
    else
    write("You are not a member of any important guilds.\n");
    return 1;
}

/*
 * Replace tunic
 */
public int
request(string str)
{
    object tunic;
    if (str != "tunic")
    {
        NF("Request what? A tunic maybe?\n");
        return 0;
    }
    if (!IS_MEMBER(TP))
    {
        write("The " + GUILD_NAME + " do not grant requests "+
        "to non-members.\n");
        return 1;
    }
    if (objectp(tunic = present(OBJECT_ID, TP)) &&
    (!tunic->query_prop(OBJ_I_BROKEN)))
    {
        write("You don't need another tunic.\n");
        return 1;
    }
    if (tunic)
    tunic->remove_object();
    clone_object(OBJECT)->move(TP, 1);
    write("A young lad enters, hands you a new tunic then departs.\n");
    say (QCTNAME(TP) + " is given a new tunic by a young lad.\n");
    return 1;
}

void
init()
{
    ::init();
    init_fire();
    add_action(list, "list");
    add_action(add_me, "choose");
    add_action(leave, "leave");
    add_action(request, "request");
}
