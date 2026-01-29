/*
 * Recode Discussion Room
 *
 * This room will house a board where members of the Spirit Circle and the
 * Elemental Worshippers can discuss the recode that is happening in
 * 2010.
 *
 * Created by Petros, February 2010
 */

#pragma save_binary
#pragma strict_types

inherit "/std/room";

#include "defs.h"
#include <stdproperties.h>
#include WORSHIP_HEADER

void load_board();
 
int
is_worship(object living)
{
    return living->query_guild_name_lay() == GUILD_NAME;
}

void
create_room()
{
    set_short("Discussion chamber");
    set_long("This chamber is rather bare, reflecting the nature of "
        + "the Creation before it has been filled. Here, members of "
        + "the Spirit Circle and the Elemental Worshippers can discuss "
        + "ideas regarding the upcoming guild recode."        
        + "\n");

    add_item(({"walls","wall"}),"The walls here are made of a "+
        "granite-like stone, much like the other walls in this "+
        "temple.\n");

    add_prop(ROOM_I_INSIDE,1);
    add_prop(ROOM_M_NO_ATTACK,1);

    add_exit(WOR_TEMPLE + "board", "down", 0, 1);

    load_board();
}

void
load_board()
{
    object bb;
    seteuid(getuid(this_object()));
    bb = clone_object(WOR_TEMPLE+"discuss_board");
    bb->move(this_object());
}
 
int query_prevent_snoop()
{
    return 1;
}
 
