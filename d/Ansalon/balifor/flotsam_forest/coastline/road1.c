#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/balifor/flotsam_forest/local.h"

#define FFF "/d/Ansalon/balifor/flotsam/room/street21"

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
   set_short("Outside the gates of Flotsam");
   set_long("@@long_descr");
   
   add_item(({"gates","gate","great iron gates"}),
      "To the west stands the great iron gates of the " +
      "town of Flotsam. At present they are open.\n");
   add_item(({"town of flotsam","flotsam","town",
            "port town","wretched port town"}),
      "To your west is the wretched port town of Flotsam. " +
      "Rumours have it that it is presently occupied by " +
      "the Blue Dragonarmy, for what reason you do not know.\n");
   add_item(({"grassy top","bluffs","coastline",
            "bloodsea coastline","coast"}),
      "Grass topped cliffs that drop 100 metres to the sea " +
      "below makes up the coastline of the Bloodsea of Istar.\n");
   add_item(({"sea","roiling surging clouds",
            "surging clouds","clouds","rain","sooty veil",
            "veil","storm"}),
      "Out to sea, black, surging clouds herald another " +
      "sudden storm common to these parts.\n");
   add_item(({"road","dirt road","eroding dirt road"}),
      "You stand upon a wide dirt road that is slowly " +
      "eroding away due to lack of maintenance.\n");
   
   
   add_exit(FFF,"west","@@enter_gate");
   add_exit(CROOM + "road2","east",0);

    seteuid(getuid(TO));
    set_up_herbs( ({ ONE_OF(herbs), ONE_OF(herbs), ONE_OF(herbs),
       ONE_OF(herbs) }), ({"cliffs","grass","bluffs","coastline",
        "road","coast"}), 2);
   
   reset_flotsam_room();
}

string
long_descr()
{
   return "You stand upon an eroding dirt road before " +
   "the gates to the wretched port town of Flotsam. " +
   "The road leads away from the town to the east, " +
   "closely following the grassy top of the bluffs that " +
   "overlook the Bloodsea coastline. Out to sea, " +
   "roiling, surging clouds, with rain trailing below " +
   "like some sooty veil, herald another of the sudden " +
   season_descr2() + " storms common to this part " +
   "of the coast. " +
   "\n";
}

int
enter_gate()
{
   write("You pass through the open gates and into the town of Flotsam.\n");
   return 0;
}
