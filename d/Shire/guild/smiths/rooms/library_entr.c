/*
 * The entrance to the smiths Library. Players can't check out 
 * or read books here. That's done in the library proper by 
 * older smiths.
 * -- Finwe, November, 2001
 */

#pragma save_binary;

inherit "/d/Shire/room";
//inherit "/lib/library";
//inherit "/d/Gondor/open/room_chairs/room_chairs";

#include "smiths.h"
#include "/d/Shire/sys/defs.h"
#include <macros.h>
#include <stdproperties.h>

//#define BOOK_ID         (MASTER + "_library_book")

void
create_room()
{
    set_short("Library entrance");
    set_long("This is the entrance to the Smiths Guild library. " +
        "It is a large room with a counter that runs the width " +
        "of the room. Books, records, parchments, and tomes " +
        "behind the counter line the walls. They may not be " +
        "checked out here in the entrance. A private entrance " +
        "leads west with a sign next to it.\n");
        
    add_item(({"books", "tomes", "parchments", "records"}),
        "They are bound between two harden leather covers and " +
        "held then together with two iron hinges. Some look " +
        "well used, while others look new. They fill the " +
        "shelves and probably contain useful information.\n");
    add_item("scrolls",
        "They are of various sizes and made of rolled up paper. " +
        "They are stored on the shelves in scroll cases.\n");
    add_item("scroll cases",
        "The scroll cases are made of metal and look sturdy. " +
        "They are cylindrical and slightly larger than the " +
        "scroll it holds. Each case holds only one scroll.\n");
    add_item("rug",
        "The rug is thick and luxurious. It is a deep blue " +
        "color with a golden fringe. The rug is decorated with " +
        "geometric shapes.\n");
     add_item(({"fringe", "golden fringe"}),
        "The fringe is made from golden colored strands of yarn " +
        "and are about a hand's length long.\n");
    add_item(({"ground", "floor"}),
        "The floor is made of stone blocks. It is covered by a " +
        "large rug.\n");
    add_item(({"stone blocks","blocks"}),
        "The stone blocks are large and of granite. The blocks " +
        "fit together and make up the floor and walls.\n");
    add_item("walls",
        "The walls are made of fitted granite stone blocks. " +
        "They are lined with bookshelves.\n");
    add_item(({"shelves", "bookshelves"}),
        "The book shelves are made of steel. They line the " +
        "walls and are stuffed with books, tomes, scrolls, " +
        "parchments, and records.\n");
    add_item("ceiling",
        "The ceiling is plain and made of supported stone.\n");

/*
    set_book_directory(SMITHSDIR_ROOMS + "library/accepted/");
    set_book_approval_directory(SMITHSDIR_ROOMS + "library/waiting/");
    set_borrow_required(1);
*/
// safe rooms
    add_prop(ROOM_I_NO_ATTACK, 1);
    add_prop(OBJ_M_NO_ATTACK,1);
    add_prop(ROOM_I_NO_MAGIC_ATTACK, 1); 

//  create_library();

  add_item("sign", "It is attached to the wall next to the western exit.\n");
    add_cmd_item("sign","read", "@@read_sign@@" );

    add_prop(ROOM_I_INSIDE,1);
    add_exit(SMITHSDIR_ROOMS+"improve", "east");
    add_exit(SMITHSDIR_ROOMS + "library", "west", "@@check_player@@", 1);

}

string
read_sign()
{
    return "On the sign you read:\n"+
        "\tOnly Advanced Smiths Beyond This Point.\n";

}
