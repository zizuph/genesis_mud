#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/kalaman/seavillage/local.h"

inherit VILLAGE_OUT;

void
reset_seavillage_room()
{
    return;
}

create_seavillage_room()
{
    set_short("The market place of this village");
    set_long("@@long_descr");

    add_item("pier","A sturdy barnacle-covered pier that juts " +
      "out into Blood Bay, where far-travelled ships that sail the " +
      "Blood Sea dock. \n");
    add_item(({"waves","supports"}),"Below you waves crash " +
      "against the supports of the docks. The supports creak " +
      "wretchedly.\n");

    add_exit(VILLAGEROOM + "street08","north",0);
    add_exit(VILLAGEROOM + "street10","east",0);
    add_exit(VILLAGEROOM + "street04","west",0);

    reset_seavillage_room();
}

string
long_descr()
{
    return tod_descr1() + tod_descr2() + "You stand in the middle of " + 
    "the market place in this small sea-side village. Around you are "+
    "small, weather beaten houses, an inn and a few shops. " +
    season_descr() + "\n";
}

