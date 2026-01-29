#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/goodlund/nethosak/city/local.h"
inherit MITHAS_IN;

void
reset_mithas_room()
{
    return;
}

create_mithas_room()
{
    set_short("Adventurers Board");
    set_long("@@long_descr");

    add_exit(MROOM + "road4","west",0);
    add_exit("/d/Genesis/room/common","common",0);

    clone_object(MOBJ + "normal_board")->move(TO);

    reset_mithas_room();
}

string
long_descr()
{
    return "You stand beside the Adventurers Board in Nethosak. " +
    "This is where travellers and warriors meet to share " +
    "different warstories and other information that might be " +
    "useful. The room is very clean and the board is filled " +
    "with different notes. To the west you can return to the " +
    "streets of of Nethosak. \n";
}

