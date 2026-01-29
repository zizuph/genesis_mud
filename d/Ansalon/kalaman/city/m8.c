#include "/d/Ansalon/common/defs.h"
#include "../local.h"
#include <macros.h>
#include <stdproperties.h>

inherit CITY_OUT;
object m1,m2,m3,c1,c2;

void
reset_kalaman_room()
{
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

    if(!objectp(m3))
    {
	m3 = clone_object(KNPC + "maiden");
	m3->arm_me();
	m3->move(TO);
    }

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
}

create_kalaman_room()
{
    set_long("@@long_descr");
    set_short("Northern side of the market place");

    add_exit(PROOM + "s01","north","@@no_go");
    add_exit(CITY + "m9","east",0);
    add_exit(CITY + "m7","west",0);
    add_exit(CITY + "m5","south",0);

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

int
no_go()
{
  if ( TP->query_wiz_level() )
  {
    write("Since you are of the higher order of things, the guard lets you pass.\n");
    return 0;
  }

  write("A guard steps out in front of you as you begin to head north.\n" +
    "The guard says: There has been a murder in the poor district! It has been " +
    "sealed off until we can find out who the murderer is.\n");
  say("A guard steps out in front of " +QTNAME(TP) + ", stopping " +
    HIM(TP) + " from going north.\n");
  return 1;
}
