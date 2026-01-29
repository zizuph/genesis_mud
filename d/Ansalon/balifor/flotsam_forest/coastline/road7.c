#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/balifor/flotsam_forest/local.h"

inherit FOREST_OUT;

#include "/d/Krynn/common/herbsearch.h"

#define ONE_OF(x)     ((x)[random(sizeof(x))])
#define HERB_MASTER "/d/Krynn/common/herbs/herb_master"

string *herbs = HERB_MASTER->query_herbs( ({ "beach", }) );

void
reset_flotsam_room()
{
   return;
}

create_flotsam_room()
{
   set_short("On a cliffside road");
   set_long("@@long_descr");
   
   add_item(({"road","eroding dirt road","dirt road",
            "cliffside road"}),
      "You stand upon a wide dirt road that travels along " +
      "the edge of a cliff. It is slowly eroding away due " +
      "to lack of maintenance.\n");
   add_item(({"grassy top","top","bluffs","cliff",
            "cliffside","bloodsea coastline","coastline","coast",
            "bloodsea of istar","cliffs"}),
      "Grass topped cliffs that drop 100 metres to the sea " +
      "below makes up the coastline of the Bloodsea of Istar.\n");
   add_item(({"sea","roiling surging clouds","surging clouds",
            "clouds","rain","sooty veil","veil","storm"}),
      "Out to sea, black, surging clouds herald another " +
      "sudden storm common to these parts.\n");
   
   
   add_exit(CROOM + "road6","northwest",0);
   add_exit(CROOM + "road8","southeast",0);

    seteuid(getuid(TO));
    set_up_herbs( ({ ONE_OF(herbs), ONE_OF(herbs), ONE_OF(herbs),
       ONE_OF(herbs) }), ({"cliffs","grass","bluffs","coastline",
        "road","coast"}), 2);

   reset_flotsam_room();
}

string
long_descr()
{
   return "You stand upon an eroding dirt road that closely " +
   "follows the grassy top of the bluffs that overlook " +
   "the Bloodsea coastline. Out to sea, roiling, surging " +
   "clouds, with rain trailing like some sooty veil, " +
   "herald another of the sudden " + season_descr2() +
   " storms common to this part of the coast.\n";
}
