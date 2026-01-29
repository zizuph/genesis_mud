/*
 *  The Hobbiton post-office
 */

inherit "/std/room";

#include "defs.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"

#define	MAILCHECKER	"/d/Genesis/postmaster/mail_checker"

void
create_room()
{
   set_short("The post office of Hobbiton");
   set_long("@@longfunc");

   add_exit(STAND_DIR + "bw_road6","south");
   add_exit(STAND_DIR + "p_house","west");

   add_prop(ROOM_I_INSIDE, 1);  /* This is a real room */
}

string
longfunc()
{
   string long;

   long =
       "You are now standing in the Hobbiton post office. Many hobbits are\n"
     + "working here to deliver mail to everyone in the world. From here\n"
     + "you can send mail to your relatives all over the world. West is a\n"
     + "small opening, leading to a small shed that serves as pigeon-house.\n"
     + "Available commands are:\n"
     + "read             Read from the mailbox.\n"
     + "mail <name>      Mail to player 'name'.\n"
     + "from             List all headers.\n";
   return long;
}

void
enter_inv(object ob, object from)
{
   if (!present("mailread",ob))
      clone_object("/d/Genesis/postmaster/mail_reader")->move(ob);
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
   int mail;
   string new;

   seteuid(getuid());
   mail = MAILCHECKER->query_mail();
   if (!mail)
      return 0;

   if (silent)
      return 1;

   new = "";

   if (mail>1)
      new = " NEW";

   write("\nThere is" + new + " mail for you in the nearest post office.\n\n");
   return 1;
}

