
/*
 * board_room.c
 *
 * Private Board room for the Spirit Circle of Psuchae Temple
 * 
 *
 * Copyright (C): Jaacar (Mike Phipps), Jul 24, 2003
 *
 */
 
#pragma strict_types
#pragma save_binary

inherit "/std/room";

#include <stdproperties.h>
#include <macros.h>

#include "defs.h"

void load_board();

int 
query_prevent_snoop()
{
    return 1;
}

void
create_room()
{
    set_short("The Temple Sanctuary");
    set_long("Gleaming white circular walls welcome you to the temple "+
        "sanctuary, where the Enlightened come to share wisdom and insight "+
        "learned in the service of Psuchae. Marble benches encircle the "+
        "round chamber, and in the center is an enormous gilded tome on a "+
        "marble pedestal that gleams with a mystical energy. Next to the "+
        "tome is a heavy silver inkwell that contains a magnificent white "+
        "plumed quill. To the north, a broad golden archway leads back to "+
        "the temple antechamber.\n");

    add_item(({"bench","benches","marble bench","marble benches"}),"These "+
        "marble benches encircle the round chamber you are standing in.\n");
    add_item(({"pedestal","marble pedestal"}),"The marble pedestal sits in "+
        "the very centre of this round chamber and gleams with a mystical "+
        "energy. On the top sits an enormous gilded tome.\n");
    add_item(({"inkwell","silver inkwell","heavy inkwell","heavy silver inkwell"}),
        "This heavy silver inkwell sits next to the enormous gilded tome on the "+
        "marble pedestal.\n");
    add_item(({"quill","plumed quill","white quill","magnificent quill",
        "white plumed quill","magnificent white plumed quill"}),"This magnificent "+
        "white plumed quill sits inside of the silver inkwell.\n");
    add_item(({"wall","walls","gleaming wall","gleaming walls",
        "white wall","white walls","circular wall","circular walls",
        "white circular wall","white circular walls","gleaming white circular wall",
        "gleaming white circular walls"}), "The walls here are gleaming white and "+
        "fashioned in a circular shape all around you.\n");
    add_item(({"roof", "ceiling"}), "The ceiling is silver in colour, "+
        "reflecting the light in the chamber down onto the bulletin "+
        "board.\n");
    add_item("floor", "The floor is very smooth and silver in colour.\n");
    add_item(({"archway","golden archway","broad golden archway"}),"The golden "+
        "archway in the northern wall leads off to the antechamber beyond "+
        "it.\n");

    IN;
    add_prop(ROOM_M_NO_ATTACK,"You cannot attack in here, you are in a "+
        "sacred place!\n");
    add_prop(ROOM_M_NO_MAGIC_ATTACK,"You cannot attack in here, you are in "+
        "a sacred place!\n");

    add_exit(SPIRIT_TEMPLE+"antechamber","north",0,1);
    load_board();
}

void
load_board()
{
    object bb;
    seteuid(getuid(this_object()));
    bb = clone_object(SPIRIT_TEMPLE+"priv_board");
    bb->move(this_object());
}

int
do_enter(string str)
{
    if (!str)
    {
        NF("Enter what? The archway? <enter archway>\n");
        return 0;
    }

    if (str != "archway")
    {
        NF("Enter what? The archway? <enter archway>\n");
        return 0;
    }

    write("You pass under the golden archway and into the antechamber "+
        "beyond.\n");
    say(QCTNAME(TP)+" passes under the golden archway and into the "+
        "antechamber beyond.\n");
    TP->move_living("M",SPIRIT_TEMPLE+"antechamber");
    tell_room(environment(TP),QCTNAME(TP)+" enters the room through "+
        "the golden archway to the south.\n",TP);
    return 1;
}

void
init()
{
    ::init();
    add_action(do_enter,"enter");
}
