inherit "/std/room";
#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include "/d/Gondor/elessar/lib/time.c"
object board;
string name;

create_room()
{
   set_short("The Rhovanion Meetingroom. \n");
   set_long(
         "Here the Rhovanion wizzes meet to discuss the future of the domain "+
         "Rhovanion, to get help with their coding, or to make announcements "+
         "of different kinds. The bulletin board may also be " +
         "used by other wizards of the Middle Earth domains, to encourage better "+
         "cooperation. An exit east leads to the idearoom of Rhovanion, southwest " +
	 "to the Middle Earth Idea Room.\n");
   
   add_exit("/d/Rhovanion/idearoom","east");
   add_exit("/d/Gondor/ME_ideas", "southwest");
   add_exit("/d/Gondor/workroom","gondor");
   add_exit("/d/Rhovanion/common/domain_entr","domains");
   add_exit("/d/Rhovanion/common/mirkwood/thranduil/throneroom","down",0,1);
   add_exit("/d/Rhovanion/milan/workroom","milan");
    add_exit("/d/Rhovanion/meeting", "meeting");
   
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
