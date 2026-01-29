#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/balifor/flotsam_forest/local.h"
#include <macros.h>
#include <ss_types.h>


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
   set_short("Cliffs end");
   set_long("@@long_descr");
   
   add_item(({"rocky edge of a cliff","rocky edge","cliff"}),
      "Here the jagged-walled cliff falls down to the crashing " +
      "waters of the Bloodbay. A natural ridge runs along the " +
      "side of it about twenty meters down.\n");
   add_item(({"ridge","natural ridge"}),"A ridge runs along " +
      "the side of the cliff like a natural path.\n");
   add_item(({"crashing waters of the bloodbay","bloodbay",
            "crashing waters","spray"}),
      "The waters of the Bloodbay pound violently against the " +
      "face of the cliff below you, sending spray far up into " +
      "the air.\n");
   add_item(({"forest","west","wild hedges","hedges",
            "forboding forest"}),
      "Wild hedges block your way into the forboding forest " +
      "to the west.\n");
   
   add_cmd_item(({"down","down to ridge","cliff","to ridge"}),
      "climb","@@climb_down");
   
   add_exit(CROOM + "road15","northwest",0);
   
    seteuid(getuid(TO));
    set_up_herbs( ({ ONE_OF(herbs), ONE_OF(herbs), ONE_OF(herbs),
       ONE_OF(herbs) }), ({"cliffs","grass","bluffs","coastline",
        "road","coast"}), 2);

   reset_flotsam_room();
}

string
long_descr()
{
   return "You stand at the rocky edge of a cliff that " +
   "falls a long distance to the crashing waters of the " +
   "Bloodbay below. The forest blocks your way to the west, " +
   "with wild hedges stopping you from entering it.\n";
}

string
climb_down()
{
   if(TP->query_skill(SS_CLIMB) < 30)
      {
      write("You try and find a good place to begin your " +
         "descent, but cannot find a place where you think you " +
         "can climb down from. Guess your not as good a climber " +
         "as you thought you were...\n");
      say(QCTNAME(TP) + " looks for a place to climb down the " +
         "cliff, but ends up looking quite confused.\n");
      return "";
   }
   write("You climb down the cliff to the narrow ridge.\n");
   TP->move_living("down the cliff's edge",
      CROOM + "ridge1.c",1,0);
   return "";
}
