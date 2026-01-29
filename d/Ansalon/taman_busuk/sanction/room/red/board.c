#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/taman_busuk/sanction/local.h"

inherit SANCINROOM;


void
create_sanction_room()
{
    set_short("northern end of a large tent used by members of the " +
      "Red Dragonarmy");
    set_long("@@long_descr");

    add_item(({"tent","large tent"}),
      "@@long_descr");

    add_exit("/d/Ansalon/guild/dragonarmy/room/start_red","south",0);

    clone_object(SOBJ + "red_board")->move(TO);
}


string
long_descr()
{
    return "You stand at the northern end of a large tent used by " +
    "Red Dragonarmy soldiers. A board has been posted here "+
    "for use by the Red Dragonarmy members to pass on "+
    "news and orders. The heat in here is rather " +
    "oppressive, not surprising considering the tents location, " +
    "on the edge of the city of fire and lava, Sanction." +
    "\n";
}
