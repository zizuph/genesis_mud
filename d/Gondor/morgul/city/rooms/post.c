/*
 * /d/Gondor/morgul/city/rooms/post.c
 *
 *  The Minas Morgul post office
 *
 *  Modified to inherit /d/Genesis/lib/post.c
 *  - Olorin, October 1994
 *  18-Jan-1999, Gorboth: Use query_domain_aliases defined in
 *                        GONDOR_MASTER to define the aliases.
 */
#pragma strict_types

inherit "/d/Gondor/morgul/city/morgul";
inherit "/lib/trade";
inherit "/d/Genesis/lib/post";

#include <files.h>
#include <stdproperties.h>
#include <macros.h>
#include <money.h>

#include "/d/Gondor/defs.h"
#include "/d/Gondor/guilds/morgulmage/morgulmage.h"
#include "/d/Gondor/common/guild2/newnpc/qbits.h"


#define PIGEON_VALUE	12
#define NUM		sizeof(MONEY_TYPES)

#define MAILREADER	"/secure/mail_reader"
#define MAILREADER_ID	"_reader_"

string  exa_poster();
string  plaque_long();


/*
 * This list keeps all commands that are allowed by mortals in a post office.
 */
#define ALLOWED_COMMANDS ({ \
    "mail", "from", "autocc", "read", "mread", "malias", \
    "bug", "idea", "praise", "typo", \
    "sysbug", "sysidea", "syspraise", "systypo", \
    "alias", "unalias", "do", "resume", "save", "quit", \
    "commune", "reply", "help", "last", "date", "who", \
    "look", "l", "examine", "exa", "put", "get", \
    })

public void
create_morgul_room()
{
   set_extraline("The office has clearly seen better days. It looks as " +
     "if it was built to house the postal service for a large and busy " +
     "city, but now it is derelict and dirt is covering the floor. But " +
     "nevertheless, from here you can still mail everyone in the world. " +
     "On one wall is an ancient poster with instructions. Next to it " +
     "is a small plaque with a list of the mail aliases available here. " +
     "The only exit is to the west, where you can see a dark and " +
     "narrow street.");
   set_road(9);
   set_short_desc("in the the post office of Minas Morgul");

   add_item(({"instructions", "poster","ancient poster"}), exa_poster());
   add_cmd_item(({"instructions", "poster","ancient poster"}), "read", exa_poster());
   add_item(({"plaque","small plaque"}), plaque_long());
   add_cmd_item(({"plaque","small plaque"}), "read", plaque_long());

   add_exit(MORGUL_DIR + "city/darkstr4","west", 0);

   add_prop(ROOM_I_LIGHT, 1);
   add_prop(ROOM_I_INSIDE,1);

   config_default_trade();  /* Set up the trading system */
                         /* Copper Silver Gold Platinum  */
   set_money_give_out(   ({ 10000,    32,   2,    1 })); /* Max_pay   */
   set_money_give_reduce(({     0,     4,   2,    1 })); /* Threshold */
   // necessary in case a player wants to hire a pigeon paying with a pc
   set_money_give_max(2000);
}

void
post_init()
{
    object tp = this_player();
    object reader;

    // If the player does not already have a mailreader (ie he is not a
    // wizard), then we clone a reader.
    if (!objectp(reader = present(MAILREADER_ID, tp)))
    {
	seteuid(getuid());
	reader = clone_object(MAILREADER);

	// We set the alias to the reader and move it into the player.
	add_aliases(reader);
        reader->set_long(break_string(
	    "This powerful magical device was probably made by the "
	  + "Dark Lord himself.", 74)
	  + "\n\nThe commands that you can use are:\n\n"
	  + "from [new]               list all [unread] headers in your mailbox.\n"
	  + "mail <name[s]>           mail something to one or more players.\n" 
	  + "resend <name[s]>         mail the last message again to other people.\n" 
	  + "read <number>            read message with number <number>.\n" 
	  + "                         without argument you enter mail reading mode.\n"
	  + "mread <number>           read message with number <number> using more.\n" 
	  + "malias                   list your mailreader aliases.\n"
	  + "malias <alias> <names>   add mailreader alias <alias> with <names>.\n" 
	  + "malias remove <alias>    remove mailreader alias <alias>.\n" 
	  + "autocc [on / off]        set/unset automatical cc to yourself.\n");
	reader->move(tp, 1);
    }
}

