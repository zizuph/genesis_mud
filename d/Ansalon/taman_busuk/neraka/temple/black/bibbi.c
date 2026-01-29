#pragma strict_types

#include "../defs.h"

inherit TEMPLE + "std_platform.c";

void
create_temple_room()
{
    object door;
    

    ::create_temple_room();

     set_short("Black Highlord's platform");
    set_long("You are standing atop one of the platforms in the Great Hall " +
        "of Audience. There are steps leading up to where you stand and a " +
        "door in the wall behind you. The only thing here is a large carved " +
        "chair that resembles a throne.\n");

    add_item(({"seat", "suede seat"}),
        "This seat is soft and covered in black suede.\n");

    add_item(({"standard", "standards", "miniature standards"}),
        "On the back of the chair and above the door hang a couple of the " +
        "Black Dragonarmy's Regimental Standards. They are made of satin " +
        "and silk embroidery.\n");

    door = clone_object( DOOR + "blk1a.c");
    door->move(this_object());
}
