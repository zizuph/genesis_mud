/* Jakob 1995-02-18 */


#include "defs.h"
#include <stdproperties.h>
#include <macros.h>
#include <std.h>
#include "/d/Genesis/delivery/delivery.h"

inherit THWIL_BASE_ROOM;
inherit "/d/Genesis/delivery/office";

object board;

void
create_thwil_room()
{
   set_short("Thwil's board room");
   set_long("This is a spacious house used by the citizens of Thwil "+
      "to gather information, post notes and make complaints. "+
      "Many people are hurrying around here busy minding their own business. "+
      "You notice that this is the local delivery office in " +
      "Thwil, you can read more about it on a huge poster. " +
      "On the western wall some requests are flapping. \n");
   
   add_item(({"request", "requests"}), "They are urgent requests for help" +
      " posted by the inhabitants. \n");
   add_prop(ROOM_I_INSIDE, 1);
   add_item("wall","Some requests are posted on it.\n");
   set_office("Isle of the Wise, Thwil",5);
   add_item("poster","@@delivery_poster@@");
   add_cmd_item("poster","read","@@delivery_poster@@");
   add_content(HERBS + "red_maple");
   
   add_exit(THWIL+"t5","south",0);
   reset_room();
   INSIDE;
}

init()
{
   ::init();
   add_action("read", "read");
   init_office();
}

int
read(string str)
{
   notify_fail("Read what? \n");
   if ( (str!="request") && (str!="requests") )
      return 0;
   else
      { 
      write("(1) Help! Some of my sheep have run away, "+
         "if I go out and look for them the rest will "+
         "escape too. Please help me. O Takwa, 3rd Sheepfarmer "+
         "of Thwil. \n"+
         "Ps. I am at the Pasture, north of Thwil. Ds \n\n\n"+
         "");
/*
         "(2) ALL MY WEALTH, to the person that can kill "+
         "the white shark. You find me in Thwil, "+
         "ask after Negel. \n");
*/
      return 1;
   }
}

static void
create_board()
{  
  board = clone_object("/std/board");
  if (board)
    {
      board->set_board_name(THWIL + "board_save");
      board->set_num_notes(30);
      board->set_silent(1);
      board->set_show_lvl(1);
      board->set_remove_rank(WIZ_NORMAL);
      board->set_remove_str("Sorry, mortals are not allowed to "+
			    "remove notes. ");
      board->move(TO);
    }
  return 0;
}

void
reset_room()
{
  /* reset the office regularly */
  reset_office();
  if (!present("board", TO))
    create_board();
}