void
init() 
{
    ::init();
    add_action("do_hire","hire",0);
    add_action("read_poster","read",0);

    /* All commands here are silenced, except the normal commands. */
    if (!this_player()->query_wiz_level())
    {
        add_action(silent_room, "", 1);
    }

    post_init();
}

void
mail_message(string new)
{
  write("\n"+
    "There is"+new+" mail for you in the post office in Minas Morgul,\n"+
    "  east of Ithilien in Gondor.\n\n");
}

string
exa_poster()
{
    string desc;

    desc = 
      "\nYou read the ancient poster hanging on the wall: \n\n" +
      "Available commands are:\n" +
      "hire pigeon      Hire a carrier pigeon.\n" +
      "  We will charge "+PIGEON_VALUE+" cc for this service.\n\n" +
      get_std_use();
         
    return desc;
}

string
plaque_long()
{
    return
        "On the plaque, you can read the mail aliases defined here:\n"
      + "\tResponsible - the wizards responsible for Minas Morgul\n"
      + "\tNazgul      - the Nazgul of the Society of Morgul Mages\n";
}

int
read_poster(string str) 
{
  if(!str || (str != "instructions" && str != "poster" && 
    str != "ancient poster"))
  {
    NF("Read what?\n");
    return 0;
  }
  write(exa_poster());
  return 1;
}

int
do_hire(string str) 
{
   object pigeon;
   string item_name, pay_type, get_type, str1, coin_pay_text, coin_get_text;
   int *money_arr;

   if(!str)
   {
     NF("Hire what?\n");
     return 0;
   }

   TP->reveal_me(1);
 /*   Check if the player defines what they want to pay with
  *   and what you would like in return.
  */
   if (sscanf(str, "%s for %s and get %s",item_name,pay_type,get_type) != 3)
   {
      get_type = "";
    /* Hmmm... Maybe they only wish to pay with a certain type */
      if (sscanf(str, "%s for %s", item_name, pay_type) != 2)
      {
         pay_type = "";
         item_name = str;
      }
   }

   if (!(item_name == "pigeon" || item_name == "carrier pigeon"))
   {
      NF("Hire what?\n");
      return 0;
   }

   if (sizeof(money_arr = pay(PIGEON_VALUE, TP, pay_type, 0, 0, get_type)) == 1)
   {
      if (money_arr[0] == 1)
      {
         tell_room(this_object(), BSN(
            "The post master says: You cannot afford a carrier pigeon "
          + "with only those coins, "
          + TP->query_race_name() + "."));
         return 1;
      }
      if (money_arr[0] == 2)
      {
         tell_room(this_object(), BSN(
            "The post master says: You have no " + pay_type + " coins on you, "
          + TP->query_race_name() + "."));
         return 1;
      }
      else
      {
         tell_room(this_object(), BSN(
            "The post master says: You cannot afford a carrier pigeon, "
          + TP->query_race_name() + "."));
         return 1;
      }
   }

 /* Okay, the pigeon is paid for, now give it to the player */
   pigeon = clone_object("/d/Genesis/obj/pigeon");
   if(pigeon->move(TP))
   {
      write("You cannot carry that much!\n");
      pigeon->remove_object();
      return 1;
   }

   coin_pay_text = text(exclude_array(money_arr, NUM, NUM*2-1));
   coin_get_text = text(exclude_array(money_arr, 0, NUM-1));

   write("You pay " +coin_pay_text+ " and hire yourself a pigeon.\n");
   if (coin_get_text)
      write("You get " + coin_get_text + " back from the small gnome.\n");
   say(QCTNAME(TP) + " hires " + TP->query_objective()
     + "self a carrier pigeon.\n");
   return 1;
}

void
leave_inv(object ob, object to)
{
    ::leave_inv(ob,to);
    post_leave_inv(ob,to);
}

void
add_aliases(object rdr)
{
    rdr->set_alias("nazgul", MORGUL_MASTER->query_nazgul_names());
    rdr->set_alias("responsible",
		   GONDOR_MASTER->query_domain_aliases(MORGUL_S_GUILD_NAME));
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
    write("The post office is a place of silence. Dishonour it at your own peril " +
          "as you may indeed draw the Dark Lord's terrible attention upon yourself!\n");
    return 1;
}

public int
query_prevent_snoop()
{
    FIX_EUID;
    if (SECURITY->query_wiz_dom(this_interactive()->query_real_name())
        == "Gondor")
    {
        return 0;
    }
    return ::query_prevent_snoop();
}
