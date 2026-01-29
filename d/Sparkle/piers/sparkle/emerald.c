#pragma save_binary
#pragma strict_types

inherit "/std/room";

#include <stdproperties.h>

#include "defs.h"

void
create_room()
{
    set_short("Berth 7 - Emerald");
    set_long("\n"+
      "This is the south pier.\n"+
      "The seabirds swoop and swerve just beyond reach of the" +
      " edge of the pier. Slowly they circle over the water, their" +
      " wings gliding on the breeze keeping a sharp lookout" +
      " for tasty tidbits to eat. The pier continues east.\n" +
      "There is a sign here that reads: Berth 7 - Emerald.\n");

    add_item(({"water" }),"Pieces of fish and other leftovers from the fishermen's\n"+
      "boats are floating in the water. It makes it less inviting\n"+
      "to swim around in, unless you're a seagull.\n"+
      "");
    add_item(({"birds","bird","seagull","seagulls" }),"The seagulls are quite busy trying to get the best pieces of fish\n"+
      "and their shrieks are quite deafening.\n"+
      "");
    add_item(({"warehouse" }),"");
    add_item(({"pier" }),"");

    add_exit(S_DOMAIN_PIERS_DIR + "sparkle/newports", "west");
    add_exit(S_DOMAIN_PIERS_DIR + "sparkle/sybarus", "east");
    add_prop(ROOM_I_INSIDE, 0);
    add_prop(ROOM_I_TYPE, ROOM_NORMAL);
}

