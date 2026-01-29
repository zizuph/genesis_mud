/*
 *  The Hobbiton post-office
 *
 * Added newbie poster
 * TAPAKAH, 25/05/2005
 */

#pragma save_binary

inherit "/std/room";

#include "defs.h"
#include <stdproperties.h>
#include <macros.h>
#include <files.h>

void
create_room()
{
   add_prop(ROOM_S_MAP_FILE, "hobbiton.txt");
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
     + "small opening, leading to a small shed that serves as pigeon-house.\n";
   return long;
}

void
enter_inv(object ob, object from)
{
  ::enter_inv(ob, from);
   setuid();
   seteuid(getuid());
   if (!present("mailread",ob))
       clone_object(MAIL_READER)->move(ob);
}

void
leave_inv(object ob, object to)
{
   object mr;

   ::leave_inv(ob, to);
   if (!ob->query_wiz_level())
      if (mr = present("mailread", ob))
         mr->remove_object();
}

public int
query_mail(int silent)
{
   int mail;
   string new;

   seteuid(getuid());
   mail = MAIL_CHECKER->query_mail();
   if (!mail)
      return 0;

   if (silent)
      return 1;

    switch(mail)
    {
    case 2:
        new = " NEW";
        break;
    case 3:

        new = " UNREAD";
        break;

    default:
        new = "";
    }

   write("\nThere is" + new + " mail for you in the nearest post office.\n\n");
   return 1;
}
