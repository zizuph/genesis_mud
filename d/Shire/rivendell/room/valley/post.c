/*  Post office in Imladris
 *  by Finwe, January 1998
 */
#include "local.h"
 
inherit HOUSE_IN_BASE;

#include <mail.h> 
 
void
create_house_room()
{
 
    set_short("The post office of Imladris");
    set_long("This is the post office of Imladris. It is used " +
        "when the citizens of the valley wish to communicate " +
        "with others in Eriador and to receive letters. " +
        "Fortunately, it is also open to travellers.\n");
   
    add_item(({"mailboxes","mailbox","box","boxes","larger box"}),
        "There are many boxes set against a wall. It here is that " +
        "the citizens of Imladris pick up their mail. A larger " +
        "box is set aside for visitors to retrieve their mail " +
        "others are just empty.\n");

    set_extra_window("@@window_position@@ set into the " +
        "east south walls.");
    add_item(({"east windows", "eastern windows", "east window",
            "eastern window"}),
        "@@east_down@@\n");
    add_item(({"south windows", "southern windows", "south window",
            "southern window"}),
        "@@south_down@@\n");

    num_of_windows=2;
   
   add_exit(VALLEY_DIR + "d_cor09", "north");
   
}
 
void
enter_inv(object ob, object from)
{
   object reader;
   object vote_room;
   string *masters;
 
   ::enter_inv(ob, from);
 
    if (!living(ob))
        return;
   if (present("mailreader", ob)) return;
   reader=clone_object("/secure/mail_reader");
   reader->move(ob, 1);
}

void
leave_inv(object ob, object to)
{
   object reader;
   
   ::leave_inv(ob, to);
   reader = present("mailreader", ob);
   if (reader && !ob->query_wiz_level())
   {
       reader->remove_object();
   }
}

/* Routine query_mail() by Mercade, copied here because of the obsolete
 * code that was in place.
 *
 * Function name: query_mail
 * Description  : Called to find out whether there is new mail for the player.
 * Arguments    : int silent - if true, don't give a message.
 * Returns      : int - mail status: 0 (no mail) 1 (read) 2 (new) 3 (unread).
 */
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
"    .______________.\n" +
"    |\\            /|\n" +
"    | \\          / |    There is " + new + " mail for you\n" +
"    |  \\________/  |    in the nearest post office.\n" +
"    |              |\n" +
"    +--------------+\n");
    }
    else
    {
        write("\nThere is mail for you in the nearest post office.\n\n");
    }

    return mail;
}
