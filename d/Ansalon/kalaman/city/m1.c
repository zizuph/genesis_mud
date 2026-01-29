#include "/d/Ansalon/common/defs.h"
#include "../local.h"
#include <macros.h>
#include <stdproperties.h>

inherit CITY_OUT;
object merchant, c1, c2;

void
reset_kalaman_room()
{
    if(!objectp(c1))
    {
	c1 = clone_object(KNPC + "civilian");
	c1->arm_me();
	c1->move(TO);
    }

    if(!objectp(c2))
    {
	c2 = clone_object(KNPC + "civilian");
	c2->arm_me();
	c2->move(TO);
    }

    if(!objectp(merchant))
    {
	merchant = clone_object(KNPC + "torch_seller");
	merchant->move(TO);
    }
}

create_kalaman_room()
{
    set_long("@@long_descr");
    set_short("Southern side of the market square");

    add_item(({"market place","market"}),"@@long_descr");
    add_item(({"merchants","vendors","booths","vendor's booths",
	"vendors booths"}),
      "All around you merchants hawk their wares, and gaily " +
      "coloured booths fill the market place.\n");
    add_item(({"crowds","crowd"}),
      "A large crowd has gathered in the market place to buy, view or sell goods " +
      "from all around Ansalon.\n");

    add_exit(CITY + "m5","north",0);
    add_exit(CITY + "m2","east",0);
    add_exit(CITY + "m3","west",0);
    add_exit(CITY + "r23","south",0);

    reset_kalaman_room();
}

string
long_descr()
{
    return "You stand in a busy square that is the market place " +
    "of Kalaman. The shouts of merchants and the babble of the " +
    "crowds fill the air. " +season_market() + "\n";
}
