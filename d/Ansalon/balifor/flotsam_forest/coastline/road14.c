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
   set_short("On top of a grassy topped cliff");
   set_long("@@long_descr");
   
   add_item(({"edge","edge of grassy topped cliff","cliff",
            "grassy topped cliff","grassy cliff","cliffs edge"}),
      "Looking down from the edge of the grassy topped cliff " +
      "you stand upon, the waters of the Bloodbay crash against " +
      "the jagged side of the cliffs face, sending spray high " +
      "up into the air.\n");
   add_item(({"crashing waters of the bloodbay","crashing waters",
            "Bloodbay","bloodbay","spray"}),
      "The waters of the Bloodbay pound viciously against the " +
      "face of the cliff below you, sending spray far up into " +
      "the air.\n");
   add_item(({"forest","shadows","shadows of the forest",
            "forboding forest"}),
      "To your south stands a forboding forest as ancient as the " +
      "sea it overlooks.\n");
   add_item(({"green grass","grass"}),"Between the forest and " +
      "the cliff's edge is a lush carpet of green grass.\n");
   
   
   add_exit(CROOM + "road8","west",0);
   add_exit(CROOM + "road16","east",0);
   add_exit(CROOM + "road15","southeast",0);

    seteuid(getuid(TO));
    set_up_herbs( ({ ONE_OF(herbs), ONE_OF(herbs), ONE_OF(herbs),
       ONE_OF(herbs) }), ({"cliffs","grass","bluffs","coastline",
        "road","coast"}), 2);
   
   reset_flotsam_room();
}

string
long_descr()
{
   return "You stand upon the edge of a grassy topped cliff " +
   "that falls a great distance to the crashing waters of " +
   "the Bloodbay. The forest to the south seems hesitant " +
   "to encroach the cliffs edge, so a comfortable distance " +
   "of green grass lies between you and the shadows of the " +
   "forest.\n";
}
