/* Riders of Last Join Room
 * Tomas  -- April 2000 
*/

#pragma strict_types
#pragma save_binary

#include "/d/Terel/include/Terel.h"
#include "../include/guild.h"
#include <ss_types.h>
#include <macros.h>
#include <ss_types.h>
#include <cmdparse.h>
#include <composite.h>

inherit STDROOM;



/*
int
north()
{
     if (COUNCIL_MEMBER(TP->query_real_name()))
         return 0;

     if (TP->query_wiz_level())
         return 0;

     write("A strong forcefield blocks the way.\n");
     return 1;
}
*/

void
create_room()
{
    string book;

    set_short("Riders of Last Recruiting Office");
    set_long("You are standing in the recruiting office of " +
        "The Riders of Last. The Riders of Last are looking " +
        "for hearty individuals that are interested in protecting " +
        "Terel and its current way of life. A couple of wooden "+
        "benches line the walls " +
        "of the office. There is a large oak table standing " +
        "in the middle of the room.\n");

    book = "Here you can <sign name> to join or <leave guild> the Riders of " +
           "Last guild. " +
           "Members may also use <request sash> to replace their sashes. " +
           "You may also <list> to see what guilds you are already " +
           "a part of. Currently the guild tax is: " + GUILD_TAX  +
           "% however, this is subject to change later on.\n";
add_item("book",book);

    add_item(({"wooden benches","benches","bench"}),
       "The long wooden benches line up along " +
       "the walls.\n");
    add_item(({"large oak table","large table","table",
       "oak table"}),"You notice a large open book resting " +
       "on the table. Next to the book is a writing quill and " +
       "inkwell.\n");

    add_cmd_item("book", "read", book);
    add_cmd_item(({"inkwell","quill", "book"}), 
                 ({"take", "get"}), "Try <sign name> instead.\n");

    add_prop(ROOM_I_NO_ATTACK, 1);
    add_prop(ROOM_I_NO_MAGIC_ATTACK, 1);
}


int
sign(string str)
{
    object sh;
    mixed why;

    if (str != "name")
    {
       NF("Sign what, you name maybe?\n");
       return 0;
    }

    /* Clone the shadow */

    setuid();
    seteuid(getuid());

    sh = clone_object(RIDER_SHADOW);

    /* See if this member is acceptable */
    if (stringp(why = sh->acceptable_member(TP)))
    {
        write(why);
    }
    else
    {

        /* Try to add the shadow to the player */
        switch (sh->add_lay_shadow(TP))
      {
            case 1:
                /* We have successfully shadowed the player, so we're set */
                TP->clear_guild_stat(8);
   
                write("You sign your name, thus joining the " +
                   "Riders of Last.\n Type: <rlhelp index>\n");
               write("A young stablekeep sunders in, " +
                  "hands you a horsemans sash then promptly leaves.\n");
                say(QCTNAME(TP) + " joins the Riders of Last Guild.\n");
        
                log_file("members", 
                    capitalize(TP->query_real_name()) +
                    " joined " + ctime(time()) + "\n");
        

                return 1;
    
            case -4:
                /* The player has a race guild already, or one of his existing
                 * guilds has blocked this one.
                 */ 
                write("Your other guilds don't want you in this one!\n");
                break;
    
            default:
                /* Some error in shadowing */
                write("An error has prevented you from joining.\n");
                break;
        }
    }

    /* We couldn't shadow the player, so remove the shadow */
    sh->remove_shadow();
    return 1;
}

int
leave(string str)
{
    if (str != "guild")
    {
        NF("Leave what? The guild??\n");
        return 0;
    }
    
    if (!IS_MEMBER(TP))
    {
        write("You aren't a member!\n");
        return 1;
    }

    TP->leave_riders();
    return 1;
}

int
list(string str)
{
    if (strlen(str))
    {
        return 0;
    }

    str = TP->list_major_guilds();
    if (str)
        write("You are a member of the following guilds.\n" + str);
    else
        write("You are not a member of any important guilds.\n");
    
    return 1;
}

nomask static int
request(string str)
{
   object sash;

   if ((str != "sash"))
   {
      NF("Request what? a sash maybe?\n");
      return 0;
   }
 
   if (!IS_MEMBER(TP))
   {
      write("The Riders of Last do not grant requests to " +
         "non-members.\n");
      return 1;
   }
   
   if (str == "sash")
   {
      if (objectp(sash = present(RIDER_GUILD_EMBLEM, TP)) &&
         (!sash->query_prop(OBJ_I_BROKEN)))
      {
         write("You don't need another sash.\n");
         return 1;
      }
  
      setuid();
      seteuid(getuid());
      
      sash->remove_object();
      clone_object(RIDER_GUILD_EMBLEM)->move(TP, 1);
      write("A young stablekeep enters, hands you a new sash, " +
         "then leaves.\n");
      say (QCTNAME(TP) + " is given a new sash by a young stablekeep.\n");
 
      return 1;
   }
}


void
init()
{
    ::init();
    add_action(sign, "sign");
    add_action(leave, "leave");
    add_action(list, "list");
    add_action(request, "request");
}
