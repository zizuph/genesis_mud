#include "/d/Ansalon/common/defs.h"
#include "../local.h"
#include <macros.h>
#include <stdproperties.h>

inherit CITY_OUT;
object merchant, guard;

void
reset_kalaman_room()
{
    if(!objectp(guard))
    {
	guard = clone_object(KNPC + "militiaman");
	guard->arm_me();
	guard->move(TO);
    }

    if(!objectp(merchant))
    {
	merchant = clone_object(KNPC + "backpack_seller");
	merchant->move(TO);
    }
}

create_kalaman_room()
{
    set_long("@@long_descr");
    set_short("Southeastern corner of the market place");

    add_exit(CITY + "m1","west",0);
    add_exit(CITY + "m6","north",0);
    add_exit(CITY + "r4","southeast",0);

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
