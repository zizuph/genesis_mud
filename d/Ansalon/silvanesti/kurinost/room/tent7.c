
#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/silvanesti/kurinost/local.h"

inherit KURINOST_IN;
object drac;
object drac2;
object drac3;
object tyb;

void
reset_kurinost_room()
{
    if(!objectp(drac))
    {
      drac = clone_object(KLIVE + "aurak_leader2");
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
      drac3 = clone_object(KNPC + "sivak");
      drac3->move(TO);
      drac3->GREEN;
    }
    if(!objectp(tyb))
    {
      tyb = clone_object(KLIVE + "tyberus");
      tyb->move(TO);
    }
    return;
}


create_kurinost_room()
{
    set_short("Inside a tent of the Green Dragonarmy");
    set_long("You stand inside a large canvas tent.  The tent "+
      "houses the members of the Green Dragonarmy that have been "+
      "stationed here to keep surveillance on the state of the "+
      "forests of Silvanesti.  This tent is significantly larger than "+
      "those that surround it.  Belonging to the ranking officer of "+
      "the outpost, it provides more room, comfort, and privacy to "+
      "its owner.\n");

    add_exit(KROOM + "road9","out",0);
    reset_kurinost_room();
}
