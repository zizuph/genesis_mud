/*
 *    message.c  
 *
 * This is the message service, (PO).
 *
 * Baldacin@Genesis, Dec 2003   
 *
 */

inherit "/std/room.c";
#include "../defs.h"
#include <stdproperties.h>
#include <macros.h>
#include <money.h>

#define MAILREADER  "/secure/mail_reader"
#define PIGEON_COST    30 /*Copper coins.*/

void
create_room()
{
    set_short("The message service");
    set_long("You are in a small platform used as mail delivery room. "+
      "The air smells of old pigeon droppings. There are cages of "+
      "pigeons and other small animals everywhere, ready to deliver "+
      "your mail. A sign hangs on a wall here.\n");
    
    add_cmd_item(({"sign","small sign"}),
        "read","@@read_sign");
    add_item(({"cage","cages"}), "The cages contains various animals, "+
      "all ready to deliver your messages.\n");
    add_exit(ROOMS + "platform","east");

}

int
read_sign()
{     
    write(" -------------------------------------- \n"+
          "|                                      |\n"+
          "| The message service                  |\n"+
          "| Here you can handle all your mail.   |\n"+
          "| You can send, read and even 'hire'   |\n"+
          "| a pigeon to take with you.           |\n"+
          "|                                      |\n"+
          " -------------------------------------- \n");
    return 1;
}

int
hire_fox(string str)
{
    if (str != "pigeon" && str != "a pigeon") 
    {
        notify_fail("Hire what? a pigeon?\n");
        return 0;
    }

    if (MONEY_ADD(TP, -PIGEON_COST))
    {
    	setuid();
        seteuid(getuid());
        clone_object("/d/Genesis/obj/pigeon")->move(TP, 1);
        TP->catch_tell("You hire a pigeon messenger.\n");
    }
   else 
      TP->catch_tell("You don't have enough money!\n");

   return 1;
}
 
void
leave_inv(object ob, mixed to)
{
    object reader;
    ::leave_inv(ob, to);
 
    reader = present("mailread", ob);
    if (reader)
        reader->remove_object();
}

void
init()
{
    object reader;
    ::init();
 
    reader = clone_object(MAILREADER);
    if (!reader)
    {
        write("No mailreader is available at this time.\n");
        return;
    }
    reader->move(TP);
    
    add_action(hire_fox, "hire");
    add_action(hire_fox, "buy");
}