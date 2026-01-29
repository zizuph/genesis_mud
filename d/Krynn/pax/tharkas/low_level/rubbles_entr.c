/*
   Pax Tharkas, Low level, entrance from Sla-Mori.

   rubbles_entr.c
   --------------

   Coded ........: 95/01/05
   By ...........: Jeremiah

   Latest update : 95/05/06
   By ...........: Jeremiah

*/


#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/pax/local.h"

inherit PAXINROOM;

void
create_pax_room()
{
   set_short("Dark tunnel");
   set_long("You are standing in a dark, narrow tunnel. The floor here " +
            "is littered with debris. Looking at the dust covering the " +
            "floor you can see that no one has been here in a long time, " +
            "except for rats maybe. The tunnel has been carved out of " +
            "solid rock, and leads on towards the west and southwest. You " +
            "notice that the rock seems to become less solid in these " +
            "directions. It is very silent in here.\n");

   INSIDE;

   add_prop(ROOM_I_LIGHT,0);

   add_item("debris", "Looking closer at the debris you see, that it's " +
            "nothing more than leftovers of broken old useless boxes, " +
            "and pieces of rock, littered all over.\n");

   add_item("dust", "Just plain dust, and a lot of it. There's a lot of " +
            "tracks in the dust. Probably rats.\n");

   add_item(({"rock", "rocks", "tunnel"}), "This tunnel has been carved " +
            "out of solid rock. The rock does become less solid towards the " +
            "west and the southwest. It looks as if the tunnel hasn't " +
            "been carved out the rock there, but rather cleared through " +
            "large boulders and rubble.\n");

    add_exit(LOW_LEVEL + "rubbles1", "west", "@@through_debris");
    add_exit(LOW_LEVEL + "rubbles2", "southwest", "@@through_debris");
    add_exit(PSLA + "final_tunnel04", "east", "@@through_debris");
}


through_debris()
{
   write("You make you way along the tunnel, through the debris.\n");
   return 0;
}

