/*
*   The Hin Warriors own post-office.
*/

#pragma save_binary

inherit "/d/Shire/room";

#include "/sys/stdproperties.h"
#include "hobbit.h"
#include "/d/Shire/common/defs.h"

#define MAILCHECKER   "/secure/mail_checker"
#define MAILREADER    "/secure/mail_reader"
#define MAILREADER_ID "_reader_"

void
create_room()
{
   set_short("Adventuresome Hobbit Post Office");
   set_long("@@my_long");
   
   add_item(({"mailboxes","mailbox","hole","holes","little holes"}),
      break_string("The little holes are mailboxes. In some are letters, "
         + "others are just empty.\n",70));

   add_item(({"hobbit", "petite hobbit", "bobby-sue"}),
            "She look fairly pretty for a hobbit. This is the mail "+
            "clerk that handles your mail, so be nice to her.\n");
  
   add_exit(HOBGLD_DIR + "start","east");
   
   add_prop(ROOM_I_INSIDE, 1);  /* This is a real room */
}



string
my_long()
 {
   string long;
   long = "A rough wet room stands here. A faint trickling sound "+
            "can be heard coming from somewhere above. This is where "+
            "hobbits come to peacefully read their mail. A small "+
            "sign is hanging from a beam in the ceiling. Just behind "+
            "a very small desk is a petite hobbit, with curly red hair.\n"
         + MAILREADER->long_description(); 
           return long;
}

void
enter_inv(object ob, object from)
{
   FIXEUID;
   ::enter_inv(ob, from);
   if (from == this_object()) return;
   if (present("mailreader", ob)) return;
   clone_object(MAILREADER)->move(ob);
}

void
leave_inv(object ob, object to)
{
   object reader;
   
   ::leave_inv(ob, to);
   if (to == this_object()) return;
   reader = present("mailreader", ob);
   if (reader) reader->remove_object();

}

/*
 * Function name: query_mail
 * Description  : This function is called when a player logs on to give him
 *                a message about the (new) mail in his mailbox at home.
 * Arguments    : silent - Set to 1 to not tell the player about the mail.
 * Returns      : 1/0    - mail or no mail.
 */
public int
query_mail(int silent)
{
    int    mail = MAILCHECKER->query_mail();
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
        write("\n**********************************************\n"+
             "There is " + new + " mail for you in the post\n" +
             "office of the " + HOBBIT_RACE_GUILD_NAME + ".\n"+
             "**********************************************\n");
    }

    else
    {
        write("\nThere is mail for you in the post office of the " +
            HOBBIT_RACE_GUILD_NAME + ".\n\n");
    }

    return mail;
}
