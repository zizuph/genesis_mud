/* The Tyr Post Office: Based on the Ciubori Post Office. */
#pragma save_binary

inherit "/d/Cirath/std/room";
inherit "/d/Genesis/lib/post";
#include "defs.h"
 
void
init_psion_specials()
{
    call_other(MANAGER, "awaken");
}

void create_room()
{
    set_short("the message center");
    set_long("The Tyr Message Center is little more than a single clay "+
             "room with some fast erdlus out back to deliver messages. "+
             "A stone counter with writing carved into it serves the "+
             "almost equally stony clerk as a place to rest his head, "+
             "and a window looks outside.\n");
 
    add_item("clerk", "It is not wise to disturb a sleeping dwarf.\n");
    add_item(({"counter", "writing"}), "The counter looks uncomfortable, "+
             "but the carved writing is quite readable.\n");
    add_item("window", "Some erdlus (200 pound featherless birds) stare "+
             "back at you from their pen.\n");
    add_cmd_item(({"counter", "writing"}), "read", "It seems to be "+
             "instructions for the use of the Center:\n"+
                "   read #           Read your mail.\n"+
                "   mail <player>    Mail to another player by 'name'.\n"+
                "   from             List all incoming mail by header.\n");

    add_exit(TYR+"caravan/rd_cw_04.c", "south", 0, 1);
    INSIDE
    init_psion_specials();
}
 
init()
{
  ::init();
  post_init();
}
 
leave_inv(ob,to)
{
  ::leave_inv(ob,to);
  post_leave_inv(ob,to);
}
 
void
mail_message(string new)
{
    write("=== A pressing voice in your mind tells you that there is a"+new+
           "\n=== message for you in the post office of Tyr.\n\n");
}

void
add_aliases(object tyrreader)
{
    tyrreader->set_long("This bizarre magical device was designed to "+
        "get around the rules against literacy that exist in Tyr. It "+
        "allows messages to be stored from one mind and then later fed "+
        "into that of another. A victory of the psionicists of Athas!\n"+
        "\nThe commands that you can use are:\n"+
        "from [new]             list all [unread] headers in your mailbox.\n"+
        "mail <name[s]>         mail something to one or more players.\n"+
        "resend <name[s]>       mail the last message again to other people.\n"+
        "read <number>          read message with number <number>.\n"+
        "                       without argument you enter mail reading mode.\n"+
        "mread <number>         read message with number <number> using more.\n"+
        "malias                 list your mailreader aliases. You have none.\n"+
        "malias <alias> <names> add mailreader alias <alias> with <names>.\n"+
        "malias remove <alias>  remove mailreader alias <alias>.\n"+
        "autocc [on / off]      set/unset automatic cc to yourself.\n"+
        "                       Current setting: Automatical cc: off.\n\n");
}