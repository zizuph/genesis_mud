/**********************************************************************
 * - join.c                                                         - *
 * - Temple room to join Thanar race guild                          - *
 * - Created by Damaris@Genesis 3/2004                              - *
 * - New Standrad file for new area for guild. Typos fixed.         - *
 * - by Mirandus@Genesis 01/2018                                    - *
 **********************************************************************/

#pragma strict_types

#include "../guild.h"
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include "/d/Kalad/defs.h"

inherit THANAR_STD_ROOM;
inherit SCROLL;

#define LOG_SIZE      25000
#define WRITE_NAME(o)   sprintf("%-11s", capitalize((o)->query_real_name()))

object obj;

/*
 * Function name: block_exit()
 * Description  : Allows us to block exit if we need.
 */
public int
block_exit()
{
    write("You may not go this way, at this time.\n");
    return 1;
}

/*
 * Function name: members_only()
 * Description  : Lets only members of the guild or wizards pass.
 */
public int
members_only()
{
    if (IS_MEMBER(this_player()) || this_player()->query_wiz_level())

    {
    /* Is a member, pass through as normal */

    return 0;
    }

    write("A magical force prevents you from entering.\nYou are not a "+
      "Thanarian human!\n");
    return 1;
}
string
query_plaque()
{
    return("\n\t __________________________________________________\n"+
     "\t/ \\                                                \\\n"+
     "\t\\_/________________________________________________/\n"+
     "\t|                                                  |\n"+
     "\t|                                                  |\n"+
     "\t|                  Basin Of Life                   |\n"+
     "\t|                                                  |\n"+
     "\t|  It is here you can pledge your life to Thanar.  |\n"+
     "\t|                                                  |\n"+
     "\t|  <list surnames>    = For a list of surnames.    |\n"+ 
     "\t|  <choose 'surname'> = To join guild              |\n"+
     "\t|  <change 'surname'> = To change your surname     |\n"+
     "\t|  <leave guild>      = To leave guild             |\n"+
     "\t|  <request necklace> = To request a new necklace  |\n"+
     "\t|  <list>             = List current guilds you    |\n"+
     "\t|                       are affiliated with.       |\n"+
     "\t|                                                  |\n"+
     "\t|__________________________________________________|\n"+
     "\t/ \\                                                \\\n"+
     "\t\\_/________________________________________________/\n"+
     "\n"); 
      
}

/*
 * Function name: create_std_thanar()
 * Description  : Creates the room from standard room file
 */
void
create_std_thanar()
{

   
   set_short("Grand Temple Vestibule");
   set_long("This vestibule is quite grand and is constructed "+
     "with a marvellous marble. The floor and walls are almost "+
     "seamless giving a strange impression that any human hand "+
     "did not make this room, instead is divinely created. "+
     "Stone pillars guard the sides of the archways to the "+
     "four corners. A large marble basin is erected in the "+
     "centre of the room with a golden plaque at its base.\n");
   add_item(({ "vestibule", "room", "area", "chamber"}), query_long);
   add_item(({ "archways", "archway", "arch", "arches" }),
      "\nFlanked by a pair of stone pillars, one of the archways leads off "+
      "to the north while another leads south. The remaining two archways "+
      "are flanked by somewhat smaller pillars and lead to the northeast and "+
      "northwest respectively. For some reason, this arrangement looks "+
      "natural.\n");
   add_item(({ "basin", "marble basin"}),
      "The large black and white marble basin is erected in "+
      "the center of the room within it dark red stains, which "+
      "appears to be blood that has been dripped into it. There "+
      "is a plaque at its base.\n");
   add_item(({ "plaque", "golden plaque", "gold plaque"}),query_plaque);
   add_cmd_item("plaque", "read", query_plaque);
   add_exit("coven", "east", members_only);
   add_exit("sanctuary", "north", members_only);
   add_exit("hall1", "northwest", members_only);
   add_exit("hall2", "northeast", members_only);
   add_exit("entrance", "south");

//   clone_object(THANAR(book))->move(this_object());
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

/*
 * Function name: add_shadow()
 * Description  : Moves the shadow to the player and runs checks
 */
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

        write("You pick up a knife that mysteriously appears "+
        "within the basin.\n\n"+
        "You slice the palm of your hand and hold it over the basin "+
        "watching your blood drip onto it's surface!\n\n"+
        "An Apparition of Thanar appears before you saying: "+
        "Welcome my child.\n\n");

        say(QCTNAME(TP) + " picks up a knife that mysteriously "+
        "appears and slices the palm of "+ HIS(TP) +" hand and "+
        "holds it over the basin.\n");

        if (!present(OBJECT_ID, TP))
        {
        clone_object(OBJECT)->move(TP);
        }

        log_file("thanar_members", capitalize(TP->query_real_name()) +
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
          "broke the guild! Please mail: raumdor and report the " +
          "error.\n");
        break;
    }
    }

    /* We couldn't shadow the player, so remove the shadow */
    sh->remove_shadow();
    return 1;
}

