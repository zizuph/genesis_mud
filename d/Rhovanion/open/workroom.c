inherit "/std/room";
#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include "/d/Gondor/elessar/lib/time.c"

/* Bugfixing stuff added 17 January 1994 by Farlong
 * in Emergency bug Fixing
 */
object board;
string name;

create_room()
{
   set_short("The Rhovanion Meetingroom. \n");
   set_long(break_string(
         "Here the Rhovanian wizzes meets to discuss the future of the domain "+
         "Rhovanion, to get help with their coding, or to make announcements,"+
         "of different kinds. The bulletin board my also be " +
         "used by other wizards of the Middle Earth domains, to encourage better "+
         "cooperation. an exit leads to the idearoom of Rhovanion. \n", 70));
   add_exit("/d/Rhovanion/domain_room","north");
   add_exit("/d/Rhovanion/idearoom","east");
   add_exit("/d/Rhovanion/daneel/workroom","daneel");
   if (!present("board",this_object())) {
      board = clone_object("/std/board");
      name = "/d/Rhovanion/common/boards";
      if (file_size(name) != -2) mkdir(name);
      board->set_board_name(name + "/domainboard");
      board->set_num_notes(30);
   board->move(this_object());
}
}

reset_room()
{
   tell_room(this_object(), "The room shivers.\n");
}
