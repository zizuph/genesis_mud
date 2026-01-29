/*
 *  Added fishing properties allowing fishing - Arman 2021
 */

#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/balifor/flotsam/local.h"
#include <ss_types.h>
#include <macros.h>

#define HARD_TO_CLIMB 40
#define LIVE_I_CAN_FISH      "_live_i_can_fish"

inherit FLOTSAM_OUT;

void
reset_flotsam_room()
{
    return;
}

create_flotsam_room()
{
    set_short("Pier in the wretched town of Flotsam");
    set_long("@@long_descr");

    add_item(({"sea","blood sea"}),"The turbulent water you now " +
      "stare into is the reknowned Blood Sea of Istar, so called " +
      "for two reasons. The first being the deep red colour the " +
      "water turns during a storm, the second, more sinister reason " +
      "is because of the number of people that now call the Blood " +
      "Sea their resting place. \n");
    add_item("supports","These barnacle covered supports hold " +
      "up the piers you stand on. A ladder is attached to " +
      "one of them.\n");
    add_item("waves","Below you waves crash against the supports of " +
      "the docks. The supports creak wretchedly.\n");
    add_item("docking places","To the north are where the ships " +
      "dock from far travelled places.\n");
    add_item("ladder","A rickety ladder has been attached to " +
      "one of the piers supports. It looks rickety and unsafe. \n");

    add_item(({"pier","docks","dock"}),"You turn your eyes onto the " +
      "sturdy barnacle-covered jetty that juts out into Blood Bay. " +
      "Far-travelled ships that sail the Blood Sea dock here. \n");
    add_item("flotsam","A sprawling slum of taverns and Inns " +
      "given the name of Flotsam \n");

    add_prop(LIVE_I_CAN_FISH, "bloodsea");

    add_exit(FROOM + "street05","north",0);
    add_exit(FROOM + "street07","east",0);
    add_invis_exit(FROOM + "rock_pool1","down","@@down_ladder");

    reset_flotsam_room();
}

string
long_descr()
{
    return tod_descr1() + tod_descr2() + "You stand on a pier at the " +
    "docks of the wretched town of Flotsam. Below you can hear the " +
    "sounds of waves crashing against the docks supports. To your north and east " +
    "the pier continues to the docking places of " +
    "far-travelled ships. To the south sprawls Flotsam, peopled by " +
    "the dregs of most of the races of Krynn. A ladder can " +
    "be just made out going down below the pier into shadowy " +
    "darkness. " + season_descr() + 
    " \n";
}


int
no_go()
{
    write("You start heading up the pier towards one of the " +
      "docks, but you notice an angry dwarven wizard in the " +
      "middle of a heated argument with a ships captain over trading " +
      "routes. You decided it would be best to return when " +
      "they have finished their arguement.\n");

    return 1;
}

int
down_ladder()
{
    if (this_player()->query_skill(SS_CLIMB) < random(HARD_TO_CLIMB))
    {
	write("You don't think you are skilled enough to " +
	  "try and climb down the rickety ladder.\n");
	say(QCTNAME(this_player()) + " looks over the edge of " +
	  "the pier but then thinks better of it, and backs away. \n");
	return 1;
    }
    write("You nimbly climb down the rickety ladder...\n");
    say(QCTNAME(this_player()) + " disappears over the edge of " +
      "the pier. \n");
    return 0;
}