/*
 * Function name: add_me()
 * Description  : Adds the player to the server file.
 */
int
add_me(string str)
{
    string *arr;
    int race;
    string surname;
    
    if (!strlen(str))
    {
    notify_fail(capitalize(query_verb()) + " what?\n");
    return 0;
    }

    if(TP->query_race() != "human" || -1 == member_array(TP->query_race_name()
        , VALID_SUBRACES))
    {
    write("You are not permitted to join this order! GET OUT!\n");
    return 1;
    }

    if (TP->query_guild_member("race"))
    {
    write("You still belong to another racial guild.\n");
    return 1;
    }

    arr = explode(str, " ");
    surname = capitalize(lower_case(arr[0]));
    str = TP->query_real_name();

    if (SERVER->query_member(str))
    {
    write("You are already a member, find something" +
      "more productive to do.\n");
    return 1;
    }

    if (member_array(surname, SURNAMES) == -1)
    {
    write("That is not a valid surname choice, please try again.\n");
    return 1;
    }

    if (SERVER->add_member(str, surname, race))
    {
    add_the_shadow();
    write("Welcome home.\n"+
      "For assistance type: <thhelp>\n");
    }
    else
    {
    write("You were not able to join, please make a bug " +
      "report.\n");
    }
    return 1;
}

/*
 * Function name: change()
 * Description  : Lets the player choose a different surname
 */
int
change(string str)
{
    string who = TP->query_real_name();
    string new = capitalize(lower_case(str));
    mixed data;
            
    if (!strlen(str))
    {
        notify_fail(capitalize(query_verb()) + " what?\n");
        return 0;
    } 
       
    if(TP->query_race() != "human" || -1 == member_array(TP->query_race_name()
        , VALID_SUBRACES))
    {
        write("You are not permitted to do that! GET OUT!\n");
        return 1;
    }

    if (!(data = SERVER->query_member(who)))
    {
        write("You are not a member yet, you have to <choose surname> " +
              "to join our elite society.\n");
        return 1;
    }

    if (member_array(new, SURNAMES) == -1)
    {
        write("That is not a valid surname choice, please try again.\n");
        return 1;
    }

    if (data[FNAME] == new)
    {
        write("Did not you state you want to CHANGE your surname?\n");
        return 1;
    }

    if(!SERVER->change_surname(who, new))
    {
        write("Something gone wrong, please make a bug report.\n");
    return 1;
    } 

    TP->update_thanar_shadow();

    write("You have successfully changed your surname, " +
          C(who) + " " + new + ".\n");

    return 1;
}

/*
 * Function name: leave()
 * Description  : Removes the player from the guild
 */
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

    if (!TP->leave_guild_race())
    {
    write("There has been an error, please contact the Liege " +
      "or an aop member.\n");
    }
    else
    {
    say(QCTNAME(TP) + " leaves the " + GUILD_NAME + ".\n");
    log_file("thanar_members", capitalize(TP->query_real_name()) +
        " left " + ctime(time()) + "\n");

    }
    return 1;
}

/*
 * Function name: list()
 * Description  : Lists possible surnames for joining
 */
int
list(string str)
{
    if (strlen(str))
    {
    if (str == "surnames")
    {
        return print_scroll(sort_array(SURNAMES),
        "These are the surnames of " + GUILD_NAME);
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
 * Function name: request()
 * Description  : replaces the guild item should it be lost
 */
public int
request(string str)
{
    object necklace;

    if (str != "necklace")
    {
    NF("Request what? A necklace maybe?\n");
    return 0;
    }

    if (!IS_MEMBER(TP))
    {
    write("The " + GUILD_NAME + " do not grant requests to " +
      "non-believers.\n");
    return 1;
    }

    if (objectp(necklace = present(OBJECT_ID, TP)) &&
      (!necklace->query_prop(OBJ_I_BROKEN)))
    {
    write("You don't need another necklace.\n");
    return 1;
    }

    if (necklace)
    necklace->remove_object();

    clone_object(OBJECT)->move(TP, 1);
    write("A young human enters, hands you a new necklace, "+
      "then leaves.\n");
    say (QCTNAME(TP) + " is given a new necklace "+
      "by a young human.\n");
    return 1;
}

/*
 * Function name: init()
 * Description  : Initializes the commands.
 */
void
init()
{
    ::init();
    add_action(list, "list");
    add_action(add_me, "choose");
    add_action(change, "change");
    add_action(leave, "leave");
    add_action(request, "request");

}
