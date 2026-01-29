#include "/d/Ansalon/common/defs.h"
#include "../local.h"
#include <macros.h>
#include <stdproperties.h>

inherit CITY_OUT;
object vendor, g1,g2;

void
reset_kalaman_room()
{
    if(!objectp(vendor))
    {
	vendor = clone_object(KNPC + "food_vendor");
	vendor->move(TO);
    }

    if(!objectp(g1))
    {
	g1 = clone_object(KNPC + "militiaman");
	g1->arm_me();
	g1->move(TO);
    }

    if(!objectp(g2))
    {
	g2 = clone_object(KNPC + "militiaman");
	g2->arm_me();
	g2->move(TO);
    }
}

create_kalaman_room()
{
    set_long("@@long_descr");
    set_short("Southwestern corner of the market place");

    add_exit(CITY + "m4","north",0);
    add_exit(CITY + "m1","east",0);
    add_exit(CITY + "r25","southwest",0);

    add_item(({"market place","market"}),"@@long_descr");
    add_item(({"merchants","vendors","booths","vendor's booths",
	"vendors booths"}),
      "All around you merchants hawk their wares, and gaily " +
      "coloured booths fill the market place.\n");
    add_item(({"crowds","crowd"}),
      "A large crowd has gathered in the market place to buy, view or sell goods " +
      "from all around Ansalon.\n");

    reset_kalaman_room();
}

string
long_descr()
{
    return "You stand in a busy square that is the market place " +
    "of Kalaman. The shouts of merchants and the babble of the " +
    "crowds fill the air. " +season_market() + "\n";
}
