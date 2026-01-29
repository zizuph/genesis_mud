

    /*Coded and written by Belize*/


inherit "/std/room";
#include <stdproperties.h>
#include "/d/Krynn/common/defs.h";

void
create_room()
{
INSIDE;
    set_short("Comfortable room for some work");
    set_long("This is a very comfortable room, with some beautiful tapestries " +
            "and furnitures. It is used by Belize, Gorr and Kishpa, when they " +
            "want to talk in their own language. Huge, dark fireplace makes " +
             "this place very nice and warm. In the centre of the room you can " +
             "see bulletin board. If you want something from Belize, Gorr, Kishpa - " +
             "write a note and leave it here. You see three doors here. West leads to " +
            "Belize's workroom, east to Gorr's and north to Kishpa's. \n");
    add_item(({"tapestries"}),"You see beautiful tapestries with some ancient pictures. \n");
    add_item(({"pictures"}),"Unfortunately you don't know anything about these pictures. \n");
    add_item(({"furnitures"}),"You see old, but still solid furnitures. \n");
    add_exit("/d/Krynn/belize/workroom.c","west",0,1);
    add_exit("/d/Ansalon/gorr/workroom.c","east",0,1);
    add_exit("/d/Ansalon/kishpa/workroom.c","north",0,1);
    load_board();
}

void
load_board()
{
    clone_object("/d/Krynn/belize/hall/bboard.c")->move(TO);
}
