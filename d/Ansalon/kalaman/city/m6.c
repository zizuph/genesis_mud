#include "/d/Ansalon/common/defs.h"
#include "../local.h"
#include <macros.h>
#include <stdproperties.h>

inherit CITY_OUT;
object bank, c1, m1, m2;

void
reset_kalaman_room()
{
    if(!objectp(c1))
    {
	c1 = clone_object(KNPC + "civilian");
	c1->arm_me();
	c1->move(TO);
    }

    if(!objectp(m1))
    {
	m1 = clone_object(KNPC + "maiden");
	m1->arm_me();
	m1->move(TO);
    }

    if(!objectp(m2))
    {
	m2 = clone_object(KNPC + "maiden");
	m2->arm_me();
	m2->move(TO);
    }
    if(!objectp(bank))
    {
	bank = clone_object("/d/Genesis/obj/deposit");
        bank->set_bank_id(4301, "Kalaman");
	bank->move(TO);
    }
}

create_kalaman_room()
{
    set_long("@@long_descr");
    set_short("Eastern side of the market place");

    add_exit(CITY + "m9","north",0);
    add_exit(CITY + "m5","west",0);
    add_exit(CITY + "m2","south",0);
    add_exit(CITY + "r24","southeast",0);

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
