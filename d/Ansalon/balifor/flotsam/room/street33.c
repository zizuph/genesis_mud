
#include "/d/Ansalon/common/defs.h"
#include  "/d/Ansalon/balifor/flotsam/local.h"

inherit FLOTSAM_OUT;
object drac1;

void
reset_flotsam_room()
{
    if(!objectp(drac1))
    {
	drac1 = clone_object(KNPC + "ogre");
	drac1->move(TO);
    }
}

create_flotsam_room()
{
    set_short("Dirty street corner in the southern parts of Flotsam");
    set_long("@@long_descr");

    add_item(({"cobbled street","street"}),"A well-used, dirty cobbled " +
      "street. \n");
    add_item("sidewalk","Nothing unusual about this sidewalk.\n");
    add_item(({"soldiers","mercenaries"}),"Drunken soldiers " +
      "of the Blue Dragonarmy along side newly recruited " +
      "mercenaries stumble through the street. It would be " +
      "best to keep out of their way if you don't want trouble.\n");
    add_item(({"brazier","iron brazier","tall iron brazier"}),"A " +
      "tall iron brazier, its light casting dark shadows on the walls" +
      " of the surrounding buildings. \n");
    add_item("clouds","Gloomy clouds, that seem to hover over this " +
      "wretched town every minute of the day. \n");
    add_item("side street","A small, dark side street runs " +
      "south from here.\n");

    add_exit(FROOM + "street32","north",0);
    add_exit(FROOM + "street34","west",0);
    add_invis_exit(FROOM + "gstreet1","south",0);

    reset_flotsam_room();
}

string
long_descr()
{
    return tod_descr1() + tod_descr2() + "You stand on a crowded " +
    "street corner in the town of Flotsam, where a small " +
    "dark side street runs south from here. Off-duty soldiers " +
    "and newly recruited mercenaries roaming from tavern to " +
    "tavern in search of cheap ale fill the streets, alongside " +
    "heavily armed patrols that seem to be searching for " +
    "something... or someone. A tall iron brazier stands off on " +
    "a sidewalk, relieving little of the gloom brought on by the " +
    "clouds overhead. " + season_descr() + "\n";

}

