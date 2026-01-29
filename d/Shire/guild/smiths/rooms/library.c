/*

     The library of the Smiths guild

     Palmer 18 July 2006 - Fixed false warning about not returning a book.

*/

#pragma save_binary;

inherit "/d/Shire/room";
inherit "/lib/library";
inherit "/d/Gondor/open/room_chairs/room_chairs";

#include "smiths.h"
#include "/d/Shire/sys/defs.h"
#include <macros.h>
#include <stdproperties.h>

#define WOODEN_CHAIR    "rounded padded chair"
#define SOFA_CHAIR      "overstuffed forest green sofa"
#define COUCH_CHAIR     "large forest green couch"
#define BOOK_ID         (MASTER + "_library_book")

public string	look_at(string arg);    /* VBFC for chairs */
public void	leave_inv(object ob, object dest);
public string	look_at(string arg);    /* VBFC for chairs */

void
create_room()
{
    set_short("Library of the Smiths Guild");
    set_long("This is the private area of the library, open " +
        "only to advanced Smiths. The room is full of shelves that line the " +
        "walls. The shelves are full of various books, tomes, " +
        "parchments, records, and scrolls. A large rug covers " +
        "the floor. A chair, a sofa, and a couch are here for " +
        "members to relax in and write or read books. There is " +
        "a sign posted on the wall.\n");
    add_item(({"books", "tomes", "parchments", "records"}),
        "They are bound between two harden leather covers and " +
        "held then together with two iron hinges. some look " +
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
        "The ceiling is plain and made of supported stone\n");
    add_chair(WOODEN_CHAIR,
        "[down] [on] / [in] [the] [rounded] [padded] 'chair'", 1);
    add_item( ({ "chair", }), &look_at(WOODEN_CHAIR) );
    add_chair(SOFA_CHAIR,
        "[down] [on] / [in] [the] [overstuffed] [forest] [green] 'sofa'", 5);
    add_item( ({ "sofa"}), &look_at(SOFA_CHAIR) );
    add_chair(COUCH_CHAIR,
        "[down] [on] / [in] [the] [large] [forest] [green] 'couch'", 5);
    add_item( ({ "couch", }), &look_at(COUCH_CHAIR) );


    set_book_directory(SMITHSDIR_ROOMS + "library/accepted/");
    set_book_approval_directory(SMITHSDIR_ROOMS + "library/waiting/");
    set_borrow_required(1);

    add_prop(ROOM_I_NO_ATTACK, 1);
    add_prop(OBJ_M_NO_ATTACK,1);
    add_prop(ROOM_I_NO_MAGIC_ATTACK, 1); 

    create_library();

    add_item("sign", library_help());
    add_cmd_item("sign","read", library_help());

    add_prop(ROOM_I_INSIDE,1);
    add_exit(SMITHSDIR_ROOMS+"library_entr", "east", "@@library_exit_block@@");
    add_exit(SMITHSDIR_ROOMS+"adv_hall", "south", "@@library_exit_block@@");

}

void
init()
{
    ::init();
    init_room_chairs(); /* add chair verbs */
    init_library();


}

public int
library_write_access()
{
    return 1;
}

 public void
leave_inv(object ob, object dest)
{
    ::leave_inv(ob, dest);
    leave_inv_room_chairs(ob, dest);
}


/*
 * Function name:   look_at
 * Description  :   VBFC to describe chair/sofa + occupants
 * Arguments    :   string arg -- what's being looked at
 *                  null str -> it's the room
 * Returns      :    string -- the description
 */
public string
look_at(string arg)
{
    switch ( arg )
    {
    case WOODEN_CHAIR:
    return "The chair is square shaped and sturdy looking. It " +
        "is a forest green chair with a high back. It is " +
        "overstuffed and very comfortable looking.\n"+
    sitting_on_chair(WOODEN_CHAIR, this_player(), 0);
    break;

    case SOFA_CHAIR:
       return "The sofa is overstuffed and very inviting. It is " +
        "covered with a green fabric. The sofa looks sturdy " +
        "enough to hold several people with ease.\n"+
    sitting_on_chair(SOFA_CHAIR, this_player(), 0);
    break;

    case COUCH_CHAIR:
       return "The couch is plush and very inviting. It is " +
        "upholstered with green fabric. The couch is sturdy " +
        "enough to hold several people with plenty of room " +
        "left over.\n"+
    sitting_on_chair(COUCH_CHAIR, this_player(), 0);
    break;


    }
} /* look_at */


/*
 * Function name: library_exit_block
 * Description:   Returns true if this_player() is in possession of
 *                a book from this library.  It can be used as a block
 *                function for library exits.
 * Returns:       1/0 - library book possessed/not possessed
 */
public int
library_exit_block()
{
    int check_borrower;

    check_borrower = !!sizeof(filter(deep_inventory(this_player()), &->id(BOOK_ID)));
    if (check_borrower)
        write ("You must return your books before leaving the library.\n");
    return check_borrower;
}


/*
 * Function name: library_admin_access
 * Description:   Redefine this function to limit permission to admin commands
 * Returns:       1 - this_player() is permitted to perform admin commands
 *                0 - this_player() is not permitted to perform admin commands
 */
public int
library_admin_access()
{
    if (!this_player()->query_wiz_level())
    {
        write("You don't have permission to do that.\n");
        return 0;
    }

    return 1;
}
