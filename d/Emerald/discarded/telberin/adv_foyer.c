/*
 * The foyer in the adv. guild of Telberin
 * By Finwe 
 * January 1997
 */
 
inherit "/std/room";
 
#include "default.h"
#include "/d/Emerald/defs.h"
#include <stdproperties.h>
 
create_room()
{
 
    object board;
    if (!objectp( board) )
    {
        board = clone_object("/std/board");
        board->set_num_notes(30);
        board->set_board_name( THIS_DIR + "board_data");
        board->move(this_object());
    }
 
 
 
    set_short("The foyer of the Adventurers Guild of Telberin");
    set_long("   This room is well visited by the people of " +
        "Telberin. They come here to post notes of interest for " +
        "all to read on the boards. One board has been set aside " +
        "for visitors, like yourself, to post notes of interest, " +
        "too. The King and Queen have allowed an entrance to the " +
        "Common board to be placed here. North of here is where " +
        "travellers may go to learn and improve their skills.\n\n");
 
    add_item(({"down", "floor"}),
        "The floor is made of polished marble. You can see " +
        "yourself in its reflection.\n");
    add_item("boards",
        "Several boards of interest are in here, most of them " +
        "unreadable to you. One board has been set aside for " +
        "travellers. You may read the notes on it.\n");
    add_item(({"walls", "wall"}),
        "The walls are made of marble blocks. They are smooth " +
        "and you can't see any seams.\n");
    add_item(({"up", "ceiling"}),
        "The ceiling is dominated by a large skylight, filling " +
        "the room with light.\n"); 
    add_item("skylight",
        "It fills the ceiling and is made from cut glass. It " +
        "lets in light and fills the room with light.\n");
    add_item(({"glass", "cut glass"}),
        "The panes of glass are expertly cut and fitted into " +
        "the skylight\n");
         
    add_prop(ROOM_I_INSIDE, 1);
 
    add_exit(THIS_DIR + "adv_guild", "north") ;
    add_exit(AVENUE_DIR + "ave20",   "out") ;
    add_exit("common", "common", 0);
 
//    ob = clone_object(OBJ_DIR+"telberinboard") ;
//    ob->move(TO) ;
}
