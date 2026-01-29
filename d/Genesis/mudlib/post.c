/*
* /d/Gondor/common/dwarf_guild/post.c
*
* The post office of the Dwarven race guild.
*
* /Mercade, May 16 1996
*/

#pragma save_binary
#pragma strict_types

inherit "/std/room";

#include <files.h>
#include <mail.h>
#include <stdproperties.h>

void
create_room()
{
   set_short("the post office of the temporary start location");
   set_long("In this post office, you can read or write mail. To see " +
      "which commands you have, examine the mail reader or when " +
      "you are in mail reader mode, type \"?\".\n");
   
   add_prop(ROOM_I_INSIDE,          1);
   add_prop(ROOM_I_NO_ATTACK,       1);
   add_prop(ROOM_I_NO_MAGIC_ATTACK, 1);
   add_prop(ROOM_M_NO_TELEPORT,1);
   
   add_exit("/d/Genesis/mudlib/start", "lobby");
   
   setuid();
   seteuid(getuid());
}

void
init()
{
   ::init();
   
   if (!objectp(present(READER_ID, this_player())))
      {
      clone_object(MAIL_READER)->move(this_player(), 1);
   }
}

void
leave_inv(object obj, object to)
{
   ::leave_inv(obj, to);
   
   if (obj->query_wiz_level())
      {
      return;
   }
   
   present(READER_ID, obj)->remove_object();
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
      new = "NEW ";
      break;
      case 3:
      
      new = "UNREAD ";
      break;
      
      default:
      new = " ";
   }
   
   if (strlen(new))
      {
      write(
         "    .______________.\n" +
         "    |\\            /|\n" +
         "    | \\          / |    There is " + new + "mail for you in the post\n" +
         "    |  \\________/  |    office of the in the temorary start location.\n" +
         "    |              |\n" +
         "    +--------------+\n");
   }
   
   return mail;
}
