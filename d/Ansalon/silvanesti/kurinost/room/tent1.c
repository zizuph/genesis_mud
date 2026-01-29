
#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/silvanesti/kurinost/local.h"

inherit KURINOST_IN;
object drac;
object drac2;
object drac3;
object drac4;

void
reset_kurinost_room()
{
    if(!objectp(drac))
    {
      drac = clone_object(KNPC+"sivak");
      drac->move(TO);
      drac->GREEN;
    }
    if(!objectp(drac2))
    {
      drac2 = clone_object(KNPC+"sivak");
      drac2->move(TO);
      drac2->GREEN;
    }
    if(!objectp(drac3))
    {
      drac3 = clone_object(KNPC + "bozak");
      drac3->move(TO);
      drac3->GREEN;
    }
    if(!objectp(drac4))
    {
      drac4 = clone_object(KNPC + "bozak");
      drac4->move(TO);
      drac4->GREEN;
    }
    return;
}


create_kurinost_room()
{
    set_short("Inside a tent of the Green Dragonarmy");
    set_long("You stand inside a large canvas tent.  The tent "+
      "houses the members of the Green Dragonarmy that have been "+
      "stationed here to keep surveillance on the state of the "+
      "forests of Silvanesti.  Large enough to house ten soldiers, "+
      "the tent provides a little comfort in a nearly decimated land.\n");

    add_exit(KROOM + "road8","out",0);
    reset_kurinost_room();
}
