/*
 * /d/Krynn/sancrist/nevermind/guild/conference.c
 * 
 * Creator: Shadowlynx
 * Date: June/97
 *
 * Modified in part from planner.c by Dajala
 *
 * to be used for discussion of future guild ideas
 * and announcements of any new additions or changes
 * to the inventors guild. Bulletin board present.
 */

#include "/d/Krynn/common/defs.h"
#include <macros.h>

#include "guild.h"

inherit "/d/Krynn/std/room";

void
create_room()
{
    object board;

    set_short("Conference room");

    set_long("A whirlwind of activity greets you when entering" +
      " the conference room. Piles of papers are stacked all over" +
      " the long table occupying the center of the room. You" +
      " see several gnomes seated around the table diligently" +
      " writing down their ideas for improvements to the" +
      " guild. The floor is strewn with forgotten papers" +
      " which have been knocked off the table by the" +
      " absentminded gnomes or blown off the top of a stack by" +
      " a gust of wind caused from the flurry of activity." +
      " There is a bulletin board on the far east wall right" +
      " behind the Head Tinkerer's chair which is used to" +
      " record and keep track of the multitude of ideas for" +
      " improvement to the Inventors guild.\n");

    add_exit(GGUILD + "planner", "west", 0);

    INSIDE;
    LIGHT;

    add_item(({"paper","papers"}),"Stacks of papers are piled" +
      " haphazardly across the long conference table appearing" +
      " to have no order. Occassionally a piece of paper from" +
      " the top of a stack will be blown to the floor by a" +
      " gust of wind as a gnome scurries by.\n");
    add_item(({"stack","stacks"}),"Stacks of papers are piled" +
      " haphazardly across the long conference table appearing" +
      " to have no order.\n");
    add_item(({"table","conference table"}),"A long rectangular" +
      " conference table occupies the center of the room with" +
      " chairs at each end and all around both sides. It is" +
      " easy to spot the Head Tinkerer's chair at the far" +
      " east end of the table as it is decorated with" +
      " plush red velvet cushions and outlined in gold" +
      " filigree. Behind the chair is a bulletin board.\n");
    add_item(({"chair","chairs","head tinkerer's chair"}),
      "At the far east end of the long rectangular conference" +
      " table sits the Head Tinkerer's chair. It is decorated" +
      " in plush red velvet cushions and gold filigree. Other" +
      " chairs line both sides of the table and the other end.\n");
    add_item(({"floor","ground"}),"The floor is strewn with" +
      " forgotten papers that have fallen from the table.\n");

    seteuid(getuid(TO));
    board = clone_object(GOBJ + "noteboard");
    board->set_board_name("/d/Krynn/sancrist/nevermind/guild/log/board_data");
    board->set_long("This is the private inventor's guild board.\n" +
      "\n" +
      "Use it to discuss ideas for improvements, modifications or" +
      " changes to the guild that you would like to see" +
      " in the future. This board can also be used for any" +
      " general announcements that might be of interest to" +
      " fellow gnomes and inventors. The guild mistress will" +
      " post any announcements of changes or modifications" +
      " to the guild on this board as well. All guild" +
      " related questions or concerns should be posted" +
      " here and not on the board in the start area.\n" +
      "You are welcome to post as frequently as you wish.\n\n");
    board->set_silent(0);
    board->set_keep_discarded(1);
    board->set_num_notes(30);
    board->set_remove_str("Sorry, only the guildmaster may" +
      " remove the notes.\n");
    board->set_short("Board for Guild Ideas");
    board->move(TO,1);
}

