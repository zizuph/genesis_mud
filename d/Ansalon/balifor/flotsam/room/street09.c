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
	ship = clone_object("/d/Ansalon/balifor/flotsam/ship3/ship");
	ship->start_ship();
   }
}


void
reset_flotsam_room()
{
    add_stuff();
}

create_flotsam_room()
{
    set_short("Docks of Flotsam");
    set_long("@@long_descr");
    add_prop(ROOM_I_NO_CLEANUP, 1);

    add_item(({"sea","blood sea","blood sea of istar"}),"The " +
      "turbulent water you now stare into is the reknowned Blood Sea " +
      "of Istar, so called for two reasons. The first being the deep " +
      "red colour the water turns during a storm, and the second, " +
      "more sinister reason is because of the number of people that " +
      "now call the Blood Sea their final resting place. \n");
    add_item(({"flotsam","Flotsam"}),"Before you to the south " +
      "lies the sprawl of Flotsam, inviting you to enter and " +
      "experience the thrills that the town has to offer.\n");
    add_item(({"pier","docks"}),"A sturdy, barnacle-covered jetty " +
      "that juts out into Blood Bay. This is where ships that sail " +
      "the Blood Sea dock. \n");
    add_item("sign","@@read_sign");


    add_exit(FROOM + "street08","west",0);

    add_prop(LIVE_I_CAN_FISH, "bloodsea");

    add_cmd_item("sign","read","@@read_sign");

    reset_flotsam_room();
}

string
long_descr()
{
    return tod_descr1() + tod_descr2() + "You stand " +
    "at the docks of the wretched town of Flotsam. Resting upon the " +
    "shores of the Blood Sea of Istar like the wreckage of a " +
    "broken vessel, you consider its name quite apt. The docks "+
    "continue to the west. "+ season_descr() + " \n" + "A wooden "+
    "sign has been placed here. \n";
}

string
read_sign()
{
    write("    ________________________ \n"
      +   "   |                        |\n"
      +   "   |     Flotsam-Mithas     |\n"
      +   "   |        30 copper       |\n"
      +   "   |                        |\n"
      +   "   |________________________|\n"
      +   "             |  | \n"
      +   "             |  | \n");
    return "";
}
