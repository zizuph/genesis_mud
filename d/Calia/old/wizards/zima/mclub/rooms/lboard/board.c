/* This "board" is used by the club to store "writings" and is not */
/* intended as a regular discussion board. It may be replaced at   */
/* a later date with a more traditional way to allow members to    */
/* write books.  (7/27/95)                                         */
inherit "std/board.c";
#include <macros.h>
#include "../defs.h"
 
create_board()
{
    seteuid(getuid(this_object()));
    set_name(({"bookshelf","shelf","book shelf"}));
    set_short("large bookshelf");
    set_board_name(ROOM_DIR+"lboard/board");
    set_long("It is a tall bookshelf which sits along the northern "+
             "wall. It contains the writings of those who remember "+
             "the arcane faith.\n");
    set_num_notes(50);
    set_anonymous(0);
    set_silent(1);
    set_show_lvl(0);
    set_remove_lvl(1);
    set_remove_str("You have to be a wizard to do that!\n");
}
 
 
/*
 * Function name: long
 * Description  : This function returns the long description on the board.
 *                If you don't have access to the board, you won't see the
 *                headers.
 * Returns      : the long description.
 * Copied from /std/board.c so that long desc can be modified (Zima-7/27/95)
 */
public mixed
long()
{
    int ind;
    string str = "It is a tall bookshelf made of cedar, used to "+
                 "hold the writings of those who remember the arcane "+
                 "faith. ";
 
    if (this_object()->check_reader()) return str + "\n";
 
    if (!msg_num) return str + "There are currently no writings here, "+
                         "but you may add one with 'note <title>'.\n";
 
    str += "You see "+msg_num+(msg_num == 1 ? " writing" : " writings") +
           " on the shelves.\n";
 
    str=str+"You may read a selection with 'read <#>' or write "+
             "one with 'note <title>'.\n";
 
 
    if (!silent && present(this_player(), environment()))
say(QCTNAME(this_player()) + " peruses the selections on the bookshelf.\n");
 
    ind = 0;
    while (ind < msg_num)
    {
str += sprintf("%2d: %s\n", (ind + 1), headers[ind][0]);
ind++;
    }
    return str;
}
