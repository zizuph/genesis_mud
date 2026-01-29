// Underwater cave   (/d/Avenir/common/port/uw4.c)
// creator(s):       Glinda may -95
// last update:
// 		Lucius, Jan 2009: Re-written for new water code.
// purpose:
//
// note:
// bug(s):
// to-do:

inherit "/d/Avenir/inherit/water";
#include "/d/Avenir/common/common.h"


public void
create_room(void)
{
    underwater_room();

    set_short("Underwater in a cave");
    set_long("You have entered what seems to be an endlesss underwater " +
      "cave. You have problems seeing anything in the vast darkness. "+
      "There is no way of telling how large the cave is since its outlines "+
      "are blurred.\n   There seems to be an irregularity in "+
      "the darkness to your northwest. To the south, the opening you "+
      "entered through is visible as a lighter shade of grey in the "+
      "shadows.\n");
    add_item(({"water"}),
      "The dark water envelops you completely.\n");
    add_item(({"cliff","rock","wall","floor","ceiling","walls"}),
      "The dark rock of the cliff appears only as a darker shade in the " +
      "darkness surrounding you.\n");
    add_item(({"opening"}),
      "The exit from the cave is visible to your south as a lighter shade "+
      "in the darkness.\n");
    add_item(({"irregularity"}),
      "There is an irregularity to the northwest. It is hard to make "+
      "out what it is from here, but it looks like - could it be a "+
      "shipwreck?\n");

    add_exit(PORT + "uw6", "north");
    add_exit(PORT + "uw7", "northeast");
    add_exit(PORT + "uw7", "east");
    add_exit(PORT + "uw2", "south");
    add_exit(PORT + "uw2", "southeast");
    add_exit(PORT + "uw2", "southwest");
    add_exit(PORT + "uw5", "west");
    add_exit(PORT + "uw5", "northwest");
}

