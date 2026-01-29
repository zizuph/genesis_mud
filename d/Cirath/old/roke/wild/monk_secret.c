/*
 * monk_secret.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Cirath by Glindor, Jan 2000.
 */

/* IT IS VERY IMPORTANT THAT THIS FILE WORKS.
   IT MUST NEVER FAIL TO LOAD.
   If you change anything, make a copy and check that it loads before
   installing the new one. Always keep a working backup handy if anything
   goes wrong.

   /Glindor

Added a post office to the west, and commented out
the mailreader here--to be able to use the board
Also changed GM to Serpine
Amelia 4/5/98

Changed Serpine to Amelia
Changed 4 to 3 to resign -- Amelia April 26 1998
*/

#pragma save_binary
#pragma strict_types

inherit "/std/room.c";

#include "defs.h"
#include <stdproperties.h>

string
table()
{
    return "There is a list of available commands on the table:\n" +
            "banish        - banish someone from training\n" +
            "unbanish      - remove your banishment on someone\n" +
            "don't forget to 'mail gmaster' about banishments\n\n" +
            "list council  - list all councilmembers\n" +
            "list banished - list all banished players\n" +
            "list apply    - list all applications\n" +
            "accept <name> - accept an application\n" +
            "deny <name>   - deny an application\n" +
            "vote <start|yes|no|obsolete> <issue>\n" +
            "              issues: boot <name>, veto <name> , resign <name>\n" +
            "list vote     - list info about votes\n" +
            "add <someone> - add someone to the council\n" +
            "                use this command carefully and only when the\n" +
            "                entire council agrees about the new member\n" +
            "                don't forget to 'mail gmaster' about it\n" +
            "list books    - list books waiting to be added to the library\n" +
            "read <book>   - read the book <book>\n" +
            "toss <book>   - toss the undesired book <book> in the trashcan\n" +
            "add_book <book> - add the book <book> to the library\n" +
            "ktell <message>   -tell all Kahedans.  This should _only_ be used to" +
            " make official council announcements.  Abuse of this command will " +
            "result in immediate removal from the position.\n" +
            "\n" +
            "You also have the normal post office commands in here, with the addition\n" +
            "of the aliases 'council' and 'gmaster'.\n";
}

public void
create_room()
{
    set_short("the secret council room.");

    set_long("You are in the heart of the Kaheda guild. This place is\n" +
             "protected with strong magic and rumours say that only the mighty\n"
             +
             "immortal wizards of Roke and the members of the Kaheda council are\n"
             +
             "allowed to enter this room. There is a board for important\n" +
             "discussions and ideas on the western wall. In the middle of the\n" +
             "floor there is a large round table with chairs around them.\n" +
             "There is an important looking tablet here.\n");

    INSIDE;

    add_prop(ROOM_M_NO_ATTACK,
             "You can not do that while on Sacred ground.\n");
    add_item("tablet", "This a stone tablet on which someone" +
             " has begun to etch the basic rules that a councillor" +
             " is required to follow.  It looks as if the tablet is" +
             " not yet finished.  You should read what is there.\n");
    add_cmd_item("tablet", "read",
                 " -----------------------------------------------------\n" +
                 "|             Tablet of Conduct                 |\n" +
                 "| A councillor must treat fellow councillors and|\n" +
                 "| guild memebers with tact and respect.  And    |\n" +
                 "| must enforce current policies, and abide by   |\n" +
                 "| proceedures that have been outlined in the    |\n" +
                 "| main library and in the Council handbook...   |\n" +
                 "|                                               |\n" +
                 "|                                               |\n" +
                 "|                                               |\n" +
                 "|                                               |\n" +
                 " ------------------------------------------------\n");
    add_item("table", "@@table");
    add_exit("monk_council", "north");
    add_exit("monk_council_post", "west");
}
