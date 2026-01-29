/*
   Pax Tharkas, Valley.....

   valley_road1.c
   --------------

   Coded ........: 95/04/09
   By ...........: Jeremiah

   Latest update : 95/05/30
   By ...........: Jeremiah

*/


#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/pax/local.h"
#include <filter_funs.h>                 /* filter functions */
#include <composite.h>

inherit PAXOUTROOM;

void
create_pax_room()
{
    set_short("Bend on road in narrow valley");
    set_long("You are standing on a road in a narrow valley. South " +
      "the valley narrows considerately, and slopes upwards " +
      "towards a high mountain pass. The pass is blocked by a " +
      "fortress. Two huge towers, almost leaning against the " +
      "sides of the mountains, connected by a massive wall, " +
      "dominates the pass and the valley below. Two lesser walls " +
      "runs across the valley on the slopes in front of the " +
      "fortress. The mighty fortress of Pax Tharkas. Behind it, " +
      "and to the sides of the fortress, the snow covered  " +
      "peaks of the Kharolis mountains glitter in the sun. " +
      "Anything or anyone wanting to travel through these " +
      "mountains will have to go through here. The road leads " +
      "south, towards the fortress, and northeast out into " +
      "the widening valley.\n");

    add_item(({"fortress", "Pax Tharkas", "Pax tharkas", "pax tharkas"}),
      "A huge grey fortress lying at the end of the valley. " +
      "Two huge towers connected by a massive wall. " +
      "Maybe you should move closer to get a better look at it." +
      "\n");

    add_item(({"tower", "towers"}), "Flanking a massive wall, two " +
      "huge grey towers rise high in the pass above you.\n");

    add_item(({"wall", "massive wall"}) ,"A massive wall running between " +
      "two huge towers. A large gate is set in the middle of " +
      "the wall. The road leads south, up to that gate.\n");

    add_item(({"walls", "lesser walls", "lesser wall"}), "On the slopes " +
      "in front of the fortress, two lesser walls run across the " +
      "valley. You'll have to walk up to the walls to get a " +
      "better look at them.\n");

    add_item("road", "A simple dusty road, running through a small " +
      "valley. The road leads up to the gate in the fortress.\n");

    add_item("valley", "A small valley cutting into the mountains. " +
      "You are standing near the end of it, where a huge fortress " +
      "lie, blocking any movement further south. The valley is " +
      "narrowing considerably here.\n");

    add_item(({"mountain", "mountains"}), "Mountains rising high into the " +
      "sky, bordering this valley. The way through these mountains " +
      "seems lie at the end of this valley, through the mighty " +
      "fortress guarding the pass above you.\n");

    OUTSIDE;

    add_exit(VALLEY + "valley_road2", "northeast", 0, 2);
    add_exit(VALLEY + "curtain_wall2", "south", 0, 2);
}

