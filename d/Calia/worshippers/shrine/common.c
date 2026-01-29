
inherit "/std/room";
#include <stdproperties.h>
#include "defs.h"

object this;

void    load_board();

void
create_room()
{
    set_short("Shrine Common Room");
    set_long("You are standing in the Shrine common room.  Located "+
        "in the centre of the room is the common board.  There are "+
        "rooms in almost every direction around you.  "+
        "The walls are carved out of a beautiful "+
        "slabs of the same white and black swirled marble that "+
        "you encountered in the entrance.  There is a small ladder "+
        "leading down from here as well as a set of stone stairs leading "+
        "up.\n");

    add_item("ladder","The ladder is made from a finely carved "+
        "oak and is lavishly decorated with gold trim.  It leads "+
        "down to the shrine bank.\n");

    add_item("stairs","These stairs are carved from some type "+
        "of magically glowing stone and lead up to the Elemental "+
        "Worshippers council chambers.\n");

    add_exit(WOR_SHRINE+"pyros","southeast",0,1);
    add_exit(WOR_SHRINE+"post","south");
    add_exit(WOR_SHRINE+"diabrecho","northeast");
    add_exit(WOR_SHRINE+"shop","west");
    add_exit(WOR_SHRINE+"entrance","east");
    add_exit(WOR_SHRINE+"gu","southwest");
    add_exit(WOR_SHRINE+"aeria","northwest");
    add_exit(WOR_SHRINE+"psuchae","north");
    add_exit(WOR_SHRINE+"bank","down",0,1);
    add_exit(WOR_SHRINE+"wcounr","up",0,1);

    add_prop(ROOM_I_NO_STEAL, 1);
    add_prop(ROOM_I_NO_TELEPORT, 1);
    add_prop(ROOM_I_NO_ATTACK, 1);
    add_prop(ROOM_I_INSIDE,1);

    this = THIS;
    load_board();
}

void
load_board()
{
    seteuid(getuid(this));

    clone_object("/d/Genesis/obj/board")->move(this);
}

/*
 * Function: enter_inv
 * Description: block non-interactives from entering.
 */
void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if (living(ob) && !interactive(ob))
        ob->move(from);
}
