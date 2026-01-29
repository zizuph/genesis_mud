#include "/d/Ansalon/common/defs.h"
#include "../local.h"
#include <macros.h>
#include <stdproperties.h>

inherit CITY_OUT;
object m1, g1;

void
reset_kalaman_room()
{
    if(!objectp(m1))
    {
	m1 = clone_object(KNPC + "maiden");
	m1->arm_me();
	m1->move(TO);
    }
    if(!objectp(g1))
    {
	g1 = clone_object(KNPC + "militiaman");
	g1->arm_me();
	g1->move(TO);
    }
}

create_kalaman_room()
{
    set_long("@@long_descr");
    set_short("Northeastern corner of the market place before a purple booth");

    add_exit(CITY + "m8","west",0);
    add_exit(CITY + "m6","south",0);
    add_cmd_item(({"purple booth","booth"}),"enter","@@enter_booth");

    add_item(({"market place","market"}),"@@long_descr");
    add_item(({"purple booth","booth"}),
      "In this part of the market square stands a booth of purple canvas. " +
      "You could enter it if you wanted to.\n");
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
    "crowds fill the air. " +season_market()+
    "A purple booth stands in this part of the market square.\n";
}

string
enter_booth()
{
    write("You step into the purple booth.\n");
    say(QCTNAME(TP) + " steps into the purple booth.\n");
    tell_room("/d/Ansalon/kalaman/city/vendor1.c", QCTNAME(TP) +
              " enters the booth.\n");
    TP->move_living("M",CITY + "vendor1",0,0);
    return "";
}
