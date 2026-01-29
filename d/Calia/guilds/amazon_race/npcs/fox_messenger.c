/*
 *    fox_messenger.c  
 *
 * A fox messenger.
 *
 * Baldacin@Genesis, Dec 2003
 *
 */

inherit "/w/baldacin/open/lib/messenger";
inherit "/std/act/action";

void
create_messenger()
{
    set_name("fox");
    set_adj("small");
    add_adj("red-speckled");
    set_short("small red-speckled fox");
    set_long("A small red-speckled fox that has a pointed muzzle, "+
      "erect ears, and a bushy tail. It can deliver a letter for "+
      "you if you 'send <name>'.\n");    
    set_delay(random(25) + 15);
    set_max_delivers(3);
    set_indoor_delivery(1);
    set_escape_message("escapes!");
    set_deliver_message(({"walks away eager to deliver your message",
      "walks up to you, delivering a messages from",
      "walks up, delivering a message to",
      "walks up to you, returning your message. It was unable to find "+gReceiver+".", }) );
}