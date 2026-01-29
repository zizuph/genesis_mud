/**********************************************************************
 * - cboard.c                                                       - *
 * - The common board room                                          - *
 * - Created by Damaris@Genesis 3/2004                              - *
 * - New Standrad file for new area for guild. Typos fixed.         - *
 * - by Mirandus@Genesis 01/2018                                    - *
 **********************************************************************/

#pragma strict_types

#include "../guild.h"
#include <stdproperties.h>

inherit THANAR_STD_ROOM; 

/* Prototype function */
public void
load_board();

/*
 * Function name: create_std_thanar()
 * Description  : Creates the room from standard room file
 */
void
create_std_thanar()
{

    set_short("Common board room");
    set_long("This is a small cosy room that has parchment papers "+
      "stacked neatly on a marble counter top, with quills placed next to "+
      "them. On the upper edge of the counter top is an inkwell that is "+
      "quite full of ink. There also is a common board. Immortals as "+
      "well as mortals read this board. There is a large notice that is "+
      "in front of the board.\n");
    add_item(({"room", "area"}), query_long);
      
   add_cmd_item(({"board"}),(({"get","take","burn","climb"})),
   "You fail to do so and should be ashamed for even trying.\n");
   
    add_item(("notice"),
      "The notice reads:\n" +
      "Only immortals can write on this board.\nIt is to help in "+
      "the communication between immortals and mortals "+
      "concerning this realm.\n");
     
    add_item(({"quill", "quills"}),
       "There are quills placed on a the marble counter top.\n");
    
     add_item(({"ink", "inkwell"}),
       "The inwell is sitting on the marble counter top and is quite full "+
       "of dark ink.\n");
    
     add_item(({"counter top", "marble counter top"}),
       "The marble counter top is placed here is attached firmly to the wall "+
       "and parchment papers, quills, and an inkwell have been placed on it.\n");
   
     add_item(({"parchment", "parchment papers", "papers", "paper"}),
       "The parchment papers have been stacked neatly on the marble "+
       "counter top for posting on the board.\n");
       
    add_cmd_item("notice", "read", "The notice reads:\n" +
      "Only immortals can write on this board.\nIt is to help in "+
      "the communication between immortals and mortals "+
      "concerning this realm.\n");          
     add_cmd_item(({"board", "parchment", "counter top", "inkwell", "quills"}),
     (({"get","take","burn","climb"})),
     "You fail to do so and should be ashamed for even trying.\n");
     
     add_exit("board", "south");
     load_board();

}

/*
 * Function name: load_board()
 * Description  : Loads the board to the room.
 */
public void
load_board()
{
    object bb;

    seteuid(getuid(this_object()));
    bb = clone_object("/d/Genesis/obj/board");
    bb->move(this_object());

    return;
}

