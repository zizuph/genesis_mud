/*
 *  The post office of Minas Morgul. Slightly modified version of the
 *  Rangers post office.
 *
 *  Modification log:
 *  26-aug-1997, Olorin: Use query_domain_aliases defined in
 *                       GONDOR_MASTER to define the aliases.
 *  11-2003, Misery: Added query_mail for guild-specific new mail
 *				     message and a check for wizards.
 *				
 */
#pragma strict_types
#pragma save_binary

inherit "/d/Gondor/morgul/tower/tower";
inherit "/d/Genesis/lib/post";

#include <stdproperties.h>
#include <macros.h>
#include <mail.h>

#include "/d/Gondor/defs.h"
#include "/d/Gondor/common/guild2/lib/morgul_defs.h"
#include "/d/Gondor/morgul/tower/tower_defs.h"

#define MAILREADER "/secure/mail_reader"
#define MAILCHECKER "/secure/mail_checker"
#define MAILREADER_ID "_reader_"


/*
 * This list keeps all commands that are allowed by mortals in a post office.
 */
#define ALLOWED_COMMANDS ({ \
    "mail", "from", "autocc", "read", "mread", "malias", \
    "bug", "idea", "praise", "typo", \
    "sysbug", "sysidea", "syspraise", "systypo", \
    "alias", "unalias", "do", "resume", "save", "quit", \
    "commune", "reply", "help", "last", "date", "who", \
    "look", "l", "examine", "exa", "get", "put", \
    })

public int     do_hire(string str);
       string  poster_long();
       string  plaque_long();
       
public void
create_morgul_tower_room() 
{
   set_level(3);
   set_room_type("post office");
   set_short("The post office of the Tower of Black Sorcery");

   add_item(({"poster","big poster", "large poster"}), poster_long());
   add_cmd_item(({"poster","big poster", "large poster"}), "read", 
       poster_long());
   add_item(({"plaque","small plaque"}), plaque_long());
   add_cmd_item(({"plaque","small plaque"}), "read", plaque_long());

   add_exit(MAGES_DIR + "tower/tower_3c", "south", 0);

   add_prop(ROOM_I_LIGHT, 1);
}

string
long_desc()
{
   string long;

   long = "This is the post office of Minas Morgul. Here the mages of Minas "
   + "Morgul may send messages to their servants throughout the realms.\n"
   + "A large poster and small plaque are secured to the wall.\n"
   + "Inspect the mailreader for instructions.\n";
   return long;
}

void
init() 
{
	object rdr;
	
    ::init();
    
    add_action(do_hire, "hire",0);

    /* All commands here are silenced, except the normal commands. */
    if (!this_player()->query_wiz_level())
    {
        add_action(silent_room, "", 1);
    }

    
    rdr = clone_object(MAILREADER);
	   
	rdr->set_alias("guildmaster",({MORGUL_GUILDMASTER}));
	rdr->set_alias("nazgul", MORGUL_NAZGUL_MASTER->query_nazgul());
	rdr->set_alias("emissaries", MORGUL_EMISSARIES);
    rdr->move(this_player(),1);   
}

void
leave_inv(object ob, object to)
{
    object reader;

    ::leave_inv(ob);

    if (reader = present("mailread", ob))
    {
        if (!(ob->query_wiz_level()))
        {
            reader->remove_object();
        }
    }
}

void
mail_message(string new)
{
  write("\n"+
    "There is"+new+" mail for you in the post office of the \n"+
    "  Society of the Morgul Mages in Minas Morgul.\n\n");
}

public int
query_mail(int silent)
{
    int    mail = MAIL_CHECKER->query_mail();
    string new;

    if (mail == 0)
    {
        return 0;
    }
    if (silent)
    {
        return mail;
    }

    switch(mail)
    {
    case 2:
        new = "NEW";
        break;
    case 3:

        new = "UNREAD";
        break;

    default:
        new = "";
    }

    if (strlen(new))
    {
        write(
"        _________    \n" +
"       /        /_   \n" +
"       | Golm   |/\\    There is " + new + " mail for you\n" +
"       \\_________\\/    in the Tower postal chamber.\n\n");
    }
    else
    {
        write("\nThere is mail for you in the Tower postal chamber.\n\n");
    }
    return mail;
}

string
poster_long()
{
   return "If letters aren't quick enough to you, you may hire a raven "
    + "which will bring your message to other player very quickly. "
    + "The mages of Minas Morgul may use this service at no charge.\n";
}

string
plaque_long()
{
    return
        "The small plaque reads:\n"
      + "You may send mail directly to either 'nazgul', 'guildmaster' or 'emissaries'.\n";
}

public int
do_hire(string str) 
{
   object raven;

   if (TP->query_guild_name_occ() != GUILD_NAME &&
      (!TP->query_wiz_level() || TP->query_domain() != "Gondor") )
   {
      write("Only the mages of Minas Morgul may use this service.\n");
      return 1; 
   }

   if ((str != "raven") && (str != "black raven"))
   {
      NF("Hire what?\n");
      return 0;
   }
   raven = clone_object(GUILD_DIR + "obj/raven");
   raven->set_owner(TP);
   if(raven->move(TP))
   {
      NF("You cannot carry that much!\n");
      raven->remove_object();
      return 0;
   }
   write("You hire yourself a black raven.\n");
   say(QCTNAME(TP) + " hires " + TP->query_objective()
     + "self a black raven.\n");
   return 1;
}

/*
 * Function name: silent_room
 * Description  : This function catches all commands. Players will be allowed
 *                to use various commands related to mail, the game and the
 *                exits, but disallows all others.
 *                Mask parent to accept the allowed gondor po verbs.
 * Arguments    : string str - the command line argument.
 * Returns      : int 1/0 - player blocked/player not blocked.
 */
public int
silent_room(string str)
{
    string verb = query_verb();

    if (member_array(verb, ALLOWED_PO_VERBS) >= 0)
    {
        return 0;
    }

    /* Wizards are not silenced. */
    if (this_player()->query_wiz_level())
    {
        return 0;
    }

    /* Any of the allowed commands will be allowed ;-) */
    if (member_array(verb, ALLOWED_COMMANDS) >= 0)
    {
        return 0;
    }

    /* Player can always use an exit of the room. */
    if (member_array(verb, this_object()->query_exit_cmds()) >= 0)
    {
        return 0;
    }

    /* Any of the allowed commands will be allowed ;-) */
    if (member_array(verb, ALLOWED_MORGUL_EMOTIONS) >= 0)
    {
        return 0;
    }

    /* Block the command. */
    write("This chamber is a place of silence. Dishonour it at your own peril " +
          "as you may indeed draw the Dark Lords terrible attention upon yourself!\n");
    return 1;
}

public int
query_prevent_snoop()
{
    FIX_EUID;
    if (SECURITY->query_wiz_dom(this_interactive()->query_real_name()) ==
"Gondor")
    {
        return 0;
    }
    return ::query_prevent_snoop();
}
