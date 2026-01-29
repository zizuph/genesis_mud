/* room coded by Elizabeth Cook/Mouse, February 1997 */

inherit "std/room";
#include <stdproperties.h> 
#include "../../mouse.h"    

void create_room()  {
     object board;
     set_short("Town Hall");
     set_long("   This is the Festiwycke Town Hall, where residents of "+ 
          "the area gather to discuss matters of importance to the general "+
          "community. The room is rather sparse and large. A long table "+
          "stands at one end of the room, with several chairs behind it. "+
          "Rows of benches fill the space in front of it. The walls are "+
          "bare, except for a bulletin board which hangs next to the "+
          "door.\n");
     add_prop(ROOM_I_INSIDE,1);
     add_prop(ROOM_I_LIGHT,2);
     board = clone_object("/std/board")->move(TO);
     board->set_short("Festiwycke Town Bulletin Board");
     board->set_long("This board is provided for the discussion of "+
          "anything of interest to those who visit Festiwycke. Feel "+
          "free to post anything that is not in violation of the general "+
          "laws of the realm.\n");
     board->set_board_name(ROOT+"village/board");
     add_exit(ROOT+"village/rooms/V9","east");
        
}

