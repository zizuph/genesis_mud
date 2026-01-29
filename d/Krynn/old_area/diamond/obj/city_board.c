/* Created by Aridor 01/31/94 
 * Modified by Kentari for Diamond City - April 1997
 * but with limited writing access :)  */

inherit "/std/board";

#define CITY_BOARD_DIR     "/d/Krynn/diamond/log/"

#include "/d/Krynn/common/defs.h"
#include <macros.h>
#include <std.h>

mapping writers = ([ ]);

void restore_me();

void
create_board()
{
  set_board_name(CITY_BOARD_DIR + "board_data");
  set_num_notes(25);
  set_silent(0);
  set_show_lvl(0);
  set_remove_rank(WIZ_LORD);
  set_remove_str("Sorry, Only a Lord may remove the notes.\n");

  set_alarm(1.0, 0.0, restore_me);
}

void
restore_me()
{
  restore_object(CITY_BOARD_DIR + "city_board_writers");
  msg_num = sizeof(query_headers());
}


int
block_writer()
{
  if (TP->query_wiz_level())
    return 0;
  if (member_array(TP->query_real_name(), m_values(writers)) != -1)
    {
      write("There is already a note with your signature on this " +
	    "board. You cannot write another note I'm afraid.\n");
      return 1;
    }
  return 0;
}

void
post_note_hook(string head)
{
    string fname;
    ::post_note_hook(head);
    if (!TP->query_wiz_level())
    {
	fname = query_headers()[sizeof(query_headers())-1][1];
	writers += ([ fname:(TP->query_real_name()) ]);
	save_object(CITY_BOARD_DIR + "city_board_writers");
    }
}

int
block_discard(string file)
{
  writers = m_delete(writers, file);
  save_object(CITY_BOARD_DIR + "city_board_writers");
  return 0;
}
