/*
 * Sets flag in players from calling dragons into ME.
 * Disabled by request of Admin, June 2001
#include "/d/Gondor/common/lib/gs_include.c"
*/
#include "/d/Shire/common/defs.h"
#include <macros.h>
#include <stdproperties.h>
#include <ss_types.h>

#undef SHIP_DIR
#include "/d/Genesis/gsl_ships/ships.h"

inherit "/d/Shire/std/room";
inherit LIBPIER;

void
create_shire_room()
{
    add_prop(ROOM_S_MAP_FILE, "grey_havens.txt");

    set_short("A pier in the Gulf of Lhun");
    set_long("This pier stretches out south of the city of Mithlond, or "+
      "Grey Havens in the common tongue. To the north, you can see high "+
      "white city walls, and a towering lighthouse is in view. Here, however "+
      "is just a pier leading to distant lands. You can hear the cry of seagulls "+
      "and you know that the elves who sail west from here never return. "+
      "A new sign is posted up where the pier meets the road connecting it "+
      "with the great Eastroad.\n");

    add_item(({"seagull","seagulls","cries of seagulls"}),"The cries of "+
      "the seagulls are unrelenting, seeming to take on a "+
      "hauntingly eerie tone. You wish you too could sail over the seas to "+
      "Eressea.\n");
    add_item(({"city","walls","city walls","lighthouse"}),"The city, "+
      "while not so far away is still somewhat blurry as you try to pick "+
      "out features. You wonder if this is an elven magic or if the city "+
      "is just a good distance from here. The lighthouse is the nearest "+
      "feature, and you cannot make out its top.\n");

    add_item(({"pier","road","dock","east road","eastroad"}),"Here you "+
      "are standing on a pier in the Gulf of Lhun, waiting for a ship, "+
      "apparently. The path to the Eastroad is to your east, and the pier "+
      "seems firm beneath you.\n");
    add_item(({"sign"}), "The sign reads: Ship to Gont for 20 coppers.\n");

    add_exit("/d/Shire/common/greyhaven/path1","east",0,1);
    add_prop(ROOM_I_NO_CLEANUP,1);

    add_pier_entry(MASTER_OB(this_object()), "Grey Havens", "Newbie Line to Sarn Ford");
    initialize_pier();   
}

