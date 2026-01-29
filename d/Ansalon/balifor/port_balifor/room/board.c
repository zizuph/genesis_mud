#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/balifor/port_balifor/local.h"

inherit         BALIFOR_IN;

void
reset_balifor_room()
{
    return;
}

create_balifor_room()
{
    set_short("Town Hall");
    set_long("@@long_descr");

    add_exit(BROOM + "city12", "southeast", 0);
    add_exit(BROOM + "city11", "east", 0);
    add_exit(BROOM + "city10", "northeast", 0);
    add_item(({"white stone","hall","city hall"}),
      "The City Hall is made of white stone, and stands out " +
      "from the other buildings.\n");
    add_item(({"upstairs","offices"}),
      "Upstairs are the offices of the City Hall. They are off " +
      "limits to you.\n");
    add_exit("/d/Ansalon/scarlet/workroom","up","@@no_enter");
    clone_object(BOBJ + "normal_board")->move(TO);

    reset_balifor_room();
}

int
no_enter()
{
    write("You are not allowed into the offices.\n");
    return 1;
}

string
no_exit()
{
    return "You are not allowed to go into the offices.\n";
}

string
long_descr()
{
    return "You stand in the City Hall of Port Balifor. The offices of " +
    "the Hall are upstairs, but you doubt you will be allowed there. " +
    "The Hall is made of white stone, and stands out from the other " +
    "buildings.\n";
}
