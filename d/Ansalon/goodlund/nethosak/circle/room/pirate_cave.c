/*
 * File Name        : pirate_cave.c
 * By               : Elmore.
 * Inspiration from : -
 * Date             : Nov. 2000.
 * Description      : This is the joinroom of the pirates.
 *                    It has three methods. Become(), Vote()
 *                    and Leave().
 *
 */

#pragma strict_types

inherit "/std/room";

#include <stdproperties.h>
#include <formulas.h>
#include <macros.h>
#include <cmdparse.h>
#include "../local.h"
#include "/d/Ansalon/common/defs.h"

void
create_room()
{
    set_short("Guild joinroom");
    set_long("@@long_descr");

    add_exit("underground_cave", "west");
    
    add_item("sign","It's a sign with words on it.\n");
    add_cmd_item(({"sign","words"}),"read",
		 "The sign reads:\n" +
                 "+-------------------------------------------------+\n" +
                 "|           The Pirates of the Bloodsea           |\n" +
                 "|           ===========================           |\n" +
                 "|  Welcome to the pirate society, this is the     |\n" +
                 "|  place that people seek if they want fame and   |\n" +
                 "|  fortune. In order to join, you must be         |\n" +
                 "|  accepted by the Legendary Pirate Lord, "+GUILD_LEADER+".   |\n" +
                 "|  If he finds you worthy you'll be invited to    |\n" +
                 "|  become a pirate.                               |\n" +
                 "|  You can also leave this society if you want    |\n" +
                 "|  to try and return to a normal life.            |\n" +
                 "|                                                 |\n" +
                 "+-------------------------------------------------+\n");
}

string
long_descr()
{ 
   return "You are standing in a huge underground cave, beneth "+
          "the isle of Mithas. The cave must have been made "+
          "by some sort of erosion of the stones that form "+
          "the bedrock of the isle. The black rock walls "+
          "are drenched with water and the smell of the fresh "+
          "seawater and wet soil dominate this place. This "+
          "might be a good place to hide ourself or something. "+
          "A only exit out of here is to the west.\n"+
          "A sign has been placed here against the wall.\n";
}

int
vote(string str)
{
    object ob,*obj;

    if(TP->query_name() == GUILD_LEADER ||
       TP->query_name() == GUILD_WIZARD)
    {   
        if(strlen(str) == 0)
        {
                notify_fail("Vote who into the pirate society?\n");
                return 0;
        }

        if(strlen(str))
        {
            if(!sizeof(obj = PARSE_THIS(str, "[the] %l")))
            {
                notify_fail("Vote who into the pirate society?\n");
                return 0;
            }

            ob = obj[0];
        }

        TP->catch_msg("You accept " +QTNAME(ob)+ " as being " +
          "worthy to become a true Pirate of the Bloodsea.\n");
        TP->tell_watcher(QTNAME(TP)+ " accepts " +QTNAME(ob)+
          "as being worthy to become a true Pirate of the Bloodsea!\n", ob);
        ob->catch_msg("You have been found worthy as to become " +
          "a true Pirate of the Bloodsea!\n");
        ob->add_prop(I_CAN_BECOME_PIRATE, 1);
        return 1;
    }
    write("Only the Legendary Pirate Lord may vote someone "+
          "into the pirate society.\n");
    return 1;
}

int
become(string str)
{
    object sh;
    mixed why;
    if(strlen(str) == 0)
    {
        notify_fail("Become what? A pirate?\n");
        return 0;
    }

    if (L(str) == "pirate" || L(str) == "a pirate" ||
        L(str) == "pirate of the bloodsea" ||
        L(str) == "the pirates" ||
        L(str) == "pirates" ||
        L(str) == "a pirate of the bloodsea")
    {
        if (!TP->query_prop(I_CAN_BECOME_PIRATE))
        {
            write("You have not been voted to join this pirate "+
                  "society. Seek out the Legendary Pirate Lord "+
                  "and he'll decide if he finds you worthy.\n");
                return 1;
        }

        /* Clone the shadow */
    
        setuid();
        seteuid(getuid());
    
        sh = clone_object(GUILD_SHADOW);
    
        /* See if this member is acceptable */
        if (stringp(why = sh->acceptable_member(this_player())))
        {
            write(why);
        }
        else
        {
            /* Try to add the shadow to the player */
    	    switch (sh->add_lay_shadow(this_player()))
    	    {
    	      case 1:
    	        /* We have successfully shadowed the player, so we're set */
                find_living(GUILD_WIZARD)->catch_msg(TP->query_name() + " JOINED THE PIRATES!\n");
                write("Welcome pirate! May all your raids be succesful.\n");
    	        return 1;
        
    	      case -4:
    	        /* The player has an lay guild already, or one of his existing
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
}

int
leave(string str)
{
    if (L(str) == "pirate" || L(str) == "a pirate" ||
        L(str) == "pirate of the bloodsea" ||
        L(str) == "the pirates" ||
        L(str) == "pirates" ||
        L(str) == "a pirate of the bloodsea")
    {
    if (!this_player()->query_guild_member(GUILD_NAME))
    {
        write("But you aren't a member of this guild!\n");
        return 1;
    }
    this_player()->remove_lay_member();
    write("You decide to leave the pirates of the Bloodsea. Farewell, for now.\n");
    say(QCTNAME(TP) + " has left the pirates of the Bloodsea.\n");
    }
    return 1;
}

void
init()
{
    ::init();
    ADA("become");
    ADA("leave");
    ADA("vote");
}
