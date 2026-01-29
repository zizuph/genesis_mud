/*
 *  Added fishing properties allowing fishing - Arman 2021
 */

#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/balifor/flotsam/local.h"

inherit FLOTSAM_OUT;

#define LIVE_I_CAN_FISH      "_live_i_can_fish"

object ship;

void
add_stuff()
{
    seteuid(getuid(TO));
    if(!ship)
    {
	ship = clone_object("/d/Ansalon/balifor/flotsam/ship/ship");
	ship->start_ship();
    }
}

void
reset_flotsam_room()
{
    set_alarm(1.0,0.0,add_stuff);
}

create_flotsam_room()
{
    set_short("Docks of Flotsam");
    set_long("@@long_descr");
    add_prop(ROOM_I_NO_CLEANUP, 1);

    add_item("sign","A sign with words. Read them. \n");
    add_item(({"sea","blood sea","blood sea of istar"}),"The " +
      "turbulent water you now stare into is the reknowned Blood Sea of Istar, " +
      "so called for two reasons. The first being the deep " +
      "red colour the water turns during a storm, the second, more " +
      "sinister reason is because of the number of people that now " +
      "call the Blood Sea their final resting place. \n");
    add_item(({"pier","docks"}),"You turn your eyes onto the sturdy " +
      "barnacle-covered jettys that jut out into Blood Bay, where far-" +
      "travelled ships that sail the Blood Sea dock. \n");

    add_cmd_item("sign", "read", "@@read_sign");

    add_exit(FROOM + "street04","south",0);

    add_prop(LIVE_I_CAN_FISH, "bloodsea");

    reset_flotsam_room();
}

string
long_descr()
{
    return tod_descr1() + tod_descr2() + "You stand at the docks of " +
    "the wretched town of Flotsam. Lying upon the shores of the " +
    "Blood Sea of Istar like the wreckage of a broken vessel, you " +
    "consider its name quite apt. Past the pier to the north " +
    "lies the infamous Blood Sea of Istar. To the south sprawls Flotsam, " +
    "peopled by the dregs of most of the races of Krynn. " +
    season_descr() + "\n" + "A barnacle-covered sign has been " +
    "erected here. \n";
}


int
read_sign()
{
    write("     ****************************\n" +
      "     " +
      "*                          *\n" +
      "     " +
      "*   Hulls shipping line.   *\n" +
      "     " +
      "*   Flotsam-Sparkle        *\n" +
      "     " +
      "*                          *\n" +
      "     " +
      "****************************\n");

    return 1;
}
