#pragma save_binary
#pragma strict_types

inherit "/std/room";

#include <stdproperties.h>

#include "../defs.h"

void
create_room()
{
    set_short("Berth 6, south pier");
    set_long("\n"+
      "This is the south pier.\n"+
      "A large warehouse lies due south and the harbour is due north.\n"+
      "Sea birds are flying overhead, swooping down to get the goodies\n"+
      "left in the water by the fishermen. The pier continues east.\n"+
      "");


    add_item(({"water" }),"Pieces of fish and other leftovers from the fishermens'\n"+
      "boats are floating in the water. It makes it less inviting\n"+
      "to swim around in, unless you're a seagull.\n"+
      "");
    add_item(({"birds","bird","seagull","seagulls" }),"The seagulls are quite busy trying to get the best pieces of fish\n"+
      "and their shrieks are quite deafening.\n"+
      "");
    add_item(({"warehouse" }),"");
    add_item(({"pier" }),"");

    add_exit(TOWN_DIR + "pier5","west");
    add_exit(TOWN_DIR + "ware1","south");
    add_exit(TOWN_DIR + "pier7","east");

    add_prop(ROOM_I_INSIDE, 0);
    add_prop(ROOM_I_TYPE, ROOM_NORMAL);
    add_my_desc("There is a sign here marked 'Berth 6'\n");
}
