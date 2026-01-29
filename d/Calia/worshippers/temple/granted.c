
 /* Worshippers granted room */
 /* by Jaacar 1997 */

#pragma save_binary
#pragma strict_types

inherit "/std/room";

#include <stdproperties.h>
#include <macros.h>
#include <language.h>
#include "defs.h"
#include WORSHIP_HEADER

void load_board();

void
create_room()
{
    set_short("Granted chamber");
    set_long("The chamber you are in is perfectly round. "+
        "You cannot determine where the walls, ceiling or floor begins or "+
        "ends. You are not touching any surface, instead you are hovering "+
        "by some sort of magic. In the middle of the chamber floats a "+
        "message board which you may read or write on. "+
        "Somehow you feel the only way to leave this place is to "+
        "'touch the surface' of the walls, floor, or ceiling."+
        "\n");

    add_prop(ROOM_I_INSIDE,1);
    add_prop(ROOM_M_NO_ATTACK,1);


    load_board();
}

void
load_board()
{
    object bb;
    seteuid(getuid(this_object()));
    bb = clone_object(WOR_TEMPLE+"gboard");
    bb->move(this_object());
}

int
drop()
{
    write("You dare not drop anything in this chamber.\n");
    return 1;
}

int
touch(string str)
{
    if (!str || str != "the surface")
        return 0;
    write("You place your hands on the surface and feel yourself elsewhere.\n");
    say(QCTNAME(TP)+" vanishes.\n");
    tell_room(WOR_TEMPLE+"estiroom",QCTNAME(TP)+" arrives.\n");
    TP->move_living("M",WOR_TEMPLE+"estiroom");
    return 1;
}

int
block()
{
    write("You dare not do that here.\n");
    return 1;
}
 
int
quit()
{
    write("You don't dare quit here.\n");
    return 1;
}

int
hide()
{
    write("Where are you going to hide something here?\n");
    return 1;
}

int query_prevent_snoop()
{
    return 1;
}
 
void
init()
{
    ::init();
    add_action(drop,"drop");
    add_action(drop,"put");
    add_action(block,"rc");
    add_action(quit,"quit");
    add_action(hide,"hide");
    add_action(touch,"touch");
}
