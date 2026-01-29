/*
 * Coded by Amelia 11/22/97
 */

#pragma strict_types
#pragma no_clone

inherit "/std/room";

#include <stdproperties.h>

#define BOOK "/d/Earthsea/obj/red_book"

public void
create_room()
{
    add_prop(ROOM_S_MAP_FILE, "earthsea_map.txt");
    set_short("Main bedroom");
    set_long("Light filters through colourful "+
        "curtains covering the north window. A large featherbed "+
        "which is neatly made is set next to the west wall. A low "+
        "table beside the bed holds a candle and a book with a red "+
        "leather cover. A large oval rug woven from goat wool covers "+
        "the hard oak floor.\n");
    add_item("candle", "The candle apparently is for night "+
        "reading. It is unlit.\n");
    add_item((({"table", "low table"})),
        "The low table is made from light coloured oak and "+
        "holds a red book and a candle.\n");
    add_item((({"featherbed", "bed"})),
        "The large featherbed is covered with a bright patchwork "+
        "quilt. It looks very comfortable.\n");
    add_item((({"curtains", "window", "flower-print curtains" })),
        "Some colourful curtains cover the window and permit "+
        "some privacy, however, they are thin enough to let in "+
        "lots of light.\n");
    add_prop(ROOM_I_INSIDE, 1);
    add_exit("house", "south");
    clone_object(BOOK)->move(this_object(), 1);
}
