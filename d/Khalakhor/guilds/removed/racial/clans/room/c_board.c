/* The Eil-Galaith common board room
* Created by Damaris 09/Y2K
*/
#pragma strict_types

#include "../guild.h"
#include <stdproperties.h>

inherit GUILD_ROOM;

/* Prototype function */
public void load_board();

void
create_guild_room()
{

    set_short("Eil-Galaith Common board room");
    set_long("This is a small cozy room that has parchment papers "+
      "stacked neatly on a marble countertop, with quils placed next to "+
      "them. On the upper edge of the countertop is an inkwell that is "+
      "quite full of ink. There also is a common board. Immortals as "+
      "well as mortals read this board. There is a large notice that is "+
      "in front of the board.\n");
      
   add_cmd_item(({"board"}),(({"get","take","burn","climb"})),"You fail to do so and should be ashamed for even trying.\n");
    add_exit("board.c", "down");

    load_board();

    add_item(("notice"),
      "The notice reads:\n" +
      "Only immortals can write on this board.\nIt is to help in "+
      "the communication between immortals and mortals "+
      "concerning this realm.\n");
     

      
    add_item(({"quil", "quils"}),
       "There are quils placed on a the marble countertop.\n");
    
     add_item(({"ink", "inkwell"}),
       "The inwell is sitting on the marble countertop and is quite full "+
       "of dark ink.\n");
    
     add_item(({"countertop", "marble countertop"}),
       "The marble countertop is placed here is attatched firmly to the wall "+
       "and parchment papers, quils, and an inkwell have been placed on it.\n");
   
     add_item(({"parchment", "parchment papers", "papers", "paper"}),
       "The parchment papers have been stacked neatly on the marble "+
       "countertop for posting on the board.\n");
       
    add_cmd_item("notice", "read", "The notice reads:\n" +
      "Only immortals can write on this board.\nIt is to help in "+
      "the communication between immortals and mortals "+
      "concerning this realm.\n");          
     add_cmd_item(({"board", "parchment", "countertop", "inkwell", "quils"}),(({"get","take","burn","climb"})),"You fail to do so and should be ashamed for even trying.\n");

}

public void
load_board()
{
    object bb;

    seteuid(getuid(this_object()));
    bb = clone_object("/d/Genesis/obj/board");
    bb->move(this_object());

    return;
}

