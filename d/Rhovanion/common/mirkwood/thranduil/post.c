/*
 *  The post-office in Thranduil's Caverns.
 */

inherit "/d/Rhovanion/lib/room";

#include "def.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"

#define MAILREADER "/secure/mail_reader"
#define MAILCHECKER "secure/mail_checker"

string messages;
int new_mail;

void
  create_room()
{
  set_short("The post office of Thranduil's Caverns");
  set_long("@@longfunc");
  
  set_noshow_obvious(1);
  add_exit(THIS_DIR + "cave18","south",0,1);
  
  add_prop(ROOM_I_INSIDE, 1);  /* This is a real room */
}

string
  longfunc()
{
  string long;
  
  long =
    "You are now standing in post office of Thranduil's Caverns. Many\n"
      + "elves are working here to deliver mail to everyone in the world.\n"
	+ "From here you can send mail to your relatives all over the world.\n"
	  + "Available commands are:\n"
	    + "read             Read from the mailbox.\n"
	      + "mail <name>      Mail to player 'name'.\n"
		+ "from             List all headers.\n";
	  
  return long;
}


init()
{
  object reader;
  ::init();
  reader = clone_object(MAILREADER);
  if (!reader)
    {
      write("No mailreader is available at this time. \n");
      return;
    }
  reader->move(this_player());
}

void
  enter_inv(object ob, object from)
{
  if (!present("mailread",ob))
    clone_object("/d/Genesis/obj/mail_reader")->move(ob);
}

void
  leave_inv(object ob, object to)
{
  object mr;
  
  if (mr = present("mailread",ob))
    mr->remove_object();
}

query_mail(int silent)
{
  string name;
  string new;
  
  name = lower_case(this_player()->query_name());
  
  if (!restore_object("/d/Genesis/post_dir/"+name) || messages == "")
    return 0;
  
  if (silent)
    return 1;
  
  new = "";
  
  if (new_mail)
    new = " NEW";
  
  write("\nThere is" + new + " mail for you in the nearest post office.\n\n");
  return 1;
}
