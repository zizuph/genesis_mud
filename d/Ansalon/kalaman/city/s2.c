#include "/d/Ansalon/common/defs.h"
#include "../local.h"
#include <macros.h>
#include <stdproperties.h>

inherit KALAMAN_IN;

void
reset_kalaman_room()
{
    return;
}

create_kalaman_room()
{
    set_long("@@long_descr");
    set_short("Sewer tunnels under Kalaman");
    add_item("water",
      "This water, if you could call it that, has a strange unpleasant smell to it. " +
      "It flows slowly through the sewer tunnels running under Kalaman.\n");
    add_item(({"streets","kalaman"}),
      "Its hard to examine something you are standing under.\n");
    add_item(({"sewers","sewer tunnels","tunnels"}),
      "@@long_descr");


    add_item(({"large grate","grate"}),
      "Above you is a large grate with a few of its bars missing. You can probably " +
      "pull yourself through it, and return to the streets of Kalaman.\n");
    add_item("bars","A few bars are missing from the grate above you.\n");

    add_exit(CITY + "s2","east","@@no_go");
    add_exit(CITY + "s3","west","@@no_go");

    add_cmd_item(({"myself through grate","myself through the grate"}),
      "pull","@@enter_grate");

    DARK;

    reset_kalaman_room();
}

int
no_go()
{
    write("The sewer tunnels seem to be flooded down that way. A dwarven " +
      "wizard can be heard in the distance grumbling as he " +
      "works what sounds to be a squeaky bilge.\n");
    return 1;
}

string
long_descr()
{
    return "You are standing in a foot of water in one of the sewer tunnels " +
    "running underneath the streets of Kalaman. " +
    "A large grate above your head allows water to drain down here from the " +
    "streets. " +
    "The tunnel continues to the east and west.\n";
}


string
enter_grate()
{

    write("You pull yourself through the grate above you.\n");
    say(QCTNAME(TP) + " pulls " +HIM(TP) +"self through the grate " +
      "above you.\n");
    TP->move_living("M",CITY + "alley",1,0);
    return "";
}
