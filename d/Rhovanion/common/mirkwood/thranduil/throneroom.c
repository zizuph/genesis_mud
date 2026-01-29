inherit "/d/Rhovanion/lib/caves.c";
#include "/d/Rhovanion/defs.h"
#include "def.h"
#include "/sys/macros.h"

object board;
string name;

create_cave()
{
  set_rock_type("soluble limestone");
  set_cave_name("Thranduil's Caverns");
  set_region("northern");
  set_cave("Mirkwood");
  set_cave_type(2);
  
  set_long("This is the throneroom of Thranduil, the king of northern "
	   + "Mirkwood. Here you see a board with which you can exchange "
	   + "ideas and knowledge about Rhovanion with other adventurers."
	   + " You can also give your suggestions and praise to the wizards "
	   + "of the Rhovanion domain. In the middle of the room you see "
	   + "a stair leading up to a blue curtain, "
	   + "and to the northeast you see some great halls and two "
	   + "corridors lead to the south and east. To the north you see "
	   + "a small room."
	   + " \n");
  
  add_item(({"stair","stairs"}),
	   "These stairs leads to the kings personal chambers. \n");
  add_item("throne","The throne is inlaid with gold and jewels. \n");
  add_item("throneroom","The throneroom is quite large. \n");
  add_item("curtain","The curtain seems to be made from pure silk.\n");
  add_item(({"hall","halls"}),"You can't see well from here.\n");
  
  add_exit("/d/Rhovanion/workroom","up","@@sblock");
  add_exit(THIS_DIR + "cave21","northeast",0,1);
  add_exit(THIS_DIR + "cave20","east",0,1);
  add_exit(THIS_DIR + "cave3","south",0,1);
  add_exit(THIS_DIR + "questroom","north",0,1);
  
  if (!present("board",this_object())) 
    {
      board = clone_object("/std/board");
      name = "/d/Rhovanion/common/boards";
      if (file_size(name) != -2) mkdir(name);
      board->set_board_name(name + "/thranduil");
      board->set_remove_lvl(10);
      board->set_remove_str("You are not able to delete any messages. \n\n");
      board->set_num_notes(30);
      board->move(this_object());
    }
}

int
sblock()
{
  if (TP->query_wiz_level())
    {
      write ("\nYou sense the magic at work all around you as you step"+
	     "through the door.\n\n");
      return 0;
    }
  write("A strong force field prevents you from going that way.\n");
  return 1;
}
